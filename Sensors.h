#include <Arduino.h>
#include <NewPing.h>

template <byte trig1, byte echo1, byte trig2, byte echo2, byte trig3, byte echo3>

class Sensors{

  private: 

    int topReading, botReading, frontReading;
    int topTotal, botTotal, frontTotal;
    static const byte numReadings = 70;
    byte index;
    int topReadings[numReadings], botReadings[numReadings], frontReadings[numReadings];
    

  public:

    int topSmoothed, botSmoothed, frontSmoothed;
      
    void resetSensors(){
      
      pinMode(echo1,OUTPUT);
      pinMode(echo2, OUTPUT);
      pinMode(echo3, OUTPUT);

      digitalWrite(echo1,LOW);
      digitalWrite(echo2, LOW);
      digitalWrite(echo3, LOW);

      pinMode(echo1,INPUT);
      pinMode(echo2, INPUT);
      pinMode(echo3, INPUT);
    }

    

    void sense(int sonar1, int sonar2, int sonar3){
      
      topReading = sonar1;
      botReading = sonar2;
      frontReading = sonar3;

      topTotal -= topReadings[index];
      botTotal -= botReadings[index];
      frontTotal -= frontReadings[index];

      topReadings[index] = topReading;
      botReadings[index] = botReading;
      frontReadings[index] = frontReading;

      topTotal += topReadings[index];
      botTotal += botReadings[index];
      frontTotal += frontReadings[index];

      index++;
      if(index >= numReadings) index = 0;

      topSmoothed = topTotal / numReadings;
      botSmoothed = botTotal / numReadings;
      frontSmoothed = frontTotal / numReadings;
    }

    

    void view(){
      Serial.print("Sensor 1: ");
      Serial.print(topSmoothed);
      Serial.print("   Sensor 2: ");
      Serial.println(botSmoothed);

    }



    void average(int sonar1, int sonar2, int sonar3){
       for(byte i = 0; i < numReadings; i++){
          resetSensors();
          sense(sonar1, sonar2, sonar3);
       }
    }

    

};
