#include <Servo.h>



// Declare servo objects
Servo SERVO1; 
Servo SERVO2;
Servo SERVO3;       


//define  pins 
#define SERVO1_PIN     3  
#define SERVO2_PIN     7  
#define SERVO3_PIN     9  

int incomingByte = 0;

double curPosition1 = 700;//1500
double curPosition2 = 700;
double curPosition3 = 700;


void setup(){

  // Attach servo and set limits
  SERVO1.attach(SERVO1_PIN);
  SERVO2.attach(SERVO2_PIN);
  SERVO3.attach(SERVO3_PIN);

  Serial.begin(9600);
  delay (500); 
  Serial.println("I'm delta robot ");  
  Serial.println("###########################");    
  Serial.println("Serial Communication Established.");
  //moveServo(SERVO1, curPosition1, 2000, 2);
  //moveServo(SERVO1, 2000, curPosition1, 2);
  moveServos(1500, 1500, 1500, 2);
}

void loop(){

  delay(100);
 
 
  if (Serial.available() > 0) {
                
    incomingByte = Serial.read();
    Serial.println(incomingByte);
  }
  
  
}

void mainMenu()
{


   Serial.println("###########################");
   Serial.println("Choose the servos: (0 - return to main menu)");
   Serial.println("1. Base");
   Serial.println("2. Shoulder");
   Serial.println("3. Elbow");
   Serial.println("4. Wrist");
   Serial.println("5. Gripper");
   Serial.println("7. Print servos positions");
   Serial.println("8. Home position");
   Serial.println("###########################");
}


void moveServo(int m)
{
 /* switch(curServ1)
  {
    case 1:BASE_SERVO.writeMicroseconds(serv1 + m); delay(10); serv1 += m; break;
    case 2:SHOULDER_SERVO.writeMicroseconds(serv2 + m);delay(10); serv2 += m; break;
    case 3:ELBOW_SERVO.writeMicroseconds(serv3 + m);delay(10); serv3 += m; break;
    case 4:WRIST_SERVO.writeMicroseconds(serv4 + m);delay(10); serv4 += m; break;
    case 5:GRIPPER_SERVO.writeMicroseconds(serv5 + m); delay(10); serv5 += m; break;
  }*/
}

void printPositions()
{
   /*Serial.println("########Servos positions####");
   Serial.print("Servo 1: ");Serial.println(serv1);
   Serial.print("Servo 2: ");Serial.println(serv2);
   Serial.print("Servo 3: ");Serial.println(serv3);
   Serial.print("Servo 4: ");Serial.println(serv4);
   Serial.print("Servo 5: ");Serial.println(serv5);
    Serial.print("{ ");
   Serial.print(serv1);
   Serial.print(", ");
   Serial.print(serv2);
   Serial.print(", ");
   Serial.print(serv3);
   Serial.print(", ");
   Serial.print(serv4);
   Serial.print(", ");
   Serial.print(serv5);
   Serial.println(" }");
   Serial.println("###########################");*/
}

void doHome()
{/*
   delay(100); 
   BASE_SERVO.writeMicroseconds(1500); 
   delay(20);
   SHOULDER_SERVO.writeMicroseconds(1500); 
   delay(20);
   ELBOW_SERVO.writeMicroseconds(1500); 
   delay(20);
   WRIST_SERVO.writeMicroseconds(1500); 
   delay(20);
   GRIPPER_SERVO.writeMicroseconds(Gripper_Home); 
   delay(20);

   serv1 = Home;
   serv2 = Home;
   serv3 = Home;
   serv4 = Home;
   serv5 = Gripper_Home;
*/
}

void moveServo(Servo servo, int startPosition, int endPosition, int moveDelay)
    {
      if(startPosition < endPosition)
          for(int i = startPosition; i <= endPosition; i++)
              {
                servo.writeMicroseconds(i);
                delay(moveDelay);
                }
      else
      for(int i = startPosition; i >= endPosition; i--)
              {
                servo.writeMicroseconds(i);
                delay(moveDelay);
                }
      }

 void moveServos(int pos1, int pos2, int pos3, int moveDelay)
    {
      double d1 = pos1 - curPosition1;
      double d2 = pos2 - curPosition2;
      double d3 = pos3 - curPosition3;
      double k1, k2 = 0;

Serial.println("OK1");

      int maxNumber = getMaxNumber(abs(d1), abs(d2), abs(d3));
      if (maxNumber == 0)return;

      Serial.println("OK2");
      
      switch(maxNumber)
      {
        case 1: 
        Serial.println("OK3");k1 = d2/d1;
                k2 = d3/d1;
                if(d1 > 0)
                {
                  for(int i = curPosition1; i <= pos1; i++)
                  {
                    SERVO1.writeMicroseconds(i);
                    curPosition2 += k1;
                    curPosition3 += k2;
                    SERVO2.writeMicroseconds(curPosition2);
                    SERVO3.writeMicroseconds(curPosition3);
                    delay(moveDelay);
                    }
                    curPosition1 = pos1;
                  }else
                  {
                  for(int i = curPosition1; i >= pos1; i--)
                  {
                    SERVO1.writeMicroseconds(i);
                    curPosition2 += k1;
                    curPosition3 += k2;
                    SERVO2.writeMicroseconds(curPosition2);
                    SERVO3.writeMicroseconds(curPosition3);
                    delay(moveDelay);
                    }
                    curPosition1 = pos1;
                  }break;
        case 2: 
        Serial.println("OK4");k1 = d1/d2;
                k2 = d3/d2;
                Serial.println(k1);
                Serial.println(k2);
                if(d2 > 0)
                {
                  for(int i = curPosition2; i <= pos2; i++)
                  {
                    SERVO2.writeMicroseconds(i);
                    curPosition1 += k1;
                    curPosition3 += k2;
                    SERVO1.writeMicroseconds(curPosition1);
                    SERVO3.writeMicroseconds(curPosition3);
                    delay(moveDelay);
                    }
                    curPosition2 = pos2;
                  }else
                  {
                  for(int i = curPosition2; i >= pos2; i--)
                  {
                    SERVO2.writeMicroseconds(i);
                    curPosition1 += k1;
                    curPosition3 += k2;
                    SERVO1.writeMicroseconds(curPosition1);
                    SERVO3.writeMicroseconds(curPosition3);
                    delay(moveDelay);
                    }
                    curPosition2 = pos2;
                  }break;
        case 3: k1 = d1/d3;
                k2 = d2/d3;
                if(d3 > 0)
                {
                  for(int i = curPosition3; i <= pos3; i++)
                  {
                    SERVO3.writeMicroseconds(i);
                    curPosition1 += k1;
                    curPosition2 += k2;
                    SERVO1.writeMicroseconds(curPosition1);
                    SERVO2.writeMicroseconds(curPosition2);
                    delay(moveDelay);
                    }
                    curPosition3 = pos3;
                  }else
                  {
                  for(int i = curPosition3; i >= pos3; i--)
                  {
                    SERVO2.writeMicroseconds(i);
                    curPosition1 += k1;
                    curPosition2 += k2;
                    SERVO1.writeMicroseconds(curPosition1);
                    SERVO2.writeMicroseconds(curPosition2);
                    delay(moveDelay);
                    }
                    curPosition3 = pos3;
                  }break;
                  
        }
      

      }

int getMaxNumber(int p1, int p2, int p3)
{
  if(p1>=p2&&p1>=p3)return 1;
  if(p2>=p1&&p2>=p3)return 2;
  if(p3>=p1&&p3>=p2)return 3;
  return 0;
  }      
