/* This example shows basic use of the AMIS-30543 stepper motor driver. It shows how to initialize the driver, set the current limit, set the micro-stepping mode, and enable the driver. It shows how to send pulses to the NXT/STEP pin to get the driver to take steps and how to switch directions using the DIR pin. The DO pin is not used and does not need to be connected. Before using this example, be sure to change the setCurrentMilliamps line to have an appropriate current limit for your system. Also, see this library's documentation for information about how to connect the driver: http://pololu.github.io/amis-30543-arduino/ */ 
/* Note: * Pin 11 - MOSI * Pin 12 - MISO * Pin 13 - SCK */

#include #include const uint8_t amisDirPin = 2; 
const uint8_t amisStepPin = 3; 
const uint8_t amisSlaveSelect1 = 4; 
const uint8_t amisSlaveSelect2 = 7; // Slave Select for Slave 2 
const uint8_t amisSlaveSelect3 = 8; // Slave Select for Slave 3 
AMIS30543 stepper; 

void slave_select(int slave) { 
  stepper.init(slave); // Drive the NXT/STEP and DIR pins low initially. 
  digitalWrite(amisStepPin, LOW); 
  pinMode(amisStepPin, OUTPUT); 
  digitalWrite(amisDirPin, LOW); 
  pinMode(amisDirPin, OUTPUT); // Give the driver some time to power up. 
  delay(1); // Reset the driver to its default settings. 
  stepper.resetSettings(); // Set the current limit. You should change the number here to // an appropriate value for your particular system. 
  stepper.setCurrentMilliamps(1000); // Set the number of microsteps that correspond to one full step. 
  stepper.setStepMode(32); // Enable the motor outputs. 
  stepper.enableDriver(); 
} 

void setup() { 
  SPI.begin(); 
  Serial.begin(9600); 
  Serial.println("Hello_Motor"); 
  stepper.init(amisSlaveSelect1); // Drive the NXT/STEP and DIR pins low initially. 
  digitalWrite(amisStepPin, LOW); pinMode(amisStepPin, OUTPUT); 
  digitalWrite(amisDirPin, LOW); pinMode(amisDirPin, OUTPUT); // Give the driver some time to power up. 
  delay(1); // Reset the driver to its default settings. 
  stepper.resetSettings(); // Set the current limit. You should change the number here to // an appropriate value for your particular system. 
  stepper.setCurrentMilliamps(1000); // Set the number of microsteps that correspond to one full step. 
  stepper.setStepMode(32); // Enable the motor outputs. 
  stepper.enableDriver(); 
} 

void loop() { // Step in the default direction 1000 times. 
  slave_select(amisSlaveSelect2); 
  slave_select(amisSlaveSelect3); 
  setDirection(1); 
  for (unsigned int x = 0; x < 4000; x++) { 
    step(); } // Wait for 300 ms. 
    
   delay(300); // Step in the other direction 1000 times. 
   setDirection(1); 
    
   for (unsigned int x = 0; x < 4000; x++) { 
    step(); } // Wait for 300 ms. 
   
  delay(300); 
} // Sends a pulse on the NXT/STEP pin to tell the driver to take // one step, and also delays to control the speed of the motor. 

void step() { // The NXT/STEP minimum high pulse width is 2 microseconds. 
  digitalWrite(amisStepPin, HIGH); 
  delayMicroseconds(3); 
  digitalWrite(amisStepPin, LOW); 
  delayMicroseconds(3); // The delay here controls the stepper motor's speed. You can // increase the delay to make the stepper motor go slower. If // you decrease the delay, the stepper motor will go fast, but // there is a limit to how fast it can go before it starts // missing steps. 
  delayMicroseconds(100); 
} // Writes a high or low value to the direction pin to specify // what direction to turn the motor. 

void setDirection(bool dir) { // The NXT/STEP pin must not change for at least 0.5 // microseconds before and after changing the DIR pin. 
  delayMicroseconds(1); 
  digitalWrite(amisDirPin, dir); 
  delayMicroseconds(1); 
}
