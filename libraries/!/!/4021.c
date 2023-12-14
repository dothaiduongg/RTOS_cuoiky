void doc_ngo_vao();
#define in1 dk_bit(PINC,3)
#define in1_d dk_bit(DDRC,3)
#define psi dk_bit(PORTC,4)
#define psi_d dk_bit(DDRC,4)
#define ci dk_bit(PORTC,5)
#define ci_d dk_bit(DDRC,5) 
//========================================
void doc_nhieu_ngo_vao()
{
	u8 i;
	psi=1;
	delay_us(5);
	psi=0;
	delay_us(5);
	for(i=0;i<so_modul;i++)
	{
		doc_ngo_vao(); 
		dl_vao[i]=bv1;
	}
} 
void sug()
{
	ci=1;
	delay_us(5);
	ci=0;
	delay_us(5);
}
void doc_ngo_vao()
{
	u8 i;
	bv1=0xff;
	v8=in1; 
	sug();
	v7=in1;
	sug();
	v6=in1; 
	sug();
	v5=in1;
	sug(); 
	v4=in1;
	sug();
	v3=in1;
	sug();
	v2=in1;
	sug();
	v1=in1;
	sug();
}
//======================================== 
void khoi_tao_4021()
{
	in1_d=vao;
	psi_d=ra;
	ci_d=ra;
}