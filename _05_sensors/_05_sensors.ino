
// Digital pins
const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

// Analog input pins
const int LIGHT_SENSOR_PIN = 1;

// Configuration values.
const int LIGHT_MIN = 600;  // <-- I have a bright room aparently.
const int LIGHT_MAX = 1000;

class OutputPin {
public:
    void setup(const int pin){
        m_pin = pin;
        pinMode(pin, OUTPUT);
    }

    int pin() const {
        return m_pin;
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

class RgbLed {
public:
    RgbLed():
        m_red{255, 0},
        m_green{255, 0},
        m_blue{255, 0}
    {}

    void setup(const int red_pin, const int green_pin, const int blue_pin){
        m_red.setup(red_pin);
        m_green.setup(green_pin);
        m_blue.setup(blue_pin);
    }

    void write(const int red, const int green, const int blue){
        m_red.write(red);
        m_green.write(green);
        m_blue.write(blue);
    }

private:
    AnalogOutput m_red;
    AnalogOutput m_green;
    AnalogOutput m_blue;
};

RgbLed led;
AnalogInput light_sensor{LIGHT_MIN, LIGHT_MAX};

void setup(){
    led.setup(RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN);
    light_sensor.setup(LIGHT_SENSOR_PIN);
}

void loop(){
    led.write(
        light_sensor.read(10, 127),
        light_sensor.read(10, 127),
        light_sensor.read(20, 127)
    );
    delay(10);
}
