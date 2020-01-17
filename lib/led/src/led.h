#ifndef LED_H
#define LED_H

class Led {
public:
  static bool prepare(int, int, int, bool, bool);

  static bool handleAmbientModeOn();
  static bool handleAmbientModeOff();
  static bool handleSwitchOn();
  static bool handleSwitchOff();
  static bool handleColorChange(int, int, int);

  static bool isAmbient();

private:
  static bool applyChange();

  static int CONTROLLER_PIN_RED;
  static int CONTROLLER_PIN_GREEN;
  static int CONTROLLER_PIN_BLUE;

  static int DC_RED;
  static int DC_GREEN;
  static int DC_BLUE;

  static bool STATE_ON;

  static bool AMBIENT_MODE;
};

#endif