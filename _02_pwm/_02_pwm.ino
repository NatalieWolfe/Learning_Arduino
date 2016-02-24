
const int LED_PIN = 9;

void setup(){
    pinMode(LED_PIN, OUTPUT);
}

void loop(){
    for (int i = 0; i < 256; ++i) {
        analogWrite(LED_PIN, i);
        delay(50);
    }

    for (int i = 255; i > 0; i -= 10) {
        analogWrite(LED_PIN, i);
        delay(50);
    }
}
