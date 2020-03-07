/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ACME4Editor  : public AudioProcessorEditor,
                     public Timer
{
public:
    //==============================================================================
    ACME4Editor (Acme4v2AudioProcessor& processor);
    ~ACME4Editor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;

    // Binary resources:
    static const char* acme4_scaled_png;
    static const int acme4_scaled_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    Acme4v2AudioProcessor& processor_;

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> infoLabel;
    std::unique_ptr<Label> label;
    Image cachedImage_acme4_scaled_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACME4Editor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

