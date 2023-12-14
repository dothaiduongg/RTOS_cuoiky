#define rfi_in (1 << 2)
#define rfi_p PORTD
#define rfi_d DDRD
#define rfi_i PIND
bool co_nhan;
#define t_rf 1100
void rf_thu_init() 
{
	rfi_d &= ~rfi_in;
}

/*----------------------------------------------------------------------------
Noi Dung    :   Nhan ve 1 byte du lieu.  
Tham Bien   :   Khong. 
Tra Ve      :   1 byte du lieu kieu uint8_t.
 -----------------------------------------------------------------------------*/ 
uint8_t RF_GetByte()
{
    uint8_t data,i; 
    data=0;  
    for(i=0;i<8;i++)
    {     
        _delay_us(750);
		
        data|=((rfi_i & rfi_in&0x01)<<(7-i));  // nhan bit cao truoc
        if(rfi_i & rfi_in)while(rfi_i & rfi_in);
        else while(!(rfi_i & rfi_in));
    }                  
    return data;
}          

/*----------------------------------------------------------------------------
Noi Dung    :   Nhan va kiem tra 3 byte 0xff lam sach duong truyen.  
Tham Bien   :   Khong. 
Tra Ve      :   1: neu dung la 3 byte 0xff.
                0: khong dung la 3 byte 0xff.
 -----------------------------------------------------------------------------*/ 
uint8_t RF_GetDataStart()
{
    uint8_t i;
    if(rfi_i & rfi_in)return 0;          
    else                                 // kiem tra canh xuong
	{
        _delay_us(10);               // chong nhieu
        if(!(rfi_i & rfi_in))
        {
            while(!(rfi_i & rfi_in));       // cho cho den khi het bit 0
            while(rfi_i & rfi_in);        // cho cho den khi het bit 1 tiep theo
            for(i=0;i<22;i++)         // neu dung 20 bit 1 thi dung là 3 byte 0xff
            {          
                _delay_us(750);
                if(rfi_i & rfi_in)
                {
                    while(rfi_i & rfi_in);
                }
                else        
                {
                    return 0;
                }      
            }
            return 1;
        }
	}    
}          

/*----------------------------------------------------------------------------
Noi Dung    :   Nhan va kiem tra xung vuong bat dau khung truyen co T=4ms.  
Tham Bien   :   Khong. 
Tra Ve      :   1: neu dung la xung vuong bat dau.
                0: neu khong dung la xung vuong bat dau.
 -----------------------------------------------------------------------------*/ 
uint8_t RF_GetPulseStart()
{
     uint16_t i;
     while(rfi_i & rfi_in);
     for(i=0;;i++)
     {
        _delay_us(200);
        if(!(rfi_i & rfi_in)) break;        
     }
     if(i<10) return 0;
     else if (i>13) return 0;
     else return 1;    
}       

/*----------------------------------------------------------------------------
Noi Dung    :   Nhan va kiem tra xung vuong ket thuc khung truyen co T=6ms.  
Tham Bien   :   Khong. 
Tra Ve      :   1: neu dung la xung vuong ket thuc.
                0: neu khong dung la xung vuong ket thuc.
 -----------------------------------------------------------------------------*/
uint8_t RF_GetPulseFinish()
{
    uint16_t i;
    while(!(rfi_i & rfi_in));
    while(rfi_i & rfi_in);
    for(i=0;;i++)
    {
        _delay_us(200);
        if(!(rfi_i & rfi_in)) break;
    }
    if(i<13) return 0;
    else if(i>15) return 0;
    else return 1;
}      

/*----------------------------------------------------------------------------
Noi Dung    :   Nhan nhieu byte du lieu.  
Tham Bien   :   *array: con tro luu tru dia chi cac byte du lieu nhan vao.
                length: so byte du lieu nhan vao. 
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/ 
void RF_GetArray(uint8_t *Array,uint8_t Length)
{
    uint8_t i;
    for(i=0;i<Length;i++)
    {
        Array[i]=RF_GetByte();
    }
}    

/*----------------------------------------------------------------------------
Noi Dung    :   Nhan va kiem tra khung du lieu truyen den. 
Tham Bien   :   *data: con tro luu tru dia chi cac byte du lieu nhan vao.
                length: so byte du lieu nhan vao. 
Tra Ve      :   1: neu dung khung du lieu
                0: neu khong dung khung du lieu
 -----------------------------------------------------------------------------*/
uint8_t RF_GetFrame(uint8_t *Data,uint8_t Length)
{
    uint8_t Stop; 
    if(!RF_GetDataStart())return 0;      // Kiem tra xem co xung start khong
    else                                 // Neu dung xung start
    {
        while(!RF_GetPulseStart());     // Kiem tra bit start
        RF_GetArray(Data,Length);       // Neu dung bit start thi tien hanh doc du lieu
        Stop=RF_GetPulseFinish();       // kiem tra bit stop
        if(Stop)
        {
            _delay_ms(5);
            return 1;                                                            
        }                             
        else return 0;
    }    
}  
//======================================== 
uint8_t nhan_1_rf()
{
	uint8_t Stop;
	u8 dl;
	if(!RF_GetDataStart())return 0;      // Kiem tra xem co xung start khong
	else                                 // Neu dung xung start
	{
		while(!RF_GetPulseStart());     // Kiem tra bit start
		dl=RF_GetByte();
		Stop=RF_GetPulseFinish();       // kiem tra bit stop
		if(Stop)
		{
			_delay_ms(5);
			return dl;
		}
		else return 0;
	}
}
/******************************KET THUC FILE*********************************
______________________________ MinhHa R&D Team______________________________*/

#define ir_in pin_a2 // TIN HIEU VAO
int8 ad1,ad2;
int8 da1,da2;
bool tin_hieu=0; // bit nhan tin hieu tu chan tin hieu vao
bool tin_hieu_nho=0; // byte nho tin hieu vao
int8 tao_tre; // khai bao bien lap tao tre
void ngat_ngoai();
void doc_chan_tin_hieu();
//========================================
void khoi_tao_thu_ir()
{
	//enable_interrupts(INT_EXT);
	//EXT_INT_EDGE(H_TO_L);
	//enable_interrupts(GLOBAL);
	//output_float(ir_in); // tha noi chan

	//doc_chan_tin_hieu();
}
//========================================
void doc_chan_tin_hieu() //10*1 u
{
	tin_hieu=rfi_i & rfi_in;
}
//========================================
void ir_doi(bool muc)
{
	while((tao_tre>0)&&(tin_hieu==muc)) // cho tin hieu muc thap ket thuc
	{
		_delay_us(18); //+ 16u
		doc_chan_tin_hieu();
		tao_tre--; // giam vong lap kiem tra
		if(tao_tre==0)loi=1; // bao loi khi tin hieu muc cao dai quá 900u
	}
}
//========================================
void ir_kiem_tra(bool muc)
{
	while((tao_tre>0)&&(loi==0)) // kiem tra bit start
	{
		_delay_us(18); //+ 16u
		doc_chan_tin_hieu();
		if(tin_hieu==muc)loi=1; // neu la bit start thi tin hieu luon = 0 trong 2,4 ms
		tao_tre--; // giam vong lap kiem tra
	}
}
//========================================
int8 ir_thu()
{
	int8 du_lieu;
	int8 i; // khai bao bien tao vong lap i
	for(i=0;i<8;i++) // tien hanh thu 8 bit lenh
	{
		_delay_us(t_rf+t_rf/2);//0); // tao tre 800u bat dau lay mau
		doc_chan_tin_hieu();
		tin_hieu_nho=tin_hieu; // doc ghi nho chan tin hieu vao
		
		if(tin_hieu==0) // cho chan tin hieu len muc cao khi chan tin hieu là muc cao
		{
			tao_tre=t_rf/5/2;//0; // tao tre 50*20us = 1000 us
			ir_doi(0);
		}
		//shift_right (&du_lieu, 1, tin_hieu_nho) ;
		du_lieu|=((tin_hieu_nho&0x01)<<(i));  // nhan bit cao truoc
		tao_tre=t_rf/5/2; //
		ir_doi(1);
	}
	return du_lieu;
}
//========================================
void doc_rf() // Doc remote ty vi samsung
{
//	disable_interrupts(INT_EXT);
	tao_tre=t_rf/11*2;// tao thoi gian tre 95*45us = 4275us < 4500u
	ir_kiem_tra(1); // kiem tra bit start bao loi neu bit = 1;
	tao_tre=t_rf/5/2; //
	if(loi==0)
	{
		cli();
		ir_doi(0); // doi ket thuc muc 0 cua bit start
	}
	//if(loi==0)
	//output_toggle(tb1); // dao trang thai cua chan
	tao_tre=t_rf/11/2;// tao thoi gian tre 95*45us = 4275us < 4500u
	if(loi==0)
	ir_kiem_tra(0); // kiem tra bit start muc 1. bao loi neu muc = 0
	tao_tre=t_rf/5/2; //
	if(loi==0)
	ir_doi(1);
	if(loi==0) // chi thuc hien tiep khi khong co loi
	ad1=ad2=da1=da2=0; // bat dau thu du lieu voi dia chi = 0
	if(loi==0)
		mang_dl_rf[0]=ir_thu();
	if(loi==0)
		mang_dl_rf[1]=ir_thu();
	if(loi==0)
		mang_dl_rf[2]=ir_thu();
	if(loi==0)
		mang_dl_rf[3]=ir_thu();
	if(loi==0)
		mang_dl_rf[4]=ir_thu();
	if(loi==0)
		mang_dl_rf[5]=ir_thu();
	if(loi==0)
		mang_dl_rf[6]=ir_thu();
	if(loi==0)
		mang_dl_rf[7]=ir_thu();
	if(loi==0)
		mang_dl_rf[8]=ir_thu();
	if(loi==0)
		mang_dl_rf[9]=ir_thu();
	if(loi==0) // thuc hien khi khong co loi
	{
		_delay_us(500); // tao thoi gian tre ms
		co_nhan=1; // bao cho chuong trinh chinh biet co phim nhan
	}
//	enable_interrupts(INT_EXT);
	sei();
	loi=0;
}
