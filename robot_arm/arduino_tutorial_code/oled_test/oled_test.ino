#include <U8x8lib.h>  // install U8g2 library

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

String upperarm_str = "world";

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 

void clear_oled(){
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"                   ");
  u8x8.drawString(0,1,"                   ");
  u8x8.drawString(0,2,"                   ");
  u8x8.drawString(0,3,"                   ");
  delay(100);
}

void setup() {
  Serial.begin(115200);
  u8x8.begin();
  clear_oled();
}

void loop() {
  clear_oled();
  delay(1000);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"hello world");
  u8x8.drawString(0,1,upperarm_str.c_str());
  delay(1000);

}
