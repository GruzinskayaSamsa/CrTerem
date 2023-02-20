#include <SPI.h>
#include <RF24.h>
RF24 radio; // порты D9, D10: CSN CE
const uint32_t pipe = 111156789; // адрес рабочей трубы;

byte data[32] = {0x47, 0, 1, 0, 2};

void setup() {
  Serial.begin(115200);
  Serial.println("TransmitterTester ON");

  radio = radio_transmitter_init(9, 10);
}

void loop() {
  radio.write(&data, 32);
//  Serial.println("data= " + String(data));
//  data++;
}


RF24 radio_transmitter_init(int CSN, int CE) {
  RF24 radio(CSN, CE);
  radio.begin();                // инициализация
  delay(2000);
  radio.setDataRate(RF24_1MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
  radio.setPALevel(RF24_PA_MAX); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setChannel(0x6f);         // чтоб хоть какой-то был
  radio.setAutoAck(false);       // автоответ
  radio.powerUp();               // включение или пониженное потребление powerDown - powerUp
  radio.stopListening();  //радиоэфир не слушаем, только передача
  radio.openWritingPipe(111156789);   // это дефолтное значение. можно поменять
}

void radio_transmit(RF24, uint8_t &data){  //хз зачем, дефолтный метод удобнее
  radio.write(data, sizeof(data)); 
}
