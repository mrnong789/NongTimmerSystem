SoftDMD dmd(2,1);
// Number of P10 panels used X, Y
DMD_TextBox box(dmd, 0, 1, 64, 16); 
// Set Box (dmd, x, y, Height, Width) 

const int sensorStart = 2;
const int sensorStop = 3; 

void setup() {
  Serial.begin(9600);
  pinMode(sensorStart, INPUT);
  pinMode(sensorStop, INPUT);
  dmd.setBrightness(10); // Set brightness 0 - 255 
  dmd.selectFont(Arial_Black_16); // Font used
  dmd.begin();     // Start DMD 
 // box.print("00.000"); // Display TEXT SFESS
}
