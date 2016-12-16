// 
// Pin configuration
// - Change these
// 
#define PIN_OE  3
#define PIN_OUT 2
#define PIN_S0  5
#define PIN_S1  4
#define PIN_S2  6
#define PIN_S3  7
 
//
// Frequency scaling
//
#define FREQSCALE_POWERDOWN 0
#define FREQSCALE_2   1
#define FREQSCALE_20  2
#define FREQSCALE_100 3
 
int freqScaleTable[4][2] = {{LOW,LOW},{HIGH,LOW},{LOW,HIGH},{HIGH,HIGH}};
 
// Set frequency scaling
void tcs3200_setFreqScale(int freqScale)
{   
  digitalWrite(PIN_S0, freqScaleTable[freqScale][1]);
  digitalWrite(PIN_S1, freqScaleTable[freqScale][0]); 
}
 
//
// Color set-up
//
#define COLOR_RED 0
#define COLOR_BLUE 1
#define COLOR_CLEAR 2
#define COLOR_GREEN 3
 
int colorTable[4][2] = {{LOW,LOW},{HIGH,LOW},{LOW,HIGH},{HIGH,HIGH}};
 
// Set color
void tcs3200_setColor(int color)
{
  digitalWrite(PIN_S2, colorTable[color][1]);
  digitalWrite(PIN_S3, colorTable[color][0]); 
}
 
//
// Color functions
//
 
void tcs3200_init()
{
 // Pin modes
 pinMode(PIN_OE, OUTPUT);
 pinMode(PIN_OUT, INPUT);
 pinMode(PIN_S0, OUTPUT);
 pinMode(PIN_S1, OUTPUT);
 pinMode(PIN_S2, OUTPUT);
 pinMode(PIN_S3, OUTPUT); 
 
  // Enable f0
  digitalWrite(PIN_OE, LOW);
  
  // Set frequency scaling to 2
  //  Gives better accuracy with the slow arduino
  tcs3200_setFreqScale(FREQSCALE_2);
}
 
unsigned long tcs3200_getRed()
{
  tcs3200_setColor(COLOR_RED);
  delay(10); 
  return pulseIn(PIN_OUT, HIGH);
}
 
unsigned long tcs3200_getGreen()
{
  tcs3200_setColor(COLOR_GREEN);
  delay(10); 
  return pulseIn(PIN_OUT, HIGH);  
}
 
unsigned long tcs3200_getBlue()
{
  tcs3200_setColor(COLOR_BLUE);
  delay(10); 
  return pulseIn(PIN_OUT, HIGH);  
}
 
unsigned long tcs3200_getAll()
{
  tcs3200_setColor(COLOR_CLEAR);
  delay(10); 
  return pulseIn(PIN_OUT, HIGH);  
}
 
//
// setup and loop
//
 
unsigned long red=0, green=0, blue=0, all=0;
 
void setup() 
{
  tcs3200_init();  
  Serial.begin(9600);
}
 
void loop() 
{    
  // Get colors
  red = 85000/tcs3200_getRed();
  green = 100000/tcs3200_getGreen(); 
  blue = 100000/tcs3200_getBlue(); 
  
  // Sum all colors
  all = red + green + blue;
 
  // Output to serial 
  Serial.write((unsigned char)0xff); // Preamble
  Serial.write((unsigned char)0xaa); // Preamble
  Serial.write((unsigned char)red);  
  Serial.write((unsigned char)green); 
  Serial.write((unsigned char)blue); 
 
  // Wait before next cycle 
  delay(200);
}
