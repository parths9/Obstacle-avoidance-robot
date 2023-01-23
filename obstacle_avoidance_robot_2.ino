#include <ESP32Servo.h>
#include <analogWrite.h>

#include <ESP32Tone.h>
#include <ESP32PWM.h>
//motor driver 
#define RMF 25   //D25
#define RMB 26   //D26
#define LMF 27   //D27
#define LMB 14   //D14

#define TrigPin 35 //D14
#define EchoPin 12 //D12
#define servoPin 23 //D15

Servo servo;
int distance;
int distanceRight;
int distanceLeft;
//int servoPos = 90;
   
void setup() 
{
Serial.begin(115200);
pinMode(RMF,OUTPUT);
pinMode(RMB,OUTPUT);
pinMode(LMF,OUTPUT);
pinMode(LMB,OUTPUT);
pinMode(TrigPin, OUTPUT);
pinMode(EchoPin, INPUT);
servo.attach(servoPin);  
servo.write(90); 
delay(200);
}

void loop()
{
distance = getDistance();
   
 if(distance<=15)
 {
  Stop();
  delay(100);
  
  Backward();
  delay(300);
   
  lookRight();
  delay(200);
  
  lookLeft();
  delay(200);

   if(distanceRight < distanceLeft)
    {
      TurnLeft();
      delay(100);
      Forward();
    }
   else
   {
    TurnRight();
    delay(100);
    Forward();
   }
         
 }
 else
 {
  Forward();
 }
}

//Function to calculate distance for ultrasonic sensor
int getDistance() 
{
long duration;
digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);
duration = pulseIn(EchoPin, HIGH);
distance= (0.0343*(duration / 2));
return distance;
}

//Servo functions
void lookRight()
{
    servo.write(0); 
    distanceRight = getDistance();
    delay(500);
    servo.write(90); 
}

void lookLeft()
{
    servo.write(180); 
    distanceLeft = getDistance();
    delay(500); 
    servo.write(90); 
}

//Motor driver functions
void Backward() 
{ 
  Serial.println("Move forward..");
  digitalWrite(RMF,LOW);
  digitalWrite(RMB,HIGH);                       
  digitalWrite(LMF,LOW);
  digitalWrite(LMB,HIGH); 
}

void Forward() 
{
  Serial.println("Move back..");
  digitalWrite(RMF,HIGH);
  digitalWrite(RMB,LOW);                         
  digitalWrite(LMF,HIGH);
  digitalWrite(LMB,LOW);
}  

void TurnRight() 
{
  Serial.println("Turn right..");
  servo.write(0);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
} 
 
void TurnLeft() 
{
 Serial.println("Turn left..");
 servo.write(180);
 digitalWrite(RMF, HIGH);
 digitalWrite(RMB, LOW);
 digitalWrite(LMF, LOW);
 digitalWrite(LMB, HIGH); 
} 
 
void Stop()
{
 digitalWrite(RMF, LOW);
 digitalWrite(RMB, LOW);
 digitalWrite(LMF, LOW);
 digitalWrite(LMB, LOW); 
}


//check obstacle
//void check_obstacle();
//{
//distance = getDistance();}
