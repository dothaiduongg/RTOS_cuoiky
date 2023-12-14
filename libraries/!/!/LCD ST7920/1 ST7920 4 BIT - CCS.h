/***************************************************************************
*                DRIVE PARA LCD GRAFICO 128X64 CHIP ST7920                 *
*   COMANDOS                                                               *
*   #define mode_8_bit user lcd mode 8 bit
*   #define mode_4_bit user lcd mode 4 bit
*   glcd_readByte()//LER DADOS DO LCD                                      *
*   glcd_check_busy()//VERIFICA SE LCD ESTA OCUPADO                        *                              *
*   glcd_instruction(instruções)//SETA INTRUÇÕES                           *
*   glcd_data(dados)//ENVIA DADOS PARA LCD                                 *
*   glcd_init_basic()//INICIA LCD  COMO MODO BASICO                        *
*   glcd_update()//ATUALIZA LCD                                            *
*   glcd_init_graph()//INICIA LCD MODO GRAFICO                             *
*   glcd_pixel( x,  y, color)//CONTROLE DE PIXEL                           *
*   glcd_fillScreen(on)//ENVIO NIVEL 1 PARA TODOS OS PIXEL DO LCD          *
*   glcd_fillScreen(off)//ENVIA NIVEL 0 PARA TODOS OS PIXEL DO LCD         *
*   glcd_plot_image(imagem,largura,altura,coluna,linha,cor) carrega imagem *
*                                                                          *                 
*   PINAGEM DO LCD                                                         *
*   Pin 1 ------------> Gnd                                                *   
*   Pin 2 ------------> +5volts                                            *
*   Pin 3 ------------> Contrast                                           *
*   Pin 4 ------------> Register Select                                    *
*   Pin 5 ------------> Read/Write                                         *
*   Pin 6 ------------> Enable                                             *
*   Pin 7-14 ---------> Data bits                                          *
*   Pin 15 -----------> PSB (parallel=high & serial=low)                   *
*   Pin 16 -----------> NoConnection                                       *
*   Pin 17 -----------> Reset                                              *
*   Pin 18 -----------> Vout                                               *
*   Pin 19 -----------> +5volts                                            *
*   Pin 20 -----------> Gnd                                                *
*                                                                          * 
***************************************************************************/
//DEFINIÇÃO DE PINOS
//PIN DEFINITION
#define  RS        PIN_B2                    //COMMNAD/DATA SELECT
#define  RW        PIN_B3                    //READ/WRITE SELECT             
#define  E         PIN_B4                    //ENABLE SIGNAL                 
#define  RST       PIN_B5                    //RESET SIGNAL 

#if defined(mode_8_bit)// define pin lcd 8 bit
#define  D0        PIN_D0
#define  D1        PIN_D1
#define  D2        PIN_D2
#define  D3        PIN_D3
#define  D4        PIN_D4
#define  D5        PIN_D5
#define  D6        PIN_D6
#define  D7        PIN_D7
#define mode       0x10
#endif

#if defined(mode_4_bit)// define pin lcd 4 bit
#define  D4        PIN_D4
#define  D5        PIN_D5
#define  D6        PIN_D6
#define  D7        PIN_D7
#define mode       0x00 
#endif

#define  set_lcd_bit  0x20 | (mode) //mode 4 bit
#define  ext_instru   0x24 | (mode) //Select extended instruction set
#define  graphic_on   0x26 | (mode) // Graphic display ON. 
#define  set_lcd_on   0x0C //display on cursor off and char blink off
#define  set_mode_lcd 0x06 //entry mode set
#define  clear_lcd    0x01 //display clear

#define  DADOS_IN  INPUT_D()
#define  BUSY_IN   PIN_D7
#define  ON   1
#define  OFF   0
//LCD GRAPHICO 128X64
#define  YVAL 64 // DEFINE 64 LINHAS
#define  XVAL 8 // DEFINE COLUNAS 8X16=128 COLUNAS

#define GLCD_WIDTH   128 //DEFINE 128 COLUNAS 

typedef union
{
  int16 word;
  int8 nbyte[2];
} Dots;

typedef struct
{
  int1 refresh;
  Dots pix[YVAL][XVAL];   // Max dimensions for display (x,y) = (128,32)
  } GD_RAM;             //  (0,0) corresponds to upper lefthand corner.

GD_RAM gdram;


unsigned int8 glcd_readByte (unsigned int1 address)//LER BYTE DO LCD
{
  unsigned int8 data;   // Stores the data read from the LCD
  if(address==1)
  {
     output_high(rs);
  }
  if(address==0)
  {
     output_low(rs);
  }
  output_high(rw);//GLCD_RW = RW_READ;      // Set for reading
  output_high(e);//GLCD_E = 1;      // Pulse the enable pin
  delay_us(1);
  data=DADOS_IN;      // Get the data from the display's output register
  output_low(e);//GLCD_E = 0;
  return (data);
}

 
void glcd_check_busy()//VERIFICA SE LCD ESTA OCUPADO
{
   int1 busy=1;
   output_low(rs);      // LOW RS and High RW will put the lcd to
   output_high(rw);      // read busy flag and address counter
   while(busy)
   {         // will cycle until busy flag is 0
      output_high(e);
      if(!input(BUSY_IN))
      {
         busy=0;
      }
      output_low(e);
   }
}
 
void glcd_instruction(unsigned char x)//ENVIA INSTRUÇÕES PARA LCD
{
  #if defined(mode_8_bit)// 8 bit mode
   glcd_check_busy();      //must be satisfied before sending instruction
   output_low(rs);      // LOW RS and LOW RW will put the lcd to
   output_low(rw);      // Write instruction mode   
   Delay_us(5);  //Delay
   output_bit(D7,bit_test(x,7)); //send data bit 7 pin D7
   output_bit(D6,bit_test(x,6)); //send data bit 6 pin D6
   output_bit(D5,bit_test(x,5)); //send data bit 5 pin D5
   output_bit(D4,bit_test(x,4)); //send data bit 4 pin D4
   output_bit(D3,bit_test(x,3)); //send data bit 3 pin D3 
   output_bit(D2,bit_test(x,2)); //send data bit 2 pin D2
   output_bit(D1,bit_test(x,1)); //send data bit 1 pin D1
   output_bit(D0,bit_test(x,0)); //send data bit 0 pin D0
   Delay_us(10);
   output_high(e);//anable
   Delay_us(20);
   output_low(e);// disable       
   #endif
 #if defined(mode_4_bit) // 4 bit mode
   glcd_check_busy();      //must be satisfied before sending instruction
   output_low(rs);      // LOW RS and LOW RW will put the lcd to
   output_low(rw);      // Write instruction mode   
   Delay_us(5);//Delay
   output_bit(D7,bit_test(x,7)); 
   output_bit(D6,bit_test(x,6));
   output_bit(D5,bit_test(x,5));
   output_bit(D4,bit_test(x,4));
   Delay_us(5);
   output_high(e); //enable
   Delay_us(5);
   output_low(e); //disable
   Delay_us(5);
   output_bit(D7,bit_test(x,3));//send data low bit 3 pin D7 
   output_bit(D6,bit_test(x,2));//send data low bit 2 pin D6
   output_bit(D5,bit_test(x,1));//send data low bit 1 pin D5
   output_bit(D4,bit_test(x,0));//send data low bit 0 pin D4
   Delay_us(5);
   output_high(e);
   Delay_us(5);
   output_low(e); // disable 
   #endif

}
void glcd_data(unsigned char x)//ENVIA DADOS PARA LCD
{
  #if defined(mode_8_bit) // 8 bit mode
   glcd_check_busy();
   output_high(rs);      // HIGH RS and LOW RW will put the lcd to
   output_low(rw);      // Write data register mode
   Delay_us(5);
   output_bit(D7,bit_test(x,7)); //send data bit 7 pin D7
   output_bit(D6,bit_test(x,6)); //send data bit 6 pin D6
   output_bit(D5,bit_test(x,5)); //send data bit 5 pin D5
   output_bit(D4,bit_test(x,4)); //send data bit 4 pin D4
   output_bit(D3,bit_test(x,3)); //send data bit 3 pin D3 
   output_bit(D2,bit_test(x,2)); //send data bit 2 pin D2
   output_bit(D1,bit_test(x,1)); //send data bit 1 pin D1
   output_bit(D0,bit_test(x,0)); //send data bit 0 pin D0
   Delay_us(10);
   output_high(e);
   Delay_us(20);
   output_low(e); // disable
   #endif
   
   #if defined(mode_4_bit) // 4 bit mode
   glcd_check_busy(); 
   output_high(rs);      // HIGH RS and LOW RW will put the lcd to
   output_low(rw);      // Write data register mode   
   Delay_us(5);
   output_bit(D7,bit_test(x,7));//send data high bit 7 pin D7 
   output_bit(D6,bit_test(x,6));//send data high bit 6 pin D6
   output_bit(D5,bit_test(x,5));//send data high bit 5 pin D5
   output_bit(D4,bit_test(x,4));//send data high bit 4 pin D4
   Delay_us(5);
   output_high(e);
   Delay_us(5);
   output_low(e); // disable 
   Delay_us(5);
   output_bit(D7,bit_test(x,3));//send data low bit 3 pin D7 
   output_bit(D6,bit_test(x,2));//send data low bit 2 pin D6
   output_bit(D5,bit_test(x,1));//send data low bit 1 pin D5
   output_bit(D4,bit_test(x,0));//send data low bit 0 pin D4
   Delay_us(5);
   output_high(e);
   Delay_us(5);
   output_low(e); // disable 
   #endif
}
 
void glcd_fillScreen (unsigned int1 color)//GRAVA 1 OU 0 EM TODOS OS PIXEL
{
  int8 v, h;
  int16 d;
  d = (color == ON ? 0xFFFF : 0x0000);
 // d = (color == ON ? 0x0000 : 0xFFFF );
  for (v=0; v < YVAL; v++)//32
  {
    for (h=0; h < XVAL; h++)//16
    {
      gdram.pix[v][h].word = d;
    }
  }
  gdram.refresh = TRUE;
}


void glcd_update ()//ATUALIZA LCD
{
  int8 v, h;
  if (gdram.refresh)//verifica se foi atualizado 
  {
    for (v=0; v <YVAL; v++) //64 linhas
    {
      if(v<32)
      {
         glcd_instruction( 0x80 | v);   // Set Vertical Address.
         glcd_instruction( 0x80);   // Set Horizontal Address.           
      }
      else
      {
         glcd_instruction( 0x80 | (v - 32));   // Set Vertical Address.
         glcd_instruction( 0x88);   // Set Horizontal Address.           
      }
      for (h=0; h <XVAL; h++) //8x16=128 colunas
      {
        glcd_data( gdram.pix[v][h].nbyte[1]);   // Write High Byte.
        glcd_data( gdram.pix[v][h].nbyte[0]);   // Write Low Byte.
      }
    }
    gdram.refresh = FALSE;
  }
}



void glcd_init_graph()//INICIA EM MODO GRAPHICO
{
   delay_ms(40);
   output_low(rst);  //reset LCD
   delay_us(1);                     
   output_high(rst);  //LCD normal operation
   glcd_instruction(set_lcd_bit);  //set 4 and 8  bit operation and basic instruction set
   delay_us(144);
   glcd_instruction(0x0C);  //display on cursor off and char blink off
   delay_us(100);
   glcd_instruction(clear_lcd);  //display clear
   delay_ms(10);
   glcd_instruction(set_mode_lcd);  //entry mode set
   delay_us(72);                 
   glcd_instruction(ext_instru);  // Select extended instruction set.
   delay_us (72);   
   glcd_instruction(graphic_on);  // Graphic display ON.
   delay_us (72);
   glcd_fillScreen (OFF); // clear all pixel
   glcd_update (); // update display

}

void glcd_init_basic()//INICIA EM MODO BASICO
{
   delay_ms(40);
   output_low(rst);         //reset LCD
   delay_us(1);                     
   output_high(rst);        //LCD normal operation
   glcd_instruction(set_lcd_bit);   //set 4 bit operation and basic instruction set
   delay_us(144);
   glcd_instruction(0x0C);   //display on cursor off and char blink off
   delay_us(100);
   glcd_instruction(clear_lcd);   //display clear
   delay_ms(10);
   glcd_instruction(set_mode_lcd);   //entry mode set
   delay_us(72);                 
}
//              0     0        0
void glcd_pixel(int8 x, int8 y, int1 color)//GRAVA NOVO VALOR DOS PIXEL
{
  int8 v, h, b;
  v = y;
  h = x/16;
  b = 15 - (x%16);
 
  if (color == ON)
  {
   bit_set (gdram.pix[v][h].word, b);
  }
 
  else
  {
   bit_clear (gdram.pix[v][h].word, b);
  }
  gdram.refresh = TRUE;
}
//                       
void glcd_plot_image(ROM char *img,int width,int height,int x,int y,int inverse)//CARREGA IMAGEM
{
   unsigned int i=0, j=0, k=0;
   unsigned int16 count=0;
   
   //glcd_fillScreen(OFF);                        //Clears the screen (opt.)
   for(j=0;j<height;j++)//linhas
      {   
         for(;i<width;)//colunas
         {
           for(k=0;k<8;k++)//bite
            {
               if(inverse)
               {//           0  ,0  ,
                 glcd_pixel(i+x,j+y,~bit_test(img[count],(k)));
               }
               else
               {
                  glcd_pixel(i+x,j+y,bit_test(img[count],(k)));
               }
               i++;
            }
            count++;
         }
      i=0;
      }
} 
///////////////////////////////////////////////////////////////////////////////////
#include <18F87K22.h>
#device ADC=16
#define  mode_4_bit //define glcd 4 bit mode
#use delay(CLOCK=64M, CRYSTAL=16M)

#include "imagem.h"
#include "st7920.h"
#include "graphics.c"
#include <math.h>
int16 adc;
float media_adc;
const unsigned char TAB[]={'T','E','S','T','E','-','O','K'};
void Voltage()
{     
   set_adc_channel(0);
   adc = read_adc();
   media_adc = ((adc*.07554945)/1000);
   char voltage[9];   
   sprintf(voltage, "%.2f", (float)media_adc); // Converts adc to text     
   //sprintf(voltage, "%Lu",(int16)read_adc());
   voltage[5] = '\0';                              // Limit shown digits to 5
   voltage[4] = 'V';
   glcd_rect(11, 0, 50, 8, yes, on);
   glcd_text57(12, 1, voltage, 1, off);//printf
 
 
}
void mode_basic()//glcd mode basic
{
    glcd_init_basic(); //init glcd basic
    glcd_instruction(clear_lcd);// clear glcd
   for(int i=0;i<8;i++)
   {
      glcd_data(TAB[i]);//printf glcd mode text
      delay_ms(100);
   }
   Delay_ms(500);
   glcd_instruction(clear_lcd);// clear glcd
}

void mode_graphic()
{
   glcd_init_graph();//glcd modo graphico
   glcd_fillScreen(OFF);//clear glcd
   for(int cont=0; cont<200; cont++)
   {
      glcd_plot_image(antena,11,9,0,0,1);//imagem, comprimento, altura, coluna, linha, cor
      glcd_plot_image(trator,11,9,0,18,0);//imagem, comprimento, altura, coluna, linha, cor
      glcd_plot_image(bico_on,11,9,64,0,0);//imagem, comprimento, altura, coluna, linha, cor
      glcd_plot_image(fluxometro,11,9,64,18,0);//imagem, comprimento, altura, coluna, linha, cor
      glcd_plot_image(barra,128,5,0,49,0);//imagem, comprimento, altura, coluna, linha, co
   
      glcd_plot_image(bico_off,11,9,0,54,1);//imagem, comprimento, altura, coluna, linha, cor
      glcd_plot_image(bico_on,11,9,59,54,0);//imagem, comprimento, altura, coluna, linha, cor
      glcd_plot_image(bico_on,11,9,115,54,0);//imagem, comprimento, altura, coluna, linha, cor
 
      voltage();//read ad chanel 0
      glcd_update();//update glcd
     // Delay_ms(5);
   }
}

void main ()
{
   setup_adc_ports(sAN0);
   setup_adc(ADC_CLOCK_DIV_32|ADC_TAD_MUL_4);
   set_adc_channel(0);
   glcd_init_graph();//glcd modo graphico
   glcd_fillScreen(off);// glcd clear full pixel 0
   glcd_update();// glcd update   
   glcd_plot_image(logo_inicio,128,64,0,0,0);//imagem,width,height,columm,line,color pixel   
   glcd_update();// glcd update
   Delay_ms(2000);//Delay
   glcd_fillScreen(OFF);//clear glcd
   
   while(1)
   {
      mode_basic();
      mode_graphic();
   }
}

//imagem 11x9 antena
ROM  char antena[]={
0x00, 0x00, 0xFC, 0x01, 0x02, 0x02, 0xF9, 0x04,
0x04, 0x01, 0x72, 0x02, 0x88, 0x00, 0x20, 0x00,
0x00, 0x00
};

//imagem 11x9 bateria
ROM  char bateria[]={
0x04, 0x00, 0x8E, 0x03, 0x04, 0x00, 0xFE, 0x03,
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
0xFE, 0x03};

//imagem 11x9 bico ligado
ROM  char bico_on[]={
0xF8, 0x00, 0xF8, 0x00, 0x70, 0x00, 0x20, 0x00,
0x50, 0x00, 0xA8, 0x00, 0x54, 0x01, 0xAA, 0x02,
0x55, 0x05};
//imagem 11x9 bico desligado
ROM  char bico_off[]={
0xF8, 0x00, 0xF8, 0x00, 0x70, 0x00, 0x20, 0x00,
0x88, 0x00, 0x50, 0x00, 0x20, 0x00, 0x50, 0x00,
0x88, 0x00};

//imagem 128x5 barra
ROM  char barra[]={
0x00, 0xFE, 0xBF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF,
0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFD, 0x7F, 0x00,
0x80, 0x11, 0xF1, 0x11, 0x11, 0x1F, 0x86, 0x61,
0x86, 0x61, 0xF8, 0x88, 0x88, 0x8F, 0x88, 0x01,
0x60, 0xAA, 0xAA, 0xAA, 0xAA, 0x2A, 0x49, 0x92,
0x49, 0x92, 0x54, 0x55, 0x55, 0x55, 0x55, 0x06,
0x18, 0x44, 0xE4, 0x44, 0x44, 0xCE, 0x30, 0x8C,
0x31, 0x0C, 0x73, 0x22, 0x22, 0x27, 0x22, 0x18,
0xFC, 0xFF, 0xBF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF,
0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFD, 0xFF, 0x3F};

//imagem 11x9 trator
ROM  char trator[]={
0x00, 0x00, 0x1E, 0x00, 0x92, 0x00, 0x92, 0x00,
0xFE, 0x03, 0xFB, 0x07, 0xF1, 0x03, 0x9B, 0x02,
0x8E, 0x03};

//imegem 11x9 fluxometro
ROM  char fluxometro[]={
0xF8, 0x00, 0x24, 0x01, 0xAA, 0x02, 0x72, 0x02,
0xDE, 0x03, 0x72, 0x02, 0xAA, 0x02, 0x24, 0x01,
0xF8, 0x00};

ROM  char logo_inicio[]={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0,
0x0F, 0x00, 0xFC, 0xFF, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
0x10, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF8,
0x3F, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x07,
0x40, 0x00, 0x1E, 0x80, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x00, 0x1E, 0x80, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0x40, 0x00, 0x1E, 0x80, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x00, 0x1E, 0x80, 0x83, 0x00, 0x00, 0x00,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x07,
0x40, 0x00, 0x1E, 0x80, 0x83, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x00, 0x1E, 0x80, 0x83, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0xC0, 0x00, 0x1E, 0x80, 0x83, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x01, 0x1E, 0x80, 0x83, 0x00, 0x00, 0x00,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x07,
0x40, 0x02, 0x1E, 0x80, 0x83, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x04, 0xFE, 0xFF, 0xFF, 0xFF, 0x07, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0x40, 0x08, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x10, 0xFE, 0xFF, 0x07, 0x80, 0x0F, 0x00,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x07,
0x40, 0x20, 0x1E, 0xFC, 0xFF, 0xFF, 0x0F, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0xC0, 0xFF, 0x07, 0xF0, 0xFF, 0xFF, 0x0F, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0x40, 0x20, 0x01, 0xC0, 0xFF, 0xFF, 0xFF, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x10, 0x01, 0xC0, 0xFF, 0xFF, 0xFF, 0x07,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x07,
0x40, 0x88, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x84, 0xC0, 0x81, 0xFF, 0xFF, 0x83, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0x40, 0x42, 0x20, 0x02, 0xFF, 0xFF, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04,
0x40, 0x41, 0x90, 0x04, 0xFF, 0xFF, 0x38, 0x02,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x07,
0xC0, 0x40, 0x50, 0x05, 0xFF, 0x7F, 0x44, 0x04,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC4,
0x43, 0x40, 0x90, 0x04, 0x01, 0x40, 0x82, 0x04,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
0x44, 0x40, 0x20, 0x02, 0x01, 0x40, 0x92, 0x04,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x14,
0x48, 0x80, 0xC0, 0x81, 0x00, 0x40, 0x82, 0x04,
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xC5, 0x8F,
0x51, 0x00, 0x01, 0x40, 0x00, 0x40, 0x44, 0x04,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x4C,
0x32, 0x00, 0x01, 0x40, 0x00, 0x80, 0x38, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48,
0x12, 0x00, 0x06, 0x30, 0x00, 0x00, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88,
0x11, 0x00, 0x18, 0x0C, 0x00, 0x00, 0x82, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
0x08, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x7C, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
/////////////////////////////////////////////////////////////////////////
////                          graphics.c                             ////
////                                                                 ////
////   This file contains functions to draw lines, rectangles, bars, ////
////   circles and text to a display. A function which draws a       ////
////   single pixel must be defined before calling the functions in  ////
////   this file. Call it glcd_pixel(x, y, color) where x is the     ////
////   horizontal coordinate, y is the vertical coordinate, and      ////
////   color is 1 bit to turn the pixel on or off.                   ////
////                                                                 ////
////   * Note: (0, 0) is treated as the upper left corner            ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////  glcd_line(x1, y1, x2, y2, color)                               ////
////     * Draws a line from the first point to the second point     ////
////       with the given color                                      ////
////       - color can be ON or OFF                                  ////
////                                                                 ////
////  glcd_rect(x1, y1, x2, y2, fill, color)                         ////
////     * Draws a rectangle with one corner at point (x1,y1) and    ////
////       the other corner at point (x2,y2)                         ////
////       - fill can be YES or NO                                   ////
////       - color can be ON or OFF                                  ////
////                                                                 ////
////  glcd_bar(x1, y1, x2, y2, width, color)                         ////
////     * Draws a bar (wide line) from the first point to the       ////
////       second point                                              ////
////       - width is the number of pixels wide                      ////
////       - color is ON or OFF                                      ////
////                                                                 ////
////  glcd_circle(x, y, radius, fill, color)                         ////
////     * Draws a circle with center at (x,y)                       ////
////       - fill can be YES or NO                                   ////
////       - color can be ON or OFF                                  ////
////                                                                 ////
////  glcd_text57(x, y, textptr, size, color)                        ////
////     * Write the null terminated text pointed to by textptr with ////
////       the upper left coordinate of the first character at (x,y) ////
////       Characters are 5 pixels wide and 7 pixels tall            ////
////       - size is an integer that scales the size of the text     ////
////       - color is ON or OFF                                      ////
////     * Note - This function wraps characters to the next line    ////
////              use #define GLCD_WIDTH to specify a display width  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996, 2010 Custom Computer Services        ////
//// This source code may only be used by licensed users of the CCS  ////
//// C compiler.  This source code may only be distributed to other  ////
//// licensed users of the CCS C compiler.  No other use,            ////
//// reproduction or distribution is permitted without written       ////
//// permission.  Derivative programs created using this software    ////
//// in object code form are not restricted in any way.              ////
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
#ifndef GRAPHICS_DRAWING_FUNCTIONS
#define GRAPHICS_DRAWING_FUNCTIONS
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
#ifndef ON
#define ON  1
#endif

#ifndef OFF
#define OFF 0
#endif

#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO  0
#endif
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
//// Defines a 5x7 font
/////////////////////////////////////////////////////////////////////////
const unsigned int8 FONT[51][5] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
                         0x00, 0x00, 0x5F, 0x00, 0x00, // !
                         0x00, 0x03, 0x00, 0x03, 0x00, // "
                         0x14, 0x3E, 0x14, 0x3E, 0x14, // #
                         0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
                         0x43, 0x33, 0x08, 0x66, 0x61, // %
                         0x36, 0x49, 0x55, 0x22, 0x50, // &
                         0x00, 0x05, 0x03, 0x00, 0x00, // '
                         0x00, 0x1C, 0x22, 0x41, 0x00, // (
                         0x00, 0x41, 0x22, 0x1C, 0x00, // )
                         0x14, 0x08, 0x3E, 0x08, 0x14, // *
                         0x08, 0x08, 0x3E, 0x08, 0x08, // +
                         0x00, 0x50, 0x30, 0x00, 0x00, // ,
                         0x08, 0x08, 0x08, 0x08, 0x08, // -
                         0x00, 0x60, 0x60, 0x00, 0x00, // .
                         0x20, 0x10, 0x08, 0x04, 0x02, // /
                         0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
                         0x00, 0x04, 0x02, 0x7F, 0x00, // 1
                         0x42, 0x61, 0x51, 0x49, 0x46, // 2
                         0x22, 0x41, 0x49, 0x49, 0x36, // 3
                         0x18, 0x14, 0x12, 0x7F, 0x10, // 4
                         0x27, 0x45, 0x45, 0x45, 0x39, // 5
                         0x3E, 0x49, 0x49, 0x49, 0x32, // 6
                         0x01, 0x01, 0x71, 0x09, 0x07, // 7
                         0x36, 0x49, 0x49, 0x49, 0x36, // 8
                         0x26, 0x49, 0x49, 0x49, 0x3E, // 9
                         0x00, 0x36, 0x36, 0x00, 0x00, // :
                         0x00, 0x56, 0x36, 0x00, 0x00, // ;
                         0x08, 0x14, 0x22, 0x41, 0x00, // <
                         0x14, 0x14, 0x14, 0x14, 0x14, // =
                         0x00, 0x41, 0x22, 0x14, 0x08, // >
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                         0x7E, 0x09, 0x09, 0x09, 0x7E, // A
                         0x7F, 0x49, 0x49, 0x49, 0x36, // B
                         0x3E, 0x41, 0x41, 0x41, 0x22, // C
                         0x7F, 0x41, 0x41, 0x41, 0x3E, // D
                         0x7F, 0x49, 0x49, 0x49, 0x41, // E
                         0x7F, 0x09, 0x09, 0x09, 0x01, // F
                         0x3E, 0x41, 0x41, 0x49, 0x3A, // G
                         0x7F, 0x08, 0x08, 0x08, 0x7F, // H
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I
                         0x30, 0x40, 0x40, 0x40, 0x3F, // J
                         0x7F, 0x08, 0x14, 0x22, 0x41, // K
                         0x7F, 0x40, 0x40, 0x40, 0x40, // L
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                         0x3E, 0x41, 0x41, 0x41, 0x3E, // O
                         0x7F, 0x09, 0x09, 0x09, 0x06, // P
                         0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
                         0x7F, 0x09, 0x09, 0x09, 0x76};// R

const unsigned int8 FONT2[44][5]={0x26, 0x49, 0x49, 0x49, 0x32, // S
                         0x01, 0x01, 0x7F, 0x01, 0x01, // T
                         0x3F, 0x40, 0x40, 0x40, 0x3F, // U
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y
                         0x61, 0x51, 0x49, 0x45, 0x43, // Z
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [
                         0x02, 0x04, 0x08, 0x10, 0x20, // \
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                         0x04, 0x02, 0x01, 0x02, 0x04, // ^
                         0x40, 0x40, 0x40, 0x40, 0x40, // _
                         0x00, 0x01, 0x02, 0x04, 0x00, // `
                         0x20, 0x54, 0x54, 0x54, 0x78, // a
                         0x7F, 0x44, 0x44, 0x44, 0x38, // b
                         0x38, 0x44, 0x44, 0x44, 0x44, // c
                         0x38, 0x44, 0x44, 0x44, 0x7F, // d
                         0x38, 0x54, 0x54, 0x54, 0x18, // e
                         0x04, 0x04, 0x7E, 0x05, 0x05, // f
                         0x08, 0x54, 0x54, 0x54, 0x3C, // g
                         0x7F, 0x08, 0x04, 0x04, 0x78, // h
                         0x00, 0x44, 0x7D, 0x40, 0x00, // i
                         0x20, 0x40, 0x44, 0x3D, 0x00, // j
                         0x7F, 0x10, 0x28, 0x44, 0x00, // k
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m
                         0x7C, 0x08, 0x04, 0x04, 0x78, // n
                         0x38, 0x44, 0x44, 0x44, 0x38, // o
                         0x7C, 0x14, 0x14, 0x14, 0x08, // p
                         0x08, 0x14, 0x14, 0x14, 0x7C, // q
                         0x00, 0x7C, 0x08, 0x04, 0x04, // r
                         0x48, 0x54, 0x54, 0x54, 0x20, // s
                         0x04, 0x04, 0x3F, 0x44, 0x44, // t
                         0x3C, 0x40, 0x40, 0x20, 0x7C, // u
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                         0x44, 0x28, 0x10, 0x28, 0x44, // x
                         0x0C, 0x50, 0x50, 0x50, 0x3C, // y
                         0x44, 0x64, 0x54, 0x4C, 0x44, // z
                         0x00, 0x08, 0x36, 0x41, 0x41, // {
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |
                         0x41, 0x41, 0x36, 0x08, 0x00, // }
                         0x02, 0x01, 0x02, 0x04, 0x02};// ~
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a line on a graphic LCD using Bresenham's
//                line drawing algorithm
// Inputs:        (x1, y1) - the start coordinate
//                (x2, y2) - the end coordinate
//                color - ON or OFF
// Dependencies:  glcd_pixel()
/////////////////////////////////////////////////////////////////////////
#ifdef LARGE_LCD
void glcd_line(unsigned int16 x1, unsigned int16 y1, unsigned int16 x2, unsigned int16 y2, int1 color)
#else
void glcd_line(unsigned int8 x1, unsigned int8 y1, unsigned int8 x2, unsigned int8 y2, int1 color)
#endif
{
   unsigned int16        dy, dx;
   signed int8  addx=1, addy=1;
   signed int16 P, diff;

   #ifdef LARGE_LCD
   unsigned int16 i=0;
   dx = abs((signed int16)(x2 - x1));
   dy = abs((signed int16)(y2 - y1));
   #else
   unsigned int8 i=0;
   dx = abs((signed int8)(x2 - x1));
   dy = abs((signed int8)(y2 - y1));
   #endif

   if(x1 > x2)
      addx = -1;
   if(y1 > y2)
      addy = -1;

   if(dx >= dy)
   {
      dy *= 2;
      P = dy - dx;
      diff = P - dx;

      for(; i<=dx; ++i)
      {
         glcd_pixel(x1, y1, color);

         if(P < 0)
         {
            P  += dy;
            x1 += addx;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
   else
   {
      dx *= 2;
      P = dx - dy;
      diff = P - dy;

      for(; i<=dy; ++i)
      {
         glcd_pixel(x1, y1, color);

         if(P < 0)
         {
            P  += dx;
            y1 += addy;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
}


/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a rectangle on a graphic LCD
// Inputs:        (x1, y1) - the start coordinate
//                (x2, y2) - the end coordinate
//                fill  - YES or NO
//                color - ON or OFF
// Dependencies:  glcd_pixel(), glcd_line()
/////////////////////////////////////////////////////////////////////////
#ifdef LARGE_LCD
void glcd_rect(unsigned int16 x1, unsigned int16 y1, unsigned int16 x2, unsigned int16 y2, int1 fill, int1 color)
#else
void glcd_rect(unsigned int8 x1, unsigned int8 y1, unsigned int8 x2, unsigned int8 y2, int1 fill, int1 color)
#endif
{
   if(fill)
   {
      #ifdef LARGE_LCD
      unsigned int16 i, xmin, xmax, ymin, ymax;
      #else
      unsigned int8  i, xmin, xmax, ymin, ymax;
      #endif

      if(x1 < x2)                            //  Find x min and max
      {
         xmin = x1;
         xmax = x2;
      }
      else
      {
         xmin = x2;
         xmax = x1;
      }

      if(y1 < y2)                            // Find the y min and max
      {
         ymin = y1;
         ymax = y2;
      }
      else
      {
         ymin = y2;
         ymax = y1;
      }

      for(; xmin <= xmax; ++xmin)
      {
         for(i=ymin; i<=ymax; ++i)
         {
            glcd_pixel(xmin, i, color);
         }
      }
   }
   else
   {
      glcd_line(x1, y1, x2, y1, color);      // Draw the 4 sides
      glcd_line(x1, y2, x2, y2, color);
      glcd_line(x1, y1, x1, y2, color);
      glcd_line(x2, y1, x2, y2, color);
   }
}

/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a bar (wide line) on a graphic LCD
// Inputs:        (x1, y1) - the start coordinate
//                (x2, y2) - the end coordinate
//                width  - The number of pixels wide
//                color - ON or OFF
/////////////////////////////////////////////////////////////////////////
#ifdef LARGE_LCD
void glcd_bar(unsigned int16 x1, unsigned int16 y1, unsigned int16 x2, unsigned int16 y2, unsigned int8 width, int1 color)
#else
void glcd_bar(unsigned int8 x1, unsigned int8 y1, unsigned int8 x2, unsigned int8 y2, unsigned int8 width, int1 color)
#endif
{
   unsigned int8         half_width;
   signed int16 dy, dx;
   signed int8  addx=1, addy=1, j;
   signed int16 P, diff, c1, c2;

   #ifdef LARGE_LCD
   unsigned int16 i=0;
   dx = abs((signed int16)(x2 - x1));
   dy = abs((signed int16)(y2 - y1));
   #else
   unsigned int8 i=0;
   dx = abs((signed int8)(x2 - x1));
   dy = abs((signed int8)(y2 - y1));
   #endif

   half_width = width/2;
   c1 = -(dx*x1 + dy*y1);
   c2 = -(dx*x2 + dy*y2);

   if(x1 > x2)
   {
      signed int16 temp;
      temp = c1;
      c1 = c2;
      c2 = temp;
      addx = -1;
   }
   if(y1 > y2)
   {
      signed int16 temp;
      temp = c1;
      c1 = c2;
      c2 = temp;
      addy = -1;
   }

   if(dx >= dy)
   {
      P = 2*dy - dx;
      diff = P - dx;

      for(i=0; i<=dx; ++i)
      {
         for(j=-half_width; j<half_width+width%2; ++j)
         {
               glcd_pixel(x1, y1+j, color);
         }
         if(P < 0)
         {
            P  += 2*dy;
            x1 += addx;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
   else
   {
      P = 2*dx - dy;
      diff = P - dy;

      for(i=0; i<=dy; ++i)
      {
         if(P < 0)
         {
            P  += 2*dx;
            y1 += addy;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
         for(j=-half_width; j<half_width+width%2; ++j)
         {
               glcd_pixel(x1+j, y1, color);
         }
      }
   }
}


/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a circle on a graphic LCD
// Inputs:        (x,y) - the center of the circle
//                radius - the radius of the circle
//                fill - YES or NO
//                color - ON or OFF
/////////////////////////////////////////////////////////////////////////
#ifdef LARGE_LCD
void glcd_circle(unsigned int16 x, unsigned int16 y, unsigned int16 radius, int1 fill, int1 color)
#else
void glcd_circle(unsigned int8 x, unsigned int8 y, unsigned int8 radius, int1 fill, int1 color)
#endif
{
   #ifdef LARGE_LCD
   signed int16 a, b, P;
   #else
   signed int8  a, b, P;
   #endif

   a = 0;
   b = radius;
   P = 1 - radius;

   do
   {
      if(fill)
      {
         glcd_line(x-a, y+b, x+a, y+b, color);
         glcd_line(x-a, y-b, x+a, y-b, color);
         glcd_line(x-b, y+a, x+b, y+a, color);
         glcd_line(x-b, y-a, x+b, y-a, color);
      }
      else
      {
         glcd_pixel(a+x, b+y, color);
         glcd_pixel(b+x, a+y, color);
         glcd_pixel(x-a, b+y, color);
         glcd_pixel(x-b, a+y, color);
         glcd_pixel(b+x, y-a, color);
         glcd_pixel(a+x, y-b, color);
         glcd_pixel(x-a, y-b, color);
         glcd_pixel(x-b, y-a, color);
      }

      if(P < 0)
         P += 3 + 2 * a++;
      else
         P += 5 + 2 * (a++ - b--);
    } while(a <= b);
}


/////////////////////////////////////////////////////////////////////////
// Purpose:       Write text on a graphic LCD
// Inputs:        (x,y) - The upper left coordinate of the first letter
//                textptr - A pointer to an array of text to display
//                size - The size of the text: 1 = 5x7, 2 = 10x14, ...
//                color - ON or OFF
/////////////////////////////////////////////////////////////////////////
#ifdef LARGE_LCD
void glcd_text57(unsigned int16 x, unsigned int16 y, char* textptr, unsigned int8 size, int1 color)
#else
void glcd_text57(unsigned int8 x, unsigned int8 y, char* textptr, unsigned int8 size, int1 color)
#endif
{
   unsigned int8 j, k, l, m;                       // Loop counters
   unsigned int1 inv=~color;
   unsigned int8 pixelData[5];                     // Stores character data
   //if(color==1)inv=0;
   //else inv=1;
   for(; *textptr != '\0'; ++textptr, ++x)// Loop through the passed string
   {
      if(*textptr < 'S') // Checks if the letter is in the first font array
         memcpy(pixelData, FONT[*textptr - ' '], 5);
      else if(*textptr <= '~') // Check if the letter is in the second font array
         memcpy(pixelData, FONT2[*textptr - 'S'], 5);
      else
         memcpy(pixelData, FONT[0], 5);   // Default to space

      // Handles newline and carriage returns
      switch(*textptr)
      {
         case '\n':
            y += 7*size + 1;
            continue;
         case '\r':
            x = 0;
            continue;
      }

      if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
      {
         x = 0;                           // Set x at far left position
         y += 7*size + 1;                 // Set y at next position down
      }
      for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
      {
         for(k=0; k < 7; ++k)             // Loop through the vertical pixels
         {
            if(bit_test(pixelData[j], k)) // Check if the pixel should be set
            {
               for(l=0; l < size; ++l)    // These two loops change the
               {                          // character's size
                  for(m=0; m < size; ++m)
                  {
                     glcd_pixel(x+m, y+k*size+l, color); // Draws the pixel
                  }
               }
            }
            else
            {
               for(l=0; l < size; ++l)    // These two loops change the
               {                          // character's size
                  for(m=0; m < size; ++m)
                  {
                     glcd_pixel(x+m, y+k*size+l, inv); // Draws the pixel
                  }
               }                       
            }
         }
      }
   }
}

#endif