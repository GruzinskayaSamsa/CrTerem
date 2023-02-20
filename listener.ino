#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


typedef struct {
  float tempC = 0;
  float tempF = 0;
  float humidity = 0;
  float soilMoisture = 0;
} STHLData;

typedef struct {
  uint8_t tp;
  uint16_t id;
  uint8_t len;
  uint8_t s;
  uint8_t data[]; 

} Message;


RF24 radio(9, 10); // порты D9, D10: CSN CE

const uint32_t pipe = 111156789; // адрес рабочей трубы;
byte data[32];
int scn;  //счетчик циклов прослушивания эфира
int sg;  //счетчик числа принятых пакетов с передатчика

void setup() {
  Serial.begin(9600);
  Serial.println("ReceiverTester ON");

  radio_listener_init(radio);
}

void loop() {
    if (radio.available())
    {
      radio.read(data, 32);

      Message mess = parse_data(data);
      
    }
    delay(20);
}


void radio_listener_init(RF24 radio) {
  radio.begin();  // инициализация
  delay(2000);
  radio.setDataRate(RF24_1MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
  radio.setChannel(0x6f);         // установка канала
  radio.setAutoAck(false);       // автоответ
  radio.openReadingPipe(1, pipe); // открыть трубу на приём
  radio.startListening();        // приём
}


Message parse_data(uint8_t data[]) {
  Message mess;

  mess.tp = data[0];
  mess.id = ((uint16_t)data[1])<<8 | data[2];
  mess.len = data[3];
  mess.s = data[4];

  switch (mess.tp) {
    case 0x47:
      /* хз пока, как пакет дальше выглядит */
        Serial.println(mess.s);
    default:
      break;
      
  }

  return mess;
}
