# 🎧 AudioCompass

**AudioCompass** is an open-source Arduino library for **ESP32-S3** boards that detects the **direction of sound** using two **I2S microphones**, **MFCC feature extraction**, and a **TinyML model**. It tells you if a sound came from the **Front**, **Back**, **Left**, or **Right**.

---

## 🚀 Features

- ✅ Dual **I2S microphone input** (e.g., INMP441)
- ✅ Real-time **audio buffering** using I2S
- ✅ **MFCC feature extraction** using CMSIS-DSP
- ✅ Embedded **TinyML model** for sound direction
- ✅ Efficient **TensorFlow Lite Micro** inference
- ✅ Simple Arduino API: `AudioCompass.getDirection()`
- ✅ Fully Arduino Library Manager compatible

---

## 🔌 Hardware Requirements

| Component      | Quantity | Notes                          |
|----------------|----------|--------------------------------|
| ESP32-S3 Board | 1        | e.g., ESP32-S3 DevKit, etc.    |
| I2S Mic        | 2        | e.g., INMP441 or SPH0645       |
| Jumper wires   | —        | To connect mics to I2S pins    |

---

## 📡 Wiring Example (ESP32-S3 + 2x INMP441)

### Mic 1 (Left side):
| INMP441 Pin | ESP32-S3 Pin |
|-------------|--------------|
| GND         | GND          |
| VCC         | 3.3V         |
| WS          | GPIO 15      |
| SCK         | GPIO 14      |
| SD          | GPIO 32      |

### Mic 2 (Right side):
| INMP441 Pin | ESP32-S3 Pin |
|-------------|--------------|
| GND         | GND          |
| VCC         | 3.3V         |
| WS          | GPIO 15 *(shared)* |
| SCK         | GPIO 14 *(shared)* |
| SD          | GPIO 33      |

> ✅ The `WS` (word select) and `SCK` (clock) lines are shared between both microphones.  
> `SD` (data line) must be unique for each mic.

---

## 📄 Example Sketch

```cpp
#include <AudioCompass.h>

void setup() {
  Serial.begin(115200);
  AudioCompass.begin();
}

void loop() {
  String direction = AudioCompass.getDirection();
  Serial.println("Detected Direction: " + direction);
  delay(500);
}
````
---

## 🧠 Model Training Overview
The TinyML model was trained using real audio recorded from a stereo mic setup. Here's the process:

## 📊 1. Data Collection
Claps/beeps/taps were played from four angles (Front, Back, Left, Right)

Audio captured using two I2S mics ~20–40cm apart

Sampled at 16kHz

## 🧮 2. Feature Extraction
13 MFCCs per frame

30ms window, 10ms step

Normalized values

## 🤖 3. Model Architecture
python
Copy
Edit
model = tf.keras.Sequential([
  tf.keras.layers.Input(shape=(N_MFCC,)),
  tf.keras.layers.Dense(16, activation='relu'),
  tf.keras.layers.Dense(4, activation='softmax')
])
## 💾 4. Deployment
Trained model exported to .tflite

Converted to .h with xxd

Inference performed using TensorFlow Lite Micro

## 🧪 Inference Output
Calling AudioCompass.getDirection() will return a String:

"Front"

"Back"

"Left"

"Right"

These values are printed to Serial or can be used in your own logic.

## 📁 Folder Structure
| File                              | Purpose                            |
| --------------------------------- | ---------------------------------- |
| `examples/AudioDirectionDemo.ino` | Simple working example           |
| `src/model_data.h`                | Embedded TFLite model as a C array |
| `src/AudioCompass.h/.cpp`         | Library implementation            |
| `library.properties`              | Arduino metadata                   |
| `keywords.txt`                    | Arduino IDE keyword coloring       |
| `README.md`                       | This documentation                 |
| `LICENSE`                         | MIT License                        |

---

## 📥 Installation
You can install this library via:

Arduino Library Manager (Recommended)

Or manually:

Download AudioCompass.zip

Arduino IDE > Sketch > Include Library > Add .ZIP Library

## 📜 License
sql
Copy
Edit
MIT License

Copyright (c) 2025 Herobrine Pixel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction...

[Full license text included in LICENSE file]
## 🙌 Credits
Developed by Herobrine Pixel with support from the OpenAI team.
Includes CMSIS-DSP and TensorFlow Lite Micro runtime.

## 🔗 Useful Resources
ESP32 I2S Docs

CMSIS-DSP Library

TensorFlow Lite for Microcontrollers

Edge Impulse Studio










