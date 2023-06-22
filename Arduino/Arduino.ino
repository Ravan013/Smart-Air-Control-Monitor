
#include <Servo.h>


Servo servo_01;
Servo servo_02;


int slot1= 8; //slots in Arduino Pin
int slot2= 9;

String sensor1;
String sensor2;

int pos1 = 90; 
int pos2 = 90;  

String com_data =""; // complete sensor data

void setup()
{
Serial.begin(9600); 

pinMode(slot1, INPUT);
pinMode(slot2, INPUT);

servo_01.attach(13);  
servo_02.attach(3);
}

void loop()
{

p_slot1(); 
p_slot2();

gates();

digitalWrite(slot1, HIGH); 
digitalWrite(slot2, HIGH); 

}


void p_slot1() // functions for each slot
{
  if( digitalRead(slot1) == LOW) 
  {
  sensor1 = "255";
 delay(200); 
  } 
if( digitalRead(slot1) == HIGH)
{
  sensor1 = "0";  
 delay(200);  
}

}

void p_slot2() 
{
  if( digitalRead(slot2) == LOW) 
  {
  sensor2 = "255"; 
  delay(200); 
  }
if( digitalRead(slot2) == HIGH)  
  {
  sensor2 = "0";  
 delay(200);
  } 
}




void gates()
{
  if ((( digitalRead(slot1) == HIGH) || ( digitalRead(slot2) == HIGH) ))
      {
        for (pos2 = 90; pos2 <= 180 ; pos2 += 1) { 
          // in steps of 1 degree
          servo_02.write(pos2);              
          delay(100);                       
        }
          delay(1000);
        for (pos2 = 180; pos2 >= 90; pos2 -= 1) { 
          servo_02.write(pos2);              
          delay(15);                       
        }
      }
  
  if ((( digitalRead(slot1) == LOW) || ( digitalRead(slot2) == LOW) ))
      {
        for (pos1 = 0; pos1 <= 90 ; pos1 += 1) { 
          // in steps of 1 degree
          servo_01.write(pos1);              
          delay(100);                       
        }
          delay(1000);
        for (pos1 = 90; pos1 >= 0; pos1 -= 1) { 
          servo_01.write(pos1);              
          delay(100);                       
        }
      }
}
