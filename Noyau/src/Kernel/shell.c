/*
 * shell.c
 *
 * Created: 06/02/2018 17:19:43
 *  Author: eleve
 */ 

 #include "./Headers/appli.h"

 char shellBuf[SHELL_EDIT_BUFFER_LEN];
 char shellEscSeq[SHELL_ESCSEQ_BUFFER_LEN];

 struct{
	uint32_t	nStatus;
	char*		pEdit;
	uint32_t	nbChar;
	uint16_t	crc;
 }shell;


 //////Nicely shortcuts........ ///////////////////
#define nStatus		shell.nStatus
#define pEdit		shell.pEdit
#define nbChar		shell.nbChar
#define crc			shell.crc 


/////Shell Private services codes ////////////////////
enum{
	_SHELL_KBHIT = 1,
};

 uint32_t Shell(uint32_t sc, ...)
 {
	switch(sc)
	{
	case SHELL_NEW:
		Shellcom(SHELLCOM_NEW);
		break;



	case _SHELL_KBHIT:
#define _kbhitChar ((char)pa1)
		Putc(_kbhitChar);
#undef _kbhitChar
		break;
		
	default:
		Error(ERR_SHELL_SWITCH_BAD_SC,sc);
	}

	return 0;
 }
