/***   Included libraries  ***/
#include <Servo.h>


/***   Global variables and function definition  ***/
Servo servo_left;
Servo servo_right;
int infrared_left = 2;
int infrared_right = 3;
float irRight = 0;
float irLeft = 0;

int previousMillis=0;
int turn = 0; // right:0; left:1;

boolean changeDirection = false;

/***   Setup  ***/
void setup() {
  Serial.begin(9600);
    servo_left.attach(6);
    servo_right.attach(9);
    pinMode(infrared_left, INPUT);
    pinMode(infrared_right, INPUT);

    previousMillis = millis();
    
}

/***   Loop  ***/
void loop() {
    irRight = digitalRead(infrared_right);
    irLeft = digitalRead(infrared_left);
    
    if (irRight == 1 && irLeft == 1 && changeDirection ) {
      changeDirection = false;
      
      servo_right.write(180);   
      servo_left.write(0);
      return;
    }

    
    if (irRight == 0 || turn == 0) {
      
        if(turn != 0)
          changeDirection = true;
        turn = 0;
        servo_left.write(60);
        
    } else {
        servo_left.write(90);
    }
    
    if (irLeft == 0 || turn == 1) {
        if(turn != 1)
          changeDirection = true;
        turn = 1;
        servo_right.write(120); 
        checkServos();
        //Serial.println("left black");
    } else {
        servo_right.write(90); 
    }

    checkServos();
}

void checkServos() {
  
  int currentMillis = millis();
  int minimalTenMillis = currentMillis - previousMillis;
  if ( minimalTenMillis < 10 )
    delay(minimalTenMillis);
  previousMillis = currentMillis;
}

