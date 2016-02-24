
// Digital pins.
const int MOTOR_SPEED_PIN = 3;
const int MOTOR_CONTROL_PIN1 = 4;
const int MOTOR_CONTROL_PIN2 = 5;

// Analog input pins.
const int POT_PIN = 1;

// Configuration values.
const int DEADZONE = 10;

class OutputPin {
public:
    void setup(const int pin){
        m_pin = pin;
        pinMode(pin, OUTPUT);
    }

    int pin() const {
        return m_pin;
    }

    void on(){
        digitalWrite(pin(), HIGH);
    }

    void off(){
        digitalWrite(pin(), LOW);
    }

private:
    int m_pin;
};

class AnalogOutput : public OutputPin {
public:
    AnalogOutput(const int min, const int max):
        m_min{min},
        m_max{max}
    {}

    AnalogOutput():
        AnalogOutput{0, 255}
    {}

    void write(const int value){
        analogWrite(pin(), constrain(map(value, m_min, m_max, 0, 255), 0, 255));
    }

private:
    int m_min;
    int m_max;
};

class Motor {
public:
    Motor(){}

    void setup(const int speed_pin, const int control_pin1, const int control_pin2){
        m_control1.setup(control_pin1);
        m_control2.setup(control_pin2);
        m_speed.setup(speed_pin);
    }

    void run(const int speed){
        int constrained_speed = constrain(speed, -255, 255);

        // Kill the circuit before adjusting.
        m_speed.off();

        // What direction are things going?
        if (constrained_speed > 0) {
            m_control1.on();
            m_control2.off();
        }
        else {
            m_control1.off();
            m_control2.on();
            constrained_speed = -constrained_speed; // Make speed positive.
        }

        // Open it up again.
        m_speed.write(constrained_speed);
    }

    void brake(){
        m_speed.off();
        m_control1.off();
        m_control2.off();
        m_speed.on();
    }

private:
    OutputPin m_control1;
    OutputPin m_control2;
    AnalogOutput m_speed;
};

class AnalogInput {
public:
    AnalogInput(const int min, const int max):
        m_min{min},
        m_max{max}
    {}

    AnalogInput():
        AnalogInput{0, 1023}
    {}

    void setup(const int pin){
        m_pin = pin;
    }

    int read(const int min, const int max) const {
        return constrain(map(analogRead(m_pin), m_min, m_max, min, max), min, max);
    }

    int read() const {
        return read(0, 1023);
    }

private:
    int m_min;
    int m_max;
    int m_pin;
};

Motor motor;
AnalogInput pot;

void setup(){
    motor.setup(MOTOR_SPEED_PIN, MOTOR_CONTROL_PIN1, MOTOR_CONTROL_PIN2);
    pot.setup(POT_PIN);
}

void loop(){
    const int reading = pot.read(-255, 255);
    if (-DEADZONE < reading && reading < DEADZONE) {
        motor.brake();
    }
    else {
        motor.run(reading);
    }
}
