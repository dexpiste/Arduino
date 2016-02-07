#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <VirtualWire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

const int BitPerSec = 2000;
const int DataPin = 2;

void setup()
{
  lcd.begin(20,2); 

  vw_set_ptt_inverted(true);
  vw_setup(BitPerSec); 
  vw_set_rx_pin(DataPin);  
  vw_rx_start(); 

  lcd.setCursor(0,0);
  lcd.print("Reciever Ready");
}

void loop()
{
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    lcd.setCursor(0,0);
    lcd.print("Got data");

    for (int i = 0; i < messageLength; i++)
    {
      lcd.write(message[i]);
    }
    delay(10);
  }
} 
