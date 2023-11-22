/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "DXComponents.h"
#include "AlgoDisplay.h"
#include "InferEngine.h"

class DexedAudioProcessorEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainEditor  : public Component,
                      public juce::Slider::Listener,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    MainEditor ();
    ~MainEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void bind(DexedAudioProcessorEditor *processor);
    ProgramSelector *programs;
    //std::unique_ptr<Component> midiMonitor;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    DexedAudioProcessorEditor *editor;
    DexedAudioProcessor *processor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> searchPosition;
    std::unique_ptr<juce::TextButton> yesButton;
    std::unique_ptr<juce::TextButton> noButton;
    std::unique_ptr<juce::TextButton> loadButton;
    std::unique_ptr<juce::TextButton> saveButton;
    // std::unique_ptr<juce::TextButton> randomButton;
    std::unique_ptr<juce::TextButton> panicButton;
    std::unique_ptr<InferEngine> inferEngine;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

