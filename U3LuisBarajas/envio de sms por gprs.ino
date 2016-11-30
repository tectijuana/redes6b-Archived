#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // Configura el puerto serial para el SIM900

void setup()
{
  //digitalWrite(9, HIGH);   // Descomentar para activar la alimentación de la tarjeta por Software
  //delay(1000);             
  //digitalWrite(9, LOW);
  SIM900.begin(19200); //Configura velocidad del puerto serie para el SIM900
  Serial.begin(19200); //Configura velocidad del puerto serie del Arduino
  Serial.println("OK");
  delay (1000);
  SIM900.println("AT + CPIN = \"1111\""); //Comando AT para introducir el PIN de la tarjeta
  delay(25000); //Tiempo para que encuentre una RED
}

void mensaje_sms()
{
  Serial.println("Enviando SMS...");
  SIM900.print("AT+CMGF=1\r"); //Comando AT para mandar un SMS
  delay(1000);
  SIM900.println("AT + CMGS = \"6648004846\""); //Numero al que vamos a enviar el mensaje
  delay(1000);
  SIM900.println("SMS enviado desde un Arduino.");// Texto del SMS
  delay(100);
  SIM900.println((char)26);//Comando de finalizacion ^Z
  delay(100);
  SIM900.println();
  delay(5000); // Esperamos un tiempo para que envíe el SMS
  Serial.println("SMS enviado");
}

void loop()
{
  mensaje_sms(); //Envia SMS
  while (1); // Espera por tiempo indefinido
}
