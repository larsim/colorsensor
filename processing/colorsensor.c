import processing.serial.*;
 
// Preambles to search for in serial data
// This is to keep the red, green and blue in sync
int PREAMBLE_A = 0xff;
int PREAMBLE_B = 0xaa;
 
// Working variables and objects
Serial arduinoPort;
int red=0, green=0, blue=0;
 
void setup() 
{
  // Set up main window
  size(200, 200);   
  background(0); 
  
  // Set up serial connection
  arduinoPort = new Serial(this, "COM7", 9600);
}
 
void draw()
{
  // Wait for a packet of >= 5 bytes
  if (arduinoPort.available() >= 5) {         
    if (arduinoPort.read() == PREAMBLE_A) {            
      if (arduinoPort.read() == PREAMBLE_B) {
        // Got both preamble bytes, read colors
        red = arduinoPort.read();
        green = arduinoPort.read();
        blue = arduinoPort.read();
        
        // Output color to console
        print("Got color: " + red + "," + green + "," + blue + "\n");
      }
    }
  }
  
  // Output color to main window
  background(255);
  fill(red, green, blue);
  rect(50, 50, 100, 100);
}
