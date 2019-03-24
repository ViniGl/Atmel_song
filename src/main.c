/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED_PIO           PIOC
#define LED_PIO_ID        ID_PIOC
#define LED_PIO_IDX       8u
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)

#define BUT_PIO   PIOA
#define BUT_PIO_ID	ID_PIOA
#define BUT_PIO_IDX	11u
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

#define BUZZ_PIO PIOB
#define BUZZ_PIO_ID ID_PIOB
#define BUZZ_IDX 2u
#define BUZZ_MASK (1u<< BUZZ_IDX)

#define BUT1_PLACA_PIO PIOA
#define BUT1_PLACA_PIO_ID ID_PIOA
#define BUT1_PLACA_IDX 2u
#define BUT1_PLACA_MASK (1u<< BUT1_PLACA_IDX)

#define BUT2_PLACA_PIO PIOD
#define BUT2_PLACA_PIO_ID ID_PIOD
#define BUT2_PLACA_IDX 30u
#define BUT2_PLACA_MASK (1u<< BUT2_PLACA_IDX)

#define BUT3_PLACA_PIO PIOC
#define BUT3_PLACA_PIO_ID ID_PIOC
#define BUT3_PLACA_IDX 13u
#define BUT3_PLACA_MASK (1u<< BUT3_PLACA_IDX)


#define LED1_PLACA_PIO PIOC
#define LED1_PLACA_PIO_ID ID_PIOC
#define LED1_PLACA_IDX 19u
#define LED1_PLACA_MASK (1u<< LED1_PLACA_IDX)

#define LED2_PLACA_PIO PIOD
#define LED2_PLACA_PIO_ID ID_PIOD
#define LED2_PLACA_IDX 26u
#define LED2_PLACA_MASK (1u<< LED2_PLACA_IDX)

#define LED3_PLACA_PIO PIOD
#define LED3_PLACA_PIO_ID ID_PIOD
#define LED3_PLACA_IDX 11u
#define LED3_PLACA_MASK (1u<< LED3_PLACA_IDX)

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


//https://www.princetronics.com/supermariothemesong/
int melody[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};

int tempo[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

//int teste[] = {NOTE_D6, NOTE_C5, NOTE_B5, NOTE_A5};


//Inicio do tema mortal kombat
int mk[] = {NOTE_A4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_D5, NOTE_A4, NOTE_E5, NOTE_D5, 
				NOTE_C4, NOTE_C4, NOTE_E5, NOTE_C4, NOTE_G5,NOTE_C4,NOTE_E5,NOTE_C4, 
				NOTE_F4, NOTE_F4, NOTE_AS5, NOTE_F4, NOTE_C5,NOTE_F4, NOTE_D5};

//http://arduinorocks.blogspot.com/2013/08/arduino-buzzer-fear-of-dark.html
//Fear of the dark, iron maiden
int tune[] = { NOTE_D5, NOTE_D5, NOTE_A4, NOTE_A4, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5,
               NOTE_C5, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_E5, NOTE_C5,
               NOTE_D5, NOTE_D5, NOTE_A4, NOTE_A4, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5,
               NOTE_C5, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_E5, NOTE_C5,
               /*NOTE_A4, NOTE_A4, NOTE_E3, NOTE_E3, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_B4, NOTE_C4, NOTE_C4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4,//PARTE 2
               NOTE_G4, NOTE_G4, NOTE_D3, NOTE_D3, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_G4,
               NOTE_A4, NOTE_A4, NOTE_E3, NOTE_E3, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_B4, NOTE_C4, NOTE_C4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4,
               NOTE_F4, NOTE_F4, NOTE_C3, NOTE_C3, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_A4, NOTE_F4, NOTE_G4*/};
               
             /*  { NOTE_D4, NOTE_D4, NOTE_A3, NOTE_A3, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4,
               NOTE_C4, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_C4,
               NOTE_D4, NOTE_D4, NOTE_A3, NOTE_A3, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4,
               NOTE_C4, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_C4,
               NOTE_A3, NOTE_A3, NOTE_E2, NOTE_E2, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_B3, NOTE_C3, NOTE_C3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3,//PARTE 2
               NOTE_G3, NOTE_G3, NOTE_D2, NOTE_D2, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_B3, NOTE_G3,
               NOTE_A3, NOTE_A3, NOTE_E2, NOTE_E2, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_B3, NOTE_C3, NOTE_C3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_B3, NOTE_A3,
               NOTE_F3, NOTE_F3, NOTE_C2, NOTE_C2, NOTE_F3, NOTE_F3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_F3, NOTE_A3, NOTE_F3, NOTE_G3};*/
			   
/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void)
{
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(BUT_PIO_ID);
	
	pmc_enable_periph_clk(BUT1_PLACA_PIO_ID);
	pmc_enable_periph_clk(BUT2_PLACA_PIO_ID);
	pmc_enable_periph_clk(BUT3_PLACA_PIO_ID);
	
	pmc_enable_periph_clk(LED1_PLACA_PIO_ID);
	pmc_enable_periph_clk(LED2_PLACA_PIO_ID);
	pmc_enable_periph_clk(LED3_PLACA_PIO_ID);
	
	pmc_enable_periph_clk(BUZZ_PIO_ID);


	pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_DEFAULT);
	pio_pull_up(BUT_PIO_ID,BUT_PIO_IDX_MASK,1);
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	
	pio_set_input(BUT1_PLACA_PIO, BUT1_PLACA_MASK, PIO_DEFAULT | PIO_PULLUP);
	pio_set_input(BUT2_PLACA_PIO, BUT2_PLACA_MASK, PIO_DEFAULT | PIO_PULLUP);
	pio_set_input(BUT3_PLACA_PIO, BUT3_PLACA_MASK, PIO_DEFAULT | PIO_PULLUP);
	
// 	pio_pull_up(BUT1_PLACA_PIO_ID,BUT1_PLACA_MASK,1);
	
	pio_set_output(LED1_PLACA_PIO, LED1_PLACA_MASK, 0, 0, 0);
	pio_set_output(LED2_PLACA_PIO, LED2_PLACA_MASK, 0, 0, 0);
	pio_set_output(LED3_PLACA_PIO, LED3_PLACA_MASK, 0, 0, 0);

	
	//pio_set_output(BUT1_PLACA_PIO, BUT1_PLACA_MASK, 0,0,0);
	pio_set_output(BUZZ_PIO, BUZZ_MASK, 0, 0, 0);


}

void play_music(int music[],int n, int duration, int octave){
	for(int s = 0; s < n ; s++){
		int f = pio_get(BUT_PIO,PIO_INPUT, BUT_PIO_IDX_MASK);
		if (!f){
			break;
			
		}
		delay_ms(duration);
		pio_set(LED_PIO,LED_PIO_IDX_MASK);
		for(int i = 0; i < duration; i++){
			pio_set(PIOB,BUZZ_MASK);
			delay_us(((1000000/(music[s]*octave))/2));
			pio_clear(PIOB,BUZZ_MASK);
			delay_us(((1000000/(music[s]*octave))/2));
		}
		pio_clear(LED_PIO,LED_PIO_IDX_MASK);
	}
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  int f,but1,but2,but3,led1,led2,led3, playing;
  
  int flag1 , flag2 , flag3;
  flag1 = 0;
  flag2 = 0;
  flag3 = 0;
  playing = 0;
  
  pio_set_debounce_filter(BUT_PIO, BUT_PIO_IDX_MASK, 1);

  while(1){
  f = pio_get(BUT_PIO,PIO_INPUT, BUT_PIO_IDX_MASK);
  
  
  but1 = !pio_get(BUT1_PLACA_PIO,PIO_INPUT, BUT1_PLACA_MASK);
  but2 = !pio_get(BUT2_PLACA_PIO,PIO_INPUT, BUT2_PLACA_MASK);
  but3 = !pio_get(BUT3_PLACA_PIO,PIO_INPUT, BUT3_PLACA_MASK);
  
  led1 = pio_get(LED1_PLACA_PIO,PIO_INPUT, LED1_PLACA_MASK);
  led2 = pio_get(LED2_PLACA_PIO,PIO_INPUT, LED2_PLACA_MASK);
  led3 = pio_get(LED3_PLACA_PIO,PIO_INPUT, LED3_PLACA_MASK);
  
  
  if(but1){
  	  
	flag1 = 1;
	flag2 = 0;
	flag3 = 0;
  	  
   } 
	if(but2) {
	flag1 = 0;
  	flag2 = 1;
	flag3 = 0;

    } 
	if (but3){
		flag1 = 0;
		flag2 = 0;
  		flag3 = 1;
    }
    
	
	if (flag1){
		pio_clear(LED1_PLACA_PIO, LED1_PLACA_MASK);
		pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);
		pio_set(LED3_PLACA_PIO,LED3_PLACA_MASK);

		
	} else if (flag2){
		pio_clear(LED2_PLACA_PIO, LED2_PLACA_MASK);
		pio_set(LED1_PLACA_PIO,LED1_PLACA_MASK);
		pio_set(LED3_PLACA_PIO,LED3_PLACA_MASK);

	} else if (flag3){
		pio_clear(LED3_PLACA_PIO, LED3_PLACA_MASK);
		pio_set(LED1_PLACA_PIO,LED1_PLACA_MASK);
		pio_set(LED2_PLACA_PIO,LED2_PLACA_MASK);

	}
	
    
  if (!f)
  {
	  if (flag1){
		  play_music(tune, sizeof(tune)/sizeof(int), 75,1);
	  }
	  else if (flag2){
		  play_music(mk, sizeof(mk)/sizeof(int), 130,3);
	  }
	
	}

  }
  return 0;
}
