//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(14, 15, 4, 5, 6, 7);


/***************************************/
const int motorIn1 = 20;  //attach to one of the pin of the motor
const int motorIn2 = 21;  //attach to another pin of the motor
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

// define motor controls
int potPin = 23;
int motorPin = 22;
int potValue = 0;
int motorValue = 0;

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(16);      // read the value from the sensor 
 Serial.println(adc_key_in, DEC);
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
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Welcome to..."); // print a simple message
 delay(1000);
 lcd.setCursor(0,0);
 lcd.print("Mr. Skeltal's");
 lcd.setCursor(0,1);
 lcd.print("Spooky Adventure!");
 delay(2000);
 
 }
 
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
   for(int i=95; i < 125; i++){
     clockwise(i);
     lcd.setCursor(0,1);
     lcd.print(i);
     delay(250); 
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
           waitAndShow(30);
           clockwise(0);
           lcd.setCursor(0,0); 
           lcd.print("Stopped        ");
           lcd.setCursor(0,1);
           lcd.print("               ");
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
         //---------****************---
         delay(3000);
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
