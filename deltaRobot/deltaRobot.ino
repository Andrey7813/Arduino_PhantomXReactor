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
  Serial.println("Hello! I'm delta robot ");  
  mainMenu();
  moveServos(curPosition1, curPosition2, curPosition3, 2);

}

void loop(){

  delay(100);
 
 
  if (Serial.available() > 0) {
                
    incomingByte = Serial.read();
    Serial.println(incomingByte);

    switch(incomingByte)
    {
      case '1': pushButton(1);break;
      case '2': pushButton(2);break;
      case '3': pushButton(3);break;
      case '4': pushButton(4);break;
      case '5': pushButton(5);break;
      case '6': pushButton(6);break;
      case '7': pushButton(7);break;
      case '8': pushButton(8);break;
      case '9': pushButton(9);break;
      case '0': pushButton(0);break;
      case 'a': pushButton(10);break;
      case 'b': pushButton(11);break;
      case 'c': pushButton(12);break;
      case 'd': pushButton(13);break;
      case 'e': pushButton(14);break;
      case 'z': mainMenu(); break;
      }
  }
  
  
}

void pushButton(int button)
{
  if(button == 14) { moveServos(700, 700, 700, 0); return;}
  moveServos(700, 700, 700, 0);
  switch(button)
  {
    case 1: moveServos( 990,  960,  805, 1); break; case 2: moveServos( 940,  950,  875, 1); break; case 3: moveServos( 900,  940,  930, 1); break;
    case 4: moveServos(1025,  935,  815, 1); break; case 5: moveServos( 960,  910,  875, 1); break; case 6: moveServos( 925,  895,  940, 1); break;
    case 7: moveServos(1045,  895,  835, 1); break; case 8: moveServos( 990,  875,  890, 1); break; case 9: moveServos( 960,  870,  950, 1); break;
                                                    case 0: moveServos(1035,  855,  915, 1); break;
    case 10:moveServos(1160,  870,  910, 1); break;                                                 case 11:moveServos(1080,  850, 1025, 1); break;
    case 12: moveServos(1500,  700,  700, 3); break;
    case 13: moveServos(700,  1300,  700, 3); break;
    
    }
    delay(500);
    if(button !=12 && button !=13) moveServos(700, 700, 700, 0);
  }

void push_(int i)
{
/*
  
  switch(i)
  {
    case 1:  moveServos(curPosition1 + 10, curPosition2 + 10, curPosition3 + 10, 0);break;
    
    case 2:  moveServos(curPosition1 + 10, curPosition2, curPosition3, 0);break;
    case 3:  moveServos(curPosition1, curPosition2 + 10, curPosition3, 0);break;
    case 4:  moveServos(curPosition1, curPosition2, curPosition3  + 10, 0);break;
    case 5:  moveServos(curPosition1 - 10, curPosition2, curPosition3, 0);break;
    case 6:  moveServos(curPosition1, curPosition2 - 10, curPosition3, 0);break;
    case 7:  moveServos(curPosition1, curPosition2, curPosition3  - 10, 0);break;
    case 8:  moveServos(curPosition1 - 10, curPosition2 - 10, curPosition3 - 10, 0);break;
    case 9:  moveServos(700, 700, 700, 0);moveServos(1155, 865, 905, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 0:  mainMenu();moveServos(700, 700, 700, 0);break;
    case 101:moveServos(700, 700, 700, 0);moveServos(900, 940, 930, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 102:moveServos(700, 700, 700, 0);moveServos(940, 950, 875, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 103:moveServos(700, 700, 700, 0);moveServos(990, 960, 805, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 104:moveServos(700, 700, 700, 0);moveServos(925, 895, 940, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 105:moveServos(700, 700, 700, 0);moveServos(960, 910, 875, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 106:moveServos(700, 700, 700, 0);moveServos(1025, 935, 815, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 107:moveServos(700, 700, 700, 0);moveServos(960, 870, 950, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 108:moveServos(700, 700, 700, 0);moveServos(990, 875, 890, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 109:moveServos(700, 700, 700, 0);moveServos(1045, 895, 835, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 110:moveServos(700, 700, 700, 0);moveServos(1035, 855, 915, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 111:moveServos(700, 700, 700, 0);moveServos(1075, 845, 1020, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 112:moveServos(700, 700, 700, 0);moveServos(1155, 865, 905, 1);delay(500);moveServos(700, 700, 700, 0);break;
    case 201:moveServos(1700, 700, 700, 3);break;
    }
    Serial.println(curPosition1);
    Serial.println(curPosition2);
    Serial.println(curPosition3);*/
  }

void mainMenu()
{
   Serial.println("###########################");
   Serial.println("Choose the option: (z - return to main menu)");
   Serial.println("1. Push button 1");
   Serial.println("2. Push button 2");
   Serial.println("3. Push button 3");
   Serial.println("4. Push button 4");
   Serial.println("5. Push button 5");
   Serial.println("6. Push button 6");
   Serial.println("7. Push button 7");
   Serial.println("8. Push button 8");
   Serial.println("9. Push button 9");
   Serial.println("0. Push button 0");
   Serial.println("a. Push CANCEL button");
   Serial.println("b. Push ENTER button");
   Serial.println("c. Go to save position #1");
   Serial.println("d. Go to save position #2");
   Serial.println("e. Rest position");
   Serial.println("z. Return to main menu");
   Serial.println("###########################");
}


void moveServos(double pos1, double pos2, double pos3, int moveDelay)
    {
      double d1 = pos1 - curPosition1;
      double d2 = pos2 - curPosition2;
      double d3 = pos3 - curPosition3;
      double k1, k2 = 0;


      int maxNumber = getMaxNumber(abs(d1), abs(d2), abs(d3));
      if (maxNumber == 0)return;


      
      switch(maxNumber)
      {
        case 1: if(d1==0){k1 = 0;k2 = 0;}else{k1 = d2/abs(d1); k2 = d3/abs(d1);}
 
                if(d1 >= 0)
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
        case 2: if(d2==0){k1 = 0;k2 = 0;}else{k1 = d1/abs(d2); k2 = d3/abs(d2);}
 
   
                if(d2 >= 0)
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
        case 3: if(d3==0){k1 = 0;k2 = 0;}else{k1 = d1/abs(d3); k2 = d2/abs(d3);}

                if(d3 >= 0)
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
                    SERVO3.writeMicroseconds(i);
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
