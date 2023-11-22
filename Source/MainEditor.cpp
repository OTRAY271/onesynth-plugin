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

//[Headers] You can add your own extra header files here...
#include "PluginEditor.h"
#include "DXLookNFeel.h"
//[/Headers]

#include "MainEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

/**
 * Ugly but useful midi monitor to know if you are really sending/receiving something from the DX7
 * If the midi is not configured this component wont show up
 *
class MidiMonitor : public Component {
    SysexComm *midi;
    Image light;

public:
    MidiMonitor(SysexComm *sysexComm) {
        midi = sysexComm;
        light = DXLookNFeel::getLookAndFeel()->imageLight;
    }

    void paint(Graphics &g) {
        if ( ! (midi->isInputActive() || midi->isOutputActive() ) )
            return;
        g.setColour(Colours::white);

        if ( midi->isInputActive() ) {
            g.drawSingleLineText("DX7 IN", 17,14);
            g.drawImage(light, 0, 3, 14, 14, 0, midi->inActivity ? 14 : 0, 14, 14);
            midi->inActivity = false;
        }

        if ( midi->isOutputActive() ) {
            g.drawSingleLineText("DX7 OUT", 17, 28);
            g.drawImage(light, 0, 17, 14, 14, 0, midi->outActivity ? 14 : 0, 14, 14);
            midi->outActivity = false;
        }
    }
};*/
//[/MiscUserDefs]

//==============================================================================
MainEditor::MainEditor ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    searchPosition.reset (new juce::Slider ("searchPosition"));
    addAndMakeVisible (searchPosition.get());
    searchPosition->setRange (-1, 1, 0);
    searchPosition->setSliderStyle (juce::Slider::LinearHorizontal);
    searchPosition->setTextBoxStyle (juce::Slider::NoTextBox, true, 80, 20);
    searchPosition->setColour (juce::Slider::ColourIds::backgroundColourId, findColour(juce::Slider::ColourIds::trackColourId));
    searchPosition->addListener (this);

    searchPosition->setBounds (12, 46, 286, 34);

    yesButton.reset (new juce::TextButton ("YES"));
    addAndMakeVisible (yesButton.get());
    yesButton->setButtonText ("YES");
    yesButton->addListener (this);

    yesButton->setBounds (159, 90, 50, 30);

    noButton.reset (new juce::TextButton ("NO"));
    addAndMakeVisible (noButton.get());
    noButton->setButtonText ("NO");
    noButton->addListener (this);

    noButton->setBounds (101, 90, 50, 30);

    loadButton.reset (new juce::TextButton ("LOAD"));
    addAndMakeVisible (loadButton.get());
    loadButton->setButtonText ("LOAD");
    loadButton->addListener (this);

    loadButton->setBounds (16, 12, 40, 20);

    saveButton.reset (new juce::TextButton ("SAVE"));
    addAndMakeVisible (saveButton.get());
    saveButton->setButtonText ("SAVE");
    saveButton->addListener (this);

    saveButton->setBounds (62, 12, 40, 20);

    // randomButton.reset (new juce::TextButton ("RAND"));
    // addAndMakeVisible (randomButton.get());
    // randomButton->setButtonText ("RAND");
    // randomButton->addListener (this);

    // randomButton->setBounds (203, 12, 40, 20);

    panicButton.reset (new juce::TextButton ("PANIC"));
    addAndMakeVisible (panicButton.get());
    panicButton->setButtonText ("PANIC");
    panicButton->addListener (this);

    panicButton->setBounds (249, 12, 45, 20);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (864, 144);

    //[Constructor] You can add your own custom stuff here..
    SharedResourcePointer<DXLookNFeel> lookAndFeel;
    //[/Constructor]

    
}

MainEditor::~MainEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    searchPosition = nullptr;
    yesButton = nullptr;
    noButton = nullptr;
    loadButton = nullptr;
    inferEngine = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]
    if (sliderThatWasMoved == searchPosition.get())
    {
        //[UserSliderCode_tune] -- add your slider handling code here..
        //[/UserSliderCode_tune]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == yesButton.get())
    {
        //[UserButtonCode_oscSync] -- add your button handler code here..
        inferEngine.get()->moveForward();
        //[/UserButtonCode_oscSync]
    } else if (buttonThatWasClicked == noButton.get())
    {
        inferEngine.get()->turnAround();
    } else if (buttonThatWasClicked == loadButton.get())
    {
        inferEngine.get()->load();
    } else if (buttonThatWasClicked == saveButton.get())
    {
        inferEngine.get()->save();
    // } else if (buttonThatWasClicked == randomButton.get())
    // {
    //     inferEngine.get()->random();
    } else if (buttonThatWasClicked == panicButton.get())
    {
        this->processor->panic();
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainEditor::bind(DexedAudioProcessorEditor *edit) {
    processor = edit->processor;
    processor->searchPosition->bind(searchPosition.get());

    editor = edit;

    inferEngine.reset(new InferEngine(processor));
    inferEngine.get()->startEngine();

    //midiMonitor = new MidiMonitor(&(processor->sysexComm));
    //addAndMakeVisible(midiMonitor);
    //midiMonitor->setBounds(155, 21, 80, 45);

    repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainEditor" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="864" initialHeight="144">
  <BACKGROUND backgroundColour="ffffff"/>
  <SLIDER name="lfoSpeed" id="b10eaf327ab3bff5" memberName="lfoSpeed" virtualName=""
          explicitFocusOrder="0" pos="564 50 34 34" min="0.0" max="99.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="lfoAmDepth" id="3e95a6206fa4a891" memberName="lfoAmDepth"
          virtualName="" explicitFocusOrder="0" pos="686 50 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="lfoPitchDepth" id="6ead769ca786c813" memberName="lfoPitchDepth"
          virtualName="" explicitFocusOrder="0" pos="646 50 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="lfoDelay" id="1fce68dc81619ef5" memberName="lfoDelay" virtualName=""
          explicitFocusOrder="0" pos="603 50 34 34" min="0.0" max="99.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="cutoff" id="40531f16bb0bd225" memberName="cutoff" virtualName=""
          explicitFocusOrder="0" pos="234 9 34 34" min="0.0" max="1.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="reso" id="c8c13464e81a8d83" memberName="reso" virtualName=""
          explicitFocusOrder="0" pos="278 9 34 34" min="0.0" max="1.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="pitchRate2" id="73f386b3c91d3de4" memberName="pitchRate2"
          virtualName="" explicitFocusOrder="0" pos="767 96 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchRate3" id="187c25b24413fccf" memberName="pitchRate3"
          virtualName="" explicitFocusOrder="0" pos="795 96 35 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchRate4" id="1aeb2a8fbbcbeaab" memberName="pitchRate4"
          virtualName="" explicitFocusOrder="0" pos="823 96 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchRate1" id="419d613b3fb9604e" memberName="pitchRate1"
          virtualName="" explicitFocusOrder="0" pos="739 96 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchLevel2" id="3a355ad2221887d9" memberName="pitchLevel2"
          virtualName="" explicitFocusOrder="0" pos="767 57 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchLevel3" id="5c5d782e8a7f3ad7" memberName="pitchLevel3"
          virtualName="" explicitFocusOrder="0" pos="795 56 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchLevel4" id="eb900b141fbad8ff" memberName="pitchLevel4"
          virtualName="" explicitFocusOrder="0" pos="823 56 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="pitchLevel1" id="344cbe26ec9fa128" memberName="pitchLevel1"
          virtualName="" explicitFocusOrder="0" pos="739 57 34 34" min="0.0"
          max="99.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="transpose" id="7d1266b1c1534947" memberName="transpose"
          virtualName="" explicitFocusOrder="0" pos="202 60 34 34" min="0.0"
          max="48.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="oscSync" id="8f3fe641537cd00" memberName="oscSync" virtualName=""
                explicitFocusOrder="0" pos="650 96 48 26" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="pitchModSens" id="904f73df85a9f886" memberName="pitchModSens"
          virtualName="" explicitFocusOrder="0" pos="666 5 34 34" min="0.0"
          max="7.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="lfoSync" id="ff92bb0a5a4f7187" memberName="lfoSync" virtualName=""
                explicitFocusOrder="0" pos="565 96 48 26" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <GENERICCOMPONENT name="pitchEnvDisplay" id="9ddaae8ef924a038" memberName="pitchEnvDisplay"
                    virtualName="" explicitFocusOrder="0" pos="751 10 93 30" class="PitchEnvDisplay"
                    params=""/>
  <GENERICCOMPONENT name="algoDisplay" id="b26fb9e3b5f0bc37" memberName="algoDisplay"
                    virtualName="" explicitFocusOrder="0" pos="335 30 152 91" class="AlgoDisplay"
                    params=""/>
  <SLIDER name="feedback" id="4fac1940c29ab8c" memberName="feedback" virtualName=""
          explicitFocusOrder="0" pos="501 81 34 34" min="0.0" max="7.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="algo" id="8a226ddf9bbff752" memberName="algo" virtualName=""
          explicitFocusOrder="0" pos="501 22 34 34" min="1.0" max="32.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <GENERICCOMPONENT name="lcdDisplay" id="30c7bb8f114cbbe3" memberName="lcdDisplay"
                    virtualName="" explicitFocusOrder="0" pos="6 87 140 13" class="LcdDisplay"
                    params=""/>
  <SLIDER name="output" id="7697fdd54fd1593e" memberName="output" virtualName=""
          explicitFocusOrder="0" pos="157 60 34 34" min="0.0" max="1.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <GENERICCOMPONENT name="vuOutput" id="dac75af912267f51" memberName="vuOutput" virtualName=""
                    explicitFocusOrder="0" pos="6 103 140 8" class="VuMeter" params=""/>
  <TEXTBUTTON name="initButton" id="92b278163c42e21d" memberName="initButton"
              virtualName="" explicitFocusOrder="0" pos="100 111 50 30" buttonText="INIT"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="parmButton" id="d5cd6260b34be817" memberName="parmButton"
              virtualName="" explicitFocusOrder="0" pos="52 111 50 30" buttonText="PARM"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="cartButton" id="465a101c3a0e744" memberName="cartButton"
              virtualName="" explicitFocusOrder="0" pos="3 111 50 30" buttonText="CART"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="storeButton" id="a94bec26832eb58b" memberName="storeButton"
              virtualName="" explicitFocusOrder="0" pos="270 109 50 30" buttonText="STORE"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="monoMode" id="e683d8cbe286367b" memberName="monoMode" virtualName=""
                explicitFocusOrder="0" pos="249 65 48 26" buttonText="" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <GENERICCOMPONENT name="lfoType" id="62f61dda9f76c8f" memberName="lfoType" virtualName=""
                    explicitFocusOrder="0" pos="583 8 36 26" class="ComboBoxImage"
                    params=""/>
  <GENERICCOMPONENT name="programSelector" id="990bbcccae72dbe6" memberName="programSelector"
                    virtualName="" explicitFocusOrder="0" pos="153 115 112 18" class="ProgramSelector"
                    params=""/>
  <IMAGEBUTTON name="aboutButton" id="d195a60b29440aa1" memberName="aboutButton"
               virtualName="" explicitFocusOrder="0" pos="8 11 135 46" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="0"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <SLIDER name="tune" id="d22c34aa3363a28a" memberName="tune" virtualName=""
          explicitFocusOrder="0" pos="190 9 34 34" min="0.0" max="1.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

