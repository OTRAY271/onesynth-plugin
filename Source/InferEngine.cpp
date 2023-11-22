#include "InferEngine.h"
#include <random>

const String SERVER_URL = "http://127.0.0.1:8000/";
const File APP_DIR = File("~/Library/Application Support/OneSynth");
const File PRESET_DIR = APP_DIR.getChildFile("presets");
const File SERVER_DIR = APP_DIR.getChildFile("server").getChildFile("onesynth_server");

InferEngine::InferEngine(DexedAudioProcessor *processor): Thread("InferEngine Thread") {
    this->processor = processor;
    this->oneSynthParams = &processor->oneSynthParams;
}

InferEngine::~InferEngine() {
    signalThreadShouldExit();
    stopThread(-1);
}

void InferEngine::seek() {
    if (!forceUpdate && oneSynthParams->searchPosition == searchPositionCache) {
        return;
    }

    json request = {
        {"position", oneSynthParams->searchPosition},
        {"basis", oneSynthParams->basis},
        {"center_z", oneSynthParams->z}
    };
    json response;
    if (post("seek", request, response)) {
        std::vector<float> synthParams = response["synth_params"].template get<std::vector<float>>();
        for (int i = 0; i < synthParams.size(); i++) {
            processor->setParameter(i, synthParams[i]);
        }
        searchPositionCache = oneSynthParams->searchPosition;
        forceUpdate = false;
    }
}

void InferEngine::moveForward() {
    json request = {
        {"position", oneSynthParams->searchPosition},
        {"basis", oneSynthParams->basis},
        {"center_z", oneSynthParams->z}
    };
    json response;
    if (post("move_forward", request, response)) {
        vh = response["vh"].template get<std::vector<std::vector<float>>>();
        sigma = response["sigma"].template get<std::vector<float>>();
        oneSynthParams->z = response["new_center_z"].template get<std::vector<float>>();
        turnAround();
    }
}

void InferEngine::turnAround() {
    json request = {
        {"vh", vh},
        {"sigma", sigma},
    };
    json response;
    if (post("turn_around", request, response)) {
        oneSynthParams->basis = response["basis"].template get<std::vector<float>>();
        oneSynthParams->searchPosition = 0;
        forceUpdate = true;
    }
}

void InferEngine::load() {
    FileChooser presetChooser("Select a preset...", PRESET_DIR, "*.json");
    if (presetChooser.browseForFileToOpen())
    {
        File file (presetChooser.getResult());
        json zJson = json::parse(file.loadFileAsString().toStdString());
        oneSynthParams->z = zJson.template get<std::vector<float>>();
        oneSynthParams->searchPosition = 0;
        moveForward();
    }
}

void InferEngine::save() {
    FileChooser locationChooser("Select a location...", PRESET_DIR, "*.json");
    if ( locationChooser.browseForFileToSave(true) ) {
        if (oneSynthParams->searchPosition != 0) {
            moveForward();
        }
        json zJson = oneSynthParams->z;
        locationChooser.getResult().replaceWithText(zJson.dump());
    }
}

// void InferEngine::random() {
//     std::vector<float> z(256, 0);
//     std::random_device seed_gen;
//     std::mt19937 engine(seed_gen());
//     std::normal_distribution<> dist(0.0, 1.0); 
//     for (int i = 0; i < z.size(); i++) {
//         z[i] = dist(engine);
//     }
//     oneSynthParams->z = z;
//     oneSynthParams->searchPosition = 0;
//     moveForward();
// }

void InferEngine::startEngine() {
    if (!ping()) {
        String command = "cd \"" + SERVER_DIR.getFullPathName() + "\" && ./onesynth_server &";
        system(command.toStdString().c_str());
        while (!ping()) {
            Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 1000);
        }
    }

    if (oneSynthParams->z.size() == 0) {
        File file ("~/Library/Application Support/OneSynth/presets/piano.json");
        String zStr = file.loadFileAsString();
        oneSynthParams->z = json::parse(zStr.toStdString()).template get<std::vector<float>>();
    }
    if (oneSynthParams->basis.size() == 0) {
        std::vector<float> zeros(256, 0);
        oneSynthParams->basis = zeros;
    }
    moveForward();

    startThread();
}

void InferEngine::run() {
    while (!threadShouldExit()) {
        if (Time::currentTimeMillis() - lastPingTime > 3000) {
            ping();
        }
        seek();
        sleep(10);
    }
}

bool InferEngine::post(String path, json request, json& response) {
    String s = request.dump();
    URL url = URL(SERVER_URL + path).withPOSTData(s);
    String res = url.readEntireTextStream(true);
    if (res == "") {
        return false;
    }
    response = json::parse(res.toStdString());
    return true;
}

bool InferEngine::ping() {
    URL url = URL(SERVER_URL + "ping");
    std::string res = url.readEntireTextStream().toStdString();
    lastPingTime = Time::currentTimeMillis();
    return res == "\"ok\"";
}