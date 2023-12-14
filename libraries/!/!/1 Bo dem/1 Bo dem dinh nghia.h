#ifndef _bo_dem_dinh_nghia_h_
#define _bo_dem_dinh_nghia_h_
#if so_so == 2
#define ghtd 99
#endif
#if so_so == 3
#define ghtd 999
#endif
#if so_so == 4
#define ghtd 9999
#endif
#if so_so == 5
#define ghtd 99999
#endif
#if so_so == 6
#define ghtd 999999
#endif
#if so_so == 7
#define ghtd 9999999
#endif
#if so_so == 8
#define ghtd 99999999
#endif
#if so_so == 22
#define ghtd 99
#endif
#ifndef tg_luu_dat
#define tg_luu_dat 30
#endif
#define gioi_han_td ghtd // gioi han toi da

#ifndef so_so
#define so_so 6
# warning "Can dinh nghia so so hien thi cho bo dem dang su dung. mac dinh la 6 so"
#endif

#ifndef cb1
//#define cb1 dk_bit(PINC,0)
//#define cb1_d dk_bit(DDRC,0)
#define cb1_p dk_bit(PORTC,0)
#define cb2 dk_bit(PINC,1)
#define cb2_d dk_bit(DDRC,1)
#define cb2_p dk_bit(PORTC,1)
#define cb3 dk_bit(PINC,2)
#define cb3_d dk_bit(DDRC,2)
#define cb3_p dk_bit(PORTC,2)
# warning "Can dinh nghia cam bien theo mau ben tren cho phu hop phan cung"
#endif
#ifndef khong_dung_led_7_doan
#ifndef l1
#ifndef ok_led
#ifndef bo_v12
#define bo_v12
#define l1 dk_bit(PORTD,2)
#define l1_d dk_bit(DDRD,2)
#define l2 dk_bit(PORTD,3)
#define l2_d dk_bit(DDRD,3)
#define l3 dk_bit(PORTD,4)
#define l3_d dk_bit(DDRD,4)
#define l4 dk_bit(PORTB,6)
#define l4_d dk_bit(DDRB,6)
#define l5 dk_bit(PORTB,7)
#define l5_d dk_bit(DDRB,7)
#define l6 dk_bit(PORTD,5)
#define l6_d dk_bit(DDRD,5)


#define la dk_bit(PORTB,1)
#define la_d dk_bit(DDRB,1)
#define lb dk_bit(PORTB,2)
#define lb_d dk_bit(DDRB,2)
#define lc dk_bit(PORTB,3)
#define lc_d dk_bit(DDRB,3)
#define ld dk_bit(PORTB,4)
#define ld_d dk_bit(DDRB,4)
#define le dk_bit(PORTB,5)
#define le_d dk_bit(DDRB,5)
#define lf dk_bit(PORTD,7)
#define lf_d dk_bit(DDRD,7)
#define lg dk_bit(PORTD,6)
#define lg_d dk_bit(DDRD,6)
#define lh dk_bit(PORTB,0)
#define lh_d dk_bit(DDRB,0)

#define nn1 dk_bit(PIND,0)
#define nn1_d dk_bit(DDRD,0)
#define nn1_p dk_bit(PORTD,0)
#define nn2 dk_bit(PINC,5)
#define nn2_d dk_bit(DDRC,5)
#define nn3 dk_bit(PINC,4)
#define nn3_d dk_bit(DDRC,4)
#define nn4 dk_bit(PINC,3)
#define nn4_d dk_bit(DDRC,3)

#define dem_out dk_bit(PORTD,1)
#define dem_out_d dk_bit(DDRD,1)
#endif
#endif

# warning "Can dinh nghia cac chan LED theo mau tren cho phu hop phan cung"
#endif
#endif




#endif