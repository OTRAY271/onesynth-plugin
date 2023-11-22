/**
 *
 * Copyright (c) 2013 Pascal Gauthier.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 */

#ifndef INFERENGINE_H_INCLUDED
#define INFERENGINE_H_INCLUDED

#include "JuceHeader.h"
#include "nlohmann/json.hpp"
#include "PluginProcessor.h"
#include "OneSynthParams.h"
using json = nlohmann::json;

class InferEngine: private juce::Thread {
public:
    InferEngine(DexedAudioProcessor *processor);
    ~InferEngine();

    void seek();
    void moveForward();
    void turnAround();

    void load();
    void save();

    // void random();

    void startEngine();

private:
    DexedAudioProcessor *processor;
    OneSynthParams *oneSynthParams;

    float searchPositionCache;
    bool forceUpdate;
    int64 lastPingTime;

    std::vector<std::vector<float>> vh;
    std::vector<float> sigma;

    void run() override;

    bool post(String path, json request, json& response);
    bool ping();
};

#endif  // INFERENGINE_H_INCLUDED
