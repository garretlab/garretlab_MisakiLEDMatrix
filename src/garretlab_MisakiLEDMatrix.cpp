#include <garretlab_MisakiLEDMatrix.h>

// Constructor
garretlab_MisakiLEDMatrix::garretlab_MisakiLEDMatrix()
  : ArduinoLEDMatrix() {
  beginText();
}

// Resets text.
void garretlab_MisakiLEDMatrix::beginText(int textX) {
  textBuffer = "";
  textBufferLength = 0;
  this->textX = textX;
}

// Display text.
void garretlab_MisakiLEDMatrix::endText(int scrollDirection) {
  int scrollLength;
  int displacementX;
  int x = textX;

  getMisakiFontData((char *)textBuffer.c_str());

  switch (scrollDirection) {
    case SCROLL_LEFT:
      scrollLength = textBufferLength * textFontWidth();
      displacementX = -1;
      break;
    case SCROLL_RIGHT:
      scrollLength = textBufferLength * textFontWidth() + width();
      displacementX = 1;
      break;
    default:
      scrollLength = 1;
      displacementX = 0;
      break;
  }

  for (int i = 0; i < scrollLength; i++, x += displacementX) {
    setFrameData(x, textBufferLength);
    ArduinoLEDMatrix::loadFrame(frameHolder);
    if (i != (scrollLength - 1)) {
      delay(scrollSpeed);
    }
  }
}

size_t garretlab_MisakiLEDMatrix::write(uint8_t c) {
  if ((c != 0x0a) && (c != 0x0d)) {
    textBuffer += (char)c;
    return 1;
  } else {
    return 0;
  }
}

int garretlab_MisakiLEDMatrix::textFontWidth() {
  return fontWidth;
}

int garretlab_MisakiLEDMatrix::textFontHeight() {
  return fontHeight;
}

void garretlab_MisakiLEDMatrix::textScrollSpeed(unsigned long scrollSpeed) {
  this->scrollSpeed = scrollSpeed;
}

int garretlab_MisakiLEDMatrix::getMisakiFontData(char *str) {
  int numChar = 0;

  while (*str) {
    fontData.resize(numChar + 1);
    fontData[numChar].resize(8);
    str = getFontData(&fontData[numChar++][0], str, true);
  }

  textBufferLength = numChar;
  return textBufferLength;
}

void garretlab_MisakiLEDMatrix::setFrameData(int x, int length) {
  int mask[3];
  int numChar;
  int index = 0;

  typedef struct {
    int f;  // frame
    int d;  // data
    int s;  // shift
  } mConv;

  mConv mc00[] = { { 0, 0, 24 }, { 0, 1, 12 }, { 0, 2, 0 }, { 1, 2, 32 }, { 1, 3, 20 }, { 1, 4, 8 }, { 1, 5, -4 }, { 2, 5, 28 }, { 2, 6, 16 }, { 2, 7, 4 }, { -1, -1, -1 } };
  mConv mc01[] = { { 0, 2, 0 }, { 1, 5, 4 }, { 1, 5, -8 }, { 2, 7, -4 }, { -1, -1, -1 } };
  mConv mc10[] = { { 0, 0, 16 }, { 0, 1, 4 }, { 1, 2, 24 }, { 1, 3, 12 }, { 1, 4, 0 }, { 2, 5, 20 }, { 2, 6, 8 }, { 2, 7, -4 }, { -1, -1, -1 } };
  mConv mc11[] = { { 0, 2, 8 }, { 1, 4, 0 }, { 1, 5, 12 }, { 2, 7, 4 }, { -1, -1, -1 } };
  mConv mc20[] = { { 0, 0, 8 }, { 0, 1, -4 }, { 1, 2, 16 }, { 1, 3, 4 }, { 2, 5, 12 }, { 2, 6, 0 }, { -1, -1, -1 } };
  mConv mc21[] = { { 1, 4, 8 }, { 2, 6, 0 }, { 2, 7, 12 }, { -1, -1, -1 } };
  mConv *mcData[][2] = { { mc00, mc01 }, { mc10, mc11 }, { mc20, mc21 } };

  if ((x + length * fontWidth < 0) || (x >= width())) {
    return;
  }

  for (int i = 0; i < 3; i++) {
    frameHolder[i] = 0;
  }

  if (x < 0) {
    index = (-x - 1) / fontWidth;
    x += index * fontWidth;
    length -= index;
  }

  numChar = min(length, 3);

  if (x < -4) {
    mask[0] = 0xff >> -x, mask[1] = 0xff, mask[2] = 0xff << (x + 12);
  } else if (x < 0) {
    mask[0] = 0xff >> -x, mask[1] = 0xff << (x + 4), mask[2] = 0xff << (x + 12);
  } else if (x < 5) {
    mask[0] = 0xff, mask[1] = 0xff << (x + 4), mask[2] = 0x00;
  } else {
    mask[0] = 0xff << (x - 4), mask[1] = 0x00, mask[2] = 0x00;
  }

  for (int i = 0; i < numChar; i++, index++) {
    for (int j = 0; j < 2; j++) {
      int k = 0;
      while (mcData[i][j][k].f != -1) {
        if (j == 0) {
          frameHolder[mcData[i][j][k].f] |= (fontData[index][mcData[i][j][k].d] & mask[i]) << (-x + mcData[i][j][k].s);
        } else {
          frameHolder[mcData[i][j][k].f] |= (fontData[index][mcData[i][j][k].d] & mask[i]) >> (x + mcData[i][j][k].s);
        }
        k++;
      }
    }
  }
}