#include "LedControl.h"

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 6 is connected to the DataIn
  pin 9 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
LedControl segmentDisplay = LedControl(6, 9, 10, 1);



long startTime1 = 0;

bool startedLine1 = false;
bool finishedLine1 = false;


static int buttonReset = 3;

static int sensorInnitLine1 = 7;
static int sensorStartLine1 = 11;
static int sensorFinishLine1 = 8;

void setup() {

  delay(150);
  segmentDisplay.shutdown(0, false);
  /* Set the brightness to a medium values */
  segmentDisplay.setIntensity(0, 8);
  /* and clear the display */
  segmentDisplay.clearDisplay(0);


  pinMode(buttonReset, INPUT);

  pinMode(sensorInnitLine1, INPUT);
  pinMode(sensorStartLine1, INPUT);
  pinMode(sensorFinishLine1, INPUT);


}


void loop() {


  if (digitalRead(buttonReset)) { //reset button
    startedLine1 = false;
    finishedLine1 = true;

    segmentDisplay.setDigit(0, 4, 0, false);
    segmentDisplay.setDigit(0, 3, 0, true);
    segmentDisplay.setDigit(0, 2, 0, false);
    segmentDisplay.setDigit(0, 1, 0, false);
    segmentDisplay.setDigit(0, 0, 0, false);

  }

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
    long _time_milli = _timeAll % 1000;
    long _time_digit1 = _timeAll / 1000;
    long _time_digit2 = _time_milli / 100;
    long _time_digit3 = (_time_milli % 100) / 10;
    long _time_digit4 = ((_time_milli % 100) % 10);

    if (_time_digit1 < 10) {
      segmentDisplay.setDigit(0, 4, 0, false);
      segmentDisplay.setDigit(0, 3, _time_digit1, true);
      segmentDisplay.setDigit(0, 2, _time_digit2, false);
      segmentDisplay.setDigit(0, 1, _time_digit3, false);
      segmentDisplay.setDigit(0, 0, _time_digit4, false);

    } else if (_time_digit1 >= 10) {
      segmentDisplay.setDigit(0, 4, _time_digit1 / 10, false);
      segmentDisplay.setDigit(0, 3, _time_digit1 % 10, true);
      segmentDisplay.setDigit(0, 2, _time_digit2, false);
      segmentDisplay.setDigit(0, 1, _time_digit3, false);
      segmentDisplay.setDigit(0, 0, _time_digit4, false);
    }


  }



}

