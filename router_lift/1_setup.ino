// QUIMAT STEPPER MOTOR model:17HS4401 with TM6600 motor driver( http://www.airspayce.com/mikem/arduino/AccelStepper/index.html )
#include <AccelStepper.h>
const uint8_t ENA = 6; // enable
const uint8_t DIR = 5; // direction
const uint8_t PUL = 4; // pulse
AccelStepper stepper( AccelStepper::DRIVER, PUL, DIR );
void setup_stepper( void ) { pinMode( ENA, OUTPUT ); stepper.setEnablePin( ENA ); stepper.setPinsInverted( true , false, true ); }

// four digit seven segment display ( https://github.com/bremme/arduino-tm1637 )
#include <SevenSegmentTM1637.h>
#define CLK_PIN 10
#define DIO_PIN 11
SevenSegmentTM1637 display( CLK_PIN, DIO_PIN );
void setup_7_segment( void ) { display.begin( 4, 1 ); display.setBacklight(80); }

// VS1838 infrared radiation receiver ( https://github.com/z3t0/Arduino-IRremote )
#include <IRremote.h>
#define RECV_PIN 12 
IRrecv irrecv( RECV_PIN ); decode_results results;
void setup_infrared( void ) { irrecv.enableIRIn(); }

// these switches are used to avoid motor crash 
#define SW1 2 // arduino digital pin D2
#define SW2 3 // LDR sensor module ( www.amazon.co.jp/dp/B0759XWC3L )
void setup_limit_switch( void ) {
  pinMode( SW1, INPUT_PULLUP );
  pinMode( SW2, INPUT_PULLUP );
}
