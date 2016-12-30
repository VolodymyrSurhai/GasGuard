#include <OLED_I2C.h>


const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;

const uint8_t SCREEN_HEIGHT = 64;

const uint8_t SCREEN_YELOW_HEIGHT = 16;

const uint8_t SCREEN_BLUE_HEIGHT = SCREEN_HEIGHT - SCREEN_YELOW_HEIGHT;
const uint8_t SCREEN_BLUE_HALF_HEIGHT = SCREEN_BLUE_HEIGHT / 2;

const uint8_t SCREEN_SDA = A4;
const uint8_t SCREEN_SCL = A5;

const uint8_t MARGINE = 4;


OLED  myOLED(SCREEN_SDA, SCREEN_SCL);
bool is_warning = false;

extern uint8_t MediumNumbers[];
extern uint8_t SmallFont[];


void draw_borders()
{
  // Vertical
  myOLED.drawLine(0, SCREEN_YELOW_HEIGHT, SCREEN_WIDTH, SCREEN_YELOW_HEIGHT);
  myOLED.drawLine(0, SCREEN_YELOW_HEIGHT + SCREEN_BLUE_HALF_HEIGHT, SCREEN_WIDTH, SCREEN_YELOW_HEIGHT + SCREEN_BLUE_HALF_HEIGHT);
  myOLED.drawLine(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, SCREEN_HEIGHT - 1);

  // Horizontal
  myOLED.drawLine(0, SCREEN_YELOW_HEIGHT, 0, SCREEN_HEIGHT);
  myOLED.drawLine(SCREEN_HALF_WIDTH, SCREEN_YELOW_HEIGHT, SCREEN_HALF_WIDTH, SCREEN_HEIGHT);
  myOLED.drawLine(SCREEN_WIDTH - 1, SCREEN_YELOW_HEIGHT, SCREEN_WIDTH - 1, SCREEN_HEIGHT);
}

void draw_warning()
{
  myOLED.print("! < WARNNING > !", CENTER, MARGINE);

  myOLED.drawRoundRect(0,0, SCREEN_WIDTH -1, SCREEN_YELOW_HEIGHT - 1);
//  for (auto x = 0; x < SCREEN_WIDTH; ++x)
//  {
//    for (auto y = 0; y < SCREEN_YELOW_HEIGHT; ++y)
//    {
//      myOLED.invPixel(x, y);
//    }
//  }
}

void setup()
{
  myOLED.begin();
}

void loop()
{
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  if (!is_warning)
  {
    draw_warning();
  }
  else
  {
    myOLED.print(String(millis()), CENTER, 4);
  }

  myOLED.setFont(MediumNumbers);

  //#TODO: Add constants on lines.
  myOLED.print(String(random(101, 2000)), LEFT + MARGINE, 16 + MARGINE);
  myOLED.print(String(random(101, 200)), RIGHT, 16 + MARGINE);
  myOLED.print(String(random(101, 200)), LEFT + MARGINE, 40 + MARGINE);
  myOLED.print(String(random(101, 200)), RIGHT, 40 + MARGINE);

  draw_borders();

  myOLED.update();
  delay (1000);
}
