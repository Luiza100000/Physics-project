#define OLED_SOFT_BUFFER_64 // использовать буфер на стороне микроконтроллера
#define OLED_EXTFONTS       // указываем, что используются расширенные шрифты
#include <GyverOLED.h>
#include <Gyver433.h>
GyverOLED<SSD1306_128x64> oled;
Gyver433_RX<2, 20> rx;
byte sc = 2;
unsigned long time;
void setup()
{
    // Serial.begin(57600);
    oled.init();
    oled.clear();
    oled.home();
    oled.setScale(sc);
    oled.setCursor(0, sc * 0);
    attachInterrupt(0, isr, CHANGE);
}
struct DataPack
{
    float Tm, Hm, Pr, H;
};

void isr()
{
    rx.tickISR();
}

void loop()
{
    if (rx.gotData())
    {
        time = millis();
        DataPack data;
        oled.clear();
        oled.setCursor(0, sc * 0);
        if (rx.readData(data))
        {
            // oled.print("T=");
            oled.print(data.Tm);
            oled.print("C");
            oled.setCursor(0, sc * 1);
            // oled.print("H=");
            oled.print(data.Hm);
            oled.print("%Hm");
            oled.setCursor(0, sc * 2);
            // oled.print("P=");
            oled.print(data.Pr);
            oled.print("mmHg");
            oled.setCursor(0, sc * 3);
            // oled.print("h=");
            oled.print(data.H);
            oled.print("m");
            oled.update();
        }
        else
        {
            oled.print("Data error");
            oled.update();
        }
    }
    if (millis()-time>2000)
    {
        oled.clear();
        oled.setCursor(0, sc * 1);
        oled.print("  NO DATA");
        oled.update();
    }
}