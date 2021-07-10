#include "dsp/Core.h"
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <cstdio>
#include <cstring>
#include <cassert>

static const char pluginURI[] = "http://jpcima.sdf1.org/plugins/bass21";

//==========================================================================
enum PluginPort {
    kInput,
    kOutput,
    kEnabled,
    kPregain,
    kLevel,
    kBlend,
    kPresence,
    kDrive,
    kBass,
    kTreble,
    kQuality,
    NumberOfPorts,
};

struct Bass21Plugin {
    double sampleRate_ = 0;

    //==========================================================================
    void *portData_[NumberOfPorts] {};

    //==========================================================================
    struct {
        // none needed
    } urid_;

    //==========================================================================
    Bass21 dsp_;
};

static LV2_Handle instantiate(const LV2_Descriptor *descriptor, double sampleRate, const char *bundlePath, const LV2_Feature *const *features)
{
    (void)bundlePath;

    Bass21Plugin *self = new Bass21Plugin;

    self->sampleRate_ = sampleRate;

    Bass21 &dsp = self->dsp_;
    dsp.init();
    dsp.setSampleRate(sampleRate);

    return self;
}

static void connectPort(LV2_Handle instance, uint32_t port, void *dataLocation)
{
    Bass21Plugin *self = (Bass21Plugin *)instance;

    if (port >= NumberOfPorts) {
        assert(false);
        return;
    }

    self->portData_[port] = dataLocation;
}

static void activate(LV2_Handle instance)
{
    Bass21Plugin *self = (Bass21Plugin *)instance;
    Bass21 &dsp = self->dsp_;

    dsp.clear();
}

static void run(LV2_Handle instance, uint32_t sampleCount)
{
    Bass21Plugin *self = (Bass21Plugin *)instance;
    Bass21 &dsp = self->dsp_;

    bool bypass = !*(float *)self->portData_[kEnabled];
    float pregain = *(float *)self->portData_[kPregain];
    float level = *(float *)self->portData_[kLevel];
    float blend = *(float *)self->portData_[kBlend];
    float presence = *(float *)self->portData_[kPresence];
    float drive = *(float *)self->portData_[kDrive];
    float bass = *(float *)self->portData_[kBass];
    float treble = *(float *)self->portData_[kTreble];
    int quality = (int)*(float *)self->portData_[kQuality];

    dsp.setBypass(bypass);
    dsp.setPregain(pregain);
    dsp.setLevel(level);
    dsp.setBlend(blend);
    dsp.setPresence(presence);
    dsp.setDrive(drive);
    dsp.setBass(bass);
    dsp.setTreble(treble);
    dsp.setQuality(quality);

    const float *input = (const float *)self->portData_[kInput];
    float *output = (float *)self->portData_[kOutput];
    dsp.run(input, output, sampleCount);
}

static void deactivate(LV2_Handle instance)
{
    Bass21Plugin *self = (Bass21Plugin *)instance;
    (void)self;
}

static void cleanup(LV2_Handle instance)
{
    Bass21Plugin *self = (Bass21Plugin *)instance;
    delete self;
}

static const void *extensionData(const char *uri)
{
    (void)uri;
    return nullptr;
}

static const LV2_Descriptor descriptor = {
    pluginURI,
    &instantiate,
    &connectPort,
    &activate,
    &run,
    &deactivate,
    &cleanup,
    &extensionData,
};

LV2_SYMBOL_EXPORT const LV2_Descriptor *lv2_descriptor(uint32_t index)
{
    return (index == 0) ? &descriptor : nullptr;
}
