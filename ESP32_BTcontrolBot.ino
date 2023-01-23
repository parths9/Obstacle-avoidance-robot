#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#include <Arduino.h>

#define RMF 25   //D25
#define RMB 26   //D26
#define LMF 27   //D27
#define LMB 14   //D14

void setup()
{
  pinMode(RMF, OUTPUT);
  pinMode(RMB, OUTPUT);
  pinMode(LMF, OUTPUT);
  pinMode(LMB, OUTPUT);

  Serial.begin(115200);
  Dabble.begin("MyEsp32");       //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("Up");
    Forward();
  } else if (GamePad.isDownPressed())
  {
    Serial.print("Down");
    Backward();
  } else if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
    TurnLeft();
  } else if (GamePad.isRightPressed())
  {
    Serial.print("Right");
    TurnRight();
  } else
  {
    Stop();
  }

  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}


//Motor driver functions
void Forward()
{
  Serial.println("Move forward..");
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, HIGH);
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, HIGH);
}

void Backward()
{
  Serial.println("Move back..");
  digitalWrite(RMF, HIGH);
  digitalWrite(RMB, LOW);
  digitalWrite(LMF, HIGH);
  digitalWrite(LMB, LOW);
}

void TurnRight()
{
  Serial.println("Turn right..");
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
