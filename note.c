#include <18F4520.h>

#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP

/*
NOWDT: KHONG SU DUNG CHE DO WATCH DOG TIMER
PUT (POWER UP TIMER): KHOI DONG SAU KHI TIMER CAP NGUON
HS: KHAI BAO SU DUNG THACH ANH TREN 4M
NOPROTECT: KHONG CHO PHEP DOC LAI MA CHUONG TRINH TRONG CHIP
NOLVP: KHONG SU DUNG CHE DO NAP DIEN AP THAP, CHAN PB5 DUNG LAM CHAN I/O BINH THUONG
NOBROWNOUT: KHONG RESET LA PIC KHI BI SUT AP TRONG 1 KHOAN THOI GIAN NHAT DINH
*/

/* Chong doi button

void button(){
   if(!input(mod)){
      delay_ms(20);
      if(!input(mod)){
         gia_tri++;
         if(gia_tri==4){
            gia_tri=0;
         }
       while(!input(mod));
      }
   }
}

*/

#use delay(crystal=20000000)
#byte portb = 0xFF81
#bit button=portb.7
#bit led = portb.0

void main(){
   set_tris_b(0b11111110);
   while(1){
      if (button==0){
         led=1;
      }
      else{
         led=0;
      }
   }
}


/* count
#include <18F4520.h>

#fuses NOWDT, HS, PUT, NOPROTECT, NOLVP
#use delay(crystal=20000000)

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
unsigned int8 dem, i, t0;

void main(){
   setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);
   set_timer0(0);
   while(1){
      t0 = get_timer0();
      output_d(number[t0%10]);
      if(t0==10){
         set_timer0(0);
      }
   }
}
*/
  




