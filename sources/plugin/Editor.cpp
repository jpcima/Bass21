// SPDX-License-Identifier: BSD-2-Clause
#include "Editor.h"
#include "Processor.h"
#include <list>

//==============================================================================
struct Editor::Impl {
    explicit Impl(Editor *editor) : editor_(editor) {}
    void setupComponents(juce::AudioProcessorValueTreeState &vts);

    //==========================================================================
    Editor *editor_ = nullptr;

    std::list<std::unique_ptr<juce::Label>> labels_;

    std::unique_ptr<juce::Slider> sliderLevel_;
    std::unique_ptr<juce::Slider> sliderBlend_;
    std::unique_ptr<juce::Slider> sliderPresence_;
    std::unique_ptr<juce::Slider> sliderDrive_;
    std::unique_ptr<juce::Slider> sliderBass_;
    std::unique_ptr<juce::Slider> sliderTreble_;
    std::unique_ptr<juce::ComboBox> comboQuality_;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
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

    impl.setupComponents(p.getValueTreeState());
}

Editor::~Editor()
{
}

void Editor::Impl::setupComponents(juce::AudioProcessorValueTreeState &vts)
{
    Editor *editor = editor_;

    const int defaultWidth = 800;
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

    addKnob("level", "Level", row.removeFromLeft(100), sliderLevel_, attachLevel_);
    addKnob("blend", "Blend", row.removeFromLeft(100), sliderBlend_, attachBlend_);
    addKnob("presence", "Presence", row.removeFromLeft(100), sliderPresence_, attachPresence_);
    addKnob("drive", "Drive", row.removeFromLeft(100), sliderDrive_, attachDrive_);
    addKnob("bass", "Bass", row.removeFromLeft(100), sliderBass_, attachBass_);
    addKnob("treble", "Treble", row.removeFromLeft(100), sliderTreble_, attachTreble_);
    addChoice("quality", "Quality", row.removeFromLeft(100), comboQuality_, attachQuality_);
}
