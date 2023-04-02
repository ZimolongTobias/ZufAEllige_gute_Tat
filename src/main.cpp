// include the Arduino standard library
#include <Arduino.h>
#include <Servo.h>
#include "pitches.h"
#include <Time.h>

// If servos are added, the PIN should be added, a new servo should be created and some functions should be slightly adapted.
#define SERVO1_PIN 5
#define SERVO2_PIN 7
#define SERVO3_PIN 3
//#define SERVO4_PIN X
//#define SERVO5_PIN Y
#define BUTTON_PIN 9
#define LED_GREEN_PIN 2
#define LED_RED_PIN 5
#define SPEAKER_PIN A4

// The soundduration and the soundPause between the tones of the melody.
int soundDuration = 150; // milliseconds
int soundPause = 275; // milliseconds

// Create four servoobjects.
Servo myServo1;
Servo myServo2;
Servo myServo3;
//Servo myServo4;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

// const will not change:
const int numServos = 3; // Number of attached servos.
const int standardPosition = 50; // Value for the standardposition of the servos.
const int ejectionPosition = 95; // Value for the ejectionposition of the servos.

// This returns a randomly myServo1, myServo2 or myServo3. If servos are added random() should be adopted
// and the additional servos should be added.
Servo randomServo() {
  static bool srand_called = false;
  if (!srand_called) {
    srand(time(nullptr));
    srand_called = true;
  }
  
  int randomNumber = random(3) + 1;
  Serial.println("numServos");
  Serial.println(numServos);
  Serial.println("randomNumber");
  Serial.println(randomNumber);
  
  switch (randomNumber) {
    case 1:
      return myServo1;
    case 2:
      return myServo2;
    case 3:
      return myServo3;
    // Additional servos should be added here.
    //case 4:
    //  return myServo4;
    // case 5: 
    //   return myServo5;
    // case 6: 
    //   return myServo6;
    // ...
    default:
      Serial.println("Error: randomServo selected invalid servo number.");
      return myServo1; // Return a default servo if something goes wrong.
  }
}



// Attaches the hardware to the pins defined above in #define.
void attachingServos() {
  myServo1.attach(SERVO1_PIN);
  myServo2.attach(SERVO2_PIN);
  myServo3.attach(SERVO3_PIN);
  //myServo4.attach(SERVO4_PIN);
  //myServo5.attach(SERVO5_PIN);
}

// Configures the specified pin to behave either as an input or an output.
void pinModeCreating() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
}

// Sets the startingposition of the servos.
void positionAtSetup() {
  myServo1.write(standardPosition);
  myServo2.write(standardPosition);
  myServo3.write(standardPosition);
  // myServo4.write(standardPosition);
  // myServo5.write(standardPosition);
}

// Attaches the Servos, configures the pins, set the position of all servos to the same value and
// calls the randomSeed() function, which seeds the random number generator 
// on the Arduino board with a value obtained by reading the analog input on pin 0.
void setup() {
  attachingServos();
  pinModeCreating();
  positionAtSetup();
  randomSeed(analogRead(0));
}

// The melody of the Hot Butter - Popcornsong using pitches.h. The delays should not be removed, so the button
// can not be pressed multiple times.
void melody() {
  tone(SPEAKER_PIN, NOTE_B5, soundDuration);
  delay(soundPause);
  tone(SPEAKER_PIN, NOTE_A5, soundDuration);
  delay(soundPause);
  tone(SPEAKER_PIN, NOTE_B5, soundDuration);
  delay(soundPause);
  tone(SPEAKER_PIN, NOTE_FS5, soundDuration);
  delay(soundPause);
  tone(SPEAKER_PIN, NOTE_D5, soundDuration);
  delay(soundPause);
  tone(SPEAKER_PIN, NOTE_FS5, soundDuration);
  delay(soundPause);
  tone(SPEAKER_PIN, NOTE_B4, soundDuration);
  delay(soundPause);
  delay(1000);
}

// If LEDs are used, this function can also be used. The functions should than be commented out at buttonPressed() and buttonNotPressed()
// If a LED is used, this function turns off a LED at the LED_GREEN_PIN PIN and turns on a LED on
// the LED_RED_PIN PIN.
void greenOffRedOn() {
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
}

// If a LED is used, this function turns on a LED at the LED_GREEN_PIN PIN and turns off a LED on
// the LED_RED_PIN PIN.
void greenOnRedOff() {
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
}

// This function runs the popcornmelody, select randomly one of the servos and runs the ejectionprocess. At the end
// the servo goes back to the standardposition.
void buttonPressed() {
  //greenOffRedOn();
  melody();
  Servo selectedServo = randomServo();
  selectedServo.write(ejectionPosition);
  Serial.println("Button pressed");
  delay(1000);
  selectedServo.write(standardPosition);
}

// This function is not used at the moment in loop(). If you want to use it comment it out at loop().
void buttonNotPressed() {
  Serial.println("Button NOT pressed");
  //greenOnRedOff();
}

void loop() {
// read the state of the button value:
    buttonState = digitalRead(BUTTON_PIN);

    // Check if the button is pressed. If it is, buttonPressed is executed.
    if (buttonState == HIGH) {
        buttonPressed();

    // If the button is not pressed, buttonNotPressed is executed. This can be commented out, if you use buttonNotPressed
    // for printing or for LEDs for example.
    // } else {
    //    buttonNotPressed();
    }
}