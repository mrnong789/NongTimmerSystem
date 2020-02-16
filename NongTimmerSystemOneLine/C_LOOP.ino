char *result = malloc(7);
int startTime = 0;
void loop() {
  long elapsedTime  =   millis() - startTime;
  long timeAll  = elapsedTime;

  int digitSec = timeAll / 1000;
  int digitMilisec = timeAll % 1000;
  sprintf(result, "%02d.%03d ",digitSec ,digitMilisec);
  Serial.println(digitSec);
  if(digitSec >= 99){
   
   dmd.drawString(8,1,"00.000 ");
   startTime = millis();
   
  }else{
     dmd.drawString(8,1,result);
  }
}
