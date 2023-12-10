#include <FastLED.h>

#define NUM_LEDS  31
#define DATA_PIN 3

#define button_oblak 2
#define button_sonce 4
#define sonce_led 12
#define oblak_led 11

CRGB leds[NUM_LEDS];

unsigned short animationState = 0;
unsigned short currentLed = 0;
unsigned short millis_delay_slow = 500,millis_delay_fast= 300;
unsigned long millis_new,millis_old = 0;

 short i = 0, j = 16, k = 0;
void setup() {
  pinMode(button_oblak, INPUT_PULLUP);
  pinMode(button_sonce, INPUT_PULLUP);
  pinMode(sonce_led,OUTPUT);
  pinMode(oblak_led,OUTPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); 

  for(int d = 0; d<NUM_LEDS; d++){
     leds[d]= CRGB::Black;
    }
    FastLED.setBrightness(32);
    FastLED.show();
   Serial.begin(9600);
}

void loop() {
  
      if(digitalRead(button_oblak)==0){
        i=0;
        j=0;
        animationState = 1;  
        for(int d = 0; d<NUM_LEDS; d++){
          leds[d]= CRGB::Black;
        }
        FastLED.show();
        
      }
      if(digitalRead(button_sonce)==0){
        i=0;
        j=16;
        animationState = 0;
        for(int d = 0; d<NUM_LEDS; d++){
          leds[d]= CRGB::Black;
        }
      FastLED.show();
     
      }
    
    millis_old = millis_new;
   
   
////////////////////////////////////////////////////////////////////////////////////////////
   if(animationState == 0){ //sončno

  /*  if(i<16){
      if(i!=0){
        leds[i-1]= CRGB::Black;
      }
      leds[i]= CRGB::Green;
    }
    if(i >= 16){
      leds[15]= CRGB::Black;
       leds[i +8]= CRGB::Black;
      leds[i + 9]= CRGB::Green;
    }
*/
    leds[j] = CRGB::Green;
    if(j!=16){
      leds[j-1] =CRGB::Black;  
    }

    FastLED.show();
    
    if(i ==21 || j == 30){
      leds[30] = CRGB::Black;     
    }
    digitalWrite(oblak_led, LOW);
    digitalWrite(sonce_led,HIGH);
    
    i++;
    i = i % 22;
    
    if(j == 30){j = 16;leds[30] = CRGB::Black;}else{j++;}
    Serial.print("i:  ");
    Serial.print(i);
    Serial.print("  j:  ");
    Serial.println(j);
        while(millis_new - millis_old < 500){millis_new = millis();if(digitalRead(button_oblak)==0){break;}}
      millis_old = millis_new;
   
   }

////////////////////////////////////////////////////////////////////////////////////////
   if(animationState == 1){//oblačno
    if(i<16){
      if(i!=0){
        leds[i-1]= CRGB::Black;
      }
      leds[i]= CRGB::Red;
    }
    if(i >= 16){
      leds[15]= CRGB::Black;
      leds[i +8]= CRGB::Black;
      leds[i + 9]= CRGB::Red;
    }

    if(j>=16){
      leds[(j)] = CRGB::Red;
      if(j!=24){
        leds[(j+1)] =CRGB::Black;
      }
      
    }
      
      
      
      
    FastLED.show();
    
    if(i ==21){
      leds[30] = CRGB::Black;     
    }
    if(j ==16){
      leds[16] = CRGB::Black;     
    }
    digitalWrite(oblak_led, HIGH);
    digitalWrite(sonce_led,LOW);
   
    i++;
    i = i % 22;
    
    if(i == 16){j = 24;}else{j--;}
    Serial.print("i:  ");
    Serial.print(i);
    Serial.print("  j:  ");
    Serial.println(j);
    while(millis_new - millis_old < 500){millis_new = millis();if(digitalRead(button_sonce)==0){break;}}
      millis_old = millis_new;
   }
}
