#include <Arduino.h>
#include <LiquidCrystal.h>
#include "GUI/GUI.h"

GUI gui;
LiquidCrystal lcd;

void main_menu() {
  
}

void setup() {
  lcd = LiquidCrystal(19, 23, 18, 17, 16, 13); //LCD Pins
  gui = GUI(&lcd, 34, 35, 32, 33); //Encoder + Button Pins
}

void loop() {
  // put your main code here, to run repeatedly:
}