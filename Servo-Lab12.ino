//Ryan Gee - 200396244
//April 17, 2020
//Servo control with two buttons: forwards and backwards, with LED status indicator
//Pressing sw1 will move the servo 45 degrees forwards, sw2 will move the servo 45 degrees backwards
//At each extreme of the servo's rotation, it will reset all the way back to the opposite side
//The servo's current angle is also display with an RGB led that changes colours according to its rotation
//V 1.0

//Import the servo library
#include <Servo.h>
 
//create a servo object to control the motor  
Servo servo;
//Initialize the angle variable
int angle = 0;  
//Record the pins for switches one and two
int sw1 = 2;
int sw2 = 3;
//Record the rgb led pins
int r = 9;
int g = 10;
int b = 11;
//Initialize a state holder for switches 1 and 2 (to detect state changes)
int sw1State = 1;
int sw2State = 1;

void setup() 
{ 
  //Attach the servo object to pin 7
  servo.attach(7);
  //Initialize our two switches
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  //Initialize the RGB led pins
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

} 
  
void loop() 
{
  //Check if sw1 is currently down
  if (digitalRead(sw1) == LOW) {
    if (sw1State == 1) {
      //Button has only just now been pressed
      //Increment the angle (by 44 degrees instead of 45 to prevent premature wrapping)
      angle += 44;
      //Adding in a small delay helps prevent over-writing
      delay(20);
    }
    //State should be set to zero as long as the button is held down
    sw1State = 0;
  }
  
  //If the button has bee released, reset the state
  if (digitalRead(sw1) == HIGH) {
    sw1State = 1;
  }
  
  //Check if sw2 is currently held down
  if (digitalRead(sw2) == LOW) {
    if (sw2State == 1) {
      //Button has only just now been pressed
      //Angle decremented by the same value as above, same delay used
      angle -= 44;
      delay(20);
    }
    //State should be set to zero when the button is being held down
    sw2State = 0;
  }
  
  //Reset the state when sw2 is released
  if (digitalRead(sw2) == HIGH) {
    //sw1 has been released
    sw2State = 1;
  }
  
  //Clamp the angle between 0 and 179 to ensure the servo moves appropriately
  //When the value exceeds one end of the range, it is wrapped around to the other side of the range, as specified
  if (angle < 0) {
    //Increment the angle one quarter of the way to the wrapped target
    angle += 44;
    //Calling update every cycle allows the leds to flick through their appropriate colours
    update(angle);
    //Adding in a short delay ensures that the changes are visible
    delay(100);
    //Repeat 3 more times
    angle += 44;
    update(angle);

    delay(100);
    angle += 44;
    update(angle);

    delay(100);
    angle += 44;
    update(angle);
    
    delay(100);
    angle = 179;
  }
  if (angle >= 180) {
    //Exactly the same as above, but decrementing the angle instead of incrementing it
    angle -= 44;
    update(angle);

    delay(100);
    angle -= 44;
    update(angle);

    delay(100);
    angle -= 44;
    update(angle);

    delay(100);
    angle -= 44;
    update(angle);
    
    delay(100);
    angle = 0;  
  }
  
  //Should always call update at the end of the loop
  update(angle);
  
}

//Generic update function updates the leds according to the current angle and moves the servo to the specified angle
void update(int a) {
  //Control the leds according to the current angle
  if (angle < 44) {
    analogWrite(r, 255);
    analogWrite(g, 0);
    analogWrite(b, 0);

  }
  if (angle >= 44 && angle < 88) {
    analogWrite(r, 255);
    analogWrite(g, 255);
    analogWrite(b, 0);
  }
  if (angle >= 88 && angle < 132) {
    analogWrite(r, 0);
    analogWrite(g, 255);
    analogWrite(b, 0);
  }
  if (angle >= 132 && angle < 176) {
    analogWrite(r, 0);
    analogWrite(g, 255);
    analogWrite(b, 255);
  }
  if (angle >= 176) {
    analogWrite(r, 0);
    analogWrite(g, 0);
    analogWrite(b, 255);
  }
  //Update the servo
  servo.write(angle);
}