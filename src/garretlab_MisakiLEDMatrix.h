#ifndef GARRETLAB_MISAKI_LED_MATRIX_H
#define GARRETLAB_MISAKI_LED_MATRIX_H

#include <misakiUTF16.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

#define COLOR_R(color) (uint8_t(color >> 16))
#define COLOR_G(color) (uint8_t(color >> 8))
#define COLOR_B(color) (uint8_t(color >> 0))

// Font structure for Misaki font.
extern const struct Font Font_Misaki;

class garretlab_MisakiLEDMatrix : public ArduinoLEDMatrix {
public:
  garretlab_MisakiLEDMatrix();                                    // Constructor.
  int begin();                                                    // Begin matrix.
  void text(const String& str, int x = 0, int y = 0);             // Display text.
  void textFont(const Font& which);                               // Set text font.
  void beginText(int x = 0, int y = 0);                           // Begin text.
  void beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b);  // Begin text.
  void beginText(int x, int y, uint32_t color);                   // Begin text.
  void set(int x, int y, uint8_t r, uint8_t g, uint8_t b);        // Set pixel.
  void endText(int scrollDirection = NO_SCROLL);                  // Display text.
  void endDraw();                                                 // End draw.
  size_t write(uint8_t c);                                        // Write for Print class.
  void textScrollSpeed(unsigned long scrollSpeed);                // Set text scroll speed.

protected:
  String textBuffer;                       // Buffer to hold text.
  int textBufferLength;                    // Text buffer length, not the memory size.
  int textX;                               // X position of text.
  int textY;                               // Y position of text.
  const struct Font* font = &Font_Misaki;  // Font name.
  static const int fontWidth = 8;          // Font width.
  static const int fontHeight = 8;         // Font height.
  static const byte canvasWidth = 12;      // Canvas width.
  static const byte canvasHeight = 8;      // Canvas height.
  unsigned long scrollSpeed = 150;         // Text scroll speed.
  uint8_t canvasBuffer[8][12] = { { 0 } };
};

#endif /* GARRETLAB_MISAKI_LED_MATRIX_H */