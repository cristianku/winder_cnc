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


// class Screen {
//   // LCDWIKI_KBV myLcd ;

//   public:
//   void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
//       {
//           my_lcd.Set_Text_Mode(mode);
//           my_lcd.Set_Text_Size(csize);
//           my_lcd.Set_Text_colour(fc);
//           my_lcd.Set_Text_Back_colour(bc);
//           my_lcd.Print_String(str,x,y);
//       };
// };

// class Scattered : public Screen {
//   public:
//     void show_scattered(){
//       show_string("Ciao scattered",  20,20 ,2,WHITE, BLACK,1);

//     };

// };



  // int16_t get_y_text_pos( int16_t y_from,int16_t y_to , int16_t text_size){
  //   if ( text_size == 2 ){    
  //     switch (text_size) { 
  //       case 2:
  //         return ((y_to - y_from)  /2  + y_from - 5);   
  //         break;


  //       default: 
  //         // instruction
  //         break;
  //     }
  //   }
  // };

//   void draw_button(uint8_t *desc,
//                  int16_t x_from, 
//                  int16_t y_from, 
//                  int16_t x_to, 
//                  int16_t y_to, 
//                  int16_t corner_radius, 
//                  int16_t text_dimension ,
//                  int16_t button_color
//                 ){


//       switch (button_color) { 
//       case 1:
//         my_lcd.Set_Draw_color(GREY);
//         break;

//       case 2:
//         my_lcd.Set_Draw_color(MAGENTA);
//         break;

//       case 3:
//         my_lcd.Set_Draw_color(YELLOW);
//         break;

//       case 4:
//         my_lcd.Set_Draw_color(WHITE);
//         break;

//       case 5:
//         my_lcd.Set_Draw_color(BLACK);
//         break;

//       default: 
//         my_lcd.Set_Draw_color(GREY);
//         break;
//       }


//       my_lcd.Fill_Round_Rectangle(x_from, y_from, x_to,y_to, corner_radius);
    
//       show_string(desc, x_from + 20,this.get_y_text_pos (y_to , y_from text_dimension) ,text_dimension,BLACK, BLACK,1);
// };
  

// MyLcd my_lcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset


int completed = 0;
int rpm = 300;
int scattering = 1;

int touch_x = 0;
int touch_y = 0;
String numeric_pad_value;


int y = 0;

String grbl_out_turns ;
String previous_string ;


void setup() {
   my_lcd.Init_LCD();
   my_lcd.Set_Text_Size(2);
   my_lcd.Fill_Screen(background);
   my_lcd.Set_Rotation(3);

  // Screen my_screen;
  my_mainmenu.show();
// Open serial communications and wait for port to open:
  // Serial.begin(115200);
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // String numeric_pad_value = my_numpad.show();
  Serial.print( "numeric pad value :");
  Serial.print( numeric_pad_value);
  

  // Scattered my_scattered;
  // my_scattered.show_scattered();
  // // my_screen.show_string("Ciao come stai",  20,20 ,2,BLACK, BLACK,1);
  // current_color = RED;
  // my_lcd.Init_LCD();
  // my_lcd.Set_Text_Size(2);
  // // my_lcd.Fill_Screen(background);
  // current_color = RED;
  // current_pen = 0;
  // my_lcd.Set_Text_Mode(0);
  // my_lcd.Set_Rotation(3);
  // my_lcd.Fill_Screen(background);
  // show_main_menu();

  // my_lcd.Init_LCD();


  // Begin the Serial at 9600 Baud


  // # Wake up grbl
  Serial.write("\r\n\r\n");
  delay(2000);   //# Wait for grbl to initialize
  // Serial.flush();  //# Flush startup text in serial input
  Serial.println("G91");
  // show_numpad();

  // show_string("G91 SENT", 10,200,3,WHITE, BLACK,1);
  // delay(1000);
  // Serial.println("$");
  // run_winder(200,200,1);

  // delay(1000);

  // my_lcd.Fill_Screen(BLACK);  
  // my_lcd.Set_Text_Back_colour(BLACK);
  // my_lcd.Set_Text_colour(WHITE);
  // my_lcd.Print_String("Serial communication open ", 0, 0);
  // y += 20     ;

  // Serial.println(my_lcd.Read_ID(), HEX);

}




void loop() {
  while (my_mainmenu.is_pressed() == false) {};

  my_mainmenu.do_actions();

// my_lcd.Set_Rotation(3);
// Serial.println("entering loop");

  // my_lcd.Fill_Screen(BLACK);  
  // delay(300);


  // Serial.println("?");

  // String grbl_out = Serial.readString();
  // int mpos_from = grbl_out.indexOf("MPos")  + 5;
  // int mpos_to = grbl_out.indexOf(".",mpos_from);

  // int idle = 0;
  // idle = grbl_out.indexOf("Idle");
  

  // char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
  // strcpy (grbl_out_uuint8, grbl_out.c_str());
  
  // if ( idle > 0 ){
  //   show_string("idle trovato !! ", 1 + 20,10,2,WHITE, BLACK,1);  
  // } else
  // {
  // show_string(grbl_out_uuint8, 1 + 20,10,2,WHITE, BLACK,1);
  // }


  // if (grbl_out.substring(mpos_from, mpos_to) != "" ){
  //   String grbl_out_turns = grbl_out.substring(mpos_from, mpos_to) + " completed turns";

  //   char * grbl_out_uuint8 = new char [grbl_out_turns.length() + 1];
  //   strcpy (grbl_out_uuint8, grbl_out_turns.c_str());



  //   draw_button(grbl_out_uuint8, // uint8_t *desc,
  //               buttons[21][0],   // int16_t x_from, 
  //               buttons[21][1],   // int16_t y_from, 
  //               buttons[21][2],   // int16_t x_to, 
  //               buttons[21][3],   // int16_t y_to, 
  //               buttons[21][4],   // int16_t corner_radius, 
  //               buttons[21][5],   //int16_t text_dimension ,
  //               buttons[21][6]    //int16_t button_color
  //             );
  // }
  // delay(100);


  // Serial.print("received:");
  // Serial.println(grbl_out);

  // delay(2000);

  // while (my_screen.is_pressed() == false) {}
  // convert_point();
  // my_screen.do_actions();
  
    // Serial.println("G1 X10 F400" ); //# Send g-code block to grbl
  // mylcd.Print_String("Sending G1 X10 F400...", 0, y);
  // y += 20     ;
  delay(20);

  // int grbl_out = Serial.read();  //# Wait for grbl response with carriage return
  // // mylcd.Print_String("Output from GRBL:      " , 0, y);
  // y += 20     ;
  // // mylcd.Print_String(char(grbl_out) , 0, 0);
  
  // if (  y > 300){ 
  //   y = 0; 
  //   mylcd.Fill_Screen(BLACK);


}




