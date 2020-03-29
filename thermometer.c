#include <16F628A.h>
#device *= 16
#device adc = 10
#use delay(clock = 4M)
#define APA output_b(0b00000000);
#fuses nowdt, noprotect, nowrt, intrc_io, nomclr
int temperature;
char vec[11] = {
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00100111, //7
    0b01111111, //8
    0b01101111, //9
    0b01000000, //out of range
};
void cycle(int units, int tens, int hundreds)
{
   output_low(pin_a1);
   output_b(vec[units]);
   delay_ms(60);
   output_high(pin_a1);

   output_low(pin_a2);
   output_b(vec[tens]);
   delay_ms(60);
   output_high(pin_a2);

   output_low(pin_a3);
   output_b(vec[hundreds]);
   delay_ms(60);
   output_high(pin_a3);
}
void sig(int units, int tens, int hundreds)
{
   if (temperature > units - 1 && temperature < units + 10)
   {
      int u;
      u = temperature - units;
      cycle(u, tens, hundreds);
   }
}
void main()
{
   setup_adc_ports(RA0_ANALOG); // DS18s20 input
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_COUNTERS(RTCC_internal.rtcc_div_1); //division mark
   setup_adc_channel(0);

   while (true)
   {
      temperature=(float)read_adc()/2;
      if (temperature>-1&&temperature<10)
      {
         cycle(temperature,0,0);
      }
      sig(10,1,0);
      sig(20,2,0);
      sig(30,3,0);
      sig(40,4,0);
      sig(50,5,0);
      sig(60,6,0);
      sig(70,7,0);
      sig(80,8,0);
      sig(90,9,0);
      sig(100,0,1);
      sig(110,1,1;
      sig(120,2,1);
      sig(130,3,1);
      sig(140,4,1);

      if (temperature>149)
      {
         cycle(10,10,10);
      }
      
   }
   
}