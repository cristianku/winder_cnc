 #include <LiquidCrystal_I2C.h>


 
 void setup() {
 // Sets the two pins as Outputs
 pinMode(stepPin,OUTPUT); 
 pinMode(dirPin,OUTPUT);
 pinMode(enablePin, OUTPUT);  // ******** set the enable pinMode
 digitalWrite(enablePin, LOW); // ******** enable the motors


  // initialize the LCD
   lcd.begin(16,2);

  // Turn on the blacklight and print a message.
   lcd.backlight();
   
 }
 void loop() {
 lcd.setCursor(0,0);
 lcd.print("Winding CNC 1.0");
 lcd.setCursor(3,1);
  lcd.print("by Zante Inc.");


   
 x_full_turn(stepsPerRevolution, fast);
 x_full_turn(stepsPerRevolution, fast);
 x_full_turn(stepsPerRevolution, fast);
 x_full_turn(stepsPerRevolution, fast);

 delay(1000); // One second delay
 
// digitalWrite(dirPin,LOW); //Changes the rotations direction
// // Makes 400 pulses for making two full cycle rotation
// for(int x = 0; x < 400; x++) {
// digitalWrite(stepPin,HIGH);
// delayMicroseconds(500);
// digitalWrite(stepPin,LOW);
// delayMicroseconds(500);
// }
// delay(1000);
 lcd.clear();

 }

 void x_full_turn(int stepsPerRevolution, int velocity)
 {
   int delay;
   if (velocity = 0) { delay = 800;}
   else {delay = 200;}
   
   digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
   // Makes stepsPerRevolution pulses for making one full cycle rotation
   for(int x = 0; x < stepsPerRevolution; x++) {
     digitalWrite(stepPin,HIGH); 
     delayMicroseconds(delay); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(delay); 
 }
  }
