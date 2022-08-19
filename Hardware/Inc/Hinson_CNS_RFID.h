
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef HINSON_CNS_RFID_H
#define HINSON_CNS_RFID_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 Hinson_CNS_RFID_valueRangeTest (UNS8 typeValue, void * value);
const indextable * Hinson_CNS_RFID_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data Hinson_CNS_RFID_Data;
extern UNS8 RfidReadStatus;		/* Mapped at index 0x2000, subindex 0x00*/
extern UNS8 RfidWriteStatus;		/* Mapped at index 0x2001, subindex 0x00*/
extern UNS8 RfidSignalRSSI;		/* Mapped at index 0x2002, subindex 0x00*/
extern UNS8 RfidReadData[8];		/* Mapped at index 0x2003, subindex 0x01 - 0x08 */
extern UNS8 RfidWriteData[8];		/* Mapped at index 0x2004, subindex 0x01 - 0x08 */
extern UNS8 RfidWriteCommand;		/* Mapped at index 0x2005, subindex 0x00*/
extern UNS8 RfidreadClearCommand;		/* Mapped at index 0x2006, subindex 0x00*/

#endif // HINSON_CNS_RFID_H