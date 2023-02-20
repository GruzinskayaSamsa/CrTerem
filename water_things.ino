#define WATER_LEVEL 3
#define WATER_MOTOR 4


void setup() {
  Serial.begin(9600);
  
  pinMode(WATER_LEVEL, INPUT_PULLUP);
  pinMode(WATER_MOTOR, OUTPUT);
  digitalWrite(WATER_MOTOR, LOW);
}

void loop() {

  int water_level = digitalRead(WATER_LEVEL);
  Serial.println(water_level);

}
