#include <Servo.h>



// Declare servo objects
Servo SERVO1; 
Servo SERVO2;
Servo SERVO3;       


//define  pins 
#define SERVO1_PIN     3  
#define SERVO2_PIN     7  
#define SERVO3_PIN     9 


#define BASE_MIN       600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2500     //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN   600
#define SHOULDER_MAX  1800
#define ELBOW_MIN      900
#define ELBOW_MAX     2400
#define WRIST_MIN      500
#define WRIST_MAX     1800
#define GRIPPER_MIN    900    //full counterclockwise for 9g servo
#define GRIPPER_MAX   2400

const int Home = 700;


int serv1 = Home;
int serv2 = Home;
int serv3 = Home;



int curServ1 = 0;
int curMenu = 0;
int incomingByte = 0;


void setup(){

  SERVO1.attach(SERVO1_PIN);
  SERVO2.attach(SERVO2_PIN);
  SERVO3.attach(SERVO3_PIN);

   Serial.begin(9600);
   delay (500); 
   Serial.println("Delta Robot Positioning tool V1. Andrey Teplyakov ");  
   Serial.println("###########################");    
   Serial.println("Serial Communication Established.");
   mainMenu();
   doHome();
   
}

void loop(){

  delay(100);
 
 
  if (Serial.available() > 0) {
                
    incomingByte = Serial.read();
    Serial.println(incomingByte);
     if(curMenu == 0)
     {     
        switch(incomingByte)
        {
          case '1': curServ1 = 1; Serial.println("Current servos: SERVO #1");incomingByte = 0;curMenu = 1; moveMenu(); break;
          case '2': curServ1 = 2; Serial.println("Current servos: SERVO #2");incomingByte = 0;curMenu = 1;moveMenu();break;
          case '3': curServ1 = 3; Serial.println("Current servos: SERVO #3");incomingByte = 0;curMenu = 1;moveMenu();break;
          case '4': incomingByte = 0;curMenu = 1;goToPos();break;
          case '7': printPositions();break;
          case '8': doHome();break;
        }
      }
  }
  
  if(incomingByte == '0' && curMenu != 0){mainMenu();curServ1=0;incomingByte = 0;curMenu = 0;}
 
  if(curMenu == 1)
  {
    switch(incomingByte)
    {
      case '1': moveServo(10);incomingByte = 999; break;
    //  case '2': moveServo(50);incomingByte = 999; break;
    //  case '3': moveServo(100);incomingByte = 999; break;
      case '2': moveServo(-10);incomingByte = 999; break;
      case '3': moveServo(1);incomingByte = 999; break;
      case '4': moveServo(-1);incomingByte = 999; break;
   //   case '5': moveServo(-50);incomingByte = 999; break;
   //   case '6': moveServo(-100);incomingByte = 999; break;
    }
  }  
}

void goToPos()
{
  moveServo(SERVO1, serv1, 970, 4);
  moveServo(SERVO2, serv2, 770, 4);
  moveServo(SERVO3, serv3, 930, 4);
}

  
void mainMenu()
{
  curServ1 = 0;

   Serial.println("###########################");
   Serial.println("Choose the servos: (0 - return to main menu)");
   Serial.println("1. Servo #1");
   Serial.println("2. Servo #2");
   Serial.println("3. Servo #3");
   Serial.println("4. Secret Position");
   Serial.println("7. Print servos positions");
   Serial.println("8. Home position");
   Serial.println("###########################");
}

void moveMenu()
{
   Serial.println("###########################");
   Serial.println("Choose the moving: (0 - return to main menu)");
   Serial.println("1. +10");
 //  Serial.println("2. +50");
 //  Serial.println("3. +100");
   Serial.println("2. -10");
   Serial.println("3. +1");
   Serial.println("4. -1");
//   Serial.println("5. -50");
 //  Serial.println("6. -100"); 
   Serial.println("###########################");
}

void moveServo(int m)
{
  switch(curServ1)
  {
    case 1:moveServo(SERVO1, serv1, serv1 + m, 2); delay(10); serv1 += m; break;
    case 2:moveServo(SERVO2, serv2, serv2 + m, 2);delay(10); serv2 += m; break;
    case 3:moveServo(SERVO3, serv3, serv3 + m, 2);delay(10); serv3 += m; break;

  }
}

void printPositions()
{
   Serial.println("########Servos positions####");
   Serial.print("Servo 1: ");Serial.println(serv1);
   Serial.print("Servo 2: ");Serial.println(serv2);
   Serial.print("Servo 3: ");Serial.println(serv3);
   Serial.println("###########################");
}

void doHome()
{
   delay(100); 
   
   moveServo(SERVO1, serv1, Home, 2);
   moveServo(SERVO2, serv2, Home, 2);
   moveServo(SERVO3, serv3, Home, 2);

   serv1 = Home;
   serv2 = Home;
   serv3 = Home;


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
      double d1 = pos1 - serv1;
      double d2 = pos2 - serv2;
      double d3 = pos3 - serv3;
      double k1, k2 = 0;


      int maxNumber = getMaxNumber(abs(d1), abs(d2), abs(d3));
      if (maxNumber == 0)return;


      
      switch(maxNumber)
      {
        case 1: 
        k1 = d2/d1;
                k2 = d3/d1;
                if(d1 > 0)
                {
                  for(int i = serv1; i <= pos1; i++)
                  {
                    SERVO1.writeMicroseconds(i);
                    serv2 += k1;
                    serv3 += k2;
                    SERVO2.writeMicroseconds(serv2);
                    SERVO3.writeMicroseconds(serv3);
                    delay(moveDelay);
                    }
                    serv1 = pos1;
                  }else
                  {
                  for(int i = serv1; i >= pos1; i--)
                  {
                    SERVO1.writeMicroseconds(i);
                    serv2 += k1;
                    serv3 += k2;
                    SERVO2.writeMicroseconds(serv2);
                    SERVO3.writeMicroseconds(serv3);
                    delay(moveDelay);
                    }
                    serv1 = pos1;
                  }break;
        case 2: 
        k1 = d1/d2;
                k2 = d3/d2;

                if(d2 > 0)
                {
                  for(int i = serv2; i <= pos2; i++)
                  {
                    SERVO2.writeMicroseconds(i);
                    serv1 += k1;
                    serv3 += k2;
                    SERVO1.writeMicroseconds(serv1);
                    SERVO3.writeMicroseconds(serv3);
                    delay(moveDelay);
                    }
                    serv2 = pos2;
                  }else
                  {
                  for(int i = serv2; i >= pos2; i--)
                  {
                    SERVO2.writeMicroseconds(i);
                    serv1 += k1;
                    serv3 += k2;
                    SERVO1.writeMicroseconds(serv1);
                    SERVO3.writeMicroseconds(serv3);
                    delay(moveDelay);
                    }
                    serv2 = pos2;
                  }break;
        case 3: k1 = d1/d3;
                k2 = d2/d3;
                if(d3 > 0)
                {
                  for(int i = serv3; i <= pos3; i++)
                  {
                    SERVO3.writeMicroseconds(i);
                    serv1 += k1;
                    serv2 += k2;
                    SERVO1.writeMicroseconds(serv1);
                    SERVO2.writeMicroseconds(serv2);
                    delay(moveDelay);
                    }
                    serv3 = pos3;
                  }else
                  {
                  for(int i = serv3; i >= pos3; i--)
                  {
                    SERVO2.writeMicroseconds(i);
                    serv1 += k1;
                    serv2 += k2;
                    SERVO1.writeMicroseconds(serv1);
                    SERVO2.writeMicroseconds(serv2);
                    delay(moveDelay);
                    }
                    serv3 = pos3;
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
