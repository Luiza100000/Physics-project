#define OLED_SOFT_BUFFER_64 // использовать буфер на стороне микроконтроллера
#define OLED_EXTFONTS       // указываем, что используются расширенные шрифты
#include <GyverOLED.h>
#include <Gyver433.h>
#include <GyverBME280.h>
GyverOLED<SSD1306_128x64> oled;
Gyver433_TX<2> tx;
GyverBME280 bme; 
byte sc=2;
void setup()
{
    // Serial.begin(57600);
    oled.init();
    oled.clear();
    oled.home();
    oled.setScale(sc);
    bme.begin();  
}
struct DataPack {
  float Tm,Hm,Pr,H;
};
DataPack data;

void loop()
{
    data.Tm=bme.readTemperature();
    data.Hm=bme.readHumidity();
    data.Pr=pressureToMmHg(bme.readPressure());
    data.H=pressureToAltitude(bme.readPressure());
    oled.clear();
    oled.setCursor(0, sc*0);
    //oled.print("T=");
    oled.print(data.Tm);
    oled.print("C");
    oled.setCursor(0, sc*1);
    //oled.print("H=");
    oled.print(data.Hm);
    oled.print("%Hm");
    oled.setCursor(0, sc*2);
    //oled.print("P=");
    oled.print(data.Pr);
    oled.print("mmHg");
    oled.setCursor(0, sc*3);
    //oled.print("h=");
    oled.print(data.H);
    oled.print("m");
    oled.update();
    tx.sendData(data);
    delay(1000);
}