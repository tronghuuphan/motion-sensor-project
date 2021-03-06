#include <18F4520.h>

#fuses NOWDT, HS, PUT, NOPROTECT, NOLVP
#use delay(crystal=20000000)
#byte    porta             =  0xff80
#byte    portb             =  0xff81
#byte    portc             =  0xff82
#byte    portd             =  0xff83



#bit     sensor            =  porta.4
/*
#bit     units             =  portc.0
#bit     tens              =  portc.1

#bit     green_led         =  portc.2
#bit     yellow_led        =  portc.3
#bit     red_led           =  portc.4
*/

#bit     units             =  portc.2
#bit     tens              =  portc.3

#bit     green_led         =  portc.0
#bit     yellow_led        =  portc.1
#bit     red_led           =  portc.4
////////////////////////
#bit     led_mode          =  portc.5

//#bit     control_button    =  portc.6
#bit     control_button    =  portb.1

#bit     relay             =  portc.7

#bit     tmr0on            =  0xffd5.7

const unsigned char number[10]={
                                 0xc0,
                                 0xf9,
                                 0xa4,
                                 0xb0,
                                 0x99,
                                 0x92,
                                 0x82,
                                 0xf8,
                                 0x80,
                                 0x90
};

unsigned int8 t0;
int1 dem=0;

#int_ext
void modeSelection(){
   dem=~dem;
}
void display(){
   portd = number[t0%10];
   units = 1;
   tens  = 0;
   delay_ms(1);

   portd = number[t0/10];
   if(portd==number[0]){
      portd=0xff;
   } 
   tens  = 1;
   units = 0;
   delay_ms(1);
}

void checkTimer(){
   switch(t0){
      case 25:
         t0 = 0;
         set_timer0(0);
      case 0:
         green_led = 1;
         yellow_led = 0;
         red_led = 0;
         break;
      case 15:
         green_led = 0;
         yellow_led = 1;
         red_led = 0;
         break;
      case 19:
         green_led = 0;
         yellow_led = 0;
         red_led = 1;
         break;
   }
}
void main(){
   set_tris_b(0xff); //Attention pin b0 for interrupt
   set_tris_d(0x00);
   set_tris_c(0b01000000);
   set_tris_a(0xff);  
   setup_timer_0(T0_EXT_L_TO_H | T0_DIV_1);
   set_timer0(0);
   enable_interrupts(global);
   enable_interrupts(int_ext_L2H);
   while(1){
      tmr0on = 1; //Cho phep counter hoat dong
      led_mode=0; //Led hien thi che do Auto/Manual
      relay = 0;
      t0 = get_timer0();
      checkTimer();
      while(sensor==1 & dem==0){
         relay = 1;
         display();
      }  
      display();
      while(dem==1){
         tmr0on = 0; //Tam dung counter khi o che do Manual, su dung bien t0
         led_mode = 1;
         display();
         if(control_button==1){
            for (int8 i=0; i<=10;i++){display();}
            if(control_button==1){
               relay = ~relay;
               if(relay){
                  t0++;
                  checkTimer(); 
               }
               while(control_button==1){
                  display();
               }
               }
         }    
          set_timer0(t0); //Set lai gia tri timer sau khi thoat khoi che do Manual
         }
      }
   } 

