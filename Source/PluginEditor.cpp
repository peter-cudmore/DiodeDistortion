/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DiodeDistortionAudioProcessorEditor::DiodeDistortionAudioProcessorEditor (DiodeDistortionAudioProcessor& ownerProc)
    : AudioProcessorEditor(ownerProc), processor(ownerProc)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (GainSldr = new Slider ("Gain Slider"));
    GainSldr->setRange (0, 10, 0);
    GainSldr->setSliderStyle (Slider::Rotary);
    GainSldr->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    GainSldr->setColour (Slider::rotarySliderFillColourId, Colours::black);
    GainSldr->addListener (this);

    addAndMakeVisible (LevelSldr = new Slider ("Level Slider"));
    LevelSldr->setRange (0, 10, 0);
    LevelSldr->setSliderStyle (Slider::Rotary);
    LevelSldr->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    LevelSldr->setColour (Slider::rotarySliderFillColourId, Colours::black);
    LevelSldr->addListener (this);

    addAndMakeVisible (GainLbl = new Label ("Gain Label",
                                            TRANS("Gain")));
    GainLbl->setFont (Font (15.00f, Font::plain));
    GainLbl->setJustificationType (Justification::centred);
    GainLbl->setEditable (false, false, false);
    GainLbl->setColour (Label::backgroundColourId, Colours::black);
    GainLbl->setColour (Label::textColourId, Colours::white);
    GainLbl->setColour (TextEditor::textColourId, Colours::black);
    GainLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (LevelLbl = new Label ("Level Label",
                                             TRANS("Level")));
    LevelLbl->setFont (Font (15.00f, Font::plain));
    LevelLbl->setJustificationType (Justification::centred);
    LevelLbl->setEditable (false, false, false);
    LevelLbl->setColour (Label::backgroundColourId, Colours::black);
    LevelLbl->setColour (Label::textColourId, Colours::white);
    LevelLbl->setColour (TextEditor::textColourId, Colours::black);
    LevelLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (BypassBtn = new TextButton ("Bypass Button"));
    BypassBtn->setButtonText (String());
    BypassBtn->addListener (this);
    BypassBtn->setColour (TextButton::buttonOnColourId, Colours::red);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 150);


    //[Constructor]
    BypassBtn->setClickingTogglesState(true);
    
    mGainAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_GAIN, *GainSldr);
    mLevelAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_LEVEL, *LevelSldr);
    mBypassAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.getState(), PARAM_BYPASS, *BypassBtn);
    //[/Constructor]
}

DiodeDistortionAudioProcessorEditor::~DiodeDistortionAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    mGainAttachment = nullptr;
    mLevelAttachment = nullptr;
    mBypassAttachment = nullptr;
    //[/Destructor_pre]

    GainSldr = nullptr;
    LevelSldr = nullptr;
    GainLbl = nullptr;
    LevelLbl = nullptr;
    BypassBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DiodeDistortionAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff3f3fff));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DiodeDistortionAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    GainSldr->setBounds (8, 56, 112, 88);
    LevelSldr->setBounds (181, 58, 112, 88);
    GainLbl->setBounds (26, 26, 80, 24);
    LevelLbl->setBounds (197, 26, 80, 24);
    BypassBtn->setBounds (142, 111, 23, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DiodeDistortionAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == GainSldr)
    {
        //[UserSliderCode_GainSldr] -- add your slider handling code here..
        //[/UserSliderCode_GainSldr]
    }
    else if (sliderThatWasMoved == LevelSldr)
    {
        //[UserSliderCode_LevelSldr] -- add your slider handling code here..
        //[/UserSliderCode_LevelSldr]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void DiodeDistortionAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == BypassBtn)
    {
        //[UserButtonCode_BypassBtn] -- add your button handler code here..
        //[/UserButtonCode_BypassBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DiodeDistortionAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor"
                 constructorParams="DiodeDistortionAudioProcessor&amp; ownerProc"
                 variableInitialisers="AudioProcessorEditor(ownerProc), processor(ownerProc)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="300" initialHeight="150">
  <BACKGROUND backgroundColour="ff3f3fff"/>
  <SLIDER name="Gain Slider" id="51c6c531ea5ef9c3" memberName="GainSldr"
          virtualName="" explicitFocusOrder="0" pos="8 56 112 88" rotarysliderfill="ff000000"
          min="0" max="10" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Level Slider" id="74a74b237850226d" memberName="LevelSldr"
          virtualName="" explicitFocusOrder="0" pos="181 58 112 88" rotarysliderfill="ff000000"
          min="0" max="10" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="Gain Label" id="c938a08884e4017a" memberName="GainLbl"
         virtualName="" explicitFocusOrder="0" pos="26 26 80 24" bkgCol="ff000000"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Gain"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Level Label" id="15f74a05f1fa29f1" memberName="LevelLbl"
         virtualName="" explicitFocusOrder="0" pos="197 26 80 24" bkgCol="ff000000"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Level"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="Bypass Button" id="5eec314bf05e65a0" memberName="BypassBtn"
              virtualName="" explicitFocusOrder="0" pos="142 111 23 24" bgColOn="ffff0000"
              buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
