
const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;
const int BUTTON_PIN = 7;

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

class InputPin {
public:
    void setup(const int pin){
        m_pin = pin;
        pinMode(pin, INPUT);
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

    void set(const int value){
        analogWrite(pin(), constrain(map(value, m_min, m_max, 0, 255), 0, 255));
    }

private:
    int m_min;
    int m_max;
};

class ToggleButton : public InputPin {
public:
    ToggleButton():
        m_on{ false }
    {}

    bool toggled(){
        bool current = digitalRead(pin());
        bool toggled = false;

        // If we've read a new state, wait for it to settle and read again.
        if (m_on != current) {
            delay(5);
            current = digitalRead(pin());
        }

        // If our state is off and the new state is on, we've toggled.
        if (!m_on && current) {
            toggled = true;
        }

        // Store the new state and return our findings.
        m_on = current;
        return toggled;
    }

private:
    bool m_on;
};

// NOTE: I am using a common anode LED, thus the input logic is reversed.
AnalogOutput red_led{255, 0};
AnalogOutput green_led{255, 0};
AnalogOutput blue_led{255, 0};
ToggleButton button;
int state;

void setup(){
    red_led.setup(RED_LED_PIN);
    green_led.setup(GREEN_LED_PIN);
    blue_led.setup(BLUE_LED_PIN);
    button.setup(BUTTON_PIN);

    state = 0;
}

void loop(){
    if (button.toggled()) {
        state = (state + 1) % 6;
        if (state == 0) {
            red_led.set(127);
            green_led.set(0);
            blue_led.set(0);
        }
        else if (state == 1) {
            red_led.set(80);
            green_led.set(80);
            blue_led.set(0);
        }
        else if (state == 2) {
            red_led.set(0);
            green_led.set(127);
            blue_led.set(0);
        }
        else if (state == 3) {
            red_led.set(0);
            green_led.set(80);
            blue_led.set(80);
        }
        else if (state == 4) {
            red_led.set(0);
            green_led.set(0);
            blue_led.set(127);
        }
        else if (state == 5) {
            red_led.set(80);
            green_led.set(0);
            blue_led.set(80);
        }
    }
}
