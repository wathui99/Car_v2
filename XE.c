﻿#include "function.h"
#define true 1
#define false 0
#define time_get_sample 50.0
#define err_ratio_PID 100.0

#define kp 1.0
#define ki 2.0
#define kd 0.1

void case_40();	// cua vuong
void case_50(); // trai
void case_60(); // phai
void PID_ctrl_motor();

uint8_t  pattern_dir;
uint8_t pattern_level;
volatile uint16_t pulse_v;
volatile uint16_t pre_err;
volatile uint16_t err;
volatile uint32_t pulse_time_get_sample;
volatile uint16_t pulse_time_case_special;
volatile float pPart=0;
volatile float iPart=0;
volatile float dPart=0;

int main(void)
{
	INIT();
	//init elements pid
	pulse_time_get_sample=0;
	pulse_v=0;
	pre_err=0;
	err=0;
	//end init
	sel_mode();
	pattern_dir=10;
	uint8_t conti=true;
	int previous=0; //truong hop truoc do
	while(1)
	{
		case40:
		if (sensor_cmp(0xFF)==0b11111111||sensor_cmp(0xFF)==0b11101111) { //truong hop case_40 (cua vuong phai)
			special_ratio=1;
			ratio=1;
			speed(-225,-225,100);
			_delay_ms(200);
			special_ratio=0.5;
			ratio=ratio_base;
			speed(100,100, 100);
			case_40();
			ratio=ratio_base;
			special_ratio=1;
		}
		if (sensor_cmp(0xFF)==0b11111000 || sensor_cmp(0xFF)==0b11111100 || sensor_cmp(0xFF)==0b11111110) { // case 50 (queo trai)
			speed(50,50,100);
			pulse_time_case_special=0; //thoi gian chong nhieu~
			while (pulse_time_case_special<150) {
				if(sensor_cmp(0xFF)==0xFF) { goto case40;}
			}
			case_50();
			ratio=ratio_base;
			special_ratio=1;
		}
		if (sensor_cmp(0xFF)==0b00011111 || sensor_cmp(0xFF)==0b00111111 || sensor_cmp(0xFF)==0b01111111 ){
			speed(50,50,100);
			pulse_time_case_special=0; //thoi gian chong nhieu~
			while (pulse_time_case_special<150) {
				if(sensor_cmp(0xFF)==0xFF) { goto case40;}
			}
			case_60();
			ratio=ratio_base;
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
					speed(255,255,100);
					previous=10;
				}
				break;
			case 20:
				pattern_level=sensor_cmp(0xFF);
				switch(pattern_level) {
					
					case 0b00011100: //21
						if (previous!=21) {
							speed(255,204,100);
							handle(15);
						}
						led7(21);
						print();
						previous=21;
						conti=false;
						break;
						
					case 0b00011110: //22					
						if(previous!=22) {
							speed(255,204,90);
							handle(20);
						}
						led7(22);
						print();
						previous=22;
						conti=false;
						break;
	
					case 0b00010110: //23
					case 0b00001110: //24
						if(previous!=23) {
							speed(255,179,80);
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
							speed(255,128,70);
							handle(30);
						}
						led7(25);
						print();
						previous=25;
						conti=false;
						break;
						
					case 0b00000111: //26
						if(previous!=26) {
							speed(255,128,65);
							handle(60);
						}
						led7(26);
						print();
						previous=26;
						conti=false;
						break;
						
					case 0b00000011: //27
						if(previous!=27) {
							speed(255,26,70);
							handle(70);
						}
						led7(27);
						print();
						previous=27;
						conti=false;
						break;
						
					case 0b00000001: //28
						if(previous!=28) {
							speed(255,0,80);
							handle(80);
						}
						led7(28);
						print();
						previous=28;
						conti=false;
						break;
						
					case 0b00000000: //29
						if(previous!=29){
							speed(255,-20,90);
							handle(110);
						}
						led7(29);
						print();
						previous=29;
						conti=false;
						break;
						
					case 0b10000000: //210
						if(previous!=210) {
							speed(255,-25,90);
							handle(120);
						}
						led7(210);
						print();
						previous=210;
						conti=false;
						break;
					case 0b11000000: //211
						if(previous!=211) {
							speed(255,-30,100);
							handle(120);
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
						speed(255,255,100);
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
							speed(204,255,100);
							handle(-15);
						}
						led7(31);
						print();
						previous=31;
						conti=false;
						break;
						
					case 0b01111000: //32
						if(previous!=32) {
							speed(204,255,90);
							handle(-20);
						}
						led7(32);
						print();
						previous=32;
						conti=false;
						break;
					
					case 0b01101000: //33
						if(previous!=33) {
							speed(179,255,80);
							handle(-25);
						}
						led7(33);
						print();
						previous=33;
						conti=false;
						break;
						
					case 0b01100000: //35
						if(previous!=35) {
							speed(128,255,70);
							handle(-30);
						}
						previous=35;
						led7(35);
						print();
						conti=false;
						break;
					case 0b11100000: //36
						if(previous!=36) {
						speed(128,255,65);
						handle(-60);
						}
						previous=36;
						led7(36);
						print();
						conti=false;
						break;
					case 0b11000000: //37
						if(previous!=37) {
							speed(26,255,70);
							handle(-70);
						}
						previous=37;
						led7(37);
						print();
						conti=false;
						break;
					case 0b10000000: //38
						if(previous!=38) {
							speed(0,255,80);
							handle(-80);
						}
						previous=38;
						led7(38);
						print();
						conti=false;
						break;
						
					case 0b00000000: //39
						if(previous!=39) {
							speed(-20,255,90);
							handle(-110);
						}
						previous=39;
						led7(39);
						print();
						conti=false;
						break;
						
					case 0b00000001: //310
						if(previous!=310) {
							speed(-25,255,90);
							handle(-120);
						}
						previous=310;
						led7(310);
						print();
						conti=false;
						break;
						
					case 0b00000011: //311
						if(previous!=311) {
							speed(-30,255,100);
							handle(-120);
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

// special case
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
		sensor_cmp(0xFF)==0b00000001||
		
		sensor_cmp(0xFF)==0b00111000||
		sensor_cmp(0xFF)==0b01111000||
		sensor_cmp(0xFF)==0b01100000||
		sensor_cmp(0xFF)==0b11100000||
		sensor_cmp(0xFF)==0b11000000||
		sensor_cmp(0xFF)==0b10000000) // delay den khi nao thoat khoi vach ngang bao hieu
		break;
	}
	while(1) { // bat dau while
		led7_data.sensor_out=sensor_cmp(0xFF);
		switch(sensor_cmp(0xFF)) {
			//tin hieu re phai (cua vuong)
			case 0b11010000:
			case 0b10010000:
			case 0b00011111:
			case 0b00001111:
			ratio=1;
			handle(120);
			special_ratio=0.3;
			speed(220,-30,100);
			uint8_t value=sensor_cmp(0xFF);
			while(1) {
				if(value==0b00111100||
				value==0b00011100||
				value==0b00011110||
				value==0b00010110||
				value==0b00001110||
				value==0b00000110||
				value==0b00111000||
				value==0b01111000||
				value==0b01101000||
				value==0b01100000)
				return;
				value=sensor_cmp(0xFF);
			}
			break;
			
			//tin hieu re trai cua vuong
			case 0b11111000:
			case 0b00010011:
			case 0b00010001:
			case 0b00010110:
			case 0b11101100:
				ratio=1;
				handle(-120);
				special_ratio=0.3;
				speed(-30,220,100);
				value=sensor_cmp(0xFF);
				while(1) {
					if(value==0b00111100||
					value==0b00011100||
					value==0b00011110||
					value==0b00010110||
					value==0b00001110||
					value==0b00000110||
					value==0b00111000||
					value==0b01111000||
					value==0b01101000||
					value==0b01100000)
					return;
					value=sensor_cmp(0xFF);
				}
			break;
		}
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
				case 0b00000001:
				pattern_dir=20; //queo phai
				break;
				case 0b00111000:
				case 0b01111000:
				case 0b01101000:
				case 0b01100000:
				case 0b11100000:
				case 0b11000000:
				case 0b10000000:
				pattern_dir=30; //queo trai
				break;
				default:
				speed(0,0,0);
				break;
			}
		}
		
		switch(pattern_dir) { //di vao chi tiet
			//case di thang
			case 10:
			if(previous!=10) {
				speed(255,255,100);
				previous=10;
			}
			break;
			//case queo phai
			case 20:
			pattern_level=sensor_cmp(0xFF);
			switch(pattern_level) {
				
				case 0b00011100: //21
				if (previous!=21) {
					speed(255,204,100);
					handle(7);
				}
				led7(21);
				print();
				previous=21;
				conti=false;
				break;
				
				case 0b00011110: //22
				if(previous!=22) {
					speed(255,204,90);
					handle(8);
				}
				led7(22);
				print();
				previous=22;
				conti=false;
				break;
				
				case 0b00010110: //23
				case 0b00001110: //24
				if(previous!=23) {
					speed(255,179,80);
					handle(10);
				}
				led7(2324);
				print();
				previous=23;
				conti=false;
				break;
				
				case 0b00000100:
				case 0b00000110: //25
				if(previous!=25) {
					speed(255,128,70);
					handle(15);
				}
				led7(25);
				print();
				previous=25;
				conti=false;
				break;
				
				case 0b00000111: //26
				if(previous!=26) {
					speed(255,128,65);
					handle(20);
				}
				led7(26);
				print();
				previous=26;
				conti=false;
				break;
				
				case 0b00000011: //27
				if(previous!=27) {
					speed(255,26,70);
					handle(25);
				}
				led7(27);
				print();
				previous=27;
				conti=false;
				break;
				
				case 0b00000001: //28
				if(previous!=28) {
					speed(255,0,80);
					handle(30);
				}
				led7(28);
				print();
				previous=28;
				conti=false;
				break;
				
				//case nhieu
				case 0b01111111:
				case 0b11111110:
				case 0b01111110:
				case 0b00111111:
				case 0b11111100:
					//tin hieu re trai trong case 20
					ratio=1;
					handle(-120);
					special_ratio=0.3;
					speed(-30,220,100);
					uint8_t value = sensor_cmp(0xFF);
					while(1) {
						if(value==0b00111100||
						value==0b00011100||
						value==0b00011110||
						value==0b00010110||
						value==0b00001110||
						value==0b00000110||
						value==0b00111000||
						value==0b01111000||
						value==0b01101000||
						value==0b01100000)
						return;
						value=sensor_cmp(0xFF);
					}
				break;
				
				case 0b00111000:// case lech phai, queo trai
				case 0b01111000:
				case 0b01101000:
				case 0b01110000:
				pattern_dir=30;
				conti=true;
				break;
				
				case 0b00111100:
				speed(255,255,100);
				pattern_dir=10;
				conti=true;
				break;
			}
			break;
			
			//case queo trai
			case 30:
			pattern_level=sensor_cmp(0xFF);
			switch(pattern_level) {
				case 0b00111000: //31
				if(previous!=31) {
					speed(204,255,100);
					handle(-8);
				}
				led7(31);
				print();
				previous=31;
				conti=false;
				break;
				
				case 0b01111000: //32
				if(previous!=32) {
					speed(204,255,90);
					handle(-10);
				}
				led7(32);
				print();
				previous=32;
				conti=false;
				break;
				
				case 0b01101000: //33
				if(previous!=33) {
					speed(179,255,80);
					handle(-15);
				}
				led7(33);
				print();
				previous=33;
				conti=false;
				break;
				
				case 0b01100000: //35
				if(previous!=35) {
					speed(128,255,70);
					handle(-20);
				}
				previous=35;
				led7(35);
				print();
				conti=false;
				break;
				case 0b11100000: //36
				if(previous!=36) {
					speed(128,255,65);
					handle(-25);
				}
				previous=36;
				led7(36);
				print();
				conti=false;
				break;
				case 0b11000000: //37
				if(previous!=37) {
					speed(26,255,70);
					handle(-30);
				}
				previous=37;
				led7(37);
				print();
				conti=false;
				break;
				case 0b10000000: //38
				if(previous!=38) {
					speed(-13,255,80);
					handle(-35);
				}
				previous=38;
				led7(38);
				print();
				conti=false;
				break;
				
				//case nhieu
				case 0b01111111:
				case 0b11111110:
				case 0b01111110:
				case 0b00111111:
				case 0b11111100:
				//tin hieu re phai trong case 30
					special_ratio=0.3;
					ratio=1;
					handle(120);
					speed(220,-30,100);
					uint8_t value=sensor_cmp(0xFF);
					while(1) {
						if(value==0b00111100||
						value==0b00011100||
						value==0b00011110||
						value==0b00010110||
						value==0b00001110||
						value==0b00000110||
						value==0b00111000||
						value==0b01111000||
						value==0b01101000||
						value==0b01100000)
						return;
						value=sensor_cmp(0xFF);
					}
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
void case_50() {
	handle(-45);
	led7(5555);
	while(sensor_cmp(0xFF)!=0x00) {}
	uint8_t temp=sensor_cmp(0xFF);
	while(temp!=0b00111000 && temp!=0b01111000 && temp!=0b01101000 && temp!=0b00011100 && temp!=0b00011110 && temp!=0b00010110 && temp!=0b00111100) {
		temp=sensor_cmp(0xff);
	}
		
}
void case_60()
{
	handle(45);
	led7(6666);
	while(sensor_cmp(0xFF)!=0x00) {}
	uint8_t temp=sensor_cmp(0xFF);
	while(temp!=0b00111000 && temp!=0b01111000 && temp!=0b01101000 && temp!=0b00011100 && temp!=0b00011110 && temp!=0b00010110 && temp!=0b00111100) {
		temp=sensor_cmp(0xff);
	}
}

//PID ctrl
void PID_ctrl_motor() {
	err=pulse_v_des-pulse_v;
	pPart=err*kp;
	dPart=kd*(err-pre_err)*time_get_sample;
	iPart+=ki*err*time_get_sample/1000; //don vi chuan la s
	PID_ratio=(pPart+dPart+iPart)/err_ratio_PID;
	pre_err=err;
}
ISR(TIMER0_COMP_vect)
{
	pulse_time_case_special=(pulse_time_case_special+1)%60000; //thoi gian trong 2s
	pulse_time_get_sample++;
	if(pulse_time_get_sample==time_get_sample) {
		PID_ctrl_motor();
		pulse_v=0; //reset
		pulse_time_get_sample=0;
	}
	print();
}
ISR(INT0_vect)
{
	pulse_v++;
}
