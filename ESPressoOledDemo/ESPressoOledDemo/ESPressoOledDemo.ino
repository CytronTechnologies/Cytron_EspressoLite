/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch
*/
#include <Wire.h>
#include "SSD1306.h"
#include "SSD1306Ui.h"
#include "images.h"

// Initialize the oled display for address 0x3c
// sda-pin=14 and sdc-pin=12
SSD1306   display(0x3c, SDA, SCL);
SSD1306Ui ui     ( &display );

bool drawFrame1(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_24);
  display->drawString(64 + x, 0 + y, "ESPresso");
  display->drawString(64 + x, 24,"Lite v2.0");
  return false;
}

bool drawFrame2(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  // Text alignment demo
  display->setFont(ArialMT_Plain_16);

  // The coordinates define the left starting point of the text
//  display.setTextAlignment(TEXT_ALIGN_LEFT);
//  display.drawString(0 + x, 0 + y, "Left aligned (0,0)");

  // The coordinates define the center of the text
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(64 + x, 16 + y, "Brought to You");
  display->drawString(64 + x, 32, "      by      ");

  // The coordinates define the right end of the text
//  display.setTextAlignment(TEXT_ALIGN_RIGHT);
//  display.drawString(128 + x, 40, "Right aligned (128,40)");
return false;
}

bool drawFrame3(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  // draw an xbm image.
  // Please note that everything that should be transitioned
  // needs to be drawn relative to x and y
  display->drawBitmap(0 + x, 0 + y, 128, 64, espert_logo);
  return false;
}

bool drawFrame4(SSD1306 *display, SSD1306UiState* state, int x, int y) {
  // draw an xbm image.
  // Please note that everything that should be transitioned
  // needs to be drawn relative to x and y
  display->drawBitmap(0 + x, 13 + y, 128, 38, cytron_logo);
  return false;
}

// this array keeps function pointers to all frames
// frames are the single views that slide from right to left
bool (*frames[])(SSD1306 *display, SSD1306UiState* state, int x, int y) = { drawFrame1, drawFrame2, drawFrame3, drawFrame4 };

// how many frames are there?
int frameCount = 4;

//bool (*overlays[])(SSD1306 *display, SSD1306UiState* state)             = { msOverlay };
//int overlaysCount = 1;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  ui.setTargetFPS(60);

  ui.setActiveSymbole(inactiveSymbole);
  ui.setInactiveSymbole(inactiveSymbole);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
//  ui.setIndicatorPosition(BOTTOM);

  // Defines where the first frame is located in the bar.
//  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_TOP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, frameCount);

  // Add overlays
//  ui.setOverlays(overlays, overlaysCount);

  // Inital UI takes care of initalising the display too.
  ui.init();

  display.flipScreenVertically();

}

void loop() {
  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    delay(remainingTimeBudget);
  }
}
