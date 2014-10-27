/* In which Eric Jennings combines the Pinoccio bootstrap with kitschpatrol's
Brain library for the NeuroSky MindFlex: https://github.com/kitschpatrol/Brain
Eric's notes:
You can get the signal strength, attention, and meditation values directly by 
calling the scoutscript:  `print brain.signal`, `print brain.attention`, or 
`print brain.meditation`.  You can also define event handlers for `on.brain.signal`, 
`on.brain.attention`, or `on.brain.meditation` that are Scoutscript functions, 
and they’ll fire whenever the values update.
*/

#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>
 
#include <Brain.h>
 
#include "version.h"
 
// hook up the Neurosky to Serial 1 (RX1/TX1)
Brain brain(Serial1);
// const int ledPin = 2; // got a big red LED stuck in d2
// int ledState = LOW;     
 
void setup() {
  Scout.setup(
  );
  // Add custom setup code here
  
//  pinMode(ledPin, OUTPUT);
  
  Serial1.begin(57600);
//  addBitlashFunction("brain.signal", (bitlash_function)signal);
//  addBitlashFunction("brain.attention", (bitlash_function)attention);
//  addBitlashFunction("brain.meditation", (bitlash_function)meditation);
}
 
void loop() {
  Scout.loop();
  // Add custom loop code here
  
  char buf[32];
  
  // Expect packets about once per second.
   //if (brain.update()) {
   if (Serial1.available()) {
//    Serial.println(brain.readErrors());
//    Serial.println(brain.readCSV());
    int inByte = Serial1.read();
    Serial.print(inByte, DEC);
    
/*   if (ledState == LOW)
     ledState = HIGH;
   else
     ledState = LOW;
//   Set the LED with the ledState of the variable:
   digitalWrite(ledPin, ledState);
*/    
    // signal
    snprintf(buf, sizeof(buf), "on.brain.signal(%d)", brain.readSignalQuality());
    if (findscript(buf)) {
      doCommand(buf);
    }
    // attention
    snprintf(buf, sizeof(buf), "on.brain.attention(%d)", brain.readAttention());
    if (findscript(buf)) {
      doCommand(buf);
    }
    // meditation
    snprintf(buf, sizeof(buf), "on.brain.meditation(%d)", brain.readMeditation());
    if (findscript(buf)) {
      doCommand(buf);
    }
  }
}
 
numvar signal() {
  return brain.readSignalQuality();
}
 
numvar attention() {
  return brain.readAttention();
}
 
numvar meditation() {
  return brain.readMeditation();
}
