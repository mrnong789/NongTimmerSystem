//Nong Timmer System//
//For drag racing
//Create at 2018

#include <Wire.h>
#include <math.h>

// Pin for 7-segment driver
byte segmentClock = 12;
byte segmentLatch = 11;
byte segmentData  = 10;

// Pin button reset
byte buttonReset = 3;

// Pin sensor
byte sensorInnitLine1   = 7;
byte sensorStartLine1   = 8;
byte sensorFinishLine1  = 9;

//Pin led line init
byte ledInnit1 = 2;

// init parameter
long startTime1     = 0;
bool startedLine1   = false;
bool finishedLine1  = false;



void setup() {

  delay(150);
  Wire.begin();

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);

  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

  pinMode(buttonReset, INPUT);
  pinMode(ledInnit1, OUTPUT);

  pinMode(sensorInnitLine1, INPUT);
  pinMode(sensorStartLine1, INPUT);
  pinMode(sensorFinishLine1, INPUT);

  initDisplay();

  DisplayTime(0);

}

// Function split digit from number
unsigned int convertDectoDigit(unsigned long number, int digit) {
  return (number / (int)pow(10, digit)) % 10;
}

// Function Display time
void DisplayTime(unsigned long number) {
  for (int i = 0; i < 5; i++) {
    postNumber(convertDectoDigit(number, i));
  }

  // Latch the current segment data
  digitalWrite(segmentLatch, LOW);
  digitalWrite(segmentLatch, HIGH); // Register moves storage register on the rising edge of RCK
}



// Sends a number to the display
void postNumber(byte number)  {
  //    -  A
  //   / / F/B
  //    -  G
  //   / / E/C
  //    -. D/DP

#define A  1<<0
#define B  1<<6
#define C  1<<5
#define D  1<<4
#define E  1<<3
#define F  1<<1
#define G  1<<2
#define DP 1<<7

  byte segments;

  switch (number) {
    case 1: segments = B | C;
      break;
    case 2: segments = A | B | D | E | G;
      break;
    case 3: segments = A | B | C | D | G;
      break;
    case 4: segments = B | C | F | G;
      break;
    case 5: segments = A | C | D | F | G;
      break;
    case 6: segments = A | C | D | E | F | G;
      break;
    case 7: segments = A | B | C;
      break;
    case 8: segments = A | B | C | D | E | F | G;
      break;
    case 9: segments = A | B | C | D | F | G;
      break;
    case 0: segments = A | B | C | D | E | F;
      break;
  }
  segments |= DP; // Turn on all the decimal point pins as we need them on digit 3 for the colon.

  // Write these bits out to the drivers
  for (byte x = 0; x < 8; x++) {
    digitalWrite(segmentClock, LOW);
    digitalWrite(segmentData, segments & 1 << (7 - x));
    digitalWrite(segmentClock, HIGH); // Data transfers to the register on the rising edge of SRCK
  }
}

void timmerTrick() {
  if (digitalRead(buttonReset)) { //reset button
    startedLine1 = false;
    finishedLine1 = true;
    DisplayTime(0);
  }

  digitalWrite(ledInnit1, digitalRead(sensorInnitLine1));

  if (digitalRead(sensorStartLine1) &&  startedLine1 == false && finishedLine1 == true) //start sensor
  {
    startedLine1 = true;
    finishedLine1 = false;
    startTime1 = millis();
  }

  if (digitalRead(sensorFinishLine1)) { // finish sensor

    startedLine1 = false;
    finishedLine1 = false;

  }

  if (startedLine1 == true)
  {
    long elapsedTime1  =   millis() - startTime1;
    long _timeAll  = elapsedTime1;
    DisplayTime(_timeAll);

  }
}
// Sends a number to the display
void initDisplay() {
  //    -  A
  //   / / F/B
  //    -  G
  //   / / E/C
  //    -. D/DP

#define A  1<<0
#define B  1<<6
#define C  1<<5
#define D  1<<4
#define E  1<<3
#define F  1<<1
#define G  1<<2
#define DP 1<<7

  int counter = 0;
  byte segmemts[] = {0, 6, 5, 4, 3, 1, 2};
  // Write these bits out to the drivers
  while (1) {
    counter++;
    if (counter > 3) return;

    for (byte j = 0; j < 7; j++) {
      for (byte i = 0; i < 5; i++) {
        for (byte x = 0; x < 8; x++) {
          digitalWrite(segmentClock, LOW);
          digitalWrite(segmentData, (1 << segmemts[j]) & 1 << (7 - x));
          digitalWrite(segmentClock, HIGH); // Data transfers to the register on the rising edge of SRCK
        }
      }
      // Latch the current segment data
      digitalWrite(segmentLatch, LOW);
      digitalWrite(segmentLatch, HIGH); // Register moves storage register on the rising edge of RCK

      delay(99);

    }
  }
}

void loop() {

  long elapsedTime1  =   millis() - startTime1;
  long _timeAll  = elapsedTime1;

  DisplayTime(_timeAll);


  //  for(int i=0;i<100000;i++){
  //     DisplayTime(i);
  //     delay(80);
  //
  //    }
}

