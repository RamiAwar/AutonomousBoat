#include <NewPing.h>
#include "Motors.h"
#include "Sensors.h"

const byte trig1 = 13;
const byte echo1 = 12;
const byte trig2 = 11;
const byte echo2 = 10;
const byte trig3 = 7;
const byte echo3 = 6;

const byte motorRight = A0;
const byte motorLeft = A1;
const byte rightA = 53;
const byte rightB = 51;
const byte leftA = 49;
const byte leftB = 47;

const byte servoRight = 9;
const byte servoLeft = 8;

byte maxDistance = 200;

int targetSide;

bool right = true;
bool left = false;


NewPing sonarLeft1(trig1, echo1, maxDistance);
NewPing sonarLeft2(trig2, echo2, maxDistance);
NewPing sonarFront(trig3, echo3, maxDistance);


Sensors<trig1, echo1, trig2, echo2, trig3, echo3> sensors;

//<byte rightMotor, byte leftMotor, byte rightInputA, byte rightInputB, 
//byte leftInputA, byte leftInputB,byte leftRudder,byte rightRudder>

Motors< motorRight, motorLeft, rightA, rightB, leftA, leftB, servoLeft, servoRight> motors;

#define MAX_DISTANCE 200

bool start = false;


void setup() {
   Serial.begin(9600);


   motors.configure();
   
   //---------KING OF SPEED SPECIFIC---------------
   //Hold boat parallel to curtain when calibrating
   
   calibrate(left);
   
}
 
void loop() {

  sensors.average(sonarLeft1.ping_cm(), sonarLeft2.ping_cm(), sonarFront.ping_cm());


 

  if( true ){
    
    motors.forward(1000);
    kingOfSpeed();

  }

}


void kingOfSpeed(){

//    if( sensors.topSmoothed - targetSide > 30){
//      motors.turnRightRudder(100 - sensors.topSmoothed + targetSide);
//      motors.turnLeftRudder(100 + sensors.topSmoothed - targetSide);
//      return;
//    }else if( targetSide - sensors.topSmoothed > 30){
//      motors.turnRightRudder(100 + sensors.topSmoothed - targetSide);
//      motors.turnLeftRudder(100 - sensors.topSmoothed + targetSide);
//      return;
//    }

    int error = 0;

    

    // if no distance is being read by either sensor assume correct direction
//    if( sonarLeft1.ping_cm() == 0 || sonarLeft2.ping_cm() == 0) return;

    //PROPORTIONAL CONTROL
    //if boat is tilting to either direction, re calibrate to straighten  
    
    if( sensors.topSmoothed > sensors.botSmoothed){
        
        error = (sensors.topSmoothed - sensors.botSmoothed) + 20;
        
        motors.turnRightRudder(100 - error);
        motors.turnLeftRudder(100 + error);
        
    }else if( sensors.topSmoothed < sensors.botSmoothed){
        
        error = (sensors.botSmoothed - sensors.topSmoothed);
  
        motors.turnRightRudder(100 + error);
        motors.turnLeftRudder(100 - error);
        
    }

    


}

void calibrate(bool direction){
  
  if(direction == false){
    sensors.average(sonarLeft1.ping_cm(), sonarLeft2.ping_cm(), sonarFront.ping_cm());
    targetSide = (sensors.topSmoothed + sensors.botSmoothed) /2;  
  }
  
}







