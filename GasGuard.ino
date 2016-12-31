#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <OLED_I2C.h>
#include <MQ135.h>

extern uint8_t SmallFont[];

namespace {
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


const OLED  my_oled(SCREEN_SDA_PIN, SCREEN_SCL_PIN);
const DHT_Unified dht(DHT_PIN, DHT_TYPE);
const MQ135 mq135(MQ135_PIN);

bool is_warning = false;
float mq135_resistance_value = 0;

float mq135_co = 0.0;
float mq135_co2 = 0.0;
float mq135_ethanol = 0.0;
float mq135_nh4 = 0.0;
float mq135_toluene = 0.0;
float mq135_acetone = 0.0;

uint32_t hds10_sensor_value = 0;

uint32_t dht_temperature_sensor_value = 0;
uint32_t dht_humidity_sensor_value = 0;

void draw_warning()
{
  my_oled.print("!!! < WARNNING > !!!", CENTER, MARGINE);

  my_oled.drawRoundRect(0, 0, SCREEN_WIDTH - 1, SCREEN_YELOW_HEIGHT - 1);
}

void read_data_from_sensor()
{
  mq135_resistance_value = mq135.getResistance();

  mq135_co = mq135.getCO(mq135_resistance_value);//co ppm
  mq135_co2 = mq135.getCO2(mq135_resistance_value);//co2 ppm
  mq135_ethanol = mq135.getEthanol(mq135_resistance_value);//ethanol ppm
  mq135_nh4 = mq135.getNH4(mq135_resistance_value); //NH4 ppm
  mq135_toluene = mq135.getToluene(mq135_resistance_value); //toluene ppm
  mq135_acetone = mq135.getAcetone(mq135_resistance_value); //acetone ppm

  hds10_sensor_value = analogRead(HDS10_PIN);

  sensors_event_t event;
  dht.temperature().getEvent(&event);

  dht_temperature_sensor_value = event.temperature;

  dht.humidity().getEvent(&event);
  dht_humidity_sensor_value = event.relative_humidity;
}

} // namespace

void setup()
{
  my_oled.begin();
  dht.begin();
}

void loop()
{
  read_data_from_sensor();

  my_oled.clrScr();
  my_oled.setFont(SmallFont);
  if (!is_warning)
  {
    draw_warning();
  }
  else
  {
    my_oled.print(String(millis()), CENTER, 4);
  }

  my_oled.print("co: " + String(mq135_co), MARGINE, 16);
  my_oled.print("co2: " + String(mq135_co2), MARGINE, 24);
  my_oled.print("ethanol: " + String(mq135_ethanol), MARGINE, 32);
  my_oled.print("NH4: " + String(mq135_nh4), MARGINE, 40);
  my_oled.print("toluene: " + String(mq135_toluene), MARGINE, 48);
  my_oled.print("acetone: " + String(mq135_acetone), MARGINE, 56);

  my_oled.print("t: " + String(dht_temperature_sensor_value), RIGHT, 16);
  my_oled.print("h: " + String(dht_humidity_sensor_value), RIGHT, 24);
  my_oled.print("hds: " + String(hds10_sensor_value), RIGHT, 32);

  my_oled.drawLine(SCREEN_HALF_WIDTH + 24, SCREEN_YELOW_HEIGHT, SCREEN_HALF_WIDTH + 24, SCREEN_HEIGHT);
  
  my_oled.update();
  delay (1000);
}
