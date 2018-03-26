#include "function.h"
#define true 1
#define false 0


void case_40();

uint8_t  pattern_dir;
uint8_t pattern_level;
uint16_t cnt1, pulse_v;
extern uint16_t pulse_ratio;
volatile uint16_t pulse_time_case_special;

int main(void)
{
	INIT();
	sel_mode();
	//sel_mode();
	///////////////////////////////////////////////////////////////////////
	//uint8_t status_sensor;
	speed(0,0,0);
	pattern_dir=10;
	handle(0);
	uint8_t conti=true;
	int previous=0;
	int special_case=0;
	ratio=0.4;
	special_ratio=1.0;
	while(1)
	{
		if (sensor_cmp(0xFF)==0b11111111||sensor_cmp(0xFF)==0b11101111) {
			conti=false;
			speed(-100,-100,100);
			_delay_ms(100);
			speed(20,20,100);
			pulse_time_case_special=0;
			case_40();
			conti=true;
		}
		//nhap du lieu led 7
		led7_data.sensor_out=sensor_cmp(0xFF);
		//===========xet truong hop queo trai, phai, thang
		if (conti) {
			led7(pattern_dir);
			switch(sensor_cmp(0xFF)) {
				case 0b00111100:
					pattern_dir=10;
					break;
				case 0b00011100:
				case 0b00011110:
				case 0b00010110:
				case 0b00001110:
				case 0b00000110:
				case 0b00000111:
				case 0b00000011:
					pattern_dir=20;
					break;
				case 0b00111000:
				case 0b01111000:
				case 0b01101000:
				case 0b01100000:
				case 0b11100000:
				case 0b11000000:
					pattern_dir=30;
					break;
				default:
					speed(0,0,0);
					break;
			}
		}
		uint8_t sensor_switch_2;
		float index_angle=0;
		switch(pattern_dir) {
			case 10:
				if(previous!=10) {
					speed(100,100,100);
					previous=10;
				}
				break;
			case 20:
				pattern_level=sensor_cmp(0xFF);
				switch(pattern_level) {
					
					case 0b00011100: //21
						if (previous!=21) {
							speed(100,80,100);
							handle(5);
						}
						led7(21);
						print();
						previous=21;
						conti=false;
						break;
						
					case 0b00011110: //22						21+10  max 20
						if(previous!=22) {
							speed(100,80,90);
							handle(12);
						}
						led7(22);
						print();
						previous=22;
						conti=false;
						break;
	
					case 0b00010110: //23
					case 0b00001110: //24
						if(previous!=23) {
							speed(100,70,70);
							handle(20);
						}
						led7(2324);
						print();
						previous=23;
						conti=false;
						break;
					
					case 0b00000100:
					case 0b00000110: //25
						if(previous!=25) {
							speed(100,60,60);
							handle(25);
						}
						led7(25);
						print();
						previous=25;
						conti=false;
						break;
						
					case 0b00000111: //26
						if(previous!=26) {
							speed(100,50,55);
							handle(30);
						}
						led7(26);
						print();
						previous=26;
						conti=false;
						break;
						
					case 0b00000011: //27
						if(previous!=27) {
							speed(100,20,60);
							handle(35);
						}
						led7(27);
						print();
						previous=27;
						conti=false;
						break;
						
					case 0b00000001: //28
						if(previous!=28) {
							speed(100,20,50);
							handle(50);
						}
						led7(28);
						print();
						previous=28;
						conti=false;
						break;
						
					case 0b00000000: //29
						if(previous!=29){
							speed(100,20,50);
							handle(70);
						}
						led7(29);
						print();
						previous=29;
						conti=false;
						break;
						
					case 0b10000000: //210
						if(previous!=210) {
							speed(100,20,60);
							handle(80);
						}
						led7(210);
						print();
						previous=210;
						conti=false;
						break;
					case 0b11000000: //211
						if(previous!=211) {
							speed(100,20,70);
							handle(80);
						}
						led7(211);
						print();
						previous=211;
						conti=false;
						break;
					case 0b00111000:
					case 0b01111000:
					case 0b01101000:
					case 0b01110000:
						pattern_dir=30;
						conti=true;
						break;
					
					case 0b00111100:
						speed(100,100,100);
						pattern_dir=10;
						conti=true;
						break;
				}
				break;
			case 30:
				pattern_level=sensor_cmp(0xFF);
				switch(pattern_level) {
					case 0b00111000: //31
						if(previous!=31) {
							speed(80,100,100);
							handle(-5);
						}
						led7(31);
						print();
						previous=31;
						conti=false;
						break;
						
					case 0b01111000: //32
						if(previous!=32) {
							speed(80,100,90);
							handle(-12);
						}
						led7(32);
						print();
						previous=32;
						conti=false;
						break;
					
					case 0b01101000: //33
						if(previous!=33) {
							speed(70,100,70);
							handle(-20);
						}
						led7(33);
						print();
						previous=33;
						conti=false;
						break;
						
					case 0b01100000: //35
						if(previous!=35) {
							speed(60,100,60);
							handle(-25);
						}
						previous=35;
						led7(35);
						print();
						conti=false;
						break;
					case 0b11100000: //36
						if(previous!=36) {
						speed(50,100,55);
						handle(-30);
						}
						previous=36;
						led7(36);
						print();
						conti=false;
						break;
					case 0b11000000: //37
						if(previous!=37) {
							speed(20,100,60);
							handle(-35);
						}
						previous=37;
						led7(37);
						print();
						conti=false;
						break;
					case 0b10000000: //38
						if(previous!=38) {
							speed(20,100,50);
							handle(-50);
						}
						previous=38;
						led7(38);
						print();
						conti=false;
						break;
						
					case 0b00000000: //39
						if(previous!=39) {
							speed(20,100,50);
							handle(-70);
						}
						previous=39;
						led7(39);
						print();
						conti=false;
						break;
						
					case 0b00000001: //310
						if(previous!=310) {
							speed(20,100,60);
							handle(-80);
						}
						previous=310;
						led7(310);
						print();
						conti=false;
						break;
						
					case 0b00000011: //311
						if(previous!=311) {
							speed(20,100,70);
							handle(-80);
						}
						previous=311;
						led7(311);
						print();
						conti=false;
						break;
					
					case 0b00011100:
					case 0b00011110:
					case 0b00010110:
					case 0b00001110:
						pattern_dir=20;
						conti=true;
						break;
						
					case 0b00111100:
						pattern_dir=10;
						conti=true;
						break;
				}
				break;
		}		
	}
}

ISR(TIMER0_COMP_vect)
{
	pulse_time_case_special=(pulse_time_case_special+1)%60000; //thoi gian trong 2s
	cnt1++;
	cal_ratio();
	print();
	
}
ISR(INT0_vect)
{
	pulse_v++;
	pulse_ratio++;
}

void	case_40() {
	while(1) {
		led7(40);
		print();
		special_ratio=0.2;
		switch(sensor_cmp(0xFF)) {
				case 0b00011100:
				handle(3);
				case 0b00011110:
				handle(3);
				case 0b00010110:
				handle(3);
				case 0b00001110:
				handle(4);
				case 0b00000110:
				handle(5);
				case 0b00111000:
				handle(-6);
				case 0b01111000:
				handle(-8);
				case 0b01101000:
				handle(-8);
				case 0b01100000:
				handle(-9);
		}
		if (pulse_time_case_special>200) {
			if (sensor_cmp(0b10000011)==0b00000011) {
				handle(114);
				special_ratio=1.0;
				ratio=0.8;
				speed(-99,11,100);
				while(1) {
					switch(sensor_cmp(0xFF)) {
					case 0b00000110:
					case 0b00111100:
					case 0b00011100:
					case 0b00111000: 
					case 0b01101000:
					case 0b01100000:
						ratio=0.4;
						speed(-100,-100,100);
						return;
						break;
					}
				}
			}
			if (sensor_cmp(0b11000011)==0b11000000) {
				handle(-105);
				special_ratio=1;
				ratio=0.8;
				speed(0,-100,100);
				uint8_t x=sensor_cmp(0xFF);
				
				while(1) {
					if(x==0b00111100||x==0b00011100||x==0b00111000||x==0b00011110||x==0b00010110||x==0b00001110) {
						ratio=0.4;
						return;
					}
					x=sensor_cmp(0xFF);
					
				}
			}
		}
		
	}
}