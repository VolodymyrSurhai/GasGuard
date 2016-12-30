#include <OLED_I2C.h>



OLED  myOLED(SDA, SCL);
bool warning = false;

extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];

void setup()
{
  myOLED.begin();
}

void loop()
{
  myOLED.clrScr();

  if (warning)
  {
    myOLED.setFont(SmallFont);
    myOLED.print("! < WARNNING > !", CENTER, 4);
    for (auto x = 0; x < 128; ++x)
    {
      for (auto y = 0; y < 16; ++y)
      {
        myOLED.invPixel(x, y);
      }
    }
  }
  myOLED.setFont(BigNumbers);
  myOLED.print("100.12", RIGHT, 16);
  myOLED.print("59", RIGHT, 40);

  myOLED.update();
  delay (5000);
}
