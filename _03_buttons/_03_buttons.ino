
const int LED_PIN = 9;
const int BUTTON_PIN = 11;

class ToggleOutput {
public:
    ToggleOutput(const int pin):
        m_pin{ pin },
        m_on{ false }
    {}

    bool toggle(){
        m_on = !m_on;
        digitalWrite(m_pin, m_on);
        return m_on;
    }

private:
    int m_pin;
    bool m_on;
};

class ToggleButton {
public:
    ToggleButton(const int pin):
        m_pin{ pin },
        m_on{ false }
    {}

    bool toggled() const {
        bool current = digitalRead(m_pin);
        bool toggled = false;

        // If we've read a new state, wait for it to settle and read again.
        if (m_on != current) {
            delay(5);
            current = digitalRead(m_pin);
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
    int m_pin;
    mutable bool m_on;
};

ToggleOutput led{ LED_PIN };
const ToggleButton button{ BUTTON_PIN };

void setup(){
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop(){
    if (button.toggled()) {
        led.toggle();
    }
}
