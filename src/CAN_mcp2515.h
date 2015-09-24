/**
 * CAN_mcp2515.h - Hardware drivers for the MCP2515 CAN bus controller
 * Copyright (C) 2015 Josh Lubawy <jlubawy@gmail.com> <jlubawy@asu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _CAN_MCP2515_H_
#define _CAN_MCP2515_H_

#include <stdint.h>
#include <stdlib.h>

#include "Utility.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
/**
 * TXBnCTRL (0x30, 0x40, 0x50)
 */
#define bsABTF   (6)
#define bsMLOA   (5)
#define bsTXERR  (4)
#define bsTXREQ  (3)
#define bsTXB1   (1)
#define bsTXB0   (0)

#define bmABTF   (BIT(bsABTF))
#define bmMLOA   (BIT(bsMLOA))
#define bmTXERR  (BIT(bsTXERR))
#define bmTXREQ  (BIT(bsTXREQ))
#define bmTXB    (BIT(bsTXB1)|BIT(bsTXB0))

/*****************************************************************************/
/**
 * TXRTSCTRL (0x0D)
 */
#define bsB2RTS   (5)
#define bsB1RTS   (4)
#define bsB0RTS   (3)
#define bsB2RTSM  (2)
#define bsB1RTSM  (1)
#define bsB0RTSM  (0)

#define bmB2RTS   (BIT(bsB2RTS))
#define bmB1RTS   (BIT(bsB1RTS))
#define bmB0RTS   (BIT(bsB0RTS))
#define bmB2RTSM  (BIT(bsB2RTSM))
#define bmB1RTSM  (BIT(bsB1RTSM))
#define bmB0RTSM  (BIT(bsB0RTSM))

/*****************************************************************************/
/**
 * TXBnSIDH (0x31, 0x41, 0x51)
 * RXBnSIDH (0x61, 0x71)
 * RXFnSIDH (0x00, 0x04, 0x08, 0x10, 0x14, 0x18)
 * RXMnSIDH (0x20, 0x24)
 */
#define bsSID10  (7)
#define bsSID9   (6)
#define bsSID8   (5)
#define bsSID7   (4)
#define bsSID6   (3)
#define bsSID5   (2)
#define bsSID4   (1)
#define bsSID3   (0)

#define bmSID10_3  (BIT(bsSID10)|BIT(bsSID9)|BIT(bsSID8)|BIT(bsSID7)|BIT(bsSID6)|BIT(bsSID5)|BIT(bsSID4)|BIT(bsSID3))

/*****************************************************************************/
/**
 * TXBnSIDL (0x32, 0x42, 0x52)
 * RXBnSIDL (0x62, 0x72)
 * RXFnSIDL (0x01, 0x05, 0x09, 0x11, 0x15, 0x19)
 * RXMnSIDL (0x21, 0x25)
 */
#define bsSID2   (7)
#define bsSID1   (6)
#define bsSID0   (5)
#define bsEID17  (1)
#define bsEID16  (0)

#define bmSID2_0    (BIT(bsSID2)|BIT(bsSID1)|BIT(bsSID0))
#define bmEID17_16  (BIT(bsEID17)|BIT(bsEID16))

/* TXBnSIDL (0x32, 0x42, 0x52) */
/* RXFnSIDL (0x01, 0x05, 0x09, 0x11, 0x15, 0x19) */
#define bsEXIDE  (3)

#define bmEXIDE  (BIT(bsEXIDE))

/* RXBnSIDL (0x62, 0x72) */
#define bsSRR  (4)
#define bsIDE  (3)

#define bmSRR  (BIT(bsSRR))
#define bmIDE  (BIT(bsIDE))

/*****************************************************************************/
/**
 * TXBnEID8 (0x33, 0x43, 0x53)
 * RXBnEID8 (0x63, 0x73)
 * RXFnEID8 (0x02, 0x06, 0x0A, 0x12, 0x16, 0x1A)
 * RXMnEID8 (0x22, 0x26)
 */
#define bsEID15  (7)
#define bsEID14  (6)
#define bsEID13  (5)
#define bsEID12  (4)
#define bsEID11  (3)
#define bsEID10  (2)
#define bsEID9   (1)
#define bsEID8   (0)

#define bmEID15_8  (BIT(bsEID15)|BIT(bsEID14)|BIT(bsEID13)|BIT(bsEID12)|BIT(bsEID11)|BIT(bsEID10)|BIT(bsEID9)|BIT(bsEID8))

/*****************************************************************************/
/**
 * TXBnEID0 (0x34, 0x44, 0x54)
 * RXBnEID0 (0x64, 0x74)
 * RXFnEID0 (0x03, 0x07, 0x0B, 0x13, 0x17, 0x1B)
 * RXMnEID0 (0x23, 0x27)
 */
#define bsEID7  (7)
#define bsEID6  (6)
#define bsEID5  (5)
#define bsEID4  (4)
#define bsEID3  (3)
#define bsEID2  (2)
#define bsEID1  (1)
#define bsEID0  (0)

#define bmEID7_0  (BIT(bsEID7)|BIT(bsEID6)|BIT(bsEID5)|BIT(bsEID4)|BIT(bsEID3)|BIT(bsEID2)|BIT(bsEID1)|BIT(bsEID0))

/*****************************************************************************/
/**
 * TXBnDLC (0x35, 0x45, 0x55)
 * RXBnDLC (0x65, 0x75)
 */
#define bsRTR   (6)
#define bsDLC3  (3)
#define bsDLC2  (2)
#define bsDLC1  (1)
#define bsDLC0  (0)

#define bmRTR     (BIT(bsRTR))
#define bmDLC3_0  (BIT(bsDLC3)|BIT(bsDLC2)|BIT(bsDLC1)|BIT(bsDLC0))

/* RXBnDLC (0x65, 0x75) */
#define bsRB1  (5)
#define bsRB0  (4)

#define bmRB  (BIT(bsRB1)BIT(bsRB0))

/*****************************************************************************/
/**
 * TXBnDm (0x36-0x3D, 0x46-0x4D, 0x56-0x5D)
 */
#define bsTXBnD7  (7)
#define bsTXBnD6  (6)
#define bsTXBnD5  (5)
#define bsTXBnD4  (4)
#define bsTXBnD3  (3)
#define bsTXBnD2  (2)
#define bsTXBnD1  (1)
#define bsTXBnD0  (0)

#define bmTXBnDm  (BIT(bsTXBnD7)|BIT(bsTXBnD6)|BIT(bsTXBnD5)|BIT(bsTXBnD4)|BIT(bsTXBnD3)|BIT(bsTXBnD2)|BIT(bsTXBnD1)|BIT(bsTXBnD0))

/*****************************************************************************/
/**
 * RXB0CTRL (0x60)
 * RXB1CTRL (0x70)
 */
#define bsRXM1     (6)
#define bsRXM0     (5)
#define bsRXRTR    (3)
#define bsFILHIT0  (0)

/* RXB0CTRL (0x60) */
#define bsBUKT     (2)
#define bsBUKT1    (1)

/* RXB1CTRL (0x70) */
#define bsFILHIT2  (2)
#define bsFILHIT1  (1)

#define bmRXM      (BIT(bsRXM1)|BIT(bsRXM0))
#define bmRXRTR    (BIT(bsRXTR))
#define bmBUKT     (BIT(bsBUKT))
#define bmBUKT1    (BIT(bsBUKT1))
#define bmFILHIT0  (BIT(bsFILHIT0))

#define bmFILHIT2_0  (BIT(bsFILHIT2)|BIT(bsFILHIT1)|BIT(bsFILHIT0))

/*****************************************************************************/
/**
 * BFPCTRL (0x0C)
 */
#define bsB1BFS  (5)
#define bsB0BFS  (4)
#define bsB1BFE  (3)
#define bsB0BFE  (2)
#define bsB1BFM  (1)
#define bsB0BFM  (0)

#define bmB1BFS  (BIT(bsB1BFS))
#define bmB0BFS  (BIT(bsB0BFS))
#define bmB1BFE  (BIT(bsB1BFE))
#define bmB0BFE  (BIT(bsB0BFE))
#define bmB1BFM  (BIT(bsB1BFM))
#define bmB0BFM  (BIT(bsB0BFM))

/*****************************************************************************/
/**
 * RXBnDm (0x66-0x6D, 0x76-0x7D)
 */
#define bsRXBnD7  (7)
#define bsRXBnD6  (6)
#define bsRXBnD5  (5)
#define bsRXBnD4  (4)
#define bsRXBnD3  (3)
#define bsRXBnD2  (2)
#define bsRXBnD1  (1)
#define bsRXBnD0  (0)

#define bmRXBnDm  (BIT(bsRXBnD7)|BIT(bsRXBnD6)|BIT(bsRXBnD5)|BIT(bsRXBnD4)|BIT(bsRXBnD3)|BIT(bsRXBnD2)|BIT(bsRXBnD1)|BIT(bsRXBnD0))

/*****************************************************************************/
/**
 * CNF1 (0x2A)
 */
#define bsSJW1  (7)
#define bsSJW0  (6)
#define bsBRP5  (5)
#define bsBRP4  (4)
#define bsBRP3  (3)
#define bsBRP2  (2)
#define bsBRP1  (1)
#define bsBRP0  (0)

#define bmSJW  (BIT(bsSJW1)|BIT(bsSJW0))
#define bmBRP  (BIT(bsBRP5)|BIT(bsBRP4)|BIT(bsBRP3)|BIT(bsBRP2)|BIT(bsBRP1)|BIT(bsBRP0))

/*****************************************************************************/
/**
 * CNF2 (0x29)
 */
#define bsBTLMODE   (7)
#define bsSAM       (6)
#define bsPHSEG1_2  (5)
#define bsPHSEG1_1  (4)
#define bsPHSEG1_0  (3)
#define bsPHSEG_2   (2)
#define bsPHSEG_1   (1)
#define bsPHSEG_0   (0)

#define bmBTLMODE  (bsBTLMODE))
#define bmSAM      (bsSAM))
#define bmPHSEG1   (bsPHSEG1_2)|bsPHSEG1_1)|bsPHSEG1_0))
#define bmPHSEG    (bsPHSEG_2)|bsPHSEG_1)|bsPHSEG_0))

/*****************************************************************************/
/**
 * CNF3 (0x28)
 */
#define bsSOF       (7)
#define bsWAKFIL    (6)
#define bsPHSEG2_2  (2)
#define bsPHSEG2_1  (1)
#define bsPHSEG2_0  (0)

#define bmSOF     (BIT(bsSOF))
#define bmWAKFIL  (BIT(bsWAKFIL))
#define bmPHSEG2  (BIT(bsPHSEG2_2)|BIT(bsPHSEG2_1)|BIT(bsPHSEG2_0))

/*****************************************************************************/
/**
 * TEC (0x1C)
 */
#define bsTEC7  (7)
#define bsTEC6  (6)
#define bsTEC5  (5)
#define bsTEC4  (4)
#define bsTEC3  (3)
#define bsTEC2  (2)
#define bsTEC1  (1)
#define bsTEC0  (0)

#define bmTEC  (BIT(bsTEC7)|BIT(bsTEC6)|BIT(bsTEC5)|BIT(bsTEC4)|BIT(bsTEC3)|BIT(bsTEC2)|BIT(bsTEC1)|BIT(bsTEC0))

/*****************************************************************************/
/**
 * REC (0x1D)
 */
#define bsREC7  (7)
#define bsREC6  (6)
#define bsREC5  (5)
#define bsREC4  (4)
#define bsREC3  (3)
#define bsREC2  (2)
#define bsREC1  (1)
#define bsREC0  (0)

#define bmREC  (BIT(bsREC7)|BIT(bsREC6)|BIT(bsREC5)|BIT(bsREC4)|BIT(bsREC3)|BIT(bsREC2)|BIT(bsREC1)|BIT(bsREC0))

/*****************************************************************************/
/**
 * EFLG (0x2D)
 */
#define bsRX1OVR  (7)
#define bsRX0OVR  (6)
#define bsTXBO    (5)
#define bsTXEP    (4)
#define bsRXEP    (3)
#define bsTXWAR   (2)
#define bsRXWAR   (1)
#define bsEWARN   (0)

#define bmRX1OVR  (BIT(bsRX1OVR))
#define bmRX0OVR  (BIT(bsRX0OVR))
#define bmTXBO    (BIT(bsTXBO))
#define bmTXEP    (BIT(bsTXEP))
#define bmRXEP    (BIT(bsRXEP))
#define bmTXWAR   (BIT(bsTXWAR))
#define bmRXWAR   (BIT(bsRXWAR))
#define bmEWARN   (BIT(bsEWARN))

/*****************************************************************************/
/**
 * CANINTE (0x2B)
 */
#define bsMERRE  (7)
#define bsWAKIE  (6)
#define bsERRIE  (5)
#define bsTX2IE  (4)
#define bsTX1IE  (3)
#define bsTX0IE  (2)
#define bsRX1IE  (1)
#define bsRX0IE  (0)

#define bmMERRE  (BIT(bsMERRE))
#define bmWAKIE  (BIT(bsWAKIE))
#define bmERRIE  (BIT(bsERRIE))
#define bmTX2IE  (BIT(bsTX2IE))
#define bmTX1IE  (BIT(bsTX1IE))
#define bmTX0IE  (BIT(bsTX0IE))
#define bmRX1IE  (BIT(bsRX1IE))
#define bmRX0IE  (BIT(bsRX0IE))

/*****************************************************************************/
/**
 * CANINTF (0x2C)
 */
#define bsMERRF  (7)
#define bsWAKIF  (6)
#define bsERRIF  (5)
#define bsTX2IF  (4)
#define bsTX1IF  (3)
#define bsTX0IF  (2)
#define bsRX1IF  (1)
#define bsRX0IF  (0)

#define bmMERRF  (BIT(bsMERRF))
#define bmWAKIF  (BIT(bsWAKIF))
#define bmERRIF  (BIT(bsERRIF))
#define bmTX2IF  (BIT(bsTX2IF))
#define bmTX1IF  (BIT(bsTX1IF))
#define bmTX0IF  (BIT(bsTX0IF))
#define bmRX1IF  (BIT(bsRX1IF))
#define bmRX0IF  (BIT(bsRX0IF))

/*****************************************************************************/
/**
 * CANCTRL (0x0F)
 */
#define bsREQOP2   (7)
#define bsREQOP1   (6)
#define bsREQOP0   (5)
#define bsABAT     (4)
#define bsOSM      (3)
#define bsCLKEN    (2)
#define bsCLKPRE1  (1)
#define bsCLKPRE0  (0)

#define bmREQOP   (BIT(bsREQOP2)|BIT(bsREQOP1)|BIT(bsREQOP0))
#define bmABAT    (BIT(bsABAT))
#define bmOSM     (BIT(bsOSM))
#define bmCLKEN   (BIT(bsCLKEN))
#define bmCLKPRE  (BIT(bsCLKPRE1)|BIT(bsCLKPRE0)

/*****************************************************************************/
/**
 * CANSTAT (0x0E)
 */
#define bsOPMOD2  (7)
#define bsOPMOD1  (6)
#define bsOPMOD0  (5)
#define bsICOD2   (3)
#define bsICOD1   (2)
#define bsICOD0   (1)

#define bmOPMOD  (BIT(bsOPMOD2)|BIT(bsOPMOD1)|BIT(bsOPMOD0))
#define bmICOD   (BIT(bsICOD2)|BIT(bsICOD1)|BIT(bsICOD0))


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    CAN_MCP2515_OPMODE_NORMAL  = 0,
    CAN_MCP2515_OPMODE_SLEEP,
    CAN_MCP2515_OPMODE_LOOPBACK,
    CAN_MCP2515_OPMODE_LISTEN_ONLY,
    CAN_MCP2515_OPMODE_CONFIGURATION,
} CAN_Mcp2515_OperatingMode_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_mcp2515_init( void );

/*****************************************************************************/
void
CAN_mcp2515_instReset( void );

/*****************************************************************************/
void
CAN_mcp2515_instRead( uint8_t address, uint8_t* buffer, size_t length );

/*****************************************************************************/
void
CAN_mcp2515_instWrite( uint8_t address, uint8_t* buffer, size_t length );

/*****************************************************************************/
CAN_Mcp2515_OperatingMode_t
CAN_mcp2515_getOperatingMode( void );

/*****************************************************************************/
void
CAN_mcp2515_setOperatingMode( CAN_Mcp2515_OperatingMode_t mode );


#endif /* _CAN_MCP2515_H_ */
