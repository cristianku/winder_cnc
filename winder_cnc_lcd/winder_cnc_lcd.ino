#include <TouchScreen.h> //touch library

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

//the definiens of 8bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset


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

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//param calibration from kbv
#define TS_MINX 906
#define TS_MAXX 116

#define TS_MINY 92 
#define TS_MAXY 952

#define MINPRESSURE 10
#define MAXPRESSURE 1000

int completed = 0;
int rpm = 300;

int turns_to_wind = 100;

// x pos, ypos , x pos max, y pos max,corner radius, text size, color ( 1=GREY, 2= MAGENTA,3 = YELLOW)
// int buttons [12] [7]= { {5          ,      30  , 480/3 -5      ,       70,  5,  2, 3},
//                         {5 + 480/3  ,      30  , 480/3*2-5     ,       70,  5,  2, 1},
//                         {5 + 480/3*2,      30  , 480/3*3-5     ,       70,  5,  2, 1},
//                         {5          ,      80  , 480/3 -5      ,      120,  5,  2, 1},
//                         {5+480/3,          80  , 480/3*2 -5    ,      120,  5,  2, 1},
//                         {480/8 +90,       130 ,  480/8 * 2 +90 ,      175,  5,  2, 1},
//                         {480/8*2 +90 + 5, 130,   480/8 * 3 +90 + 5,   175,  5,  2, 1},
//                         {480/8*3 +90 + 10, 130,  480/8 * 4 +90 + 10,  175,  5,  2, 1},
//                         {480/8*4 +90 + 15, 130,  480/8 * 5 +90 + 15,  175,  5,  2, 1},
//                         {5,                250,  160,                 300,  5,  2, 2}, //"Run Winder"
//                         {170,              250,  460,                 300,  5,  2, 1}, //"5200 completed turns"
//                         {170,              220,  350,                 240,  5,  2, 1} //"additional turns +50 turns"
//                       } ;

// char buttons_desc[][12] = { 
//                         "+50 turns",
//                         "+200 turns",
//                         "+350 turns",
//                         "+900 turns",
//                         "ZERO",
//                         "1",
//                         "2",
//                         "3",
//                         "4",
//                         "Run Winder",
//                         "0 completed",
//                         "+50 turns"
// };

//  switch (button_color) { 
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

//       default: 
//         my_lcd.Set_Draw_color(GREY);
//         break;
//       }

int total_menu_elements =22;

//                       x pos,           ypos ,  x pos max,      y pos max,corner radius, text size, color ( 1=GREY, 2= MAGENTA,3 = YELLOW)
             
int buttons [22] [7]= { {5          ,       30,   480/10   -5   ,       70,  5,  2, 1}, //0
                        {5 + 480/10 ,       30,   480/10*2 -5   ,       70,  5,  2, 1}, //1
                        {5 + 480/10*2,      30,   480/10*3 -5   ,       70,  5,  2, 1}, //2
                        {5 + 480/10*3,      30,   480/10*4 -5   ,       70,  5,  2, 1}, //3
                        {5 + 480/10*4,      30,   480/10*5 -5   ,       70,  5,  2, 1}, //4
                        {5 + 480/10*5,      30,   480/10*6 -5   ,       70,  5,  2, 1}, //5
                        {5 + 480/10*6,      30,   480/10*7 -5   ,       70,  5,  2, 1}, //6
                        {5 + 480/10*7,      30,   480/10*8 -5   ,       70,  5,  2, 1}, //7
                        {5 + 480/10*8,      30,   480/10*9 -5   ,       70,  5,  2, 1}, //8
                        {5 + 480/10*9,      30,   480/10*10 -5  ,      70,   5,  2, 1}, //9
                        {5 ,                80,   120,                 120,  5,  2, 1}, //reset

                        {330 ,              80,   450,                 120,  1,  2, 4}, //total turns to do

                        {480/8 +90,       130 ,  480/8 * 2 +90 ,      175,  5,  2, 1}, //scattering 1
                        {480/8*2 +90 + 5, 130,   480/8 * 3 +90 + 5,   175,  5,  2, 1}, //scattering 2
                        {480/8*3 +90 + 10, 130,  480/8 * 4 +90 + 10,  175,  5,  2, 1}, //scattering 3
                        {480/8*4 +90 + 15, 130,  480/8 * 5 +90 + 15,  175,  5,  2, 4}, //scattering 4

                        {5          ,      180,   480/4   -5   ,       220,  5,  2, 3}, // speed 
                        {5 + 480/4 ,       180,   480/4*2 -5   ,       220,  5,  2, 1}, // speed
                        {5 + 480/4*2,      180,   480/4*3 -5   ,       220,  5,  2, 1}, // speed
                        {5 + 480/4*3,      180,   480/4*4 -5   ,       220,  5,  2, 1}, // speed

                        {5,                250,  160,                 300,  5,  2, 2}, //"Run Winder"
                        {170,              250,  460,                 300,  5,  2, 1}, //"5200 completed turns"
                      } ;

char buttons_desc[][22] = { 
                        "0",
                        "1",
                        "2",
                        "3",
                        "4",
                        "5",
                        "6",
                        "7",
                        "8",
                        "9",
                        "reset",

                        "100",

                        "1", // scatter level 
                        "2", // scatter level 
                        "3", // scatter level 
                        "4", // scatter level 

                        "300 rpm",
                        "450 rpm",
                        "500 rpm",
                        "600 rpm",

                        "Run Winder",
                        "0 completed"
};


////// fine bottoni



//char button_50_turns_desc []= "+50 turns";

// int button_50_turns [] =  {5, 30, 480/3 -5,70,2};
// char button_50_turns_desc []= "+50 turns";

// int button_200_turns [] = {5 + 480/3, 30 , 480/3*2-5  ,70, 5,2};
// char button_200_turns_desc []= "+200 turns";

// int button_350_turns [] = {5 + 480/3*2, 30 , 480/3*3-5  ,70, 5,2};
// char button_350_turns_desc []= "+350 turns";

// int button_900_turns [] = {5, 80, 480/3 -5,120,2};
// char button_900_turns_desc []= "+900 turns";

// int button_zero_turns [] = {5480/3, 80, 480/3*2 -5,120,2};
// char button_zero_turns_desc []= "ZERO";


// int button_scattering_1 [] = {480/8 +90, 130, 480/8 * 2 +90,175,5 ,2};
// char button_scattering_1_desc[]= "1";

// int button_scattering_2 [] = {480/8*2 +90 + 5, 130, 480/8 * 3 +90 + 5,175,5 ,2};
// char button_scattering_2_desc[]= "2";

// int button_scattering_3 [] = {480/8*3 +90 + 10, 130, 480/8 * 4 +90 + 10,175,5,2 };
// char button_scattering_3_desc[]= "3";

// int button_scattering_4 [] = {480/8*4 +90 + 15, 130, 480/8 * 5 +90 + 15,175,5,2 };
// char button_scattering_4_desc[]= "4";

// int button_run_winder []={5, 250, 160,300,5, 2};
// char button_run_winder_desc[]= "Run Winder";

// int text_completed_turns [] = {170, 250, 460,300,5,2};
// char text_completed_turns_desc []= "5200 completed turns";

// int text_additional_turns [] =  {170, 220, 480/3*2 -5,240,5,2};
// char text_additional_turns_desc []= "+50 turns";


// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int y = 0;

uint16_t color_mask[] = {0xF800,0xFFE0,0x07E0,0x07FF,0x001F,0xF81F}; //color select

String grbl_out_turns ;
String previous_string ;

#define COLORBOXSIZE my_lcd.Get_Display_Width()/6
#define PENBOXSIZE my_lcd.Get_Display_Width()/4

int16_t old_color, current_color,flag_colour;
int16_t old_pen,current_pen,flag_pen;
boolean show_flag = true;

void draw_button(uint8_t *desc,
                 int16_t x_from, 
                 int16_t y_from, 
                 int16_t x_to, 
                 int16_t y_to, 
                 int16_t corner_radius, 
                 int16_t text_dimension ,
                 int16_t button_color
                ){


      switch (button_color) { 
      case 1:
        my_lcd.Set_Draw_color(GREY);
        break;

      case 2:
        my_lcd.Set_Draw_color(MAGENTA);
        break;

      case 3:
        my_lcd.Set_Draw_color(YELLOW);
        break;

      case 4:
        my_lcd.Set_Draw_color(WHITE);
        break;

      default: 
        my_lcd.Set_Draw_color(GREY);
        break;
      }


      my_lcd.Fill_Round_Rectangle(x_from, y_from, x_to,y_to, corner_radius);
    
      show_string(desc, x_from + 20,get_y_text_pos (y_to , y_from,text_dimension) ,text_dimension,BLACK, BLACK,1);

}

void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
    my_lcd.Set_Text_Mode(mode);
    my_lcd.Set_Text_Size(csize);
    my_lcd.Set_Text_colour(fc);
    my_lcd.Set_Text_Back_colour(bc);
    my_lcd.Print_String(str,x,y);
}

int16_t get_y_text_pos( int16_t y_from,int16_t y_to , int16_t text_size){
  if ( text_size == 2 ){    
    switch (text_size) { 
      case 2:
        return ((y_to - y_from)  /2  + y_from - 5);   
        break;


      default: 
        // instruction
        break;
    }
  }

}


//show main menu
void show_main_menu(void)
{

  //  my_lcd.Fill_Round_Rectangle(5, 0, (my_lcd.Get_Display_Width()-20)/3+5,COLORBOXSIZE/2+20, 5);
  //  my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3*2+15, 0, (my_lcd.Get_Display_Width()-20)/3*3+15,COLORBOXSIZE/2+20, 5);
  //  my_lcd.Set_Draw_color(MAGENTA);
  //  my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3+10, 0, (my_lcd.Get_Display_Width()-20)/3*2+10,COLORBOXSIZE/2+20, 5);
  //  show_string("RUN",5+((my_lcd.Get_Display_Width()-20)/3-72)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,BLUE, BLACK,1);
  //  show_string("SPEED 300",(my_lcd.Get_Display_Width()-20)/3+10+((my_lcd.Get_Display_Width()-20)/3-60)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,WHITE, BLACK,1);
  //  show_string("SPEED 500",(my_lcd.Get_Display_Width()-20)/3*2+15+((my_lcd.Get_Display_Width()-20)/3-84)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,BLUE, BLACK,1);
  show_string("WINDER CNC",10,5,2,WHITE, BLACK,1);
  // TURNS BUTTONS
  // my_lcd.Set_Draw_color(YELLOW);
  // my_lcd.Fill_Round_Rectangle(button_50_turns[0], button_50_turns[1], button_50_turns[2],button_50_turns[3],button_50_turns[4]);

  // my_lcd.Set_Draw_color(GREY);
  // my_lcd.Fill_Round_Rectangle(button_200_turns[0], button_200_turns[1], button_200_turns[2],button_200_turns[3], button_200_turns[4]);
  // my_lcd.Fill_Round_Rectangle(button_350_turns[0], button_350_turns[1], button_350_turns[2],button_350_turns[3], button_350_turns[4]);
  // my_lcd.Fill_Round_Rectangle(button_900_turns[0], button_900_turns[1], button_900_turns[2],button_900_turns[3], button_900_turns[4]);

  // show_string(button_50_turns_desc, button_50_turns[0] + 5,button_50_turns[1] + 10 ,2,BLACK, BLACK,button_50_turns[5]);

  // show_string(button_200_turns_desc, button_200_turns[0] + 5,button_200_turns[1] + 10 ,2,BLACK, BLACK,button_200_turns[5]);

  // show_string(button_350_turns_desc, button_350_turns[0] + 5,button_350_turns[1] + 10 ,2,BLACK, BLACK,button_350_turns[5]);

  // show_string(button_900_turns_desc, button_900_turns[0] + 5,button_900_turns[1] + 10 ,2,BLACK, BLACK,button_900_turns[5]);

  // // scattering
  // show_string("Scattering:", 5, 145 ,2,WHITE, BLACK,1);

  // my_lcd.Set_Draw_color(MAGENTA);
  // my_lcd.Fill_Round_Rectangle(button_scattering_1[0], button_scattering_1[1], button_scattering_1[2],button_scattering_1[3], button_scattering_1[4]);
  
  // my_lcd.Set_Draw_color(GREY);
  // my_lcd.Fill_Round_Rectangle(button_scattering_2[0], button_scattering_2[1], button_scattering_2[2],button_scattering_2[3], button_scattering_2[4]);
  // my_lcd.Fill_Round_Rectangle(button_scattering_3[0], button_scattering_3[1], button_scattering_3[2],button_scattering_3[3],button_scattering_3[4]);
  // my_lcd.Fill_Round_Rectangle(button_scattering_4[0], button_scattering_4[1], button_scattering_4[2],button_scattering_4[3], button_scattering_4[4]);

  // show_string(button_scattering_1_desc, button_scattering_1[0] + 25,button_scattering_1[1] + 10 ,button_scattering_1[5],BLACK, BLACK,1);
  // show_string(button_scattering_2_desc, button_scattering_2[0] + 25,button_scattering_2[1] + 10 ,button_scattering_2[5],BLACK, BLACK,1);
  // show_string(button_scattering_3_desc, button_scattering_3[0] + 25,button_scattering_3[1] + 10 ,button_scattering_3[5],BLACK, BLACK,1);
  // show_string(button_scattering_4_desc, button_scattering_4[0] + 25,button_scattering_4[1] + 10 ,button_scattering_4[5],BLACK, BLACK,1);

  // // RUN WINDER BUTTON
  // my_lcd.Set_Draw_color(MAGENTA);
  // my_lcd.Fill_Round_Rectangle(button_run_winder[0], button_run_winder[1], button_run_winder[2],button_run_winder[3], 5);
  // show_string(button_run_winder_desc, button_run_winder[0] + 20,button_run_winder[1] + 15 ,button_run_winder[5],WHITE, BLACK,1);

  // // COMPLETED TURNS
  // my_lcd.Set_Draw_color(GREY);
  // my_lcd.Fill_Round_Rectangle(text_completed_turns[0], text_completed_turns[1], text_completed_turns[2],text_completed_turns[3], text_completed_turns[4]);
  // show_string(text_completed_turns_desc, text_completed_turns[0] + 20,text_completed_turns[1] + 15 ,text_completed_turns[5],BLACK, BLACK,1);

  // // ADDITIONAL TURNS TURNS
  // my_lcd.Set_Draw_color(GREY);
  // my_lcd.Fill_Round_Rectangle(text_additional_turns[0], text_additional_turns[1], text_additional_turns[2],text_additional_turns[3],text_additional_turns[4]);
  // int y_middle_point = (text_additional_turns[3] - text_additional_turns[1])  /2  + text_additional_turns[1]-5;
  // show_string(text_additional_turns_desc, text_additional_turns[0] + 20,y_middle_point ,text_additional_turns[5],WHITE, BLACK,1);


   for ( int i = 0; i < total_menu_elements ; ++i ) {

    // ( 1=GREY, 2= MAGENTA,3 = YELLOW)
      // switch (buttons[i][6]) { 
      // case 1:
      //   my_lcd.Set_Draw_color(GREY);
      //   break;

      // case 2:
      //   my_lcd.Set_Draw_color(MAGENTA);
      //   break;

      // case 3:
      //   my_lcd.Set_Draw_color(YELLOW);
      //   break;

      // default: 
      //   my_lcd.Set_Draw_color(GREY);
      //   break;
      // }


      // my_lcd.Fill_Round_Rectangle(buttons[i][0], buttons[i][1], buttons[i][2],buttons[i][3], buttons[i][4]);
    
      // show_string(buttons_desc[i], buttons[i][0] + 20,get_y_text_pos (buttons[i][3] , buttons[i][1],buttons[i][5]) ,buttons[i][5],BLACK, BLACK,1);
      Serial.println(buttons_desc[i]);
      draw_button(buttons_desc[i], // uint8_t *desc,
                  buttons[i][0],   // int16_t x_from, 
                  buttons[i][1],   // int16_t y_from, 
                  buttons[i][2],   // int16_t x_to, 
                  buttons[i][3],   // int16_t y_to, 
                  buttons[i][4],   // int16_t corner_radius, 
                  buttons[i][5],   //int16_t text_dimension ,
                  buttons[i][6]    //int16_t button_color
                );
    }
        // scattering
    show_string("Scattering:", 5, 145 ,2,WHITE, BLACK,1);

    show_string("Turns to wind:", 150, 95 ,2,WHITE, BLACK,1);


  // show_string("+200 turns", button_200_turns[0] + 5,button_200_turns[1] + 10 ,2,BLUE, BLACK,1);

  // show_string("+200 turns",my_lcd.Get_Display_Width()/3 + 15,40,2,BLUE, BLACK,1);

  // show_string("+350 turns",my_lcd.Get_Display_Width()/3*2 + 15,40,2,BLUE, BLACK,1);


  // show_string("+900 turns",15,90,2,BLUE, BLACK,1);

  // Serial.println(my_lcd.Get_Display_Width());
  // Serial.println(my_lcd.Get_Display_Height());

 }


void run_winder(int16_t turns, int16_t speed, int16_t scatter_level ){

  Serial.print("G1 X");
  Serial.print(turns);
  Serial.print(" F" );
  Serial.print(speed );
  Serial.println("" );

  // String speed_str = String(speed);
  
  // char * grbl_out_uuint8 = new char [speed_str.length() + 1];
  // strcpy (grbl_out_uuint8, speed_str.c_str());

  // draw_button(grbl_out_uuint8, // uint8_t *desc,
  //             buttons[21][0],   // int16_t x_from, 
  //             buttons[21][1],   // int16_t y_from, 
  //             buttons[21][2],   // int16_t x_to, 
  //             buttons[21][3],   // int16_t y_to, 
  //             buttons[21][4],   // int16_t corner_radius, 
  //             buttons[21][5],   //int16_t text_dimension ,
  //             buttons[21][6]    //int16_t button_color
  //           );

  // delay(1000);
  // wait to grbl to start
  int running = -1;
  while ( running == -1){
    // my_lcd.Fill_Screen(BLACK);  
      draw_button("waiting for start", // uint8_t *desc,
                  buttons[21][0],   // int16_t x_from, 
                  buttons[21][1],   // int16_t y_from, 
                  buttons[21][2],   // int16_t x_to, 
                  buttons[21][3],   // int16_t y_to, 
                  buttons[21][4],   // int16_t corner_radius, 
                  buttons[21][5],   //int16_t text_dimension ,
                  buttons[21][6]    //int16_t button_color
                );
    Serial.println("?");
    String grbl_out = Serial.readString();
    running = grbl_out.indexOf("Run");
    // char * grbl_out_uuint8 = new char [grbl_out.length() + 1];
    // strcpy (grbl_out_uuint8, grbl_out.c_str());

    delay (1000);
  }
  //

  draw_button("STARTED", // uint8_t *desc,
              buttons[21][0],   // int16_t x_from, 
              buttons[21][1],   // int16_t y_from, 
              buttons[21][2],   // int16_t x_to, 
              buttons[21][3],   // int16_t y_to, 
              buttons[21][4],   // int16_t corner_radius, 
              buttons[21][5],   //int16_t text_dimension ,
              buttons[21][6]    //int16_t button_color
            );
  delay (2000);

  int idle = -1;
  Serial.println("?");
  String grbl_out = Serial.readString();
  delay(100);

  while (idle == -1){
    Serial.println("?");

    String grbl_out = Serial.readString();
    int mpos_index = grbl_out.indexOf("MPos") ;
    int mpos_from = mpos_index + 5;
    int mpos_to = grbl_out.indexOf(".",mpos_from);

    idle = grbl_out.indexOf("Idle");

    if (mpos_index > 1 ){
      String grbl_out_turns = grbl_out.substring(mpos_from, mpos_to) + " completed turns";

      char * grbl_out_uuint8 = new char [grbl_out_turns.length() + 1];
      strcpy (grbl_out_uuint8, grbl_out_turns.c_str());

      draw_button(grbl_out_uuint8, // uint8_t *desc,
                  buttons[21][0],   // int16_t x_from, 
                  buttons[21][1],   // int16_t y_from, 
                  buttons[21][2],   // int16_t x_to, 
                  buttons[21][3],   // int16_t y_to, 
                  buttons[21][4],   // int16_t corner_radius, 
                  buttons[21][5],   //int16_t text_dimension ,
                  buttons[21][6]    //int16_t button_color
                );
        }
  delay(100);

  }


  draw_button("FINISH", // uint8_t *desc,
              buttons[21][0],   // int16_t x_from, 
              buttons[21][1],   // int16_t y_from, 
              buttons[21][2],   // int16_t x_to, 
              buttons[21][3],   // int16_t y_to, 
              buttons[21][4],   // int16_t corner_radius, 
              buttons[21][5],   //int16_t text_dimension ,
              buttons[21][6]    //int16_t button_color
                  );



}

void setup() {
  current_color = RED;
  my_lcd.Init_LCD();
  my_lcd.Set_Text_Size(2);
  // my_lcd.Fill_Screen(background);
  current_color = RED;
  current_pen = 0;
  my_lcd.Set_Text_Mode(0);
  my_lcd.Set_Rotation(3);
  my_lcd.Fill_Screen(background);
  show_main_menu();

  // my_lcd.Init_LCD();


  // Begin the Serial at 9600 Baud

// Open serial communications and wait for port to open:
  Serial.begin(115200);
  // Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // # Wake up grbl
  Serial.write("\r\n\r\n");
  delay(2000);   //# Wait for grbl to initialize
  // Serial.flush();  //# Flush startup text in serial input
  Serial.println("G91");
  // show_string("G91 SENT", 10,200,3,WHITE, BLACK,1);
  delay(1000);
  // Serial.println("$");
  run_winder(200,200,1);

  // delay(1000);

  // my_lcd.Fill_Screen(BLACK);  
  // my_lcd.Set_Text_Back_colour(BLACK);
  // my_lcd.Set_Text_colour(WHITE);
  // my_lcd.Print_String("Serial communication open ", 0, 0);
  // y += 20     ;

  // Serial.println(my_lcd.Read_ID(), HEX);

}




void loop() {

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

  delay(2000);

  // digitalWrite(13, HIGH);
  // TSPoint p = ts.getPoint();
  // digitalWrite(13, LOW);
  // pinMode(XM, OUTPUT);
  // pinMode(YP, OUTPUT);
  // if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
  // {
    
  // }
    // Serial.println("G1 X10 F400" ); //# Send g-code block to grbl
  // mylcd.Print_String("Sending G1 X10 F400...", 0, y);
  // y += 20     ;
  // delay(3000);

  // int grbl_out = Serial.read();  //# Wait for grbl response with carriage return
  // // mylcd.Print_String("Output from GRBL:      " , 0, y);
  // y += 20     ;
  // // mylcd.Print_String(char(grbl_out) , 0, 0);
  
  // if (  y > 300){ 
  //   y = 0; 
  //   mylcd.Fill_Screen(BLACK);


}




