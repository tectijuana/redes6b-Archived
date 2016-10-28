/* YourDuino SoftwareSerialExample1Remote
   - Used with YD_SoftwareSerialExampleRS485_1 on another Arduino
   - Remote: Receive data, loop it back...
   - Connect this unit Pins 10, 11, Gnd
   - To other unit Pins 11,10, Gnd  (Cross over)
   - Pin 3 used for RS485 direction control   
   - Pin 13 LED blinks when data is received  
   
   Questions: terry@yourduino.com 
*/

/*-----( Import needed libraries )-----*/
#include <SoftwareSerial.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin

#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Pin13LED         13

/*-----( Declare objects )-----*/
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

/*-----( Declare Variables )-----*/
int byteReceived;
int byteSend;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  // Start the built-in serial port, probably to Serial Monitor
  Serial.begin(9600);
  Serial.println("SerialRemote");  // Can be ignored
  
  pinMode(Pin13LED, OUTPUT);   
  pinMode(SSerialTxControl, OUTPUT);  
  
  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver
  
  // Start the software serial port, to another device
  RS485Serial.begin(4800);   // set the data rate 
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  //Copy input data to output  
  if (RS485Serial.available()) 
  {
    byteSend = RS485Serial.read();   // Read the byte 
    
    digitalWrite(Pin13LED, HIGH);  // Show activity
    delay(10);              
    digitalWrite(Pin13LED, LOW);   
    
    digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit    
    RS485Serial.write(byteSend); // Send the byte back
    delay(10);   
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit      
//    delay(100);
  }// End If RS485SerialAvailable
  
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//NONE

//*********( THE END )***********
