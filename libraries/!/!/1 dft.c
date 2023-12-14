#ifndef _dft_c_
#define _dft_c_

void dft_khoi_tao()
{
	TCCR1B=0;
	TCCR1B = (1<<WGM12)|(1<<CS10);
	TIMSK |= 1<<OCIE1A;
	//OCR1A = 400; (0-20k)
	//OCR1A = 800;// (0-10k)
	OCR1A = 600;// (0-15k)
	cam_ngat;
}


#endif