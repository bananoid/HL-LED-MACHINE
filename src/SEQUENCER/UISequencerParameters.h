#pragma once

#include "UIScrollView.h"
#include <Sequencer.h>
#include "UIParameterView.h"

#include <stddef.h>
#include <vector>

using namespace HLMusicMachine;

struct UISequencerParameterDescription
{
    String label;
    UIView *view;
};

class UISequencerParameters : public UIScrollView
{
private:
public:
    Sequencer *sequencer;

    UISequencerParameters(Sequencer *sequencer)
    {
        this->sequencer = sequencer;
    }
    void build() override
    {
        const std::vector<UISequencerParameterDescription> pDesk = {
            {
                "steps",
                new UIParameterView<uint8_t>(&sequencer->parameters.steps),
            },
            {
                "events",
                new UIParameterView<uint8_t>(&sequencer->parameters.events),
            },
            {
                "offset",
                new UIParameterView<uint8_t>(&sequencer->parameters.offset),
            },
            {
                "stepLenght",
                new UIParameterView<uint8_t>(&sequencer->parameters.stepLenght),
            },
            {
                "octave",
                new UIParameterView<int8_t>(&sequencer->parameters.octave),
            },
            {
                "noteCount",
                new UIParameterView<uint8_t>(&sequencer->parameters.noteCount),
            },
            {
                "noteOffset",
                new UIParameterView<uint8_t>(&sequencer->parameters.noteOffset),
            },
            {
                "noteSpread",
                new UIParameterView<uint8_t>(&sequencer->parameters.noteSpread),
            },

            {
                "arpeggioType",
                new UIParameterView<Sequencer::ArpeggioType>(&sequencer->parameters.arpeggioType),
            },
            {
                "chord",
                new UIParameterView<bool>(&sequencer->parameters.chord),
            },
            {
                "retrig",
                new UIParameterView<int8_t>(&sequencer->parameters.retrig),
            },
            {
                "retrigLFO",
                new UIParameterView<uint8_t>(&sequencer->parameters.retrigLFO),
            },
            {
                "retrig min",
                new UIParameterView<uint8_t>(&sequencer->parameters.retrigMin),
            },
            {
                "retrig max",
                new UIParameterView<uint8_t>(&sequencer->parameters.retrigMax),
            },

            {
                "vel Max",
                new UIParameterView<uint8_t>(&sequencer->parameters.velocityMax),
            },
            {
                "vel Min",
                new UIParameterView<uint8_t>(&sequencer->parameters.velocityMin),
            },
            {
                "vel LFO Enabled",
                new UIParameterView<bool>(&sequencer->parameters.velocityLFOEnabled),
            },
            {
                "vel LFO Speed",
                new UIParameterView<uint8_t>(&sequencer->parameters.velocityLFOSpeed),
            },
        };

        auto cFrame = frame;
        cFrame.h = 32;

        for (auto it : pDesk)
        {
            it.view->label = it.label;
            it.view->frame = cFrame;
            addChild(it.view);
        }
    }
};