/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Feb 2012 12:52:59am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_ACMEPLUGINAUDIOPROCESSOREDITOR_ACMEEDITOR_CEC5CA03__
#define __JUCER_HEADER_ACMEPLUGINAUDIOPROCESSOREDITOR_ACMEEDITOR_CEC5CA03__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "../JuceLibraryCode/JucePluginCharacteristics.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ACME4PluginAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Timer
{
public:
    //==============================================================================
    ACME4PluginAudioProcessorEditor (ACME4PluginAudioProcessor* ownerFilter);
    ~ACME4PluginAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* acme4_scaled_png;
    static const int acme4_scaled_pngSize;


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    ACME4PluginAudioProcessor* getProcessor() const
    {
        return static_cast <ACME4PluginAudioProcessor*> (getAudioProcessor());
    }

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);
    //[/UserVariables]

    //==============================================================================
    Label* infoLabel;
    Label* label;
    Image cachedImage_acme4_scaled_png;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    ACME4PluginAudioProcessorEditor (const ACME4PluginAudioProcessorEditor&);
    const ACME4PluginAudioProcessorEditor& operator= (const ACME4PluginAudioProcessorEditor&);
};


#endif   // __JUCER_HEADER_ACMEPLUGINAUDIOPROCESSOREDITOR_ACMEEDITOR_CEC5CA03__
