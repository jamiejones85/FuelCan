#include <mcp_can.h>
#include <SPI.h>

int fuel = 0;
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN); 




void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];



    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned int canId = CAN.getCanId();

        if (canId == 0x355) {
          uint16_t soc = (buf[1] << 8) + buf[0];
          Serial.println(soc);
          Fuel(100 - soc);
        }
    }
}

void Fuel(int amount)
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
 
  if (amount >= 90)
  {
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    return;
  }
  if (amount >= 75)
  {
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    return;
  }
  if (amount >= 50)
  {
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    return;
  }
  if (amount >= 25)
  {
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    return;
  }
  if (amount >= 10)
  {
    pinMode(6, OUTPUT);
    digitalWrite(6, LOW);
    return;
  }
  if (amount >= 0)
  {
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
    return;
  }
}
