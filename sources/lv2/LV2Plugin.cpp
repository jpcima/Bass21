#include "dsp/Core.h"
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>

static const char pluginURI[] = "http://jpcima.sdf1.org/plugins/bass21";

//==========================================================================
enum PluginParameter {
    kEnabled,
    kPregain,
    kLevel,
    kBlend,
    kPresence,
    kDrive,
    kBass,
    kTreble,
    kQuality,
};

struct Bass21Plugin {
    double sampleRate_ = 0;
    LV2_URID_Map *map_ = nullptr;
    LV2_URID_Unmap *unmap_ = nullptr;
    std::unique_ptr<LV2_Atom_Forge> forge_;
    const std::map<LV2_URID, uint32_t> *mapURItoParameter_ = nullptr;

    //==========================================================================
    struct {
        LV2_URID patch_Set = 0;
        LV2_URID patch_property = 0;
        LV2_URID patch_value = 0;
    } urid_;

    //==========================================================================
    const LV2_Atom_Sequence *controlIn_ = nullptr;
    const LV2_Atom_Sequence *controlOut_ = nullptr;
    const float *audioIn_ = nullptr;
    float *audioOut_ = nullptr;

    //==========================================================================
    Bass21 dsp_;
};

static LV2_Handle instantiate(const LV2_Descriptor *descriptor, double sampleRate, const char *bundlePath, const LV2_Feature *const *features)
{
    (void)bundlePath;

    Bass21Plugin *self = new Bass21Plugin;

    self->sampleRate_ = sampleRate;

    LV2_URID_Map *map = nullptr;
    LV2_URID_Unmap *unmap = nullptr;

    while (const LV2_Feature *feature = *features++) {
        const char *uri = feature->URI;
        if (!std::strcmp(uri, LV2_URID_MAP_URI))
            self->map_ = map = (LV2_URID_Map *)feature->data;
        else if (!std::strcmp(uri, LV2_URID_UNMAP_URI))
            self->unmap_ = unmap = (LV2_URID_Unmap *)feature->data;
    }

    if (!map || !unmap) {
        assert(false);
        return nullptr;
    }

    LV2_Atom_Forge *forge = new LV2_Atom_Forge;
    self->forge_.reset(forge);
    lv2_atom_forge_init(forge, map);

    static const std::map<LV2_URID, uint32_t> mapURItoParameter {
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#enabled"), kEnabled},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#pregain"), kPregain},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#level"), kLevel},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#blend"), kBlend},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#presence"), kPresence},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#drive"), kDrive},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#bass"), kBass},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#treble"), kTreble},
        {map->map(map->handle, "http://jpcima.sdf1.org/plugins/bass21#quality"), kQuality},
    };
    self->mapURItoParameter_ = &mapURItoParameter;

    self->urid_.patch_Set = map->map(map->handle, LV2_PATCH__Set);
    self->urid_.patch_property = map->map(map->handle, LV2_PATCH__property);
    self->urid_.patch_value = map->map(map->handle, LV2_PATCH__value);

    Bass21 &dsp = self->dsp_;
    dsp.init();
    dsp.setSampleRate(sampleRate);

    return self;
}

static void connectPort(LV2_Handle instance, uint32_t port, void *dataLocation)
{
    Bass21Plugin *self = (Bass21Plugin *)instance;

    switch (port) {
    case 0:
        self->controlIn_ = (const LV2_Atom_Sequence *)dataLocation;
        break;
    case 1:
        self->controlOut_ = (const LV2_Atom_Sequence *)dataLocation;
        break;
    case 2:
        self->audioIn_ = (const float *)dataLocation;
        break;
    case 3:
        self->audioOut_ = (float *)dataLocation;
        break;
    }
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

    LV2_Atom_Forge *forge = self->forge_.get();
    lv2_atom_forge_set_buffer(forge, (uint8_t *)self->controlOut_, self->controlOut_->atom.size);

    LV2_Atom_Forge_Frame frame;
    if (!lv2_atom_forge_sequence_head(forge, &frame, 0))
        assert(false);

    LV2_ATOM_SEQUENCE_FOREACH(self->controlIn_, atomEvent) {
        LV2_URID type = atomEvent->body.type;
        if (type == forge->Object) {
            LV2_Atom_Object *object = (LV2_Atom_Object *)&atomEvent->body;
            LV2_URID otype = object->body.otype;

            if (otype == self->urid_.patch_Set) {
                const LV2_Atom *property = nullptr;
                const LV2_Atom *value = nullptr;
                uint32_t param = ~0u;
                lv2_atom_object_get(object, self->urid_.patch_property, &property, 0);
                if (property && property->type == forge->URID && property->size >= sizeof(LV2_URID)) {
                    LV2_URID ptype = *(const LV2_URID *)LV2_ATOM_BODY_CONST(property);
                    auto it = self->mapURItoParameter_->find(ptype);
                    if (it != self->mapURItoParameter_->end()) {
                        param = it->second;
                        lv2_atom_object_get(object, self->urid_.patch_value, &value, 0);
                    }
                }

                switch (param) {
                case kEnabled:
                    if (value && value->type == forge->Bool && value->size >= sizeof(int32_t))
                        dsp.setBypass(((const LV2_Atom_Bool *)value)->body == 0);
                    break;
                case kPregain:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setPregain(((const LV2_Atom_Float *)value)->body);
                    break;
                case kLevel:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setLevel(((const LV2_Atom_Float *)value)->body);
                    break;
                case kBlend:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setBlend(((const LV2_Atom_Float *)value)->body);
                    break;
                case kPresence:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setPresence(((const LV2_Atom_Float *)value)->body);
                    break;
                case kDrive:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setDrive(((const LV2_Atom_Float *)value)->body);
                    break;
                case kBass:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setBass(((const LV2_Atom_Float *)value)->body);
                    break;
                case kTreble:
                    if (value && value->type == forge->Float && value->size >= sizeof(float))
                        dsp.setTreble(((const LV2_Atom_Float *)value)->body);
                    break;
                case kQuality:
                    if (value && value->type == forge->Int && value->size >= sizeof(int32_t))
                        dsp.setQuality(((const LV2_Atom_Int *)value)->body);
                    break;
                }
            }
        }
    }

    dsp.run(self->audioIn_, self->audioOut_, sampleCount);

    lv2_atom_forge_pop(forge, &frame);
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
