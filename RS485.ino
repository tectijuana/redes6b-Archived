#include <SoftwareSerial.h>
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin
#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
#define Pin13LED         13

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

int byteReceived;
int byteSend;

void setup() 
{
  // Start the built-in serial port, probably to Serial Monitor
  Serial.begin(9600);
  Serial.println("PRACTICA RS485 REDES");
  
  pinMode(Pin13LED, OUTPUT);   
  pinMode(SSerialTxControl, OUTPUT);    
  
  digitalWrite(SSerialTxControl, RS485Receive);  
  RS485Serial.begin(4800);

}


void loop()   
{
  digitalWrite(Pin13LED, HIGH);  
  if (Serial.available())
  {
    byteReceived = Serial.read();
    
    digitalWrite(SSerialTxControl, RS485Transmit);  
    RS485Serial.write(byteReceived);              
    digitalWrite(Pin13LED, LOW);  
    delay(10);
    digitalWrite(SSerialTxControl, RS485Receive);  
    }
  
  if (RS485Serial.available())  
   {
    digitalWrite(Pin13LED, HIGH);
    byteReceived = RS485Serial.read();
    Serial.write(byteReceived);       
    delay(10);
    digitalWrite(Pin13LED, LOW);  
   }  
  }

