// https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0
#include <Joystick.h>

double  Channel[6];
byte PWM_PIN[6];
int i;

//Define Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK, 0, 0,
                   true, true, false, false, false, true,
                   false, true, false, false, false);


void setup() {
  //Setup the values for the Joystick.
    //If input value is higher than set e.g. 2052 a overflow will occur and the output will be 952!
  Joystick.setXAxisRange(950 , 2050);
  Joystick.setYAxisRange(950 , 2050);
  Joystick.setRzAxisRange(950 , 2050);
  Joystick.setThrottleRange(950 , 2050);
  
  //Start the Joystick
  Joystick.begin();

  for (i = 0; i < 4; i++) {
    PWM_PIN[i] = i;
    pinMode(PWM_PIN[i], INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i = 0; i < 4; i++) {
    Channel[i] = pulseIn(PWM_PIN[i], HIGH);
  }

  //write the input on Joystick
  Joystick.setXAxis(Channel[1]);
  Joystick.setYAxis( (Channel[2] ) * ( -1 ) + 3000 );
  Joystick.setRzAxis(Channel[3]);
  Joystick.setThrottle(Channel[0]);
}
