#include <TouchScreen.h> //touch library

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

//the definiens of 8bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset


//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

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


int button_50_turns [] = {5, 30, 480/3 -5,70};
char button_50_turns_desc []= "+50 turns";

int button_200_turns [] = {5 + 480/3, 30 , 480/3*2-5  ,70, 5};
char button_200_turns_desc []= "+200 turns";

int button_350_turns [] = {5 + 480/3*2, 30 , 480/3*3-5  ,70, 5};
char button_350_turns_desc []= "+350 turns";

int button_900_turns [] = {5, 80, 480/3 -5,120};
char button_900_turns_desc []= "+900 turns";

int button_scattering_1 [] = {480/8 +90, 135, 480/8 * 2 +90,175,5 };
char button_scattering_1_desc[]= "1";

int button_scattering_2 [] = {480/8*2 +90 + 5, 135, 480/8 * 3 +90 + 5,175,5 };
char button_scattering_2_desc[]= "2";

int button_scattering_3 [] = {480/8*3 +90 + 10, 135, 480/8 * 4 +90 + 10,175,5 };
char button_scattering_3_desc[]= "3";

int button_scattering_4 [] = {480/8*4 +90 + 15, 135, 480/8 * 5 +90 + 15,175,5 };
char button_scattering_4_desc[]= "4";

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int y = 0;

uint16_t color_mask[] = {0xF800,0xFFE0,0x07E0,0x07FF,0x001F,0xF81F}; //color select

#define COLORBOXSIZE my_lcd.Get_Display_Width()/6
#define PENBOXSIZE my_lcd.Get_Display_Width()/4

int16_t old_color, current_color,flag_colour;
int16_t old_pen,current_pen,flag_pen;
boolean show_flag = true;

void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
    my_lcd.Set_Text_Mode(mode);
    my_lcd.Set_Text_Size(csize);
    my_lcd.Set_Text_colour(fc);
    my_lcd.Set_Text_Back_colour(bc);
    my_lcd.Print_String(str,x,y);
}

void show_color_select_menu(void)
{
   uint16_t i;
   for(i = 0;i<6;i++)
   {
       my_lcd.Set_Draw_color(color_mask[i]);
       my_lcd.Fill_Rectangle(i*COLORBOXSIZE, 0, (i+1)*COLORBOXSIZE-1, COLORBOXSIZE/2-1);
   }  
   my_lcd.Set_Draw_color(GREEN);
   my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3+10, COLORBOXSIZE/2+2, (my_lcd.Get_Display_Width()-20)/3*2+10,COLORBOXSIZE/2+20, 5);
   show_string("OK",CENTER,COLORBOXSIZE/2+4,2,RED, BLACK,1);
}

//show main menu
void show_main_menu(void)
{
   my_lcd.Set_Draw_color(YELLOW);

  //  my_lcd.Fill_Round_Rectangle(5, 0, (my_lcd.Get_Display_Width()-20)/3+5,COLORBOXSIZE/2+20, 5);
  //  my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3*2+15, 0, (my_lcd.Get_Display_Width()-20)/3*3+15,COLORBOXSIZE/2+20, 5);
  //  my_lcd.Set_Draw_color(MAGENTA);
  //  my_lcd.Fill_Round_Rectangle((my_lcd.Get_Display_Width()-20)/3+10, 0, (my_lcd.Get_Display_Width()-20)/3*2+10,COLORBOXSIZE/2+20, 5);
  //  show_string("RUN",5+((my_lcd.Get_Display_Width()-20)/3-72)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,BLUE, BLACK,1);
  //  show_string("SPEED 300",(my_lcd.Get_Display_Width()-20)/3+10+((my_lcd.Get_Display_Width()-20)/3-60)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,WHITE, BLACK,1);
  //  show_string("SPEED 500",(my_lcd.Get_Display_Width()-20)/3*2+15+((my_lcd.Get_Display_Width()-20)/3-84)/2-1,((COLORBOXSIZE/2+20)-16)/2,2,BLUE, BLACK,1);
  show_string("WINDER CNC",1,5,2,BLUE, BLACK,1);

  my_lcd.Fill_Round_Rectangle(button_50_turns[0], button_50_turns[1], button_50_turns[2],button_50_turns[3], 5);
  my_lcd.Fill_Round_Rectangle(button_200_turns[0], button_200_turns[1], button_200_turns[2],button_200_turns[3], 5);
  my_lcd.Fill_Round_Rectangle(button_350_turns[0], button_350_turns[1], button_350_turns[2],button_350_turns[3], 5);
  my_lcd.Fill_Round_Rectangle(button_900_turns[0], button_900_turns[1], button_900_turns[2],button_900_turns[3], 5);

  show_string(button_50_turns_desc, button_50_turns[0] + 5,button_50_turns[1] + 10 ,2,BLACK, BLACK,1);

  show_string(button_200_turns_desc, button_200_turns[0] + 5,button_200_turns[1] + 10 ,2,BLACK, BLACK,1);

  show_string(button_350_turns_desc, button_350_turns[0] + 5,button_350_turns[1] + 10 ,2,BLACK, BLACK,1);

  show_string(button_900_turns_desc, button_900_turns[0] + 5,button_900_turns[1] + 10 ,2,BLACK, BLACK,1);

  show_string("Scattering:", 5, 150 ,2,WHITE, BLACK,1);

   my_lcd.Set_Draw_color(MAGENTA);

  my_lcd.Fill_Round_Rectangle(button_scattering_1[0], button_scattering_1[1], button_scattering_1[2],button_scattering_1[3], 5);
  my_lcd.Fill_Round_Rectangle(button_scattering_2[0], button_scattering_2[1], button_scattering_2[2],button_scattering_2[3], 5);
  my_lcd.Fill_Round_Rectangle(button_scattering_3[0], button_scattering_3[1], button_scattering_3[2],button_scattering_3[3], 5);
  my_lcd.Fill_Round_Rectangle(button_scattering_4[0], button_scattering_4[1], button_scattering_4[2],button_scattering_4[3], 5);

  show_string(button_scattering_1_desc, button_scattering_1[0] + 25,button_scattering_1[1] + 10 ,2,BLACK, BLACK,1);
  show_string(button_scattering_2_desc, button_scattering_2[0] + 25,button_scattering_2[1] + 10 ,2,BLACK, BLACK,1);
  show_string(button_scattering_3_desc, button_scattering_3[0] + 25,button_scattering_3[1] + 10 ,2,BLACK, BLACK,1);
  show_string(button_scattering_4_desc, button_scattering_4[0] + 25,button_scattering_4[1] + 10 ,2,BLACK, BLACK,1);


  // show_string("+200 turns", button_200_turns[0] + 5,button_200_turns[1] + 10 ,2,BLUE, BLACK,1);

  // show_string("+200 turns",my_lcd.Get_Display_Width()/3 + 15,40,2,BLUE, BLACK,1);

  // show_string("+350 turns",my_lcd.Get_Display_Width()/3*2 + 15,40,2,BLUE, BLACK,1);


  // show_string("+900 turns",15,90,2,BLUE, BLACK,1);

  // Serial.println(my_lcd.Get_Display_Width());
  // Serial.println(my_lcd.Get_Display_Height());

 }



void setup() {
  current_color = RED;

  // Begin the Serial at 9600 Baud

// Open serial communications and wait for port to open:
  // Serial.begin(115200);
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // # Wake up grbl
  Serial.write("\r\n\r\n");
  delay(2000);   //# Wait for grbl to initialize
  // Serial.flush();  //# Flush startup text in serial input
  Serial.println("G91");

  my_lcd.Init_LCD();

  
  my_lcd.Set_Rotation(3);
  my_lcd.Set_Text_Mode(0);
  
  // my_lcd.Fill_Screen(BLACK);  
  // my_lcd.Set_Text_Back_colour(BLACK);
  // my_lcd.Set_Text_colour(WHITE);
  my_lcd.Set_Text_Size(2);
  // my_lcd.Print_String("Serial communication open ", 0, 0);
  y += 20     ;

  my_lcd.Init_LCD();
  // Serial.println(my_lcd.Read_ID(), HEX);
  my_lcd.Fill_Screen(BLACK);
  show_main_menu();
  current_color = RED;
  current_pen = 0;

}




void loop() {

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
  {
    
  }
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




/// arduino mega
// void setup() {
       
//   // put your setup code here, to run once:
// Serial.begin(9600);
// Serial1.begin(9600);

// }

// void loop() {
//   // put your main code here, to run repeatedly:
// String readString;
// String Q;

// //-------------------------------Check Serial Port---------------------------------------
 
//  while (Serial1.available()){
//   delay(1);
//   if(Serial1.available()>0){
//   char c = Serial1.read();
//     Serial.print(c);
//    if (isControl(c)){
//   break;
//   }
   
//   }
 
//  }
 
  
//  while (Serial.available()) {
//      delay(1);
//     if (Serial.available() >0) {
//       char c = Serial.read();  //gets one byte from serial buffer
//     if (isControl(c)) {
//       //'Serial.println("it's a control character");
//       break;
//     }
//       readString += c; //makes the string readString    
//     }
//  }   

//  Q = readString;
// //--------Checking Serial Read----------
//       if(Q=="on"){         
//         Serial1.print("1");
//         Serial.println("Sent:On");               
//       }
//       if(Q=="off"){         
//         Serial1.print("2");  
//         Serial.println("Sent:Off");                          
//       }

// }

/////////

// #include <SoftwareSerial.h>

// SofwareSerial s(3,1);

// void setup(){
//   Serial.begin(115200);
// }

// void loop(){
//   s.write("G00  X-100\n\r");
//   delay(1000);
// }



// //Remember to set the pins to suit your display module!

// #include <LCDWIKI_GUI.h> //Core graphics library
// #include <LCDWIKI_KBV.h> //Hardware-specific library

// //the definiens of 8bit mode as follow:
// //if the IC model is known or the modules is unreadable,you can use this constructed function
// LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset


// //define some colour values
// #define  BLACK   0x0000
// #define BLUE    0x001F
// #define RED     0xF800
// #define GREEN   0x07E0
// #define CYAN    0x07FF
// #define MAGENTA 0xF81F
// #define YELLOW  0xFFE0
// #define WHITE   0xFFFF

// //clear screen
// void fill_screen_test()
// {
//   mylcd.Fill_Screen(BLACK);  
//   mylcd.Fill_Screen(RED);
//   mylcd.Fill_Screen(GREEN);
//   mylcd.Fill_Screen(BLUE);
//   mylcd.Fill_Screen(BLACK);
// }

// //display some strings
// void text_test()
// {
//   mylcd.Set_Text_Mode(0);
  
//   mylcd.Fill_Screen(BLACK);  
//   mylcd.Set_Text_Back_colour(BLACK);
//   mylcd.Set_Text_colour(WHITE);
//   mylcd.Set_Text_Size(1);
//   mylcd.Print_String("Hello World!", 0, 0);
  
//   mylcd.Set_Text_colour(YELLOW);
//   mylcd.Set_Text_Size(2);
//   mylcd.Print_Number_Float(1234.56,2,0, 8, '.', 0, ' ');
  
//   mylcd.Set_Text_colour(RED);
//   mylcd.Set_Text_Size(3);
//   //mylcd.Print_String("DEADBEEF", 0, 24); 
//   mylcd.Print_Number_Int(0xDEADBEF, 0, 24, 0, ' ', 16); 

//   mylcd.Set_Text_colour(GREEN);
//   mylcd.Set_Text_Size(5);  
//   mylcd.Print_String("Groop", 0, 56); 

//   mylcd.Set_Text_Size(2);
//   mylcd.Print_String("I implore thee,", 0, 96);

//   mylcd.Set_Text_Size(1);
//   mylcd.Print_String("my foonting turlingdromes.", 0, 112);
//   mylcd.Print_String("And hooptiously drangle me", 0, 120);
//   mylcd.Print_String("with crinkly bindlewurdles,", 0, 128);
//   mylcd.Print_String("Or I will rend thee", 0, 136);
//   mylcd.Print_String("in the gobberwarts", 0, 144);
//   mylcd.Print_String("with my blurglecruncheon,", 0, 152);
//   mylcd.Print_String("see if I don't!", 0, 160);
// }

// //draw some oblique lines
// void lines_test(void)
// {
//     mylcd.Fill_Screen(BLACK);
//       mylcd.Set_Draw_color(GREEN);
//     int i = 0;   
//     for(i = 0; i< mylcd.Get_Display_Width();i+=5)
//     {
//        mylcd.Draw_Line(0, 0, i, mylcd.Get_Display_Height()-1);
//      }
//      for(i = mylcd.Get_Display_Height()-1; i>= 0;i-=5)
//      {
//        mylcd.Draw_Line(0, 0, mylcd.Get_Display_Width()-1, i);
//      }
     
//      mylcd.Fill_Screen(BLACK); 
//        mylcd.Set_Draw_color(RED);
//     for(i = mylcd.Get_Display_Width() -1; i>=0;i-=5)
//     {
//       mylcd.Draw_Line(mylcd.Get_Display_Width()-1, 0, i, mylcd.Get_Display_Height()-1);
//      }
//     for(i = mylcd.Get_Display_Height()-1; i>=0;i-=5)
//     {
//       mylcd.Draw_Line(mylcd.Get_Display_Width()-1, 0, 0, i);
//      }
     
//      mylcd.Fill_Screen(BLACK); 
//       mylcd.Set_Draw_color(BLUE);
//      for(i = 0; i < mylcd.Get_Display_Width();i+=5)
//     {
//       mylcd.Draw_Line(0, mylcd.Get_Display_Height()-1, i, 0);
//      }
//      for(i = 0; i < mylcd.Get_Display_Height();i+=5)
//     {
//       mylcd.Draw_Line(0, mylcd.Get_Display_Height()-1, mylcd.Get_Display_Width()-1, i);
//      }

//      mylcd.Fill_Screen(BLACK);
//       mylcd.Set_Draw_color(YELLOW);
//      for(i = mylcd.Get_Display_Width()-1; i >=0;i-=5)
//     {
//       mylcd.Draw_Line(mylcd.Get_Display_Width()-1, mylcd.Get_Display_Height()-1, i, 0);
//      }
//      for(i = 0; i<mylcd.Get_Display_Height();i+=5)
//     {
//       mylcd.Draw_Line(mylcd.Get_Display_Width()-1, mylcd.Get_Display_Height()-1, 0, i);
//      }
// }

// //draw some vertical lines and horizontal lines
// void h_l_lines_test(void)
// {
//     int i=0;
//    mylcd.Fill_Screen(BLACK);
//      mylcd.Set_Draw_color(GREEN);
//     for(i =0;i<mylcd.Get_Display_Height();i+=5)
//     {
//       mylcd.Draw_Fast_HLine(0,i,mylcd.Get_Display_Width()); 
//       delay(5);
//     }
//      mylcd.Set_Draw_color(BLUE);
//      for(i =0;i<mylcd.Get_Display_Width();i+=5)
//     {
//       mylcd.Draw_Fast_VLine(i,0,mylcd.Get_Display_Height()); 
//            delay(5);
//     }
// }

// //draw some rectangles
// void rectangle_test(void)
// {
//   int i = 0;
//    mylcd.Fill_Screen(BLACK);
//      mylcd.Set_Draw_color(GREEN);
//    for(i = 0;i<mylcd.Get_Display_Width()/2;i+=4)
//    {
//       mylcd.Draw_Rectangle(i,(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2+i,mylcd.Get_Display_Width()-1-i,mylcd.Get_Display_Height()-(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2-i);  
//         delay(5);
//    }
// }

// //draw some filled rectangles
// void fill_rectangle_test(void)
// {
//   int i = 0;
//    mylcd.Fill_Screen(BLACK);
//      mylcd.Set_Draw_color(YELLOW);
//    mylcd.Fill_Rectangle(0,(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2,mylcd.Get_Display_Width()-1,mylcd.Get_Display_Height()-(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2);
//     mylcd.Set_Draw_color(MAGENTA);
//    for(i = 0;i<mylcd.Get_Display_Width()/2;i+=4)
//    {
//       mylcd.Draw_Rectangle(i,(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2+i,mylcd.Get_Display_Width()-1-i,mylcd.Get_Display_Height()-(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2-i);  
//         delay(5);
//    }
//    for(i = 0;i<mylcd.Get_Display_Width()/2;i+=4)
//    {
//        mylcd.Set_Draw_color(random(255), random(255), random(255));
//       mylcd.Fill_Rectangle(i,(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2+i,mylcd.Get_Display_Width()-1-i,mylcd.Get_Display_Height()-(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2-i);  
//         delay(5);
//    }
// }

// //draw some filled circles
// void fill_circles_test(void)
// {
//   int r=10,i=0,j=0;
//   mylcd.Fill_Screen(BLACK);
//    mylcd.Set_Draw_color(MAGENTA);
//   for(i=r;i<mylcd.Get_Display_Width();i+=2*r)
//   {
//     for(j=r;j<mylcd.Get_Display_Height();j+=2*r)
//     {
//       mylcd.Fill_Circle(i, j, r);
//     }
//   }
// }

// //draw some circles
// void circles_test(void)
// {
//   int r=10,i=0,j=0;
//    mylcd.Set_Draw_color(GREEN);
//   for(i=0;i<mylcd.Get_Display_Width()+r;i+=2*r)
//   {
//     for(j=0;j<mylcd.Get_Display_Height()+r;j+=2*r)
//     {
//       mylcd.Draw_Circle(i, j, r);
//     }
//   }  
// }

// //draw some triangles
// void triangles_test(void)
// {
//    int i = 0;
//    mylcd.Fill_Screen(BLACK);
//    for(i=0;i<mylcd.Get_Display_Width()/2;i+=5)
//    {
//       mylcd.Set_Draw_color(0,i+64,i+64);
//       mylcd.Draw_Triangle(mylcd.Get_Display_Width()/2-1,mylcd.Get_Display_Height()/2-1-i,
//                     mylcd.Get_Display_Width()/2-1-i,mylcd.Get_Display_Height()/2-1+i,
//                     mylcd.Get_Display_Width()/2-1+i,mylcd.Get_Display_Height()/2-1+i);                   
//    }
// }

// //draw some filled triangles
// void fill_triangles_test(void)
// {
//    int i = 0;
//    mylcd.Fill_Screen(BLACK);
//     for(i=mylcd.Get_Display_Width()/2-1;i>0;i-=5)
//    {
    
//       mylcd.Set_Draw_color(0,i+64,i+64);
//       mylcd.Fill_Triangle(mylcd.Get_Display_Width()/2-1,mylcd.Get_Display_Height()/2-1-i,
//                     mylcd.Get_Display_Width()/2-1-i,mylcd.Get_Display_Height()/2-1+i,
//                     mylcd.Get_Display_Width()/2-1+i,mylcd.Get_Display_Height()/2-1+i);                   
//       mylcd.Set_Draw_color(i,0,i);
//       mylcd.Draw_Triangle(mylcd.Get_Display_Width()/2-1,mylcd.Get_Display_Height()/2-1-i,
//                     mylcd.Get_Display_Width()/2-1-i,mylcd.Get_Display_Height()/2-1+i,
//                     mylcd.Get_Display_Width()/2-1+i,mylcd.Get_Display_Height()/2-1+i);                   
//    }
// }

// //draw some round rectangles
// void round_rectangle(void)
// {
//    int i = 0;
//    mylcd.Fill_Screen(BLACK);
//      for(i = 0;i<mylcd.Get_Display_Width()/2;i+=4)
//    {
//        mylcd.Set_Draw_color(255-i,0,160-i);
//       mylcd.Draw_Round_Rectangle(i,(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2+i,mylcd.Get_Display_Width()-1-i,mylcd.Get_Display_Height()-(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2-i,8);
//         delay(5);
//    } 
// }

// //draw some filled round rectangles
// void fill_round_rectangle(void)
// {
//      int i = 0;
//    mylcd.Fill_Screen(BLACK);
//      for(i = 0;i<mylcd.Get_Display_Width()/2;i+=4)
//    {
//        mylcd.Set_Draw_color(255-i,160-i,0);
//       mylcd.Fill_Round_Rectangle(i,(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2+i,mylcd.Get_Display_Width()-1-i,mylcd.Get_Display_Height()-(mylcd.Get_Display_Height()-mylcd.Get_Display_Width())/2-i,8);
//         delay(5);
//    } 
// }

// void setup() 
// {
//   mylcd.Init_LCD();
//   fill_screen_test();
//   delay(500);
//   text_test();
//   delay(500);
//   lines_test();
//   delay(500);
//   h_l_lines_test();
//   delay(500);
//   rectangle_test();
//   delay(500);
//   fill_rectangle_test();
//   delay(500);
//   fill_circles_test();
//   delay(500);
//   circles_test();
//   delay(500);
//   triangles_test();
//   delay(500);
//   fill_triangles_test();
//   delay(500);
//    round_rectangle();
//    delay(500);
//    fill_round_rectangle();
//    delay(3000);
// }

// void loop() 
// {
//   //rotate for four directions
//  for(uint8_t rotation=0; rotation<4; rotation++) 
//  {
//     mylcd.Set_Rotation(rotation);
//     text_test();
//     delay(2000);
//  }
// }

//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
