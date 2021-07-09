// SPDX-License-Identifier: BSD-2-Clause
#include "Editor.h"
#include "Processor.h"
#include <list>

//==============================================================================
struct Editor::Impl {
    explicit Impl(Editor *editor) : editor_(editor) {}
    void setupComponents(juce::AudioProcessorValueTreeState &vts);

    //==========================================================================
    enum ColourIds {
        backgroundColourId = 0x0000,
    };

    //==============================================================================
    class LookAndFeel : public juce::LookAndFeel_V4 {
    public:
        LookAndFeel();

        struct Initializer {
            Initializer();
        };
    };

    //==========================================================================
    class BypassButton : public juce::ShapeButton {
    public:
        explicit BypassButton(const juce::String &name);

        enum ColourIds {
            activeColourId = 0x1000,
            activeHoveredColourId,
            inactiveColourId,
            inactiveHoveredColourId,
        };
    };

    //==========================================================================
    Editor *editor_ = nullptr;

    std::list<std::unique_ptr<juce::Label>> labels_;

    std::unique_ptr<juce::Button> buttonBypass_;
    std::unique_ptr<juce::Slider> sliderPregain_;
    std::unique_ptr<juce::Slider> sliderLevel_;
    std::unique_ptr<juce::Slider> sliderBlend_;
    std::unique_ptr<juce::Slider> sliderPresence_;
    std::unique_ptr<juce::Slider> sliderDrive_;
    std::unique_ptr<juce::Slider> sliderBass_;
    std::unique_ptr<juce::Slider> sliderTreble_;
    std::unique_ptr<juce::ComboBox> comboQuality_;

    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<ButtonAttachment> attachBypass_;
    std::unique_ptr<SliderAttachment> attachPregain_;
    std::unique_ptr<SliderAttachment> attachLevel_;
    std::unique_ptr<SliderAttachment> attachBlend_;
    std::unique_ptr<SliderAttachment> attachPresence_;
    std::unique_ptr<SliderAttachment> attachDrive_;
    std::unique_ptr<SliderAttachment> attachBass_;
    std::unique_ptr<SliderAttachment> attachTreble_;
    std::unique_ptr<ComboBoxAttachment> attachQuality_;
};

//==============================================================================
Editor::Editor(Processor &p)
    : AudioProcessorEditor(p),
      impl_(new Impl(this))
{
    Impl &impl = *impl_;

    static Impl::LookAndFeel::Initializer lookAndFeelInitializer;

    impl.setupComponents(p.getValueTreeState());
}

Editor::~Editor()
{
}

void Editor::paint(juce::Graphics &g)
{
    g.fillAll(findColour(Editor::Impl::backgroundColourId));
}

void Editor::Impl::setupComponents(juce::AudioProcessorValueTreeState &vts)
{
    Editor *editor = editor_;

    const int defaultWidth = 1000;
    const int defaultHeight = 200;
    editor->setSize(defaultWidth, defaultHeight);

    ///
    juce::Rectangle<int> row = editor->getBounds().expanded(-50, -50);

    auto addTitleUnder = [this, editor](const juce::String &title, juce::Rectangle<int> bounds)
    {
        juce::Label *label = new juce::Label(juce::String(), title);
        labels_.emplace_back(label);
        label->setJustificationType(juce::Justification::horizontallyCentred);
        label->setBounds(bounds);
        editor->addAndMakeVisible(label);
    };
    auto addOnOffButton = [editor, &vts, &addTitleUnder](
        const juce::String &paramID, const juce::String &title, juce::Rectangle<int> bounds,
        std::unique_ptr<juce::Button> &outComponentPtr, std::unique_ptr<ButtonAttachment> &outAttachPtr)
    {
        juce::Button *button = new BypassButton(juce::String());
        outComponentPtr.reset(button);
        outAttachPtr = std::make_unique<ButtonAttachment>(vts, paramID, *button);
        addTitleUnder(title, bounds.removeFromBottom(20));
        button->setBounds(bounds.withSizeKeepingCentre(bounds.getWidth() * 2 / 3, bounds.getHeight() * 2 / 3));
        editor->addAndMakeVisible(button);
    };
    auto addKnob = [editor, &vts, &addTitleUnder](
        const juce::String &paramID, const juce::String &title, juce::Rectangle<int> bounds,
        std::unique_ptr<juce::Slider> &outComponentPtr, std::unique_ptr<SliderAttachment> &outAttachPtr)
    {
        juce::Slider *slider = new juce::Slider(juce::Slider::Rotary, juce::Slider::NoTextBox);
        outComponentPtr.reset(slider);
        outAttachPtr = std::make_unique<SliderAttachment>(vts, paramID, *slider);
        addTitleUnder(title, bounds.removeFromBottom(20));
        slider->setBounds(bounds);
        editor->addAndMakeVisible(slider);
    };
    auto addChoice = [editor, &vts, &addTitleUnder](
        const juce::String &paramID, const juce::String &title, juce::Rectangle<int> bounds,
        std::unique_ptr<juce::ComboBox> &outComponentPtr, std::unique_ptr<ComboBoxAttachment> &outAttachPtr)
    {
        juce::ComboBox *combo = new juce::ComboBox;
        outComponentPtr.reset(combo);

        juce::RangedAudioParameter *param = vts.getParameter("quality");
        jassert(dynamic_cast<juce::AudioParameterChoice *>(param));
        const juce::StringArray &choices = static_cast<juce::AudioParameterChoice *>(param)->choices;
        for (int i = 0, n = choices.size(); i < n; ++i)
            combo->addItem(choices[i], i + 1);

        outAttachPtr = std::make_unique<ComboBoxAttachment>(vts, paramID, *combo);
        addTitleUnder(title, bounds.removeFromBottom(20));
        combo->setBounds(bounds.withSizeKeepingCentre(bounds.getWidth(), 30.0));
        editor->addAndMakeVisible(combo);
    };

    addOnOffButton("bypass", "Enable", row.removeFromLeft(100), buttonBypass_, attachBypass_);
    addKnob("pregain", "Pregain", row.removeFromLeft(100), sliderPregain_, attachPregain_);
    addKnob("level", "Level", row.removeFromLeft(100), sliderLevel_, attachLevel_);
    addKnob("blend", "Blend", row.removeFromLeft(100), sliderBlend_, attachBlend_);
    addKnob("presence", "Presence", row.removeFromLeft(100), sliderPresence_, attachPresence_);
    addKnob("drive", "Drive", row.removeFromLeft(100), sliderDrive_, attachDrive_);
    addKnob("bass", "Bass", row.removeFromLeft(100), sliderBass_, attachBass_);
    addKnob("treble", "Treble", row.removeFromLeft(100), sliderTreble_, attachTreble_);
    addChoice("quality", "Quality", row.removeFromLeft(100), comboQuality_, attachQuality_);
}

//==============================================================================
Editor::Impl::LookAndFeel::LookAndFeel()
{
    setColour(Editor::Impl::ColourIds::backgroundColourId, juce::Colour(0xff3f3f3f));

    const ColourScheme &cs = getCurrentColourScheme();

    setColour(Editor::Impl::BypassButton::ColourIds::activeColourId, cs.getUIColour(ColourScheme::UIColour::defaultFill));
    setColour(Editor::Impl::BypassButton::ColourIds::activeHoveredColourId, cs.getUIColour(ColourScheme::UIColour::defaultFill).brighter());
    setColour(Editor::Impl::BypassButton::ColourIds::inactiveColourId, cs.getUIColour(ColourScheme::UIColour::widgetBackground));
    setColour(Editor::Impl::BypassButton::ColourIds::inactiveHoveredColourId, cs.getUIColour(ColourScheme::UIColour::widgetBackground).brighter());
}

Editor::Impl::LookAndFeel::Initializer::Initializer()
{
    static LookAndFeel lookAndFeel;
    juce::LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
}

//==============================================================================
Editor::Impl::BypassButton::BypassButton(const juce::String &name)
    : ShapeButton(name, juce::Colour(), juce::Colour(), juce::Colour())
{
    setClickingTogglesState(true);

    juce::Path shape = juce::Drawable::parseSVGPath("m310.06 655.31c-122.24 0-221.47-99.22-221.47-221.47 0.004-60.88 24.72-115.94 64.53-155.96l0.19 0.18c8.05-11.11 21.05-18.4 35.81-18.4 24.45 0 44.32 19.83 44.32 44.28 0 14.99-7.5 28.2-18.91 36.22l0.16 0.15c-23.93 24.1-38.91 57-38.91 93.53 0 73.7 60.11 133.54 134.16 133.54 74.04 0 134.12-59.84 134.12-133.54 0-33.34-12.54-63.58-32.9-86.93-12.12-7.91-20.19-21.53-20.19-37.07 0-24.45 19.86-44.31 44.31-44.31 11.95 0 22.75 4.83 30.72 12.53l0.62-0.62c40.06 40.05 64.88 95.32 64.88 156.4 0 122.25-99.19 221.47-221.44 221.47zm-0.03-219.93c-24.54 0-44.28-20.11-44.28-45.1v-178.66c0-24.99 19.74-45.09 44.28-45.09s44.31 20.1 44.31 45.09v178.66c0 24.99-19.77 45.1-44.31 45.1z");
    setShape(shape, true, true, false);

    setColours(
        findColour(ColourIds::activeColourId),
        findColour(ColourIds::activeHoveredColourId),
        findColour(ColourIds::inactiveColourId));
    setOnColours(
        findColour(ColourIds::inactiveColourId),
        findColour(ColourIds::inactiveHoveredColourId),
        findColour(ColourIds::activeColourId));
    shouldUseOnColours(true);
}
