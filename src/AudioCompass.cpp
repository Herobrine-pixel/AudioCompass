
#include "AudioCompass.h"
#include "model_data.h"
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Globals for inference
namespace {
    constexpr int kTensorArenaSize = 10 * 1024;
    uint8_t tensor_arena[kTensorArenaSize];

    const tflite::Model* model = nullptr;
    tflite::MicroInterpreter* interpreter = nullptr;
    TfLiteTensor* input = nullptr;
    TfLiteTensor* output = nullptr;
}

void AudioCompass::begin() {
    model = tflite::GetModel(g_model);
    static tflite::MicroMutableOpResolver<5> resolver;
    resolver.AddFullyConnected();
    resolver.AddSoftmax();
    resolver.AddReshape();
    resolver.AddConv2D();
    resolver.AddMaxPool2D();

    static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
    interpreter = &static_interpreter;
    interpreter->AllocateTensors();

    input = interpreter->input(0);
    output = interpreter->output(0);
}

String AudioCompass::getDirection() {
    // Simulate MFCC input (replace with real MFCCs from audio)
    for (int i = 0; i < input->bytes; ++i) {
        input->data.f[i] = 0.0f;  // Placeholder for MFCC data
    }

    interpreter->Invoke();

    int predicted = 0;
    float max_score = output->data.f[0];
    for (int i = 1; i < 4; ++i) {
        if (output->data.f[i] > max_score) {
            max_score = output->data.f[i];
            predicted = i;
        }
    }

    switch (predicted) {
        case 0: return "Front";
        case 1: return "Back";
        case 2: return "Left";
        case 3: return "Right";
        default: return "Unknown";
    }
}
