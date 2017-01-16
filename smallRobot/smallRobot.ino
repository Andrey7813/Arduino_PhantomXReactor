#include <Servo.h>


int WAIT_TIME_FOR_CARD_PROCESSING = 5000;

#define ROBOT_GEEK_9G_GRIPPER 1
#define GRIPPER_TYPE ROBOT_GEEK_9G_GRIPPER

//define  pins 
#define BASE_PIN     3  
#define SHOULDER_PIN 5 
#define ELBOW_PIN    6  //lokot
#define WRIST_PIN    9  //zapjast'e
#define GRIPPER_PIN  10 //connected to Rotation Knob / Potentiometer # 2

#define WAG_ROBOT_ROTATION_PIN  11 


#define BASE             0     //connected to Rotation Knob / Potentiometer # 1
#define BASE_MIN       600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400     //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN   600
#define SHOULDER_MAX  1800
#define ELBOW_MIN      900
#define ELBOW_MAX     2400
#define WRIST_MIN      400
#define WRIST_MAX     1800
#define GRIPPER_MIN    900    //full counterclockwise for 9g servo
#define GRIPPER_MAX   2400    //full clockwise for 9g servo

#define CENTERED  1500

// Declare servo objects
Servo BASE_SERVO;        //base servo - RobotGeek Servo
Servo SHOULDER_SERVO;    //shoulder servo - RobotGeek Servo 
Servo ELBOW_SERVO;       //elbow servo - RobotGeek Servo
Servo WRIST_SERVO;       //wrist servo - RobotGeek Servo
Servo GRIPPER_SERVO;     //gripper servo - 9g servo

Servo WAG_SERVO;

//present positions of the servos 
int Base     = CENTERED;    //holds the present position of the Base servo, starts at 1500 (centered)
int Shoulder = 1400;    //holds the present position of the Shoulder servo, starts at 1500 (centered)
int Elbow    = CENTERED;    //holds the present position of the Elbow servo, starts at 1500 (centered)
int Wrist    = 1000;         //holds the present position of the wrist servo, starts at 1500 (centered)
int Gripper  = 900;         //holds the present position of the gripper servo, starts at 1500 (centered)

int cur_Wrist = Wrist;
int cur_Elbow = Elbow;
int cur_Shoulder = Shoulder;
int cur_Base = Base;


int byteReceived;

void setup() {
   Serial.begin(9600);

  // Attach servo and set limits
  BASE_SERVO.attach(BASE_PIN, BASE_MIN, BASE_MAX);
  SHOULDER_SERVO.attach(SHOULDER_PIN, SHOULDER_MIN, SHOULDER_MAX);
  ELBOW_SERVO.attach(ELBOW_PIN, ELBOW_MIN, ELBOW_MAX);
  WRIST_SERVO.attach(WRIST_PIN, WRIST_MIN, WRIST_MAX);
  GRIPPER_SERVO.attach(GRIPPER_PIN, GRIPPER_MIN, GRIPPER_MAX);

  moveServo(BASE_SERVO, cur_Base, 600, 2); cur_Base = 600;

  WAG_SERVO.attach(WAG_ROBOT_ROTATION_PIN, 10, 180);
  WAG_SERVO.write(175);

  mainMenu();

}


void loop() {
    if (Serial.available() > 0)
    {
      
     byteReceived = Serial.read();

     mainMenu();

     switch(byteReceived)
     {
      case '1': sweep(1); break;
      case '2': sweep(2); break;
      case '3': sweep(3); break;
      case '4': sweep(4); break;
      case '5': sweep(5); break;
      case '6': wag(); break;
     }

    }

}

void sweep(int i)
{
   move_all_servos_to_default_position();
   takeCard(i);
   sweepBig();
   move_all_servos_to_default_position();
   returnCard(i);
   move_all_servos_to_default_position();
}

void move_all_servos_to_default_position()
{
   moveServo(SHOULDER_SERVO, cur_Shoulder, Shoulder, 2);
   cur_Shoulder = Shoulder;
   delay(300);

   moveServo(BASE_SERVO, cur_Base, 1450, 2);
   cur_Base = 1450;
   delay(300);
   
   
   moveServo(ELBOW_SERVO, cur_Elbow, 1500, 2);
   cur_Elbow = 1500; 
   delay(300);
   
   moveServo(WRIST_SERVO, cur_Wrist, 1500, 2);
   cur_Wrist = 1500;
   delay(300);
   
   GRIPPER_SERVO.writeMicroseconds(1100);
   delay(1000);
  }

void sweepBig()
{

   //go to rest position
 
   moveServo(ELBOW_SERVO, cur_Elbow, 2100, 2); cur_Elbow = 2100;
   moveServo(BASE_SERVO, cur_Base,1440,2); cur_Base = 1440;
   delay(1);
   
    moveServo(WRIST_SERVO, cur_Wrist, 580, 2); cur_Wrist = 580;
   
   delay(1);
   
   moveServo(SHOULDER_SERVO, cur_Shoulder, 2000, 2); cur_Shoulder = 2000; 
   moveServo(WRIST_SERVO, cur_Wrist, 680, 3); cur_Wrist = 680;
   moveServo(WRIST_SERVO, cur_Wrist, 600, 3); cur_Wrist = 600;
   delay(1500);


    //Card down
   double j = cur_Elbow;

   for(int i = cur_Shoulder; i >= 1450; i--) 
   {
    ELBOW_SERVO.writeMicroseconds(j);
    SHOULDER_SERVO.writeMicroseconds(i);
    j -= 1.6;
     delay(1);
    } cur_Shoulder = 1450; cur_Elbow = 1220;

    delay(WAIT_TIME_FOR_CARD_PROCESSING);

}

void sweepSmall()
{
   //go to rest position
    moveServo(ELBOW_SERVO, 1500, 2100, 2);
   delay(1);
   moveServo(WRIST_SERVO, 1500, 580, 2);//700
   delay(1);
   moveServo(SHOULDER_SERVO, 1500, 2000, 1); //1900
   delay(1);
//moveServo(WRIST_SERVO, 700, 900, 2);//510
   delay(1);
   
   //Card down
   double j = 2100;
   int cnt=0;
   
   for(int i = 2000; i>=1450; i--)
   {
    cnt++;
    //Serial.print(j);Serial.print(" - ");Serial.println(cnt);
    ELBOW_SERVO.writeMicroseconds(j);
    SHOULDER_SERVO.writeMicroseconds(i);
    j-=1.6;
     delay(1);
    }

//moveServo(SHOULDER_SERVO, 1220, 900, 3); //1790   
delay(10000);

   j=1220;
   for(int i = 1450; i<=2100; i++)
   {
    cnt++;
    //Serial.print(j);Serial.print(" - ");Serial.println(cnt);
    ELBOW_SERVO.writeMicroseconds(j);
    SHOULDER_SERVO.writeMicroseconds(i);
    j+=1.3;
     delay(1);
    }
     /* moveServo(ELBOW_SERVO, Elbow, 1800, 2);
   delay(5);
   moveServo(WRIST_SERVO, Wrist, 700, 2);
   delay(5);
   moveServo(SHOULDER_SERVO, Shoulder, 1700, 2);
   delay(3000);

int t = 1800;

   for(int i = 1700; i <= 1850; i++)
   {
    SHOULDER_SERVO.writeMicroseconds(i);
    ELBOW_SERVO.writeMicroseconds(t);
    t=t+1;
    delay(3);
    }

   int k = 1950;

   for(int i = 1850; i>=1500; i--)
   {
    
    ELBOW_SERVO.writeMicroseconds(k);
    SHOULDER_SERVO.writeMicroseconds(i);
    k = k - 1.05;
    delay(3);
    }

   delay(5000);

   //ELBOW_SERVO.writeMicroseconds(1500);
   moveServo(ELBOW_SERVO, k, 1500, 2);
   moveServo(SHOULDER_SERVO, 1500, 1000, 2);
   */
   
  }

void mainMenu()
{
  Serial.println("###########################");
  Serial.println("Hello, I'm Ava. What do you want?");
  Serial.println("1. Sweep card from slot 1");
  Serial.println("2. Sweep card from slot 2");
  Serial.println("3. Sweep card from slot 3");
  Serial.println("4. Sweep card from slot 4");
  Serial.println("5. Sweep card from slot 5");
  Serial.println("6. Wag card ");
  Serial.println("###########################");
  }

void wag()
{
  WAG_SERVO.write(175);
  WAG_SERVO.write(20);
  delay(500);
  WAG_SERVO.write(175);
  }

void takeCard(int slot)
{
  int base_angle = 0;
  switch(slot)
  {
    case 1: base_angle = 608; break;
    case 2: base_angle = 704; break;
    case 3: base_angle = 793; break; 
    case 4: base_angle = 900; break;
    case 5: base_angle = 994; break;
    }
  
  moveServo(BASE_SERVO, cur_Base, base_angle, 2); cur_Base = base_angle;
  moveServo(GRIPPER_SERVO, Gripper, 2000, 2);
  moveServo(ELBOW_SERVO, cur_Elbow, 1590, 2); cur_Elbow = 1590;
  moveServo(WRIST_SERVO, cur_Wrist, 730, 2); cur_Wrist = 730;
  moveServo(SHOULDER_SERVO, cur_Shoulder, 1720, 2); cur_Shoulder = 1720;//1730
  moveServo(GRIPPER_SERVO, 1800, 1100, 2);
  moveServo(SHOULDER_SERVO, cur_Shoulder, Shoulder, 2); cur_Shoulder = Shoulder;
}

void returnCard(int slot)
{  
  int base_angle = 0;
  switch(slot)
  {
    case 1: base_angle = 608; break;
    case 2: base_angle = 704; break;
    case 3: base_angle = 793; break;
    case 4: base_angle = 900; break;
    case 5: base_angle = 994; break;
    }
    
  moveServo(BASE_SERVO, cur_Base, base_angle, 2); cur_Base = base_angle;
  moveServo(ELBOW_SERVO, cur_Elbow, 1590, 2); cur_Elbow = 1590;
  moveServo(WRIST_SERVO, cur_Wrist, 685, 2); cur_Wrist = 685; //690
  moveServo(SHOULDER_SERVO, cur_Shoulder, 1720, 2); cur_Shoulder = 1720; //1730
  moveServo(GRIPPER_SERVO, 1100, 2000, 2);

  int k_elbow = cur_Elbow;

  for(int i = cur_Shoulder; i <= 1750; i++)
   {
      ELBOW_SERVO.writeMicroseconds(k_elbow);
      SHOULDER_SERVO.writeMicroseconds(i);
      k_elbow = k_elbow + 1;
      delay(3);
    } cur_Shoulder = 1750; cur_Elbow = 1610;
    
   moveServo(SHOULDER_SERVO, cur_Shoulder, Shoulder, 4); cur_Shoulder = Shoulder;
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

