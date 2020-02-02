void loop() {
  long elapsedTime  =   millis() - startTime;
  long timeAll  = elapsedTime;
  if(timeAll >= 99899){
   box.print("0"); // Display TEXT SFE
    startTime = millis();
     Serial.println(0);
  }else{
       Serial.println(timeAll);
      box.print(timeAll); // Display TEXT SFE
  }
 
}
