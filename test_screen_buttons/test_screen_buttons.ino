//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(14, 15, 4, 5, 6, 7);

/***************************************/
const int motorIn1 = 20;  //attach to one of the pin of the motor
const int motorIn2 = 21;  //attach to another pin of the motor
const int speakerOut = 19; //piezo speaker
/***************************************/

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//define piezo notes
#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
// Define a special note, 'R', to represent a rest
#define  R     0

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(16);      // read the value from the sensor 
 //Serial.println(adc_key_in, DEC);
 // my buttons when read are centered at these values: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 550)  return btnDOWN; 
 if (adc_key_in < 800)  return btnLEFT; 
 //if (adc_key_in < 850)  return btnSELECT; //select is broken? 
 
 return btnNONE;  // when all others fail, return this...
}

void setup()
{
 pinMode(speakerOut, OUTPUT);
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Welcome to..."); // print a simple message
 delay(500);
 lcd.setCursor(0,0);
 lcd.print("Mr. Skeltal's");
 lcd.setCursor(0,1);
 lcd.print("Spooky Adventure!");
 Serial.begin(9600);
 delay(1000);
 }
 
 // MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 
int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
//int MAX_COUNT = sizeof(melody); // Melody length, for looping.
int MAX_COUNT = 13;
int lengthOfMelody = sizeof(melody);
// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1500;

// Initialize core variables
int tone_ = 0;
int beat = 0;
int currentStep = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else {
      delayMicroseconds(duration);                               
  }                                 
}
void playSong(){
   for (int i=0; i<MAX_COUNT; i++) 
     {
     currentStep = i%lengthOfMelody;
     tone_ = melody[currentStep];
     beat = beats[currentStep];

     duration = beat * tempo; // Set up timing

     playTone(); 
     // A pause between notes...
     delayMicroseconds(pause);
    }
};
 void clockwise(int Speed)
{
  analogWrite(motorIn1,Speed);  //set the speed of motor
  analogWrite(motorIn2,0);  //stop the motorIn2 pin of motor
}

void waitAndShow(int Seconds)
{
  lcd.setCursor(0,0);
  lcd.print("Running for    ");
  lcd.setCursor(2,1);
  lcd.print(" more seconds.");
  for (int i = Seconds; i > 0; i--){
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print(i);
    delay(1000);
  }
}
 
void ramp()
{
   lcd.setCursor(0,0);
   lcd.print("Ramping up...  ");
   lcd.setCursor(0,1);
   lcd.print("               ");
   for(int i=125; i < 250; i++){
     clockwise(i);
     lcd.setCursor(0,1);
     lcd.print(i);
     delay(150); 
   }
}
 
 
void loop()
{
 //lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 //lcd.print(millis()/1000);      // display seconds elapsed since power-up   

 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons
 
     switch (lcd_key)               // depending on which button was pushed, we perform an action
     {
       case btnRIGHT:
         {
           ramp();
           waitAndShow(5);
           clockwise(0);
           lcd.setCursor(0,0); 
           lcd.print("Stopped        ");
           lcd.setCursor(0,1);
           lcd.print("               ");
           break;
         }
       case btnLEFT:
         {
         lcd.setCursor(0,0);
         lcd.print("There is no    ");
         //--------****************---
         lcd.setCursor(0,1);
         lcd.print("left doot!     ");
         //---------****************---
         delay(3000);
         break;
         }
       case btnUP:
         {
         lcd.setCursor(0,0);
         lcd.print("good bones!    ");
         //--------****************---
         lcd.setCursor(0,1);
         lcd.print("calcium! doot!  ");
         //---------****************--
         playSong();
         break;
         }
       case btnDOWN:
         {
         lcd.setCursor(0,0);
         lcd.print(" osteoporosis ");
         //--------****************---
         lcd.setCursor(0,1);
         lcd.print("    5 ever!    ");
         //---------****************---
         delay(3000);
         break;
         }
       case btnSELECT:
         {
         lcd.print("SELECT");
         break;
         }
       case btnNONE:
         {
         lcd.setCursor(0,0);
         lcd.print("Updoot, or      ");
         //--------****************---
         lcd.setCursor(0,1);
         lcd.print("Downdoot?       ");
         //---------****************---
         break;
         }
   }
   

}
