// https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0
#include <Joystick.h>

//Define Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 0, 0,
  true, true, false, false, false, true,
  false, true, false, false, false);

//Arduino Leonardo Pin Input
//No Button set
const byte Throttle = 0;
const byte Roll = 1;
const byte Pitch = 2;
const byte Yaw = 3;


//micros when the pin goes HIGH
volatile unsigned long timer_start;
//difference between timer_start and micros() is the length of time that the pin 
//was HIGH - the PWM pulse length for Throttle, Roll, Pitch and Yaw.
volatile int pulse_timeT; 
volatile int pulse_timeR; 
volatile int pulse_timeP; 
volatile int pulse_timeY; 

//this is the time that the last interrupt occurred. 
//you can use this to determine if your receiver has a signal or not. 

volatile int last_interrupt_time; //calcSignal is the interrupt handler 

void calcSignalThrottle() 
{
    last_interrupt_time = micros(); 
    if(digitalRead(Throttle) == HIGH) 
    { 
        timer_start = micros();
    } 
    else
    { 
        if(timer_start != 0)
        { 
            pulse_timeT = ((volatile int)micros() - timer_start);
            timer_start = 0;
        }
    } 
}
void calcSignalRoll() 
{
    last_interrupt_time = micros(); 
    if(digitalRead(Roll) == HIGH) 
    { 
        timer_start = micros();
    } 
    else
    { 
        if(timer_start != 0)
        { 
            pulse_timeR = ((volatile int)micros() - timer_start);
            timer_start = 0;
        }
    } 
}
void calcSignalPitch() 
{
    last_interrupt_time = micros(); 
    if(digitalRead(Pitch) == HIGH) 
    { 
        timer_start = micros();
    } 
    else
    { 
        if(timer_start != 0)
        { 
            pulse_timeP = ((volatile int)micros() - timer_start);
            timer_start = 0;
        }
    } 
} 
void calcSignalYaw() 
{
    last_interrupt_time = micros(); 
    if(digitalRead(Yaw) == HIGH) 
    { 
        timer_start = micros();
    } 
    else
    { 
        if(timer_start != 0)
        { 
            pulse_timeY = ((volatile int)micros() - timer_start);
            timer_start = 0;
        }
    } 
} 
 
//this is all normal arduino stuff 
void setup() 
{
    timer_start = 0; 
    
    //attach the Pins to the Interruptroutine
    attachInterrupt(digitalPinToInterrupt(Throttle), calcSignalThrottle, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pitch), calcSignalPitch, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Roll), calcSignalRoll, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Yaw), calcSignalYaw, CHANGE);
    
    //Setup the values for the Joystick.
    //If input value is higher than set e.g. 2052 a overflow will occur and the output will be 952!
    Joystick.setXAxisRange(950 , 2050);
    Joystick.setYAxisRange(950 , 2050);
    Joystick.setRzAxisRange(950 , 2050);
    Joystick.setThrottleRange(950 , 2050);
    
    //Start the Joystick
    Joystick.begin();
    
    //for debug output
    //Serial.begin(115200);
} 
 
void loop()
{
    //old debug output
/*     Serial.print("Throttle: ");
    Serial.println(pulse_timeT);
    
    Serial.print("Pitch: ");
    Serial.println(pulse_timeP);

    Serial.print("Roll: ");
    Serial.println(pulse_timeR);

    Serial.print("Yaw: ");
    Serial.println(pulse_timeY);
    delay(20); */
    
    //write the input on Joystick
    Joystick.setXAxis(pulse_timeR);
    //Y-Axis had to be inverted
    Joystick.setYAxis( (pulse_timeP) * ( -1 ) + 3000 );
    Joystick.setRzAxis(pulse_timeY);
    Joystick.setThrottle(pulse_timeT);
}


