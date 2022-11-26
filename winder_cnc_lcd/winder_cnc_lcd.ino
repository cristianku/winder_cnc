#include <TouchScreen.h> //touch library

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
//the definiens of 8bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function

// #define YP 6  // must be an analog pin, use "An" notation!
// #define XM A2  // must be an analog pin, use "An" notation!
// #define YM 7   // can be a digital pin
// #define XP A1   // can be a digital pin
#define ArrayCount(array) (sizeof array / sizeof array[0])

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin


//param calibration from kbv
#define TS_LEFT 130
#define TS_RT   940

#define TS_BOT  130
#define TS_TOP  960

#define MINPRESSURE 100
#define MAXPRESSURE 1000

//define some colour values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define GREY    0xC618

#define WHITE   0xFFFF
#define background 0x30D2

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// TouchScreen mytouch = TouchScreen(XP, YP, XM, YM, 300);
// TSPoint tp;                      //Touchscreen_due branch uses Point
LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
#include "Screen.h"
#include "NumPad.h"
#include "Scattering.h"
#include "Rpm.h"
#include "Winder.h"
#include "Turns.h"

#include "MainMenu.h"

MainMenu my_mainmenu;


void setup() {
  Serial.begin(115200);

  // Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.write("\r\n\r\n");
  delay(2000);   //# Wait for grbl to initialize
  // Serial.flush();  //# Flush startup text in serial input
  Serial.println("G91")
  ;

  my_lcd.Init_LCD();
  my_lcd.Set_Text_Size(2);
  my_lcd.Fill_Screen(background);
  my_lcd.Set_Rotation(3);

  // Screen my_screen;
  my_mainmenu.show();

}


void loop() {
  while (my_mainmenu.is_pressed() == false) {};

  my_mainmenu.do_actions();

  delay(20);


}




