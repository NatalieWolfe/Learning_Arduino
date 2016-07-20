
#include <Servo.h>

enum class PIN : int {
    // PWM output pins.
    LED_0 = 3,
    LED_1 = 5,
    LED_2 = 6,
    LED_3 = 9,
    SERVO = 11,

    // Analog input pins.
    IR_SENSOR = 0
};

Servo servo;
int servoPosition = 0;

void setup() {
    pinMode((int)PIN::LED_0, OUTPUT);
    pinMode((int)PIN::LED_1, OUTPUT);
    pinMode((int)PIN::LED_2, OUTPUT);
    pinMode((int)PIN::LED_3, OUTPUT);
    servo.attach((int)PIN::SERVO);

    Serial.begin(9600);
}

void loop() {
    int distance = analogRead((int)PIN::IR_SENSOR);
    servoPosition = constrain(map(distance, 50, 500, 0, 179), 0, 179);
    servo.write(servoPosition);

    Serial.println(distance);

    delay(300);
}
