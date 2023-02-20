#include <SPI.h>
#include <RF24.h>

class Drive {
  public:
    void init(int I1, int I2, int I3, int I4, int bt) {
      this->IN1 = I1; 
      this->IN2 = I2;
      this->IN3 = I3;
      this->IN4 = I4;
      this->STOP_BUTTON = bt;
//      steps_long = stp;

      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT);
      pinMode(STOP_BUTTON, INPUT_PULLUP);

      while (digitalRead(bt)== 1) { 
        stepper(-1);
      }
      this->position_steps = 0;
    }

    void setStepsLong(int steps) {this->steps_long = steps;}
    void setStopButton(int bt) {this->STOP_BUTTON = bt;}
      
    void stepper(int xw){
      int dir = (int) (xw / abs(xw));
      int steps = abs(xw);
      int i = 0;
      unsigned long int w_time = micros();
      while (i < steps) {
        if (micros() - w_time >= 1000) {
          switch(Step){
            case 0:
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, HIGH);
              break;
            case 1:
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
              break;
            case 2:
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, LOW);
              break;
            case 3:
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, LOW);
              break;
            case 4:
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
              break;
            case 5:
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
              break;
            case 6:
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
              break;
            case 7:
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, HIGH);
              break;
            default:
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
              break;
          }
          
          SetDirection(dir);
          i++;
          w_time = micros();
        }
      }
  }

  void angle_stepper(int angle) {
    int steps = (int) ((this->steps_long / 360) * angle);
    stepper(steps);
  }

  void setReversed() {
      this->dir_modify *= -1;
    }

  void setPositionSteps(int target) {
    int d_steps = (target % this->steps_long) - this->position_steps;
//    Serial.println(d_steps);
    stepper(d_steps);
  }

  void setPositionAngle(int target) {
    int d_steps = (int) ((((target%360) / 360.0) * this->steps_long) - this->position_steps);
    stepper(d_steps);
  }

  private:
    int steps_long;
    int Step;
    int IN1, IN2, IN3, IN4, STOP_BUTTON;
    int position_steps;
    int dir_modify = 1;
    
    void SetDirection(int dir){
      this->Step += this->dir_modify * dir;
      this->position_steps += dir;
      if(Step>7){Step=0;}
      if(Step<0){Step=7; }
    }
    
};




#define steps 4095

Drive drive;

int Steps = 0;
int steps_left=4095;

void setup(){
  Serial.begin(9600);

  drive.init(2, 3, 4, 5, 6);
  drive.setStepsLong(4095);
  delay(3000);

  drive.setPositionAngle(270);
  delay(1000);
  drive.setPositionAngle(90);

//  delay(5000);
}

void loop(){
//  drive.angle_stepper(180, 1);
}
