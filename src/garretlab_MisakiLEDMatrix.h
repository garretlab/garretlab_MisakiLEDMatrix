#ifndef GARRETLAB_MISAKI_LED_MATRIX_H
#define GARRETLAB_MISAKI_LED_MATRIX_H

#include <misakiUTF16.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include <vector>

using namespace std;

class garretlab_MisakiLEDMatrix : public ArduinoLEDMatrix {
public:
  garretlab_MisakiLEDMatrix();                       // Constructor.
  void beginText(int x = 0);                        // Begin text.
  void endText(int scrollDirection = NO_SCROLL);    // Display text.
  int textLength();                                 // Get text length.
  size_t write(uint8_t c);                          // Write for Print class.
  int textFontWidth();                              // Get Text Font Width.
  int textFontHeight();                             // Get Text Font Height.
  void textScrollSpeed(unsigned long scrollSpeed);  // Set text scroll speed.

private:
  String textBuffer;                       // Buffer to hold text.
  int textBufferLength;                    // Text buffer length, not the memory size.
  int textX;                               // X position of text.
  const int fontWidth = 8;                 // Font width.
  const int fontHeight = 8;                // Font height.
  uint32_t frameHolder[3] = { 0 };         // LED matrix frame.
  unsigned long scrollSpeed = 150;         // Text scroll speed.
  vector<vector<unsigned char>> fontData;  //Fontdata to dispalay on the matrix.

  int getMisakiFontData(char *str);      // Get Misaki-font data.
  void setFrameData(int x, int length);  // Set Frame data.
};

#endif /* GARRETLAB_MISAKI_LED_MATRIX_H */