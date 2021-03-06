#include <Arduino.h>
#include "FastLED.h"

#define Pixel_PIN 3
#define NUM_LEDS 16
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B

CRGB leds[NUM_LEDS];

int mic_in = A1;
int mic_value;
int old_mic_value = 580;
int mic_delta = 160;

const uint8_t saturation = 255;
//start at hue value 85 (pure green)
uint8_t gHue = 85;
//getting the right gradtient for led ring or strip
uint8_t gHueDelta = 255/NUM_LEDS;
//intensity for leds
uint8_t value = 255;

void setup() {
	Serial.begin(9600);
	FastLED.addLeds<LED_TYPE, Pixel_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(255);
	pinMode(mic_in, INPUT);
}

void loop() {
	for (int i = 0; i <= 9; i++) {
		mic_value += analogRead(mic_in);
	}
	mic_value = mic_value/10;
	Serial.println(mic_value);
	for (int i = 0; i <= 15; i++) {
		if ((mic_value - old_mic_value) > 10*i) {
			leds[i] = CHSV(gHue+(gHueDelta*i),saturation,value);
		}
		else {
			leds[i] = CRGB::Black;
		}
	}
	old_mic_value = mic_value;
	FastLED.show();
}
