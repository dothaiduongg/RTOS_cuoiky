/*-------Dinh nghia one-wire-------*/ 
#define ONE_WIRE_PIN PC0
#define OW_IN   PINC
#define OW_OUT  PORTC
#define OW_DDR  DDRC
#define OW_CONF_DELAYOFFSET 0
#define OW_GET_IN()   ( ONE_WIRE_PIN & (1<<ONE_WIRE_PIN))
#define OW_OUT_LOW()  ( OW_OUT &= (~(1 << ONE_WIRE_PIN)) )
#define OW_OUT_HIGH() ( OW_OUT |= (1 << ONE_WIRE_PIN) )
#define OW_DIR_IN()   ( OW_DDR &= (~(1 << ONE_WIRE_PIN )) )
#define OW_DIR_OUT()  ( OW_DDR |= (1 << ONE_WIRE_PIN) )

#define OW_MATCH_ROM	0x55
#define OW_SKIP_ROM	    0xCC
#define	OW_SEARCH_ROM	0xF0

#define	OW_SEARCH_FIRST	0xFF		// start new search
#define	OW_PRESENCE_ERR	0xFF
#define	OW_DATA_ERR	    0xFE
#define OW_LAST_DEVICE	0x00		// last device found
//			0x01 ... 0x40: continue searching

// rom-code size including CRC
#define OW_ROMCODE_SIZE 8

uint8_t onewire_reset()  // reset one wire
{
	uint8_t err;
	uint8_t sreg;

	OW_OUT_LOW(); // disable internal pull-up (maybe on from parasite)
	OW_DIR_OUT(); // pull OW-Pin low for 480us

	_delay_us(480);

	sreg=SREG;
	cli();

	// set Pin as input - wait for clients to pull low
	OW_DIR_IN(); // input

	_delay_us(66);
	err = OW_GET_IN();		// no presence detect
	// nobody pulled to low, still high

	SREG=sreg; // sei()

	// after a delay the clients should release the line
	// and input-pin gets back to high due to pull-up-resistor
	_delay_us(480-66);
	if( OW_GET_IN() == 0 )		// short circuit
	err = 1;

	return err;
}
//======================================== 
/*void ow_set_bus(volatile uint8_t* in, volatile uint8_t* out, volatile uint8_t* ddr, uint8_t pin)
{
	OW_DDR=ddr;
	OW_OUT=out;
	OW_IN=in;
	ONE_WIRE_PIN=(1<<pin);
	onewire_reset();
}*/

//====================
uint8_t ow_bit_io( uint8_t b )
{ uint8_t sreg;

	sreg=SREG;
	cli();
	
	OW_DIR_OUT(); // drive bus low

	_delay_us(1); // Recovery-Time wuffwuff was 1
	if ( b ) OW_DIR_IN(); // if bit is 1 set bus high (by ext. pull-up)
	
	// wuffwuff delay was 15uS-1 see comment above
	_delay_us(15-1-OW_CONF_DELAYOFFSET);
	
	if( OW_GET_IN() == 0 ) b = 0;  // sample at end of read-timeslot
	
	_delay_us(60-15);
	OW_DIR_IN();

	SREG=sreg; // sei();
	
	return b;
}
//======================================== 
//Ghi vao 1 wire
uint8_t ghi_1wire(uint8_t data) 
{ 
	uint8_t i = 8, j;
	do
	{ j = ow_bit_io( data & 1 );
		data >>= 1;
		if( j ) data |= 0x80;
	}
	while( --i );
	return data;
} 
//====================
//Doc 1 byte tu 1 wire
uint8_t doc_1wire() 
{ 
	return ghi_1wire( 0xFF ); 
} 


void ow_command( uint8_t command, uint8_t *id )
{ uint8_t i;

	onewire_reset();
	if( id )
	{ ghi_1wire( OW_MATCH_ROM );			// to a single device
		i = OW_ROMCODE_SIZE;
		do
		{ ghi_1wire( *id );
			id++;
		}
		while( --i );
	}
	else
	ghi_1wire( OW_SKIP_ROM );			// to all devices

	ghi_1wire( command );
}


uint8_t ow_input_pin_state()
{ return OW_GET_IN();
}

void ow_parasite_enable(void)
{ OW_OUT_HIGH();
	OW_DIR_OUT();
}

void ow_parasite_disable(void)
{ OW_OUT_LOW();
	OW_DIR_IN();
}
