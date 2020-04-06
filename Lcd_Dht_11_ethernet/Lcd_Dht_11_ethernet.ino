#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd (0x3F, 16, 2);
IPAddress ip (192, 168, 2, 4);  //don't change this or i will kick you

EthernetClient client;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
 
byte customChar[] = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


int hue;
unsigned long myChannelNumber = 643477;
const char * myWriteAPIKey = "9M9T11FTPIQGW8Q9";
unsigned long previousMillis = 0;
const long interval = 20000;
bool h = LOW;     
unsigned int r, g, b;


void setup ()
{
  Serial.begin (115200);
  pinMode (3, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  digitalWrite (8, HIGH);
  lcd.backlight ();
  lcd.init ();
  lcd.setCursor (0, 0);   
  Ethernet.init (10);
  Ethernet.begin (mac, ip);
  dht.begin ();
  ThingSpeak.begin (client);
  lcd.createChar (0, customChar);
  lcd.clear ();
  
  
}


void
loop ()
{
  int humidity = dht.readHumidity ();
  int temperature = dht.readTemperature (); 
  unsigned long currentMillis = millis ();
  h = LOW;    
  if (currentMillis - previousMillis >= interval)
    {

      previousMillis = currentMillis;
      ThingSpeak.setField (1, temperature);
      ThingSpeak.setField (2, humidity);


      int x = ThingSpeak.writeFields (myChannelNumber, myWriteAPIKey);
      if (x == 200)
  {
    Serial.println ("Channel update successful.");
  }
      else
  {
    Serial.println ("Problem updating channel. HTTP error code " +
        String (x));
  }

      lcd.clear ();
    }









  if (temperature >= 23 && temperature <= 26)
    {
      hue = 62;
    }
  if (temperature <= 22)
    {
      hue = 177;
    }
  if (temperature >= 27)
    {
      hue = 2;
    }
  if (humidity >= 50||humidity<=30)
    {
      h = HIGH;
    }



  HSBToRGB (hue, 255, 255, &r, &g, &b);
  analogWrite (3, r);
  analogWrite (5, g);
  analogWrite (6, b);
  digitalWrite (9, h);
  Serial.print (temperature);
  Serial.print (" °C ");
  Serial.print (humidity);
  Serial.println (" %");
  lcd.setCursor (0, 0);
  lcd.print ("Temp = ");
  lcd.print (temperature);
  lcd.write (0);
  lcd.print ("C ");
  lcd.setCursor (0, 1);
  lcd.print ("Hum. = ");
  lcd.print (humidity);
  lcd.print (" %");
  delay (1250);     // DHT11 sampling rate is 1HZ.
  


}






/*void
autolcd (String s)
{

 
lcd.print (s);
delay(1000);

  int i = 0;
  int len = s.length ();
  len = len - 16;   //because the lcd doesnt have to be completely clear  
  for (i = 0;     //do this once when run for the first time
       i < len;     // until this is false for loop continues
       i++      //  do this every time the for loop is run this is also known as the increment 
             )
    {
      lcd.scrollDisplayLeft (); // Loop to do something len times
      delay (500);
    }
delay(1000);


}


*/

void
HSBToRGB (unsigned int inHue, unsigned int inSaturation,
    unsigned int inBrightness, unsigned int *oR, unsigned int *oG,
    unsigned int *oB)
{
  if (inSaturation == 0)
    {
      // achromatic (grey)
      *oR = *oG = *oB = inBrightness;
    }
  else
    {
      unsigned int scaledHue = (inHue * 6);
      unsigned int sector = scaledHue >> 8; // sector 0 to 5 around the color wheel
      unsigned int offsetInSector = scaledHue - (sector << 8);  // position within the sector
      unsigned int p = (inBrightness * (255 - inSaturation)) >> 8;
      unsigned int q =
  (inBrightness * (255 - ((inSaturation * offsetInSector) >> 8))) >> 8;
      unsigned int t =
  (inBrightness *
   (255 - ((inSaturation * (255 - offsetInSector)) >> 8))) >> 8;

      switch (sector)
  {
  case 0:
    *oR = inBrightness;
    *oG = t;
    *oB = p;
    break;
  case 1:
    *oR = q;
    *oG = inBrightness;
    *oB = p;
    break;
  case 2:
    *oR = p;
    *oG = inBrightness;
    *oB = t;
    break;
  case 3:
    *oR = p;
    *oG = q;
    *oB = inBrightness;
    break;
  case 4:
    *oR = t;
    *oG = p;
    *oB = inBrightness;
    break;
  default:    // case 5:
    *oR = inBrightness;
    *oG = p;
    *oB = q;
    break;
  }
    }
}
