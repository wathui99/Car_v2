﻿#include "function.h"
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
	pattern_dir=10;
	uint8_t conti=true;
	int previous=0;
	ratio=0.5; //giam 1/2 van toc max
	special_ratio=1.0; //he so van toc truong hop dac biet
	while(1)
	{
		if (sensor_cmp(0xFF)==0b11111111||sensor_cmp(0xFF)==0b11101111) { //truong hop case_40 (cua vuong phai)
			speed(-100,-100,100);
			_delay_ms(100);
			speed(20,25,100);
			special_ratio=0.5;
			pulse_time_case_special=0; //thoi gian chong nhieu~
			case_40();
			ratio=0.5;
			special_ratio=1;
		}
		//nhap du lieu led 7
		led7_data.sensor_out=sensor_cmp(0xFF);
		
		//===========xet truong hop queo trai, phai, thang
		if (conti) {
			led7(pattern_dir);
			switch(sensor_cmp(0xFF)) {
				case 0b00111100:
					pattern_dir=10; //di thang
					break;
				case 0b00011100:
				case 0b00011110:
				case 0b00010110:
				case 0b00001110:
				case 0b00000110:
				case 0b00000111:
				case 0b00000011:
					pattern_dir=20; //queo phai
					break;
				case 0b00111000:
				case 0b01111000:
				case 0b01101000:
				case 0b01100000:
				case 0b11100000:
				case 0b11000000:
					pattern_dir=30; //queo trai
					break;
				default:
					speed(0,0,0);
					break;
			}
		}
		
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
						
					case 0b00011110: //22					
						if(previous!=22) {
							speed(100,80,90);
							handle(15);
						}
						led7(22);
						print();
						previous=22;
						conti=false;
						break;
	
					case 0b00010110: //23
					case 0b00001110: //24
						if(previous!=23) {
							speed(100,70,80);
							handle(25);
						}
						led7(2324);
						print();
						previous=23;
						conti=false;
						break;
					
					case 0b00000100:
					case 0b00000110: //25
						if(previous!=25) {
							speed(100,60,70);
							handle(30);
						}
						led7(25);
						print();
						previous=25;
						conti=false;
						break;
						
					case 0b00000111: //26
						if(previous!=26) {
							speed(100,50,65);
							handle(35);
						}
						led7(26);
						print();
						previous=26;
						conti=false;
						break;
						
					case 0b00000011: //27
						if(previous!=27) {
							speed(100,20,70);
							handle(50);
						}
						led7(27);
						print();
						previous=27;
						conti=false;
						break;
						
					case 0b00000001: //28
						if(previous!=28) {
							speed(100,10,70);
							handle(80);
						}
						led7(28);
						print();
						previous=28;
						conti=false;
						break;
						
					case 0b00000000: //29
						if(previous!=29){
							speed(100,10,70);
							handle(100);
						}
						led7(29);
						print();
						previous=29;
						conti=false;
						break;
						
					case 0b10000000: //210
						if(previous!=210) {
							speed(100,10,70);
							handle(110);
						}
						led7(210);
						print();
						previous=210;
						conti=false;
						break;
					case 0b11000000: //211
						if(previous!=211) {
							speed(100,10,70);
							handle(110);
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
							handle(-15);
						}
						led7(32);
						print();
						previous=32;
						conti=false;
						break;
					
					case 0b01101000: //33
						if(previous!=33) {
							speed(70,100,80);
							handle(-25);
						}
						led7(33);
						print();
						previous=33;
						conti=false;
						break;
						
					case 0b01100000: //35
						if(previous!=35) {
							speed(60,100,70);
							handle(-30);
						}
						previous=35;
						led7(35);
						print();
						conti=false;
						break;
					case 0b11100000: //36
						if(previous!=36) {
						speed(50,100,65);
						handle(-35);
						}
						previous=36;
						led7(36);
						print();
						conti=false;
						break;
					case 0b11000000: //37
						if(previous!=37) {
							speed(20,100,70);
							handle(-50);
						}
						previous=37;
						led7(37);
						print();
						conti=false;
						break;
					case 0b10000000: //38
						if(previous!=38) {
							speed(20,100,70);
							handle(-80);
						}
						previous=38;
						led7(38);
						print();
						conti=false;
						break;
						
					case 0b00000000: //39
						if(previous!=39) {
							speed(20,100,70);
							handle(-100);
						}
						previous=39;
						led7(39);
						print();
						conti=false;
						break;
						
					case 0b00000001: //310
						if(previous!=310) {
							speed(20,100,70);
							handle(-110);
						}
						previous=310;
						led7(310);
						print();
						conti=false;
						break;
						
					case 0b00000011: //311
						if(previous!=311) {
							speed(20,100,70);
							handle(-110);
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

void case_40() {
	uint8_t conti=true;
	uint8_t pattern_dir=10;
	uint8_t pattern_level;
	int previous=10;
	while (1) {
		if (sensor_cmp(0xFF)==0b00011100||
		sensor_cmp(0xFF)==0b00011110||
		sensor_cmp(0xFF)==0b00010110||
		sensor_cmp(0xFF)==0b00001110||
		sensor_cmp(0xFF)==0b00000110||
		sensor_cmp(0xFF)==0b00000111||
		
		sensor_cmp(0xFF)==0b00111000||
		sensor_cmp(0xFF)==0b01111000||
		sensor_cmp(0xFF)==0b01100000||
		sensor_cmp(0xFF)==0b11100000||
		sensor_cmp(0xFF)==0b11000000) // delay den khi nao thoat khoi vach ngang bao hieu
		break;
	}
	while(1) { // bat dau while
		led7_data.sensor_out=sensor_cmp(0xFF);
		if (conti) {
			led7(pattern_dir);
			switch(sensor_cmp(0xFF)) {
				case 0b00111100:
				pattern_dir=10; //di thang
				break;
				case 0b00011100:
				case 0b00011110:
				case 0b00010110:
				case 0b00001110:
				case 0b00000110:
				pattern_dir=20; //queo phai
				break;
				case 0b00111000:
				case 0b01111000:
				case 0b01101000:
				case 0b01100000:
				pattern_dir=30; //queo trai
				break;
				default: //khong nam trong case nao ca ->stop
				speed(0,0,0);
				break;
			}
		}// if (conti)
		
		switch(pattern_dir) { //di vao chi tiet
			//case di thang
			case 10:
			if(previous!=10) {
				speed(100,100,100);
				previous=10;
			}
			break;
			//case queo phai
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
				
				case 0b00011110: //22
				if(previous!=22) {
					speed(100,80,90);
					handle(15);
				}
				led7(22);
				print();
				previous=22;
				conti=false;
				break;
				
				case 0b00010110: //23
				case 0b00001110: //24
				if(previous!=23) {
					speed(100,70,80);
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
					speed(100,60,70);
					handle(25);
				}
				led7(25);
				print();
				previous=25;
				conti=false;
				break;
				
				
				case 0b00111000:// case lech phai
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
				
/*
///////////////////////
//////////////////////
///////////////////// INSERT CODE
/////////////////////
////////////////////
*/
			}
			break;
			
			//case queo trai
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
					handle(-15);
				}
				led7(32);
				print();
				previous=32;
				conti=false;
				break;
				
				case 0b01101000: //33
				if(previous!=33) {
					speed(70,100,80);
					handle(-20);
				}
				led7(33);
				print();
				previous=33;
				conti=false;
				break;
				
				case 0b01100000: //35
				if(previous!=35) {
					speed(60,100,70);
					handle(-25);
				}
				previous=35;
				led7(35);
				print();
				conti=false;
				break;
				
				case 0b00011100: //case lech trai
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
	} //ket thuc while
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
