#include <FastLED.h>
#include <TM1637.h>
#include <MsTimer2.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define NUM_LEDS  81
#define spotSize  4
#define LED_PIN   4
#define Button  5
int brightness = 20;
const int range = 18;
boolean clicked = false;
int tracker = 0;
unsigned long now = millis();
int CLK = 2;
int DIO = 3;
TM1637 tm(CLK,DIO);
Adafruit_SSD1306 display(-1);
int brick = 0; 
int wheat = 0; 
int wood = 0; 
int rock = 0; 
int sheep = 0;


// Brick::Red, Boulder::Cyan, Logs::Green, Hay::Orange, Sheep::white, Desert::Black
uint32_t resource[range] = {CRGB::Red,CRGB::Red,CRGB::Red,CRGB::Cyan,CRGB::Cyan,CRGB::Cyan,
CRGB::Green,CRGB::Green,CRGB::Green,CRGB::Green,CRGB::Orange,CRGB::Orange,CRGB::Orange,CRGB::Orange,
CRGB::White,CRGB::White,CRGB::White,CRGB::White};
CRGB all[5] = {CRGB::Red,CRGB::Green,CRGB::Orange,CRGB::Cyan,CRGB::White};
//int temp[range] = {5,2,6,3,8,10,9,12,11,4,8,10,9,4,5,6,3,11};
int values[range] = {11,3,6,5,4,9,10,8,4,11,12,9,10,8,3,6,2,5};
int spotValues[range];
CRGB leds[NUM_LEDS];
CRGB currentColors[range];

void setSpot (int spot, CRGB color, boolean save){  
    int currentLED = (spot - 1)*spotSize;
    int lastLED = currentLED + spotSize; 
    for (currentLED; currentLED < lastLED; currentLED++) {   
      leds[currentLED] = color;
    }
    if (save){
      currentColors[spot-1] = color; 
    }
}

boolean arrayIncludeElement(int randArray[], int input, int range) {
  for (int i = 0; i < range; i++) {   
    if (randArray[i] == input) {
      return true;
    }
  }
  return false;
}

void rollDice() {
  // Roll dice
  // randomSeed(analogRead(0));
  int roll = random(1,7) + random(1,7);
  tm.init(); // clear
  if (roll < 10){
    tm.display(3,roll);
  } else{
    tm.display(2,1);
    tm.display(3,roll-10);
  }
  // show dice value
  for (int i = 0; i < range; i++) {   
    setSpot(i+1, CRGB::Black, false);
  }
  FastLED.show();  
  for (int i = range-1; i >= (range-roll); i--) {   
    setSpot(i+1, CRGB::White, false);
    FastLED.show();
    delay(100);
  }
  delay(500);
  // show only spots with that roll
  int locations[range];
  int count = 0;
  if (roll == 7){
    for (int a = 0; a < 3; a++) {
      for (int i = 0; i < range; i++) {   
        setSpot(i+1, CRGB::Red, false);
      }
      FastLED.show();
      delay(500);
      if (a < 2){
        for (int i = 0; i < range; i++) {   
          setSpot(i+1, CRGB::Black, false);
        }
        FastLED.show();
        delay(500);
      }
    }
  } else{
    for (int i = 0; i < range; i++) {   
      if (values[i] == roll){
        setSpot(i+1, currentColors[i], false);
        if (currentColors[i] == all[0]){
          brick++;
        }
        if (currentColors[i] == all[1]){
          wood++;
        }
        if (currentColors[i] == all[2]){
          wheat++;
        }
        if (currentColors[i] == all[3]){
          rock++;
        }
        if (currentColors[i] == all[4]){
          sheep++;
        }
      }
      else{
        setSpot(i+1, CRGB::Black, false);
      }
    }
    updateDisplay(brick, wheat, wood, rock, sheep);
    FastLED.show();
    //delay(5000);
    for (int i = 0; i < 4; i++){
      leds[72] = all[i];
      leds[73] = all[i];
      leds[76] = all[i];
      leds[79] = all[i];
      FastLED.show(); 
      delay(1500);
    }
  }
  // updateDisplay(brick, wheat, wood, rock, sheep);
  // reset board
  for (int i = 0; i < range; i++) {   
    setSpot(i+1, currentColors[i], true);
  }
  FastLED.show();
}

void updateDisplay(int brick, int wheat, int wood, int rock, int sheep){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Brick: " + String(brick));
  display.setCursor(0, 10);
  display.println("Wheat: " + String(wheat));
  display.setCursor(0, 20);
  display.println("Sheep: " + String(sheep));
  display.setCursor(70, 0);
  display.println("Wood: " + String(wood));
  display.setCursor(70, 10);
  display.println("Rock: " + String(rock));
  display.display();
}


void setup() {
   // set up display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  updateDisplay(brick, wheat, wood, rock, sheep);
  // put your setup code here, to run once:
  tm.init();
  // set brightness; 0-7
  tm.set(1);
  pinMode(Button, INPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  leds[74] = CRGB::Red;
  leds[75] = CRGB::Green;
  leds[77] = CRGB::Orange;
  leds[78] = CRGB::Cyan;
  leds[80] = CRGB::White;

  // set up random board 
  randomSeed(analogRead(0));
  int first = random(range);
  int randArray[range] = {first};
  int num = 1;
  while(num < range){
    int input = random(range);
    if (!arrayIncludeElement(randArray, input, num)){
      randArray[num] = input;
      
      num++;
    }
  }
  for (int i = 0; i < range; i++) {   
    setSpot(i + 1, resource[randArray[i]], true);
  }
}

void loop() { 
  if (tracker >= 5){
     tracker = 0;
  }
  if(millis() >= (now + 1500)){
    leds[72] = all[tracker];
    leds[73] = all[tracker];
    leds[76] = all[tracker];
    leds[79] = all[tracker];
    FastLED.show(); 
    tracker++;
    Serial.println(tracker);
    now = millis();
  }
   
  int ButtonState = digitalRead(Button);

  if (ButtonState == HIGH){ // clicked
    clicked = true;   
  }

  if (clicked == true){
    delay(250);
    rollDice();
    clicked = false;     
  }

}
