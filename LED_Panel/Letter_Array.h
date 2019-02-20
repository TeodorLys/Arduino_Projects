#ifndef _H_LETTER_ARRAY
#define _H_LETTER_ARRAY

#include "Letters.h"
#include <LedControl.h>
#include <Arduino.h>

//#define REVERSED

struct String_Convert{
  byte *letter_Form;
  char letter;

 String_Convert(byte *lc, char c) : letter_Form(lc), letter(c){}

String_Convert(){}

};

const String_Convert Char_A[] = {String_Convert(letters::Letter_A, 'A'),
                          String_Convert(letters::Letter_B, 'B'),
                          String_Convert(letters::Letter_C, 'C'),
                          String_Convert(letters::Letter_D, 'D'),
                          String_Convert(letters::Letter_E, 'E'),
                          String_Convert(letters::Letter_F, 'F'),
                          String_Convert(letters::Letter_G, 'G'),
                          String_Convert(letters::Letter_H, 'H'),
                          String_Convert(letters::Letter_I, 'I'),
                          String_Convert(letters::Letter_J, 'J'),
                          String_Convert(letters::Letter_K, 'K'),
                          String_Convert(letters::Letter_L, 'L'),
                          String_Convert(letters::Letter_M, 'M'),
                          String_Convert(letters::Letter_N, 'N'),
                          String_Convert(letters::Letter_O, 'O'),
                          String_Convert(letters::Letter_P, 'P'),
                          String_Convert(letters::Letter_Q, 'Q'),
                          String_Convert(letters::Letter_R, 'R'),
                          String_Convert(letters::Letter_S, 'S'),
                          String_Convert(letters::Letter_T, 'T'),
                          String_Convert(letters::Letter_U, 'U'),
                          String_Convert(letters::Letter_V, 'V'),
                          String_Convert(letters::Letter_W, 'W'),
                          String_Convert(letters::Letter_X, 'X'),
                          String_Convert(letters::Letter_Y, 'Y'),
                          String_Convert(letters::Letter_Z, 'Z'),
                          String_Convert(letters::Letter_SPACE, (char)32),
                          String_Convert(letters::Letter_FORWARD_SLASH, '/'),
                          String_Convert(letters::Letter_BACKWARD_SLASH, '\\'),
                          String_Convert(letters::Letter_COLON, ':'),
                          String_Convert(letters::Letter_DOT, '.')
};

class Letter_Array{
private:
  static const byte MAX_Screen_Number = 125;
   volatile byte Screen_Number = 0;
   volatile byte Screen_Buffer_Size = 0;
  //byte Screen[Screen_Buffer_Size*8];
  byte Screen2[8*MAX_Screen_Number];
  String display = "";
  LedControl *Panels;
  bool changed = true;
  byte Buffer_Panel0[8];
  byte Buffer_Panel1[8];
  byte Buffer_Panel2[8];
  byte Buffer_Panel3[8];
  byte Buffer_Panel4[8];
  byte Buffer_Panel5[8];
public:

Letter_Array() {
  Panels = new LedControl(4,2,3,6);
}

void set_String(String s){
  s.toUpperCase();
  display = s;

  if(display.length() >= 125)
    Screen_Number = MAX_Screen_Number;
  else
    Screen_Number = display.length() + 1;

Screen_Buffer_Size = 8 * Screen_Number;

int revBit = 7;
  for(int a = 0; a < Screen_Number; a++){
    for(int b = 0; b < 31; b++){
      if(display[a] == Char_A[b].letter){
        for(int bit_Row = 0; bit_Row < 8; bit_Row++){
          Screen2[bit_Row * Screen_Number + a] = Char_A[b].letter_Form[bit_Row];
        }
      }
    }
  }

}

void draw(){
  if(changed){
    int c = 7;
    for(int b = 0 ; b < 8; b++){
        Buffer_Panel0[b] = Screen2[b * Screen_Number + 0];
        Buffer_Panel1[b] = Screen2[b * Screen_Number + 1];
        Buffer_Panel2[b] = Screen2[b * Screen_Number + 2];
        Buffer_Panel3[b] = Screen2[b * Screen_Number + 3];
        Buffer_Panel4[b] = Screen2[b * Screen_Number + 4];
        Buffer_Panel5[b] = Screen2[b * Screen_Number + 5];

    }
    changed = false;
  }

  for (int i = 0; i < 8; i++) {
   Panels->setRow(0,i,Buffer_Panel0[i]);
   Panels->setRow(1,i,Buffer_Panel1[i]);
   Panels->setRow(2,i,Buffer_Panel2[i]);

   Panels->setRow(3,i,Buffer_Panel3[i]);
   Panels->setRow(4,i,Buffer_Panel4[i]);
   Panels->setRow(5,i,Buffer_Panel5[i]);
  }
 }

void Init_Panels(int intensity = 15){
  Panels->shutdown(5,0);  // Wake up displays
  Panels->setIntensity(5,intensity);  // Set intensity levels
  Panels->clearDisplay(5);  // Clear Displays

  Panels->shutdown(4,0);  // Wake up displays
  Panels->setIntensity(4,intensity);  // Set intensity levels
  Panels->clearDisplay(4);  // Clear Displays

  Panels->shutdown(3,0);  // Wake up displays
  Panels->setIntensity(3,intensity);  // Set intensity levels
  Panels->clearDisplay(3);  // Clear Displays

  Panels->shutdown(2,0);  // Wake up displays
  Panels->setIntensity(2,intensity);  // Set intensity levels
  Panels->clearDisplay(2);  // Clear Displays

  Panels->shutdown(1,0);  // Wake up displays
  Panels->setIntensity(1,intensity);  // Set intensity levels
  Panels->clearDisplay(1);  // Clear Displays

  Panels->shutdown(0,0);  // Wake up displays
  Panels->setIntensity(0,intensity);  // Set intensity levels
  Panels->clearDisplay(0);  // Clear Displays
}

void Move_Left(int amount){
  byte test_Bit = 0;
  changed = true;
  byte row_Buffer[Screen_Buffer_Size];

    for(int a = 0; a < 8; a++){
      Buffer_Panel0[a] = 0;
      Buffer_Panel1[a] = 0;
      Buffer_Panel2[a] = 0;
      Buffer_Panel3[a] = 0;
      Buffer_Panel4[a] = 0;
      Buffer_Panel5[a] = 0;
    }

int rev1 = 7;
for(int a  = 0; a < 8; a++){
  for(int b = 0; b < Screen_Number; b++){
    for(int bit = 0; bit < 8; bit++){
      row_Buffer[(bit + (8 * b))] = bitRead(Screen2[a * Screen_Number + b], rev1);
      rev1--;
    }
    rev1 = 7;
  }

  Bit_Progress(0, row_Buffer, Screen_Buffer_Size);

  int rev2 = 7;  // Reset the /*EXTERNAL*/ reversed loop counter.
  for(int row_Bit = 0; row_Bit < Screen_Number; row_Bit++){
    for(int col_bit = 0; col_bit < 8; col_bit++){
        test_Bit |= row_Buffer[row_Bit * 8 + col_bit] << rev2;
        rev2--;
    }
    rev2 = 7;   // Reset the /*EXTERNAL*/ reversed loop counter.
    Screen2[a * Screen_Number + row_Bit] = test_Bit;
    test_Bit = 0;
  }
}
}

inline void Bit_Progress(int direction, byte *row, byte buffersize){
  byte First_Number = 0;
  if(direction == 1){
    for(int b = buffersize - 1; b != -1; b--){
      if(b == buffersize - 1)
        First_Number = row[b];

      if(b != 0)
        row[b] = row[(b - 1)];

      if(b == 0)
        row[b] = First_Number;
    }
  }else {
    for(int b = 0; b < buffersize; b++){
      if(b == 0)
        First_Number = row[b];

      if(b != buffersize - 1)
        row[b] = row[(b + 1)];

      if(b == buffersize - 1)
        row[b] = First_Number;
    }
  }
}

  };
#endif
