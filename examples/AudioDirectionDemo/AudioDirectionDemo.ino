

#include <AudioCompass.h>

void setup() {
    Serial.begin(115200);
    AudioCompass.begin();
}

void loop() {
    String direction = AudioCompass.getDirection();
    Serial.println("Detected Direction: " + direction);
    delay(1000);
}


