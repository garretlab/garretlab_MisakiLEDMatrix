#include <garretlab_MisakiLEDMatrix.h>

garretlab_MisakiLEDMatrix matrix;

void setup() {
  matrix.begin();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(150);
}

void loop() {
  const char text0[] = "4x6";
  matrix.beginDraw();
  matrix.clear();
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFFFF);
  matrix.println(text0);
  matrix.endText();
  matrix.endDraw();

  delay(2000);

  const char text1[] = "みさきフォント";
  matrix.beginDraw();
  matrix.clear();
  matrix.textFont(Font_Misaki);
  matrix.beginText(0, 0, 0xFFFFFF);
  matrix.println(text1);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();

  delay(2000);

  matrix.beginDraw();
  matrix.clear();
  matrix.rect(0, 0, 12, 8);
  matrix.rect(2, 2, 8, 4);
  matrix.endDraw();

  delay(2000);
}