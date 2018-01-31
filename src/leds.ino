//#include <Arduino.h>
#include <WS2812FX.h>

#define LED_COUNT 50 // кол-во светодиодов в гирлянде
#define LED_PIN 6 // пин для вывода на гирлянду
#define DEF_SPEED 2500 // задержка в мс, по дефолту 1000
#define TIMER_MS 5000 // время длительности одного эффекта в мс

WS2812FX strip = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long last_change = 0;
unsigned long now = 0;
unsigned long t = 6;
// some common colors
/*
#define RED        0xFF0000
#define GREEN      0x00FF00
#define BLUE       0x0000FF
#define WHITE      0xFFFFFF
#define BLACK      0x000000
#define YELLOW     0xFFFF00
#define CYAN       0x00FFFF
#define MAGENTA    0xFF00FF
#define PURPLE     0x400080
#define ORANGE     0xFF3000
#define ULTRAWHITE 0xFFFFFFFF
*/
//
//int colors[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, PURPLE, ORANGE};
long int colors[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0x400080, 0xFF3000};

//int colors[] = {0xFF0000,0x00FF00,0x0000FF,0xFFFF00,0x00FFFF,0xFF00FF,0x400080,0xFF3000};

int modes[] = {15,7,51,46,8,2,32,10,38,3,48,11,33,12,5,42,9,17,39,12,39}; // массив с желаемыми ID эффектов
//  2 - Breath (set color)
//  3 - Color Wipe (set color) (short)
//  5 - Color Wipe Inverse (set color) (short)
//  7 - Color Wipe Random !
//  8 - Random Color !-
//  9 - Single Dynamic !--
// 10 - Multi Dynamic !
// 11 - Rainbow !
// 12 - Rainbow Cycle !
// 13 - Scan (set color) (short)
// 14 - Dual Scan (set color) (short)
// 15 - Fade (set color) (x3)
// 17 - Theater Chase Rainbow (x3)
// 20 - Twinkle Random !--
// 32 - Chase Random
// 33 - Chase Rainbow
// 38 - Chase Blackout Rainbow --
// 39 - Color Sweep Random
// 42 - Running Random (x3)
// 46 - Fireworks Random (x3)
// 48 - Fire Flicker (x3)
// 51 - Circus combustus (x3) (short)


int i = 0; // счётчик индекса в массиве эффектов
int l = 0; // индекс прошлого (last) эффекта
//int m = 13; // кол-во эффектов, см. массив modes
int m = sizeof(modes)/sizeof(int); // кол-во эффектов, см. массив modes


void setup() {
  strip.init();
  strip.setBrightness(70); // установка яркости 0 - 255
  strip.setSpeed(DEF_SPEED); // установка скорости (задержки)
  strip.setColor(0xFF0400); // дефолтный цвет
  strip.setMode(8); // стартовая установка 8го режима
  strip.start();
}

void loop() {
  now = millis();
  strip.service();
  if(now - last_change > TIMER_MS*t) {
      strip.setSpeed(DEF_SPEED); // вернуть скорость на дефолт
      t = 6;
    if(modes[i] == 15 || modes[i] == 17 || modes[i] == 42 || modes[i] == 46 || modes[i] == 48 || modes[i] == 51){
      strip.setSpeed(DEF_SPEED*3); // очень быстрые - замедлить, больше задержка х3
    }
    if(modes[i] == 2 || modes[i] == 3 || modes[i] == 5 || modes[i] == 13 || modes[i] == 14 || modes[i] == 15){
      strip.setColor(colors[random(0,7)]); // изменение базового цвета
    }
    if(modes[i] == 3 || modes[i] == 5  || modes[i] == 13  || modes[i] == 14  || modes[i] == 48  || modes[i] == 51){
      t = 1;
    }

    strip.setMode(modes[i]);
    last_change = now;
    l = modes[i];
    //i = random(0,12);
    i++;
    if(i == m){
      i = 0;
    }
  }
}
