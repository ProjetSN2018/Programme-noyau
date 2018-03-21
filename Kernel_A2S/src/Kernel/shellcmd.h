typedef struct tt_cmdEntry {
	uint16_t	cmdCode;
	t_ptf		pCmdFunc;
}t_cmdEntry;

extern const t_cmdEntry _cmdEntries[];

void _cmd_menu(uint32_t sc, void* pParam);

void _cmd_start(uint32_t sc, void*pParam);

void _cmd_set(uint32_t sc, void*pParam);

void _cmd_cls(uint32_t sc, void*pParam);

void _cmd_show(uint32_t sc, void*pParam);

void _cmd_hide(uint32_t sc, void*pParam);

void _cmd_restart(uint32_t sc, void*pParam);

void _cmd_infos(uint32_t sc, void*pParam);