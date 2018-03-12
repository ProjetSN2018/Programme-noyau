/*
 * shellcmd.h
 *
 * Created: 07/02/2018 17:28:59
 *  Author: Mod_loc
 */ 
 #define TEST_ADDRESS_INT (IFLASH_ADDR + IFLASH_SIZE- IFLASH_PAGE_SIZE*8)

typedef struct tt_cmdEntry {
	uint16_t	cmdCode;
	t_ptf		pCmdFunc;
}t_cmdEntry;

extern const t_cmdEntry _cmdEntries[];


void _cmd_set(uint32_t sc, void* pParam);

void _cmd_show(uint32_t sc, void* pParam);

void _cmd_menu(uint32_t sc, void* pParam);