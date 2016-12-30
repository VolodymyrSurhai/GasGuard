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
const uint8_t FIRST_LINE = 16;
const uint8_t SECOND_LINE = 40;



OLED  myOLED(SCREEN_SDA, SCREEN_SCL);
bool is_warning = false;

extern uint8_t MediumNumbers[];
extern uint8_t SmallFont[];


void draw_borders()
{
  myOLED.drawRoundRect(0, SCREEN_YELOW_HEIGHT, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
  
  // Vertical line in center
  myOLED.drawLine(0, SCREEN_YELOW_HEIGHT + SCREEN_BLUE_HALF_HEIGHT, SCREEN_WIDTH, SCREEN_YELOW_HEIGHT + SCREEN_BLUE_HALF_HEIGHT);

  // Horizontal line in center
  myOLED.drawLine(SCREEN_HALF_WIDTH, SCREEN_YELOW_HEIGHT, SCREEN_HALF_WIDTH, SCREEN_HEIGHT);
}

void draw_warning()
{
  myOLED.print("!!! < WARNNING > !!!", CENTER, MARGINE);

  myOLED.drawRoundRect(0,0, SCREEN_WIDTH -1, SCREEN_YELOW_HEIGHT - 1);
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
  myOLED.printNumI(random(0, 101), MARGINE, FIRST_LINE + MARGINE,3,'0');
  myOLED.printNumI(random(0, 101), SCREEN_HALF_WIDTH + MARGINE, FIRST_LINE + MARGINE,3,'0');
  myOLED.printNumI(random(0, 101), MARGINE, SECOND_LINE + MARGINE,3,'0');
  myOLED.printNumI(random(0, 101), SCREEN_HALF_WIDTH + MARGINE, SECOND_LINE + MARGINE,3,'0');

  draw_borders();

  myOLED.update();
  delay (1000);
}
