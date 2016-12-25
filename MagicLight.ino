#include <Adafruit_NeoPixel.h> //引用此文件
#define PIN 6   //led灯控制引脚
#define PIN_NUM 2 //允许接的led灯的个数
#define val_max 255
#define val_min 0   
unsigned int temp_on = 25;
double temp;
int i=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIN_NUM, PIN, NEO_GRB + NEO_KHZ800);  //该函数第一个参数控制串联灯的个数，第二个是控制用哪个pin脚输出，第三个显示颜色和变化闪烁频率

void setup() //创建无返回值函数
{
   Serial.begin(115200);           //串口初始化
  analogReference(INTERNAL);  //调用板载1.1V基准源
  strip.begin(); //准备对灯珠进行数据发送
  strip.show(); //初始化LED为关的状态
}

void loop() //无返回值loop函数
{
  double analogVotage = 1.1*(double)analogRead(A3)/1024.0;
  temp = 100*analogVotage; //计算温度
  if(temp >= temp_on)
  {
    i++;
    if(i%3==1)  rainbowCycle( 255, 0, 0, 3); //红色呼吸
    else if(i%3==2)  rainbowCycle( 0, 255, 0, 3); //绿色呼吸
    else if(i%3==0)  rainbowCycle( 0, 0, 255, 3); //蓝色呼吸
  }
  else  rainbowCycle( 0, 0, 0, 3); 
   Serial.print("Temp: "); 
   Serial.print(temp);
}
/*“rainbowCycle( int r, int g, int b, uint8_t wait)”函数说明：
r：红色值（0-255）。g：绿色值（0-255）。b：蓝色值（0-255）。
“uint8_t wait”定义呼吸的速度，数值越小呼吸速度越快*/

void colorSet(uint32_t c) 
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) 
  //从0自增到LED灯个数减1
{
strip.setPixelColor(i, c); //此函数表示将第i个LED点亮
}
  strip.show(); //LED灯显示
}

void rainbowCycle( int r, int g, int b, uint8_t wait) {
  for (int val = 0; val < 255; val++) 
  //val由0自增到254不断循环
  {
colorSet(strip.Color(map(val, val_min, val_max, 0, r), map(val, val_min, val_max, 0, g), map(val, val_min, val_max, 0, b)));
//红绿蓝LED灯依次从暗到亮
/*“map(val,x,y,m,n)”函数为映射函数，可将某个区间的值（x-y）变幻成（m-n），val则是你需要用来映射的数据*/
    delay(wait); //延时
  }
  for (int val = 255; val >= 0; val--)  //val从255自减到0不断循环
  {
colorSet(strip.Color(map(val, val_min, val_max, 0, r), map(val, val_min, val_max, 0, g), map(val, val_min, val_max, 0, b)));
//红绿蓝LED灯依次由亮到暗
    delay(wait); //延时
  }
}
