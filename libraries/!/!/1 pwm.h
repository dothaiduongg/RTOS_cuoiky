#ifndef _pwm_h_
#define _pwm_h_
#define pwm_chan_d dk_bit(DDRB,1)
#define pwm_chan2_d dk_bit(DDRB,2)
void pwm_khoi_tao()
{
	TCCR1A|=(1<<COM1A1)|(1<<WGM11)|(1<<COM1B1);
	TCCR1B|=(1<<WGM13) |(1<<WGM12) |(1<<CS10) ;
	OCR1A=0;
	OCR1B=0;
	ICR1=pwm_chu_ky;
	pwm_chan_d=ra;
	pwm_chan2_d=ra;
}

#endif
