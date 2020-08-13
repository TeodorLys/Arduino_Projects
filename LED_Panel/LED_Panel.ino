#include <LedControl.h>
#include "Letters.h"
#include "Letter_Array.h";
Letter_Array la;

unsigned long time;

int count = 0;
void setup() {
  //Serial.begin(9600);
  la.Init_Panels();
  la.set_String("teodorlys");
  time = millis();
}

void loop() {
   la.draw();

  delay(5);
  la.Move_Left(1);
  //delay(5);
}
