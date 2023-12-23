#include <garretlab_MisakiLEDMatrix.h>

garretlab_MisakiLEDMatrix matrix;

void setup() {
  matrix.begin();
}

void loop() {
  char *str1 = "こんにちは";
  matrix.beginDraw();
  matrix.beginText(0);
  matrix.println(str1);
  matrix.endText(SCROLL_LEFT);
  delay(1000);
  matrix.endDraw();

  char *str2 = "こんばんは";
  matrix.beginDraw();
  matrix.beginText(-40);
  matrix.println(str2);
  matrix.endText(SCROLL_RIGHT);
  delay(1000);
  matrix.endDraw();

  char *str3 = "Hello";
  matrix.beginDraw();
  matrix.beginText(0);
  matrix.println(str3);
  matrix.endText();
  delay(2000);
  matrix.endDraw();
}