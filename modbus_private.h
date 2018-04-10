/*
 * modbus_private.h
 *
 * Created: 24/03/2018 14:27:02
 *  Author: Thierry
 */

////////////MOBDUS PRIVATE MODULE DEFINITIONS //////////////////////////////////////////////////////

enum {
	WRITE_MULTIPLE_REGISTERS	= 0x10,
	READ_HOLDING_REGISTERS		= 0x03
};

struct{
	union{
		uint32_t reg;
		struct{
			uint8_t		status;
			uint16_t	timer;
			unsigned	tries:4;
			unsigned	:4;
		};
	};
	uint16_t	crc;
	uint8_t		moduleAddr;
	uint16_t	startAddr;
	uint16_t	regQty;
}modbus;

#define	ST_MODULE_IS_MASTER		0x01
#define IsMaster()		mIsBitsSet(modbus.status,ST_MODULE_IS_MASTER)
#define ST_FRAME_ACK_REQ		0x02


/// MODBUS PRIVATE SERVICE CODES //////////////////////////////////////////////
enum{
	_MODBUS_PROCESS_RECEIVED_FRAME = 1
};


typedef struct  __attribute__ ((packed)) tt_modbusFrame{
	uint8_t		moduleAddr;
	uint8_t		functionCode;
	union{
		struct  __attribute__ ((packed)){
			uint16_t	startingAddr;
			uint16_t	registerQty;
			uint8_t		byteCount;
			uint16_t	dataField[123];
		}writeMultipleRegister_header;
	};
}t_modbusFrame;

