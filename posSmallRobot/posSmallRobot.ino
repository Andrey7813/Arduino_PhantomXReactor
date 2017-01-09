#include <Servo.h>

#define ROBOT_GEEK_9G_GRIPPER 1
#define GRIPPER_TYPE ROBOT_GEEK_9G_GRIPPER

// Declare servo objects
Servo BASE_SERVO;        //base servo - RobotGeek Servo
Servo SHOULDER_SERVO;    //shoulder servo - RobotGeek Servo 
Servo ELBOW_SERVO;       //elbow servo - RobotGeek Servo
Servo WRIST_SERVO;       //wrist servo - RobotGeek Servo
Servo GRIPPER_SERVO;     //gripper servo - 9g servo

//define  pins 
#define BASE_PIN     3  
#define SHOULDER_PIN 5 
#define ELBOW_PIN    6  //lokot
#define WRIST_PIN    9  //zapjast'e
#define GRIPPER_PIN  10 //connected to Rotation Knob / Potentiometer # 2

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

const int Home = 1500;
const int Gripper_Home = 900;

int serv1 = Home;
int serv2 = Home;
int serv3 = Home;
int serv4 = Home;
int serv5 = Gripper_Home;


int curServ1 = 0;
int curMenu = 0;
int incomingByte = 0;


void setup(){

  // Attach servo and set limits
  BASE_SERVO.attach(BASE_PIN, BASE_MIN, BASE_MAX);
  SHOULDER_SERVO.attach(SHOULDER_PIN, SHOULDER_MIN, SHOULDER_MAX);
  ELBOW_SERVO.attach(ELBOW_PIN, ELBOW_MIN, ELBOW_MAX);
  WRIST_SERVO.attach(WRIST_PIN, WRIST_MIN, WRIST_MAX);
  GRIPPER_SERVO.attach(GRIPPER_PIN, GRIPPER_MIN, GRIPPER_MAX);

   Serial.begin(9600);
   delay (500); 
   Serial.println("Geek Robot Positioning tool V1. Andrey Teplyakov ");  
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
          case '1': curServ1 = 1; Serial.println("Current servos: BASE");incomingByte = 0;curMenu = 1; moveMenu(); break;
          case '2': curServ1 = 2; Serial.println("Current servos: SHOULDER");incomingByte = 0;curMenu = 1;moveMenu();break;
          case '3': curServ1 = 3; Serial.println("Current servos: ELBOW");incomingByte = 0;curMenu = 1;moveMenu();break;
          case '4': curServ1 = 4; Serial.println("Current servos: WRIST");incomingByte = 0;curMenu = 1;moveMenu();break;
          case '5': curServ1 = 5; Serial.println("Current servos: GRIPPER");incomingByte = 0;curMenu = 1;moveMenu();break;
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
      case '1': moveServo(100);incomingByte = 999; break;
    //  case '2': moveServo(50);incomingByte = 999; break;
    //  case '3': moveServo(100);incomingByte = 999; break;
      case '2': moveServo(-100);incomingByte = 999; break;
      case '3': moveServo(10);incomingByte = 999; break;
      case '4': moveServo(-10);incomingByte = 999; break;
   //   case '5': moveServo(-50);incomingByte = 999; break;
   //   case '6': moveServo(-100);incomingByte = 999; break;
    }
  }  
}

void mainMenu()
{
  curServ1 = 0;

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

void moveMenu()
{
   Serial.println("###########################");
   Serial.println("Choose the moving: (0 - return to main menu)");
   Serial.println("1. +100");
 //  Serial.println("2. +50");
 //  Serial.println("3. +100");
   Serial.println("2. -100");
   Serial.println("3. +10");
   Serial.println("4. -10");
//   Serial.println("5. -50");
 //  Serial.println("6. -100"); 
   Serial.println("###########################");
}

void moveServo(int m)
{
  switch(curServ1)
  {
    case 1:BASE_SERVO.writeMicroseconds(serv1 + m); delay(10); serv1 += m; break;
    case 2:SHOULDER_SERVO.writeMicroseconds(serv2 + m);delay(10); serv2 += m; break;
    case 3:ELBOW_SERVO.writeMicroseconds(serv3 + m);delay(10); serv3 += m; break;
    case 4:WRIST_SERVO.writeMicroseconds(serv4 + m);delay(10); serv4 += m; break;
    case 5:GRIPPER_SERVO.writeMicroseconds(serv5 + m); delay(10); serv5 += m; break;
  }
}

void printPositions()
{
   Serial.println("########Servos positions####");
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
   Serial.println("###########################");
}

void doHome()
{
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
