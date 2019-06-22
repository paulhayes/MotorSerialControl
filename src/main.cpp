#include <Arduino.h>
#include <Settings.h>
#include <readline.h>
#include <Commands.h>
#include "main.h"

const int dirPin1 = 7;
const int dirPin2 = 8;
const int dirPin3 = 9;
const int dirPin4 = 10;
const int pwmPin = 6;

const int bufLen = 32;
char buffer[bufLen];

int speed = 0;
Commands commands;

void setup(){
    pinMode(dirPin1,OUTPUT);
    pinMode(dirPin2,OUTPUT);
    pinMode(pwmPin,OUTPUT);


    int t = 0;
    setSpeed(&t);
    
    
    while(!Serial)
        delay(500);

    Serial.begin(115200);

    commands.registerCommand("S%d",setSpeed);
    commands.registerCommand("s%d",setSpeed);

}

void loop(){
    if(readline(buffer,bufLen)){
        if( commands.parseCommands(buffer) ){
            Serial.println("ok");
        }
        else {
            Serial.println("invalid command");
        }
    }
}

void setSpeed(void *data){
    speed = * (int *) data; 
    analogWrite(pwmPin,abs(speed));
    digitalWrite(dirPin1,speed>0?HIGH:LOW);
    digitalWrite(dirPin2,speed<0?HIGH:LOW);
}