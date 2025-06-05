
# 🎧 AudioCompass

**AudioCompass** is an Arduino-compatible library for **ESP32-S3** boards with **two I2S microphones** that detects the **direction of incoming sound** using a real **TinyML model** and **MFCC feature extraction**.

It outputs one of the four directions:
- `"Front"`
- `"Back"`
- `"Left"`
- `"Right"`

---

## 🚀 Features

- ✅ Dual I2S microphone input (e.g., INMP441)
- ✅ Real-time audio capture & buffering
- ✅ MFCC feature extraction using CMSIS-DSP
- ✅ TinyML model trained on directional audio features
- ✅ TFLite Micro inference on-device (no internet or PC needed)
- ✅ Clean Arduino API: `AudioCompass.getDirection()`
- ✅ Fully compatible with Arduino Library Manager

---

## 🔌 Hardware Required

- 1x **ESP32-S3** board (with I2S support)
- 2x **I2S microphones** (e.g. INMP441)
- Wires & headers

---

## 📦 Installation

1. Download the latest release of `AudioCompass.zip`
2. Open Arduino IDE → **Sketch > Include Library > Add .ZIP Library**
3. Select `AudioCompass.zip`

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

## 🧠 Model Training Process

The included TFLite model was trained using synthetic and real audio captured from a stereo microphone setup. Here's how it was done:

### 🔉 1. Data Collection

* 2x I2S microphones were placed **20–40 cm apart**
* Sounds (e.g., clap, tap, beep) were played from:

  * Front (0°)
  * Left (90°)
  * Right (270°)
  * Back (180°)
* Audio was recorded at **16 kHz**, mono or stereo depending on configuration
* Data was labeled accordingly and split into training/validation

### 📊 2. Feature Extraction

* Extracted **13 MFCCs** per frame
* Window size: 30 ms
* Frame step: 10 ms
* Normalized to 0–1 float range

### 🧠 3. Model Architecture (TensorFlow)

```python
model = tf.keras.Sequential([
    tf.keras.layers.Input(shape=(N_MFCC,)),
    tf.keras.layers.Dense(16, activation='relu'),
    tf.keras.layers.Dense(4, activation='softmax')
])
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
```

### 🔁 4. Conversion to TFLite

```bash
tflite_convert \
  --keras_model_file=direction_model.h5 \
  --output_file=direction_model.tflite \
  --optimize \
  --target_ops=TFLITE_BUILTINS_INT8
```

### 🔀 5. Convert to C for Arduino

```bash
xxd -i direction_model.tflite > model_data.h
```

---

## 🧪 Inference & Output

The function `AudioCompass.getDirection()`:

1. Captures a 1-second buffer from the mics
2. Extracts MFCCs
3. Runs inference on the TFLite Micro model
4. Returns a string: `"Front"`, `"Back"`, `"Left"`, or `"Right"`

---

## 📁 Library Contents

| File                              | Purpose                            |
| --------------------------------- | ---------------------------------- |
| `src/AudioCompass.h/.cpp`         | Library implementation             |
| `src/model_data.h`                | Embedded TFLite model as a C array |
| `examples/AudioDirectionDemo.ino` | Simple working example             |
| `library.properties`              | Arduino metadata                   |
| `keywords.txt`                    | Arduino IDE keyword coloring       |
| `README.md`                       | This documentation                 |
| `LICENSE`                         | MIT License                        |

---

## 📜 License

This project is released under the **MIT License**.
MIT License

Copyright (c) 2025 Herobrine Pixel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


---

## 🧠 Want to Train Your Own Model?

You can train your own directional model using:

* [TensorFlow](https://www.tensorflow.org/)
* [Edge Impulse](https://www.edgeimpulse.com/)
* [Python scripts for I2S audio capture](https://github.com/espressif/esp-idf-examples)

Let me know if you want a training notebook or scripts!

---

## 🔗 Useful Resources

* [TFLite Micro](https://www.tensorflow.org/lite/microcontrollers)
* [ESP32-S3 Datasheet](https://www.espressif.com/en/products/socs/esp32-s3)
* [CMSIS-DSP](https://arm-software.github.io/CMSIS_5/DSP/html/index.html)
* [Edge Impulse Studio](https://studio.edgeimpulse.com/)

---

**Developed by Herobrine Pixel**
*2025*

