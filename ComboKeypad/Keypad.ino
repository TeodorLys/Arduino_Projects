

//
//USER VARIABLES, Variables that YOU change for YOUR preferences
const int buttons[] {7, 6, 5, 4};   //The PIN of all of the buttons

const int combination[] = {3, 1, 2, 4};  //what the combination is

const bool useFiveVoltpin = false;   //Change this if you want to use the
///////////////////////////////////////5Volt PIN instead of PIN 2(IN MY CASE)
/*----(USER VARIABLES END)----*/

const int numOfCombos = sizeof(combination) / sizeof(combination[0]);   //How many combinations
const int numOfButtons = sizeof(buttons) / sizeof(buttons[0]);   //How many buttons you have

bool doonce = false;   //Button stopper
int count = 0;   //How many buttens that have been pressed
int input[numOfCombos]; //Saves what the user has clicked
//

const int del = 10000;   //Timer(10s), if user inputs a number
                               //and not inputs another within 10 seconds program will reset
unsigned long time;
int buttonsRead[numOfButtons];   //Stores the "digitalRead()" of buttons[]
const int buttonStream = 2;   //Electricity for the buttons, didnt really know how to name this one so buttonStream it is
const int rightLight = 9;   //Correct combo PIN, "Green" light
const int wrongLight = 8;   //Incorrect combo PIN, "Red" Light
///
/*----(Function prototyping)----*/
void pressButton(int num, int digRead);
void reset();
void debug();


/*----(Function setup)----*/
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
}/*----(Setup Function End)----*/


/*----(Function loop)----*/
void loop() {
    //Gets the Button States
for(int state = 0; state < numOfButtons; state++){
  buttonsRead[state] = digitalRead(buttons[state]); // First Switch
}


  //Debug
  debug();

    //If timer has run out, reset all arrays the count variable
    if(count != 0 && millis() - time > del) {   //Resets if timer runs out
      reset();
    }

int value = 0;   //how many combos are correct
for(int a = 0; a < numOfCombos; a++){
    if(input[a] == combination[a]){   //Checks if the input and the combo are the same
     value++;   //Adds one if combo is correct
    }
}

 //////////////////////////////////////////////////////////////////////////////
 /// Checks if what button the user presses is correct                      ///
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
    digitalWrite(wrongLight, 1);   //Lights up the "red" button
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

}/*----(Function Loop END)----*/

//////////////////////////////////////////////////////

/*(—