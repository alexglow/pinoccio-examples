#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>

/** Capacitive Sense Library **/
/** http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense **/
#include <CapacitiveSensor.h>

/** Creation of touch objects **/
CapacitiveSensor   cap_P = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_I = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_N = CapacitiveSensor(0, 0);
CapacitiveSensor   cap_O = CapacitiveSensor(0, 0);

long total_P, total_I, total_N, total_O;
bool pPushed, iPushed, nPushed, oPushed;

void setup() {
  Scout.setup();

  /** Configure send and receive pins **/
  /** CapacitiveSensor(sendPin, receivePin) **/
  cap_P = CapacitiveSensor(8, A3);
  cap_P.set_CS_AutocaL_Millis(100);  // Turn off autocalibrate
  cap_P.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
  
  cap_I = CapacitiveSensor(8, A6);
  cap_I.set_CS_AutocaL_Millis(100);  // Turn off autocalibrate
  cap_I.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
  
  cap_N = CapacitiveSensor(8, A4);
  cap_N.set_CS_AutocaL_Millis(100);  // Turn off autocalibrate
  cap_N.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
  
  cap_O = CapacitiveSensor(8, A5);
  cap_O.set_CS_AutocaL_Millis(100);  // Turn off autocalibrate
  cap_O.set_CS_Timeout_Millis(100);         // Set Timeout to 100 ms
}

void loop() {
   Scout.loop();
   char buf[32];
   
   /** Read capacitive electrodes **/
   /** capacitiveSensor(numberOfSamples) **/
   total_P =  cap_P.capacitiveSensor(5);
   delay(2);
   total_I =  cap_I.capacitiveSensor(5);
   delay(2);
   total_N =  cap_N.capacitiveSensor(5);
   delay(2);
   total_O =  cap_O.capacitiveSensor(5);
   delay(2);
   
   /** Read if buttons are pressed **/
   if (total_P > 10) {
     if (pPushed == false) {
       pPushed = true;
       snprintf(buf, sizeof(buf), "on.cp.high");
       if (findscript(buf)) {
         doCommand(buf);
       }
     }
   } else if (total_P <= 10) {
     if (pPushed == true) {
       pPushed = false;
       snprintf(buf, sizeof(buf), "on.cp.low");
       doCommand(buf);
     }
   }   
   if (total_I > 10) {
     if (iPushed == false) {
       iPushed = true;
       snprintf(buf, sizeof(buf), "on.ci.high");
       doCommand(buf);
     }
   } else if (total_I <= 10) {
     if (iPushed == true) {
       iPushed = false;
       snprintf(buf, sizeof(buf), "on.ci.low");
       doCommand(buf);
     }
   }   
   if (total_N > 10) {
     if (nPushed == false) {
       nPushed = true;
       snprintf(buf, sizeof(buf), "on.cn.high");
       doCommand(buf);
     }
   } else if (total_N <= 10) {
     if (nPushed == true) {
       nPushed = false;
       snprintf(buf, sizeof(buf), "on.cn.low");
       doCommand(buf);
     }
   } 
   if (total_O > 10) {
     if (oPushed == false) {
       oPushed = true;
       snprintf(buf, sizeof(buf), "on.co.high");
       doCommand(buf);
     }
   } else if (total_O <= 10) {
     if (oPushed == true) {
       oPushed = false;
       snprintf(buf, sizeof(buf), "on.co.low");
       doCommand(buf);
     }
   }
   
   delay(10);
}
