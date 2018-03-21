 //Acc�s aux contenus des param�tres optionnels des fonctions
 #define pa1         (*(uint32_t*)(&sc+1))
 #define pa2         (*(uint32_t*)(&sc+2))
 #define pa3         (*(uint32_t*)(&sc+3))
 #define pa4         (*(uint32_t*)(&sc+4))
 #define pa5         (*(uint32_t*)(&sc+5))

 //Acc�s aux adresses des param�tres optionnels des fonctions
 #define pPa1         ((uint32_t*)(&sc+1))
 #define pPa2         ((uint32_t*)(&sc+2))
 #define pPa3         ((uint32_t*)(&sc+3))
 #define pPa4         ((uint32_t*)(&sc+4))
 #define pPa5         ((uint32_t*)(&sc+5))

 #define mBitsSet(flags,mask)     (flags|=(mask))
 #define mBitsClr(flags,mask)     (flags&=~(mask))
 #define mBitsTgl(flags,mask)     (flags^=(mask))
 #define mBitsMsk(flags,mask)     (flags&(mask))
 #define mIsBitsSet(flags,mask)   (( (flags&(mask)))==(mask))
 #define mIsBitsClr(flags,mask)   (((~flags)&(mask))==(mask))

 #define BOARD_FREQ_SLCK_XTAL      (32768UL)
 #define BOARD_FREQ_MAINCK_XTAL    (12000000UL)
 #define BOARD_FREQ_MAINCK_BYPASS  (12000000UL)
 #define BOARD_OSC_STARTUP_US      (15625UL)
 #define BOARD_FREQ_SLCK_BYPASS    (32768UL)

#include <asf.h>
#include <stdint.h>
#include "./Kernel/kernel.h"
#include "sas.h"
#include "menu.h"


extern char buf[];

 uint32_t Appli(uint32_t sc, ...);

 #define APPLI_NEW				100
 #define APPLI_TEST				102


#define BLUETOOTH_PWR					(PIO_PB21_IDX)
#define BLUETOOTH_FLAGS					(PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define BLUETOOTH_ACTIVE_LEVEL			0
#define BLUETOOTH_NAME					"Bluetooth module power"

//#define BUZZER_PWR					(PIO_PB22_IDX)		//To switch to PB16 ARGHHHHH!!!!! PWMH3 PERIPHERAL B
#define BUZZER_PWR						(PIO_PB16_IDX)
//#define BUZZER_PWR						(PIO_PB16B_PWMH3)
#define BUZZER_FLAGS					(PIO_TYPE_PIO_PERIPH_B | PIO_DEFAULT)
//#define BUZZER_FLAGS					(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

#define BUZZER_ACTIVE_LEVEL				1
#define BUZZER_NAME						"Buzzer module power"

#define CMD_MOSFET						(PIO_PB0_IDX)
#define CMD_MOSFET_FLAGS				(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define CMD_MOSFET_ACTIVE_LEVEL			1
#define CMD_MOSFET_NAME					"CMD MOSFET"

#define CMD_MOT_SERRURE					(PIO_PB1_IDX)
#define CMD_MOT_SERRURE_FLAGS			(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define CMD_MOT_SERRURE_ACTIVE_LEVEL	1
#define CMD_MOT_SERRURE_NAME			"CMD MOT SERRURE"

#define CMD_RELAIS						(PIO_PB2_IDX)
#define CMD_RELAIS_FLAGS				(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define CMD_RELAIS_ACTIVE_LEVEL			1
#define CMD_RELAIS_NAME					"CMD RELAIS"

#define CMD_RELAIS_1					(PIO_PB3_IDX)
#define CMD_RELAIS_1_FLAGS				(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define CMD_RELAIS_1_ACTIVE_LEVEL		1
#define CMD_RELAIS_1_NAME				"CMD RELAIS 1"

#define CMD_RELAIS_2					(PIO_PB4_IDX)
#define CMD_RELAIS_2_FLAGS				(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define CMD_RELAIS_2_ACTIVE_LEVEL		1
#define CMD_RELAIS_2_NAME				"CMD RELAIS 2"




#define PENE_OUVERT						(PIO_PA14_IDX)
#define PENE_OUVERT_FLAGS				(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define PENE_OUVERT_ACTIVE_LEVEL		0
#define PENE_OUVERT_NAME				"PENE OUVERT"

#define PENE_FERME						(PIO_PA15_IDX)
#define PENE_FERME_FLAGS				(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define PENE_FERME_ACTIVE_LEVEL			0
#define PENE_FERME_NAME					"PENE FERME"

#define IN_ILS							(PIO_PA16_IDX)
#define IN_ILS_FLAGS					(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_ILS_ACTIVE_LEVEL				0
#define IN_ILS_NAME						"ILS"

#define IN_SV							(PIO_PA17_IDX)
#define IN_SV_FLAGS						(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_SV_ACTIVE_LEVEL				0
#define IN_SV_NAME						"SV"

#define IN_RADAR						(PIO_PA24_IDX)
#define IN_RADAR_FLAGS					(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_RADAR_ACTIVE_LEVEL			0
#define IN_RADAR_NAME					"RADAR"

#define IN_DVU							(PIO_PA25_IDX)
#define IN_DVU_FLAGS					(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_DVU_ACTIVE_LEVEL				0
#define IN_DVU_NAME						"DVU"

#define IN_PREMIERE_ENTREE				(PIO_PA26_IDX)
#define IN_PREMIERE_ENTREE_FLAGS		(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_PREMIERE_ENTREE_ACTIVE_LEVEL	0
#define IN_PREMIERE_ENTREE_NAME			"PREMIERE ENTREE"

#define IN_DVU_GENERAL					(PIO_PA27_IDX)
#define IN_DVU_GENERAL_FLAGS			(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_DVU_GENERAL_ACTIVE_LEVEL		0
#define IN_DVU_GENERAL_NAME				"DVU GENERAL"

#define IN_ENTREE_LIBRE					(PIO_PA28_IDX)
#define IN_ENTREE_LIBRE_FLAGS			(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_ENTREE_LIBRE_ACTIVE_LEVEL	0
#define IN_ENTREE_LIBRE_NAME			"ENTREE LIBRE"

#define IN_ENTREE_OPTION				(PIO_PA29_IDX)
#define IN_ENTREE_OPTION_FLAGS			(PIO_TYPE_PIO_INPUT | PIO_PULLUP)
#define IN_ENTREE_OPTION_ACTIVE_LEVEL	0
#define IN_ENTREE_OPTION_NAME			"ENTREE OPTION"






