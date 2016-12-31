#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <OLED_I2C.h>

const uint8_t HDS10_PIN = A2;
const uint8_t MQ135_PIN = A3;

const uint8_t SCREEN_SDA_PIN = A4;
const uint8_t SCREEN_SCL_PIN = A5;

const uint8_t DHT_PIN = 13;
const auto DHT_TYPE = DHT11;

const uint8_t SCREEN_WIDTH = 128;
const uint8_t SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;

const uint8_t SCREEN_HEIGHT = 64;

const uint8_t SCREEN_YELOW_HEIGHT = 16;

const uint8_t SCREEN_BLUE_HEIGHT = SCREEN_HEIGHT - SCREEN_YELOW_HEIGHT;
const uint8_t SCREEN_BLUE_HALF_HEIGHT = SCREEN_BLUE_HEIGHT / 2;

const uint8_t MARGINE = 4;
const uint8_t FIRST_LINE = 16;
const uint8_t SECOND_LINE = 40;


OLED  myOLED(SCREEN_SDA_PIN, SCREEN_SCL_PIN);
DHT_Unified dht(DHT_PIN, DHT_TYPE);

bool is_warning = false;
uint32_t mq135_sensorValue = 0;
uint32_t hds10_sensorValue = 0;
uint32_t dht_temperature_sensorValue = 0;
uint32_t dht_humidity_sensorValue = 0;

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

void read_data_from_sensor()
{
  mq135_sensorValue = analogRead(MQ135_PIN);
  hds10_sensorValue = analogRead(HDS10_PIN);

  sensors_event_t event;
  dht.temperature().getEvent(&event);

  dht_temperature_sensorValue = event.temperature;

  dht.humidity().getEvent(&event);
  dht_humidity_sensorValue = event.relative_humidity;
}

void setup()
{
  myOLED.begin();
  dht.begin();
}

void loop()
{
  read_data_from_sensor();
  
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

  myOLED.printNumI(mq135_sensorValue, MARGINE, FIRST_LINE + MARGINE,3,'0');
  myOLED.printNumI(dht_temperature_sensorValue, SCREEN_HALF_WIDTH + MARGINE, FIRST_LINE + MARGINE,3,'0');
  myOLED.printNumI(hds10_sensorValue, MARGINE, SECOND_LINE + MARGINE,3,'0');
  myOLED.printNumI(dht_humidity_sensorValue, SCREEN_HALF_WIDTH + MARGINE, SECOND_LINE + MARGINE,3,'0');

  draw_borders();

  myOLED.update();
  delay (1000);
}
