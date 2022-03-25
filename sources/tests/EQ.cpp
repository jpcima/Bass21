#include "nonstd/scope.hpp"
#include <getopt.h>
#include <memory>
#include <cstdlib>

#if defined(USE_FAUST_DSP)
#include "dsp/Bass21EQFaust.hxx"
#else
#include "dsp/cpp/Filter.h"
#include "dsp/cpp/Bass21Filters.h"
#endif

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

int main(int argc, char *argv[])
{
    const char *in_path = nullptr;
    const char *out_path = nullptr;
    float bass = -1;
    float treble = -1;
    bool help = false;

    ///
    auto parse_float = [](const char *text, double fallback_value) -> double {
        errno = 0;
        char *endp = nullptr;
        double value = std::strtod(text, &endp);
        return (errno == 0 && *endp == '\0') ? value : fallback_value;
    };

    ///
    if (argc < 2) {
        help = true;
    }
    else {
        for (int c; (c = getopt(argc, argv, "i:o:b:t:h")) != -1; ) {
            switch (c) {
            case 'b':
                bass = parse_float(optarg, -1);
                break;
            case 't':
                treble = parse_float(optarg, -1);
                break;
            case 'i':
                in_path = optarg;
                break;
            case 'o':
                out_path = optarg;
                break;
            case 'h':
                help = true;
                break;
            default:
                return 1;
            }
        }
    }

    if (help) {
        fprintf(stderr, "Usage: -i <input.wav> -o <output.wav> -b <bass> -t <treble>\n");
        return 0;
    }

    ///
    if (argc != optind) {
        fprintf(stderr, "Positional arguments are not accepted.\n");
        return 1;
    }
    if (!in_path) {
        fprintf(stderr, "No input path given (option -i).\n");
        return 1;
    }
    if (!out_path) {
        fprintf(stderr, "No output path given (option -o).\n");
        return 1;
    }
    if (bass < 0 || bass > 1) {
        fprintf(stderr, "Invalid option for bass (option -b).\n");
        return 1;
    }
    if (treble < 0 || treble > 1) {
        fprintf(stderr, "Invalid option for treble (option -t).\n");
        return 1;
    }

    ///
    drwav wr;
    if (!drwav_init_file(&wr, in_path, nullptr)) {
        fprintf(stderr, "Cannot open sound file for reading.\n");
        return 1;
    }
    auto wr_cleanup = nonstd::make_scope_exit([&wr]() { drwav_uninit(&wr); });

    drwav_data_format ww_fmt{};
    ww_fmt.container = drwav_container_riff;
    ww_fmt.format = DR_WAVE_FORMAT_PCM;
    ww_fmt.channels = wr.channels;
    ww_fmt.sampleRate = wr.sampleRate;
    ww_fmt.bitsPerSample = 16;
    drwav ww;
    if (!drwav_init_file_write(&ww, out_path, &ww_fmt, nullptr)) {
        fprintf(stderr, "Cannot open sound file for writing.\n");
        return 1;
    }
    auto ww_cleanup = nonstd::make_scope_exit([&ww]() { drwav_uninit(&ww); });

    size_t nchan = wr.channels;
    constexpr size_t max_nframes_at_once = 512;
    std::unique_ptr<float[]> interleaved{new float[nchan * max_nframes_at_once]};
    std::unique_ptr<drwav_int16[]> interleaved_s16{new drwav_int16[nchan * max_nframes_at_once]};
    std::unique_ptr<float[]> dsp_in{new float[max_nframes_at_once]};
    std::unique_ptr<float[]> dsp_out{new float[max_nframes_at_once]};

#if defined(USE_FAUST_DSP)
    std::unique_ptr<Bass21EQFaustDSP[]> dsp{new Bass21EQFaustDSP[nchan]};
    for (size_t i = 0; i < nchan; ++i) {
        dsp[i].init(wr.sampleRate);
        dsp[i].setBegin(true);
        dsp[i].setBass(bass);
        dsp[i].setTreble(treble);
    }
#else
    using Real = double;
    using DSP = IIR_TF2<Real, 6>;
    std::unique_ptr<DSP[]> dsp{new DSP[nchan]};
    {
        TF<Real, 6> tf = makeEQ(wr.sampleRate, bass, treble).to<Real>();
        for (size_t i = 0; i < nchan; ++i)
            dsp[i].setTransfer(tf);
    }
#endif

    size_t count;
    while ((count = (size_t)drwav_read_pcm_frames_f32(&wr, max_nframes_at_once, interleaved.get())) > 0) {
        for (size_t c = 0; c < nchan; ++c) {
            for (size_t i = 0; i < count; ++i)
                dsp_in[i] = interleaved[i * nchan + c];

#if defined(USE_FAUST_DSP)
            const float *const dsp_ins[] = { dsp_in.get() };
            float *const dsp_outs[] = { dsp_out.get() };
            dsp[c].compute((int)count, dsp_ins, dsp_outs);
            dsp[c].setBegin(false);
#else
            dsp[c].process(dsp_in.get(), dsp_out.get(), count);
#endif

            for (size_t i = 0; i < count; ++i)
                interleaved[i * nchan + c] = dsp_out[i];
        }

        drwav_f32_to_s16(interleaved_s16.get(), interleaved.get(), nchan * count);
        drwav_write_pcm_frames(&ww, count, interleaved_s16.get());
    }

    ///
    return 0;
}
