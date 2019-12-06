#ifndef LED_H
#define LED_H

class Led{
    public:
        Led(int, int, int, bool, bool);
        ~Led();

        bool begin();

        bool handleToggleAmbientMode();
        bool handleToggleState();
        bool handleToggleState(bool);
        bool handleColorChange(int, int, int);

        const bool isAmbient();
    private:
        bool applyChange();

        int CONTROLLER_PIN_RED = 13; //D7
        int CONTROLLER_PIN_GREEN = 12; //D6
        int CONTROLLER_PIN_BLUE = 14; //D5

        int DC_RED;
        int DC_GREEN;
        int DC_BLUE;

        bool STATE_ON;

        bool AMBIENT_MODE;
};

#endif