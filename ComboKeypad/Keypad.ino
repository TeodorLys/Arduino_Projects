//USER VARIABLES, Variables that YOU change for YOUR preferences
const int buttons[] {7, 6, 5, 4};   //The PIN of all of the buttons

const int combination[] = {3, 1, 2, 4};  //what the combination is, to add just add a "," and a number

const int numOfCombos = sizeof(combination) / sizeof(combination[0]);   //How many combinations

const int numOfButtons = sizeof(buttons) / sizeof(buttons[0]);   //How many buttons you have

const bool useFiveVoltpin = false;   //Change this if you want to use the
///////////////////////////////////////5Volt PIN instead of PIN 2(IN MY CASE)
//USER VARIABLES, Variables that YOU change for YOUR preferences | end
///
bool doonce = false;   //Button stopper
int count = 0;   //How many buttens that have been pressed
int input[numOfCombos]; //Saves what the user has clicked
//
const int del = 10000;   //Timer, if user inputs a number
///////////////////////////and not inputs another within 10 seconds program will reset
unsigned long time;
short int buttonsRead[numOfButtons];   //Stores the "digitalRead()" of buttons[]
const short int buttonStream = 2;   //Electricity for the buttons, didnt really know how to name this one so buttonStream it is
const short int rightLight = 9;   //Correct combo PIN, "Green" light
const short int wrongLight = 8;   //Incorrect combo PIN, "Red" Light
///
//Function prototyping
void pressButton(int num, int digRead);
void reset();
void debug();
//Function prototyping

//Function setup
void setup() {
    //Used to be able to add as many buttons as you want
    for(int setb = 0; setb < numOfButtons; setb++){
      pinMode(buttons[setb], INPUT); // sets All Input pin
     }

    pinMode(wrongLight, OUTPUT);   //Wrong Light, "Red" Light
    pinMode(rightLight, OUTPUT);   //Right Light, "Green" Light

  if(!useFiveVoltpin){
  pinMode(buttonStream, OUTPUT);   //Button Stream
  digitalWrite(buttonStream, 1);   //Starts the Electricity for button pull down resistor
}
  Serial.begin(9600); //Debug
}//Setup Function End


//Function loop
void loop() {
    //Gets the Button States
for(int state = 0; state < numOfButtons; state++){
  buttonsRead[state] = digitalRead(buttons[state]); // First Switch
}


  // Debug
  debug();
  // Debug

    //If timer has run out, reset all arrays the count variable
    if(count != 0 && millis() - time > del) {   //Resets if timer runs out
      reset();   //Runs the Reset function
    }

int value = 0;   //how many combos are correct
for(int a = 0; a < numOfCombos; a++){
    if(input[a] == combination[a]){   //Checks if the input and the combo are the same
     value++;   //Adds one if combo is correct
    }
}

 //////////////////////////////////////////////////////////////////////////////
 /// Checks if what button the user presses is correct                          ///
 //////////////////////////////////////////////////////////////////////////////
 if(value == numOfCombos) { // Correction number
   digitalWrite(9, 1); //Corrections Light
    Serial.println("Correct");   //Prints "Correct" if user enters the correct combo
     delay(3000);   //Safety delay
      reset(); // Resets Everything
 }

///////////////////////////////////////////////////////////////////////////////
/// If the combo number limit is reached                                    ///
/// and some or all are wrong                                               ///
/// \                                                                       ///
/// this for loop is here to be able to customize this code                 ///
/// to add any amount of combinations and buttons                           ///
///////////////////////////////////////////////////////////////////////////////
for(int a = 0; a < numOfCombos; a++){
  if(input[a] != combination[a] && count == numOfCombos){
    digitalWrite(wrongLight, 1);   //Lights up the "Red" button
     Serial.println("Wrong");   //Prints that the combination is wrong
      delay(100);   //Safety delay
       reset();   //Runs the reset function
  }
}

// Which number I have input
if (count < numOfCombos) { // Restricts the variable to not go over 4

  //Start of Combo,('(Badger and Skinny Pete)')
  for(int a = 0; a < numOfButtons; a++){
    pressButton(a, buttonsRead[a]);   //Runs the function pressButton
////////////////////////////////////////to save the button press and
////////////////////////////////////////add to the counter
  }
}

}   //Function Loop end


//Function pressButton, If user presses a Button
void pressButton(int num, int digRead){
  if (digRead == 1 && doonce != true) { // If I hit a Button
   time = millis();   //Starts the 10 second timer
    input[count] = num + 1; // sends the number 1 into the array at the "count number"
     count++; // Where to put 4 into the array
      doonce = true;
    }
    int exists;

      for(int a = 0; a < numOfButtons; a++){
        if(buttonsRead[a] == 0){
          exists++;
        }
      }

      //////////////////////////////////////////////////////////////////////
      /// So the it doesnt go ON and OFF infinitly, Basically a stopper  ///
      /// If no button is pressed reset the doonce                       ///
      //////////////////////////////////////////////////////////////////////
      if (exists == numOfButtons && doonce == true){
         doonce = false;
          delay(50);
        }
}   //Function pressButton end

// Functions "Reset",
void reset() {
  for (int inputIndex = 0; inputIndex < numOfCombos; inputIndex++) {   //You could aparently declare an int in a for loop... C++ Style?
    input[inputIndex] = 0;   //Zeros the input array
  }

    time = millis();   //Sets this to 0 because it might be a bugg there
     digitalWrite(rightLight, 0);   //Turns the "Green" light off
      digitalWrite(wrongLight, 0);   //Turns the "Red" light off
       count = 0;  //Sets the counter to 0

}//Function Reset end

//Function Debug, Prints the count, and what has been pressed
void debug(){
  Serial.print("Count = ");
   Serial.print(count);
    Serial.print(", |");
     for(int a = 0; a < numOfCombos; a++){
      Serial.print(input[a]);   //Prints which number has been pressed
    }
       Serial.println();
}
