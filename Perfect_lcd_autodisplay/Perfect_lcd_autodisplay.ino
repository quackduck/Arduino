#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x3F, 16, 1);

void setup() { 
  


  lcd.backlight ();
  lcd.init ();
}

void loop() {
  lcd.print("is this gone?");
  delay(1000);
  lcdtoobig ("whatever 123456789012345678901234567890diffeliursg",16,1); 

}
void
lcdtoobig (String s,int a,int b)
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
