#include <garretlab_MisakiLEDMatrix.h>

// Constructor.
garretlab_MisakiLEDMatrix::garretlab_MisakiLEDMatrix()
  : ArduinoLEDMatrix() {
}

// Begin matrix.
int garretlab_MisakiLEDMatrix::begin() {
  ArduinoGraphics::begin();
  ArduinoLEDMatrix::begin();

  return 1;
}

// Display text.
void garretlab_MisakiLEDMatrix::text(const String &str, int x, int y) {
  byte fontData[fontHeight];
  char *ptr = (char *)str.c_str();

  if (font != &Font_Misaki) {
    ArduinoLEDMatrix::text(str, x, y);
  } else {
    while (*ptr) {
      ptr = getFontData(fontData, ptr, true);
      bitmap(fontData, x, y, fontWidth, fontHeight);
      x += fontWidth;
    }
  }
}

// Set text font.
void garretlab_MisakiLEDMatrix::textFont(const Font &which) {
  font = &which;

  ArduinoGraphics::textFont(which);
}

// Begin text.
void garretlab_MisakiLEDMatrix::beginText(int x, int y) {
  textBuffer = "";
  textBufferLength = 0;
  this->textX = x;
  this->textY = y;

  ArduinoLEDMatrix::beginText(x, y);
}

// Begin text.
void garretlab_MisakiLEDMatrix::beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  beginText(x, y);

  ArduinoLEDMatrix::beginText(x, y, r, g, b);
}

// Begin text.
void garretlab_MisakiLEDMatrix::beginText(int x, int y, uint32_t color) {
  beginText(x, y, COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

// Set pixel.
void garretlab_MisakiLEDMatrix::set(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  if (y >= canvasHeight || x >= canvasWidth || y < 0 || x < 0) {
    return;
  }

  ArduinoLEDMatrix::set(x, y, r, g, b);
  canvasBuffer[y][x] = (r | g | b) > 0 ? 1 : 0;
}

// Display text.
void garretlab_MisakiLEDMatrix::endText(int scrollDirection) {
  int scrollLength;

  if (font != &Font_Misaki) {
    ArduinoLEDMatrix::endText(scrollDirection);
    return;
  }

  switch (scrollDirection) {
    case SCROLL_LEFT:
      scrollLength = textBufferLength * textFontWidth();

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX - i, textY);
        endDraw();

        delay(scrollSpeed);
      }
      break;
    case SCROLL_RIGHT:
      scrollLength = textBufferLength * textFontWidth();

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX - (scrollLength - i - 1), textY);
        endDraw();

        delay(scrollSpeed);
      }
      break;
    case SCROLL_UP:
      scrollLength = textFontHeight() + textY;

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX, textY - i);
        endDraw();

        delay(scrollSpeed);
      }
      break;
    case SCROLL_DOWN:
      scrollLength = textFontHeight() + textY;

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX, textY - (scrollLength - i - 1));
        endDraw();

        delay(scrollSpeed);
      }
      break;
    default:
      beginDraw();
      text(textBuffer, textX, textY);
      endDraw();
      break;
  }
}

// End draw.
void garretlab_MisakiLEDMatrix::endDraw() {
  ArduinoGraphics::endDraw();
  renderBitmap(canvasBuffer, canvasHeight, canvasWidth);
}

// Write for Print class.
size_t garretlab_MisakiLEDMatrix::write(uint8_t c) {
  static int skip = 0;

  if ((c != 0x0a) && (c != 0x0d)) {  // Skip cr/lf.
    textBuffer += (char)c;
    if (skip == 0) {
      textBufferLength++;
      if ((c & 0x80) == 0) {
        skip = 0;
      } else if ((c & 0xe0) == 0xc0) {
        skip = 1;
      } else if ((c & 0xf0) == 0xe0) {
        skip = 2;
      }
    } else {
      skip--;
    }
  }

  ArduinoGraphics::write(c);
  return 1;
}

// Set text scroll speed.
void garretlab_MisakiLEDMatrix::textScrollSpeed(unsigned long scrollSpeed) {
  this->scrollSpeed = scrollSpeed;

  ArduinoLEDMatrix::textScrollSpeed(scrollSpeed);
}

// Font structure for Misaki font.
const struct Font Font_Misaki = {
  8, 8, NULL
};