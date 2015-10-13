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
#define bsTXP1   (1)
#define bsTXP0   (0)

#define bmABTF   (BIT(bsABTF))
#define bmMLOA   (BIT(bsMLOA))
#define bmTXERR  (BIT(bsTXERR))
#define bmTXREQ  (BIT(bsTXREQ))
#define bmTXP    (BIT(bsTXP1)|BIT(bsTXP0))

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

/*****************************************************************************/
#define CAN_MCP2515_NUM_OF_TX_BUFFERS  (3)
#define CAN_MCP2515_NUM_OF_RX_BUFFERS  (2)


/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define CAN_MCP2515_WRITE_REG( _regName, _data )  (CAN_mcp2515_writeByte( CAN_MCP2515_REG_ ## _regName, _data ))

/*****************************************************************************/
#define CAN_MCP2515_READ_REG( _regName )   (CAN_mcp2515_readByte( CAN_MCP2515_REG_ ## _regName ))


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    /* */
    CAN_MCP2515_REG_BFPCTRL    = 0x0C,
    /* */
    CAN_MCP2515_REG_TXRTSCTRL  = 0x0D,
    /* */
    CAN_MCP2515_REG_CANSTAT    = 0x0E,
    CAN_MCP2515_REG_CANCTRL    = 0x0F,
    /* */
    CAN_MCP2515_REG_TEC        = 0x1C,
    CAN_MCP2515_REG_REC        = 0x1D,
    /* */
    CAN_MCP2515_REG_CNF3       = 0x28,
    CAN_MCP2515_REG_CNF2       = 0x29,
    CAN_MCP2515_REG_CNF1       = 0x2A,
    /* */
    CAN_MCP2515_REG_CANINTE    = 0x2B,
    CAN_MCP2515_REG_CANINTF    = 0x2C,
    /* */
    CAN_MCP2515_REG_EFLG       = 0x2D,
    /* */
    CAN_MCP2515_REG_RXF0SIDH   = 0x00,
    CAN_MCP2515_REG_RXF1SIDH   = 0x04,
    CAN_MCP2515_REG_RXF2SIDH   = 0x08,
    CAN_MCP2515_REG_RXF3SIDH   = 0x10,
    CAN_MCP2515_REG_RXF4SIDH   = 0x14,
    CAN_MCP2515_REG_RXF5SIDH   = 0x18,
    /* */
    CAN_MCP2515_REG_RXF0SIDL   = 0x01,
    CAN_MCP2515_REG_RXF1SIDL   = 0x05,
    CAN_MCP2515_REG_RXF2SIDL   = 0x09,
    CAN_MCP2515_REG_RXF3SIDL   = 0x11,
    CAN_MCP2515_REG_RXF4SIDL   = 0x15,
    CAN_MCP2515_REG_RXF5SIDL   = 0x19,
    /* */
    CAN_MCP2515_REG_RXF0EID8   = 0x02,
    CAN_MCP2515_REG_RXF1EID8   = 0x06,
    CAN_MCP2515_REG_RXF2EID8   = 0x0A,
    CAN_MCP2515_REG_RXF3EID8   = 0x12,
    CAN_MCP2515_REG_RXF4EID8   = 0x16,
    CAN_MCP2515_REG_RXF5EID8   = 0x1A,
    /* */
    CAN_MCP2515_REG_RXF0EID0   = 0x03,
    CAN_MCP2515_REG_RXF1EID0   = 0x07,
    CAN_MCP2515_REG_RXF2EID0   = 0x0B,
    CAN_MCP2515_REG_RXF3EID0   = 0x13,
    CAN_MCP2515_REG_RXF4EID0   = 0x17,
    CAN_MCP2515_REG_RXF5EID0   = 0x1B,
    /* */
    CAN_MCP2515_REG_RXM0SIDH   = 0x20,
    CAN_MCP2515_REG_RXM1SIDH   = 0x24,
    /* */
    CAN_MCP2515_REG_RXM0SIDL   = 0x21,
    CAN_MCP2515_REG_RXM1SIDL   = 0x25,
    /* */
    CAN_MCP2515_REG_RXM0EID8   = 0x22,
    CAN_MCP2515_REG_RXM1EID8   = 0x26,
    /* */
    CAN_MCP2515_REG_RXM0EID0   = 0x23,
    CAN_MCP2515_REG_RXM1EID0   = 0x27,
    /* */
    CAN_MCP2515_REG_TXB0CTRL   = 0x30,
    CAN_MCP2515_REG_TXB1CTRL   = 0x40,
    CAN_MCP2515_REG_TXB2CTRL   = 0x50,
    /* */
    CAN_MCP2515_REG_TXB0SIDH   = 0x31,
    CAN_MCP2515_REG_TXB1SIDH   = 0x41,
    CAN_MCP2515_REG_TXB2SIDH   = 0x51,
    /* */
    CAN_MCP2515_REG_TXB0SIDL   = 0x32,
    CAN_MCP2515_REG_TXB1SIDL   = 0x42,
    CAN_MCP2515_REG_TXB2SIDL   = 0x52,
    /* */
    CAN_MCP2515_REG_TXB0EID8   = 0x33,
    CAN_MCP2515_REG_TXB1EID8   = 0x43,
    CAN_MCP2515_REG_TXB2EID8   = 0x53,
    /* */
    CAN_MCP2515_REG_TXB0EID0   = 0x34,
    CAN_MCP2515_REG_TXB1EID0   = 0x44,
    CAN_MCP2515_REG_TXB2EID0   = 0x54,
    /* */
    CAN_MCP2515_REG_TXB0DLC    = 0x35,
    CAN_MCP2515_REG_TXB1DLC    = 0x45,
    CAN_MCP2515_REG_TXB2DLC    = 0x55,
    /* */
    CAN_MCP2515_REG_TXB0D0     = 0x36,
    CAN_MCP2515_REG_TXB0D1     = 0x37,
    CAN_MCP2515_REG_TXB0D2     = 0x38,
    CAN_MCP2515_REG_TXB0D3     = 0x39,
    CAN_MCP2515_REG_TXB0D4     = 0x3A,
    CAN_MCP2515_REG_TXB0D5     = 0x3B,
    CAN_MCP2515_REG_TXB0D6     = 0x3C,
    CAN_MCP2515_REG_TXB0D7     = 0x3D,
    /* */
    CAN_MCP2515_REG_TXB1D0     = 0x46,
    CAN_MCP2515_REG_TXB1D1     = 0x47,
    CAN_MCP2515_REG_TXB1D2     = 0x48,
    CAN_MCP2515_REG_TXB1D3     = 0x49,
    CAN_MCP2515_REG_TXB1D4     = 0x4A,
    CAN_MCP2515_REG_TXB1D5     = 0x4B,
    CAN_MCP2515_REG_TXB1D6     = 0x4C,
    CAN_MCP2515_REG_TXB1D7     = 0x4D,
    /* */
    CAN_MCP2515_REG_TXB2D0     = 0x56,
    CAN_MCP2515_REG_TXB2D1     = 0x57,
    CAN_MCP2515_REG_TXB2D2     = 0x58,
    CAN_MCP2515_REG_TXB2D3     = 0x59,
    CAN_MCP2515_REG_TXB2D4     = 0x5A,
    CAN_MCP2515_REG_TXB2D5     = 0x5B,
    CAN_MCP2515_REG_TXB2D6     = 0x5C,
    CAN_MCP2515_REG_TXB2D7     = 0x5D,
    /* */
    CAN_MCP2515_REG_RXB0CTRL   = 0x60,
    CAN_MCP2515_REG_RXB1CTRL   = 0x70,
    /* */
    CAN_MCP2515_REG_RXB0SIDH   = 0x61,
    CAN_MCP2515_REG_RXB1SIDH   = 0x71,
    /* */
    CAN_MCP2515_REG_RXB0SIDL   = 0x62,
    CAN_MCP2515_REG_RXB1SIDL   = 0x72,
    /* */
    CAN_MCP2515_REG_RXB0EID8   = 0x63,
    CAN_MCP2515_REG_RXB1EID8   = 0x73,
    /* */
    CAN_MCP2515_REG_RXB0EID0   = 0x64,
    CAN_MCP2515_REG_RXB1EID0   = 0x74,
    /* */
    CAN_MCP2515_REG_RXB0DLC    = 0x65,
    CAN_MCP2515_REG_RXB1DLC    = 0x75,
    /* */
    CAN_MCP2515_REG_RXB0D0     = 0x66,
    CAN_MCP2515_REG_RXB0D1     = 0x67,
    CAN_MCP2515_REG_RXB0D2     = 0x68,
    CAN_MCP2515_REG_RXB0D3     = 0x69,
    CAN_MCP2515_REG_RXB0D4     = 0x6A,
    CAN_MCP2515_REG_RXB0D5     = 0x6B,
    CAN_MCP2515_REG_RXB0D6     = 0x6C,
    CAN_MCP2515_REG_RXB0D7     = 0x6D,
    /* */
    CAN_MCP2515_REG_RXB1D0     = 0x76,
    CAN_MCP2515_REG_RXB1D1     = 0x77,
    CAN_MCP2515_REG_RXB1D2     = 0x78,
    CAN_MCP2515_REG_RXB1D3     = 0x79,
    CAN_MCP2515_REG_RXB1D4     = 0x7A,
    CAN_MCP2515_REG_RXB1D5     = 0x7B,
    CAN_MCP2515_REG_RXB1D6     = 0x7C,
    CAN_MCP2515_REG_RXB1D7     = 0x7D,
} CAN_Mcp2515_Reg_t;

/*****************************************************************************/
typedef enum {
    CAN_MCP2515_INST_RESET             = 0xC0,
    CAN_MCP2515_INST_READ              = 0x03,
    CAN_MCP2515_INST_READ_RX_BUFFER_0  = 0x90,
    CAN_MCP2515_INST_READ_RX_BUFFER_1  = 0x92,
    CAN_MCP2515_INST_READ_RX_BUFFER_2  = 0x94,
    CAN_MCP2515_INST_READ_RX_BUFFER_3  = 0x96,
    CAN_MCP2515_INST_WRITE             = 0x02,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_0  = 0x40,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_1  = 0x41,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_2  = 0x42,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_3  = 0x43,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_4  = 0x44,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_5  = 0x45,
    CAN_MCP2515_INST_RTS_TXB0          = 0x81,
    CAN_MCP2515_INST_RTS_TXB1          = 0x82,
    CAN_MCP2515_INST_RTS_TXB2          = 0x83,
    CAN_MCP2515_INST_READ_STATUS       = 0xA0,
    CAN_MCP2515_INST_RX_STATUS         = 0xB0,
    CAN_MCP2515_INST_BIT_MODIFY        = 0x05,
} CAN_Mcp2515_Inst_t;

/*****************************************************************************/
typedef enum {
    CAN_MCP2515_OPMODE_NORMAL  = 0,
    CAN_MCP2515_OPMODE_SLEEP,
    CAN_MCP2515_OPMODE_LOOPBACK,
    CAN_MCP2515_OPMODE_LISTEN_ONLY,
    CAN_MCP2515_OPMODE_CONFIGURATION,
} CAN_Mcp2515_OperatingMode_t;

/*****************************************************************************/
typedef enum {
    CAN_MCP2515_ERROR_SUCCESS = 0,
    CAN_MCP2515_ERROR_GENERAL,
    CAN_MCP2515_ERROR_MSG_TX,
    CAN_MCP2515_ERROR_RECEIVER_OVERFLOW,
    CAN_MCP2515_ERROR_RECEIVER_WARNING,
    CAN_MCP2515_ERROR_TRANSMITTER_WARNING,
    CAN_MCP2515_ERROR_RECEIVER_PASSIVE,
    CAN_MCP2515_ERROR_TRANSMITTER_PASSIVE,
    CAN_MCP2515_ERROR_BUS_OFF,
} CAN_Mcp2515_Error_t;

/*****************************************************************************/
typedef void (*CAN_Mcp2515_RxCallback_t)( uint32_t id,
                                          bool     isExtended );

/*****************************************************************************/
typedef void (*CAN_Mcp2515_ErrorCallback_t)( CAN_Mcp2515_Error_t errorType );


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_mcp2515_init( uint8_t* rxBuf,
                  size_t   rxBufSize,
                  CAN_Mcp2515_RxCallback_t rxCallback,
                  CAN_Mcp2515_ErrorCallback_t errorCallback );

/*****************************************************************************/
void
CAN_mcp2515_reset( void );

/*****************************************************************************/
bool
CAN_mcp2515_sendStandardDataFrame( uint16_t id, void* buf, size_t size );

/*****************************************************************************/
bool
CAN_mcp2515_sendExtendedDataFrame( uint32_t id, void* buf, size_t size );

/*****************************************************************************/
void
CAN_mcp2515_instReset( void );

/*****************************************************************************/
void
CAN_mcp2515_instRead( uint8_t address, uint8_t* buffer, size_t length );

/*****************************************************************************/
uint8_t
CAN_mcp2515_readByte( uint8_t address );

/*****************************************************************************/
void
CAN_mcp2515_instWrite( uint8_t address, uint8_t* buffer, size_t length );

/*****************************************************************************/
void
CAN_mcp2515_writeByte( uint8_t address, uint8_t data );

/*****************************************************************************/
void
CAN_mcp2515_instBitModify( uint8_t address, uint8_t mask, uint8_t data );

/*****************************************************************************/
CAN_Mcp2515_OperatingMode_t
CAN_mcp2515_getOperatingMode( void );

/*****************************************************************************/
void
CAN_mcp2515_setOperatingMode( CAN_Mcp2515_OperatingMode_t mode );

/*****************************************************************************/
void
CAN_mcp2515_disableInterrupts( void );

/*****************************************************************************/
void
CAN_mcp2515_enableInterrupts( uint8_t mask );

/*****************************************************************************/
uint8_t
CAN_mcp2515_getInterruptFlags( void );

/*****************************************************************************/
uint8_t
CAN_mcp2515_getTxErrorCount( void );

/*****************************************************************************/
uint8_t
CAN_mcp2515_getRxErrorCount( void );

/*****************************************************************************/
uint8_t
CAN_mcp2515_getErrorFlags( void );


#endif /* _CAN_MCP2515_H_ */
