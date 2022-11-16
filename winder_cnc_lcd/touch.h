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

void Read_Resistive(void)
{
    tp = mytouch.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
}

bool is_pressed(void)
{
    bool state;
    Read_Resistive();

    if ( tp.z > MINPRESSURE && tp.z  < MAXPRESSURE)
    { return true; }
    else
    {return false;}


}


void convert_point(void)
{

    touch_x = map(tp.y, TS_BOT, TS_TOP, 0, my_lcd.Get_Display_Width());

    touch_y = my_lcd.Get_Display_Height() - map(tp.x, TS_LEFT, TS_RT, 0, my_lcd.Get_Display_Height());

}
