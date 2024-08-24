/*
 * Autor: Ignazio Leonardo Calogero Sperandeo
 * Date: 27/12/2023
 * Project: Particular Power Strip(PPS)
 * by jim_bug :)
 * 
 * Command from device:
 * 0: on/off socket 1
 * 1: on/off socket 2
 * 2: on/off socket 3
 * 3: on/off socket 4
 * N: States of socket
*/

#include <SoftwareSerial.h>
#define LEN 4
#define START_PIN 12
#define END_PIN 9
SoftwareSerial btserial(0, 1);  // rx tx pin
int pinPrese[LEN];
int statusPrese[LEN];   // reverse logic 0=true 1=false
int printState = 0;
int i = 0;
char code;

void setup(){
  Serial.begin(9600);
  btserial.begin(9600);
  // Serial.println("Particolar Power Strip by jim_bug :)");
  for(int i = START_PIN;i >= END_PIN; i--){
    pinPrese[START_PIN-i] = i;
    statusPrese[START_PIN-i] = 1;   
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);          // de-exciting every relay, so every socket state are HIGH
  }
}

void loop(){
  if(btserial.available()){       // blocking function
    if(printState == 0){
      code = btserial.read();
      if(code == 'N'){
        
        printState = 1;  
      }
    }
    // Serial.print("I've recived: ");
    // Serial.println(code);
    if(((int)code >= 48 && (int)code <= (48+LEN)-1)){     // modify the state of a choising socket
        statusPrese[(int)code-48] = !statusPrese[(int)code-48];
        digitalWrite(pinPrese[(int)code-48], statusPrese[(int)code-48]);
    }
  }
  else if(printState){
        if(i < LEN){
          if(statusPrese[i] == 1){
              Serial.print(i+1);
              Serial.println(") Socket State: DISACTIVE");
          }
          else{
              Serial.print(i+1);
              Serial.println(") Socket State: ACTIVE");
          }
          i++;
      }
      else{
        i = 0;
        printState = 0;
      }
    }
}
// :)
