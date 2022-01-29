#include <LiquidCrystal.h>
#define NOTE_C4 262
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_F4 349
#define NOTE_E4 330
#define NOTE_D4 294
#define NOTE_B4 494

#define NOTE_D5 587
#define NOTE_E5 659


//This prepares ABC notes.
int melody[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,0,
               NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0,
               NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
               NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
               NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,0,
               NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0};



//This determines the duration of the above code.
int noteDurations[] = {4, 4, 4, 4, 4, 4, 8, 4, 
                      
                    4, 4, 4, 4, 4, 4, 8, 4,
                      4, 4, 4, 4, 4, 4, 8, 4,
                      4, 4, 4, 4, 4, 4, 8, 4,
                      4, 4, 4, 4, 4, 4, 8, 4,
                      4, 4, 4, 4, 4, 4, 8};

/*
D              G         G - G - B       A   G - A
Should old acquaintance be forgot

B       G - G         B       ^D   ^E
And never brought to mind?

^E          ^D        B - B - G        A   G - A
Should old acquaintance be forgot

B-A  G-E  E-D   G
And old lang syne?

 
*/

//This prepares the first part of the Auld Lang Syne song.
int melody2[] = {NOTE_D4, NOTE_G4,  0, NOTE_G4, NOTE_G4, NOTE_B4,  NOTE_A4, NOTE_G4, NOTE_A4, 
                
                NOTE_B4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_D5, NOTE_E5, 0,
                
                
                NOTE_E5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4, 
                
                NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G4};

int noteDurations2[] = {4, 2,  4, 4, 4,  4, 4, 4, 4, 
                       4, 4, 4, 4, 4, 4, 4,
                       4, 4, 4, 4, 4, 4, 4, 4,
                       4,4,4,4,4,4,4};

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//This tells which ports are connected to the LCD.
int sensor = 9;  //The PIR signal is attached to Port 9.
int state = LOW; //The default mode, assuming nothing is detected.
int val = 0;   //It determines the motion (HIGH) or not. 
int buzzer= 7;  //The buzzer is attahed to Port 7. 

void setup() {
  pinMode(sensor, INPUT);    //This initialises the sensor variable as an input.
  pinMode(buzzer, OUTPUT); //This initialises the buzzer variable as an output.
// lcd.begin(16, 2); //This sets the LCD ex: where to show those characters. 
  pinMode(13, OUTPUT); //This initialises the bulb as an output.
}

void loop(){
  val = digitalRead(sensor);   //This reads the sensor variable by returning HIGH or LOW. 
 

  if (val == HIGH){
    delay(100);                
    if (state == LOW){ //If it detects sth when it is in default mode....
      lcd.setCursor(0, 1); //This sets the LCD ex: where to show those characters. 
      lcd.print("Motion Detected!");//It displays this sentence.
 
      state = HIGH;       //This updates the state variable to HIGH.
       
        digitalWrite(13, HIGH); //It lights the bulb up. 
      
      abc();
     
      //digitalWrite(13, LOW); //This turns the light off after the music. 
  }
 }
 else { 
     delay(200);            
     if (state == HIGH){ //If it stops detecting sth when it is in active mode....
      lcd.setCursor(0, 1); //This sets the LCD ex: where to show those characters. 
        lcd.print("Motion Stopped!"); //It displays this sentence.
        
        state = LOW;       //This updates the variable state to LOW
        
       // digitalWrite(13, HIGH); //It lights the bulb up. 
       
        als();
       
        digitalWrite(13, LOW);//This turns the light off.
     }
  }
}

void abc() {
  for (int thisNote = 0; thisNote < 49; thisNote++) { 
      int noteDuration = 2000 / noteDurations[thisNote]; //This calculates the note duration, 2 seconds divided by the note type. 
      tone(7, melody[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;//This distinguishes the notes.
      delay(pauseBetweenNotes);
      
      noTone(7); //This stops the music. 
    }
}

void als() {
  for (int thisNote = 0; thisNote < 35; thisNote++) { 
      int noteDuration2 = 1000 / noteDurations2[thisNote]; //This calculates the note duration, 1 second divided by the note type. 
      tone(7, melody2[thisNote], noteDuration2);
      
      int pauseBetweenNotes = noteDuration2 * 1.30;//This distinguishes the notes.
      delay(pauseBetweenNotes);
      
      noTone(7); //This stops the music. 
    }
}
