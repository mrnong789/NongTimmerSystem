unsigned long startTime = 0;
//char *result = "      \0";
char *result = malloc(7);
int startState = 1;
int stopState = 1;
bool stateCurrent = false;

void loop() {
  
  startState = digitalRead(sensorStart);
  stopState = digitalRead(sensorStop);
  
  if(stateCurrent == false && startState == 0){
    stateCurrent = true;
    startTime = millis();
  }
  
  if(stateCurrent == true && stopState == 0){
    stateCurrent = false;
  }
  
 if(stateCurrent == true) {
  unsigned long elapsedTime =  millis() - startTime;
  unsigned int digitSec = (elapsedTime / 1000);
  unsigned int digitMilisec = elapsedTime % 1000;
  sprintf(result, "%02d.%03d ",digitSec ,digitMilisec);
  dmd.drawString(8,1,result);
 }
}

