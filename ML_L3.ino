/** 
* Nikon ML L3 - compatible remote control
*  
* Author: Barry Lim
*/ 

#include <Bounce2.h>

const unsigned int BAUDRATE = 19200;    // Baudrate halved from 38.4kHz. Reason being that the tone() represents 2 bit length
const unsigned char IR_PORT = 2;
const unsigned char BUTTON_PIN = 3;

// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

unsigned buttonLastState = HIGH;

void ir_activate(unsigned int Tactive, unsigned int Tinactive){
  tone( IR_PORT, BAUDRATE );
  delayMicroseconds(Tactive);

  noTone(IR_PORT);
  delayMicroseconds(Tinactive);
}


void ir_sequence(){
  ir_activate(2083, 26667);
  ir_activate(417, 1667);
  ir_activate(417, 3333);
  ir_activate(417, 62500);
}



void setup() {
  // put your setup code here, to run once:
  pinMode(IR_PORT, OUTPUT);

  //  Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);

  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(10); // interval in ms
}


void loop() {

  // Update the Bounce instance
  debouncer.update();

  // Get the updated value
  int value = debouncer.read();

  if ( value == LOW ) {
      if(buttonLastState == HIGH){
        buttonLastState = LOW;

        // trigger 3x in succession
        ir_sequence();
        ir_sequence();
        ir_sequence();
      }
      else{}    // do nothing
  } 
  else {
      buttonLastState = HIGH;
  } 
}
