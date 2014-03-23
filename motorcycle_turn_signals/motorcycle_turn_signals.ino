#include <Adafruit_NeoPixel.h>

#define N_LEDS 40
#define PIN     1

// Left and Right Inputs
#define SWITCH 0
#define SWITCH2 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
   // initialize the SWITCH pins as an input.
  pinMode(SWITCH, INPUT);
  pinMode(SWITCH2, INPUT);
  // ...with a pullup
  digitalWrite(SWITCH, HIGH);
  digitalWrite(SWITCH2, HIGH);
  strip.begin();
}

int pos = (N_LEDS/2), dir = 1; // Position, direction of "eye"
int beginLeft(){
  int j;

  // Draw 5 pixels centered on pos.  setPixelColor() will clip any
  // pixels off the ends of the strip, we don't need to watch for that.
  // MAX color 255
  strip.setPixelColor(pos - 2, strip.Color(255, 255/4, 0));
  strip.setPixelColor(pos - 1, strip.Color(255, 255/4, 0));
  strip.setPixelColor(pos    , strip.Color(128, 128/4, 0));
  if(pos < (N_LEDS/2)-1) strip.setPixelColor(pos + 1, strip.Color(64, 64/4, 0));
  if(pos < (N_LEDS/2)-2) strip.setPixelColor(pos + 2, strip.Color(32, 32/4, 0));
  
  strip.show();
  delay(50);

  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);

  // left turn
  pos -= dir;
  if(pos <= 0) {
    pos = (N_LEDS/2)-2;
  }
}
int beginRight(){
  int j;
  if(pos < (N_LEDS/2)){
    pos = (N_LEDS/2);
  }
  // Draw 5 pixels centered on pos.  setPixelColor() will clip any
  // pixels off the ends of the strip, we don't need to watch for that.
  // MAX color 255
  if(pos > (N_LEDS/2)+2) strip.setPixelColor(pos - 2, strip.Color(32, 32/4, 0));
  if(pos > (N_LEDS/2)+1) strip.setPixelColor(pos - 1, strip.Color(64, 64/4, 0));
  strip.setPixelColor(pos    , strip.Color(128, 128/4, 0));
  strip.setPixelColor(pos + 1, strip.Color(255, 255/4, 0));
  strip.setPixelColor(pos + 2, strip.Color(255, 255/4, 0));
  
  strip.show();
  delay(50);

  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);

  // left turn
  pos += dir;
  if(pos >= N_LEDS+1) {
    pos = (N_LEDS/2);
  }
}
int emergency1(){
  int j;
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  strip.setPixelColor(pos-4, red);  
  strip.setPixelColor(pos-3, red);
  strip.setPixelColor(pos-2, red);  
  strip.setPixelColor(pos-1, red);
  strip.setPixelColor(pos , red);
  strip.setPixelColor(pos+1 , red);
  strip.setPixelColor(pos+2, red);
  strip.setPixelColor(pos+3, red);  
  strip.setPixelColor(pos+4, red);  
  
  strip.setPixelColor(pos+5, blue);
  strip.setPixelColor(pos-5, blue);
  strip.show();
  delay(10);

  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);

  // left turn
  pos += dir;
  if(pos <= 0) {
    dir = -dir;
  } else if(pos == N_LEDS) {
    pos = N_LEDS;
    dir = -dir;
  }
}
int emergency2(){
  int j;
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  strip.setPixelColor(pos-4, red);  
  strip.setPixelColor(pos-3, red);
  strip.setPixelColor(pos-2, red);  
  strip.setPixelColor(pos-1, red);
  strip.setPixelColor(pos , red);
  strip.setPixelColor(pos+1 , red);
  strip.setPixelColor(pos+2, red);
  strip.setPixelColor(pos+3, red);  
  strip.setPixelColor(pos+4, red);  
  
  strip.setPixelColor(pos+5, blue);
  strip.setPixelColor(pos-5, red);
  strip.show();
  delay(10);

  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);

  // left turn
  pos += dir;
  if(pos <= -5) {
    dir = -dir;
  } else if(pos == N_LEDS) {
    pos = N_LEDS;
    dir = -dir;
  }
}
int emergency3(){
  int j;
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);

  for(j=0; j <= N_LEDS; j++){
    if(j <= N_LEDS/2){
      strip.setPixelColor(j, red);
    }else{
      strip.setPixelColor(j, blue);
    }
  }
  strip.show();
}
int count;
void loop() {
  if (! digitalRead(SWITCH2) && ! digitalRead(SWITCH)){
    count++;
    if(count <= 1000){
      emergency1();
    }else{
      emergency2();
    }
    if(count == 2000){
      count = 0;
    }
 }
  else if (! digitalRead(SWITCH2)){
    dir = 1;
    beginRight();
 } else if (! digitalRead(SWITCH)) { // if the button is pressed
    dir = 1;
    beginLeft();
  } 
 else {
   pos = (N_LEDS/2);
   strip.show();
 }
}
