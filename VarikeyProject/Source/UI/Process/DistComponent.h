/*
  ==============================================================================

    DistComponent.h
    Created: 30 Apr 2022 2:32:30pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistComponent  : public juce::Component
{
public:
    DistComponent();
    ~DistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistComponent)
};
