
// Number of P10 panels used X, Y
SoftDMD dmd(2,1);

// Set Box (dmd, x, y, Height, Width) 
DMD_TextBox box(dmd, 2, 1, 16, 64); 


void setup() {
  // pinMode(PIN_SEGMENT_CLOCK, OUTPUT);
  Serial.begin(9600);
  dmd.setBrightness(10); // Set brightness 0 - 255 
  dmd.selectFont(Arial_Black_16); // Font used
  dmd.begin();     // Start DMD 
  box.print("NONG TIMER SYSTEM"); // Display TEXT SFE
}
