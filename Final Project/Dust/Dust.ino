//for sg90
#include <Servo.h> 
#define PIN_SERVO 9
#define PIN_SERVO 10
Servo myservo,myservo2;
             
//for ws2812
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif 
#define PIN        8
#define NUMPIXELS 10 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50
int count = 180;
int vel = -10;
int angle = 0;
  //for gp2y1010
int measurePin = A5;            
int ledPower = 2; 
unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680; 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
//for mq2
int MQ2=A0;
int val=0;
 Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_RGB + NEO_KHZ800);
void setup(){
  Serial.begin(9600);
  //for gp2y1010
  pinMode(ledPower,OUTPUT);
  //for ws2812
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  //for sg90
    myservo.attach(PIN_SERVO);
 //for mq2
      pinMode(MQ2,INPUT);
       #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop(){
 colorWipe(strip.Color(255, 0, 0), 50); // Red
  //for gp2y1010
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime); 
  voMeasured = analogRead(measurePin); 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime); 
  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1; 
  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }


    val=analogRead(MQ2);
 if(val>300){
   colorWipe(strip.Color(255, 0, 0), 50); // Red
  }
   if(dustDensity>0.2){
   colorWipe1(strip.Color(255, 0, 0), 50); // Red
  }
  
 
// for sg90

  
int anglle1 = map(val,100,660,360,0);
int anglle2 = map(dustDensity,0,0.5,360,0);
    
  myservo.write(anglle1);
  myservo2.write(anglle2);
  Serial.println(anglle1);
//  Serial.println(anglle1);
  delay(500); 
//  Serial.println(dustDensity);

 
//  delay(1000);
}
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<20; i++) {
    strip.setPixelColor(i, c);
    strip.show();
//    delay(wait);
  }
}
void colorWipe1(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<20; i++) {
    strip.setPixelColor(i, c);
    strip.show();
//    delay(wait);
  }
}
