#include <Arduino.h>
#include <Servo.h>

/////////////README////////////////
//RIGHT MOTOR AND LEFT MOTOR SHOULD HAVE ANALOG 
//WRITES EMBEDDED I.E. ANALOG PINS



template <byte rightMotor, byte leftMotor, byte rightInputA, byte rightInputB, byte leftInputA, byte leftInputB,byte leftRudder,byte rightRudder>

class Motors{

  private:

    Servo leftServo;
    Servo rightServo;

  public:

    void configure(){
      
      pinMode(rightMotor, OUTPUT);  
      pinMode(leftMotor, OUTPUT);
      pinMode(rightInputA, OUTPUT);
      pinMode(rightInputB, OUTPUT);
      pinMode(leftInputA, OUTPUT);
      pinMode(leftInputB, OUTPUT);

 
      leftServo.attach(leftRudder);
      rightServo.attach(rightRudder);
    }

    void setLeftSpeed(int speed){

      digitalWrite(leftInputA, HIGH);
      digitalWrite(leftInputB, LOW);
      
      analogWrite(leftMotor, speed);

    }

    void setRightSpeed(int speed){
      
      digitalWrite(rightInputA, HIGH);
      digitalWrite(rightInputB, LOW);

      analogWrite(rightMotor, speed);  
    }

    void forward(int speed){
      setRightSpeed(speed);
      setLeftSpeed(speed);  
    }

    void backward(){
      digitalWrite(rightInputA, LOW);
      digitalWrite(rightInputB, HIGH);
      digitalWrite(leftInputA, LOW);
      digitalWrite(leftInputB, HIGH);

      analogWrite(rightMotor, 200);
      analogWrite(leftMotor, 200);
    }

    void stopLeft(){
        digitalWrite(leftInputA, LOW);
        digitalWrite(leftInputB, LOW);
    }

    void stopRight(){
      digitalWrite(rightInputA, LOW);
      digitalWrite(rightInputB, LOW);  
    }

    void stop(){
      stopRight();
      stopLeft();  
    }


    //100 is the central position
    void turnLeftRudder(int angle){
      leftServo.write(angle - 5);  
    }

    void turnRightRudder(int angle){
      rightServo.write(angle - 10);  
    }

    void turnRight(){
        turnRightRudder(0);
        turnLeftRudder(200);
    }

    void turnLeft(){
      turnRightRudder(200);
      turnLeftRudder(0);  
    }



    

};
