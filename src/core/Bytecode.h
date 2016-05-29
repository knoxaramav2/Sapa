#ifndef BYTECODE
#define BYTECODE

/*
This long list defines the 1.0.0 encoding values
*/

#define BYTECODE_VERSION  1

#define _EOF          0x00
#define _SBODY        0x01
#define _EBODY        0x02
#define _SGROUP       0x04
#define _EGROUP       0x05
#define _SBRACE       0x06
#define _EBRACE       0x07
#define _SPLIT        0x08
#define _MEMREF       0x09
#define _INDEX        0x0A

#define _ADD          0x10
#define _SUB          0x11
#define _DIV          0x12
#define _MULT         0x13
#define _MOD          0x14
#define _POW          0x15
#define _ROOT         0x16

//not keywords
#define _iAND         0x1A
#define _iOR          0x1B
#define _iNOT         0x1C
#define _iNAND        0x1D
#define _iNOR         0x1E
#define _iXOR         0x1F
#define _iXNOR        0x20
#define _iEQU         0x21
#define _iNEQU        0x22
#define _iGTR         0x23
#define _iLSS         0x24
#define _iGTREQU      0x25
#define _iLSSEQU      0x26
#define _iWITHIN      0x27
#define _iOUTSIDE     0x28

//i prefix represents identifier
#define _iCELL        0x30
#define _iGROUP       0x31
#define _iFLOAT       0x32
#define _iINT         0x33
#define _iBOOL        0x34
#define _iCHAR        0x35
#define _iSTRING      0x36
#define _iFIBER       0x37
#define _iEXPRSS      0x38
#define _iSYNAPSE     0x39
#define _iINTERFACE   0x3A
#define _iSTRUCT      0x3B
#define _iOUTDEVICE   0x3C
#define _iINDEVICE    0x3D

#define _kCONST        0x40
#define _kOVERRIDE     0x41
#define _kNEW          0x42
#define _kDELETE       0x43
#define _kPERSIST      0x44

#define _kCELL        0x4A
#define _kGROUP       0x4B
#define _kFLOAT       0x4C
#define _kINT         0x4D
#define _kBOOL        0x4E
#define _kCHAR        0x4F
#define _kSTRING      0x50
#define _kFIBER       0x51
#define _kEXPRSS      0x52
#define _kSYNAPSE     0x53
#define _kINTERFACE   0x54
#define _kSTRUCT      0x55
#define _KDEVICE      0x56

#define _iSET          0x5A
#define _iADDSET       0x5B
#define _iSUBSET       0x5C
#define _iMULTSET      0x5D
#define _iDIVSET       0x5E
#define _iINC          0x5F
#define _iDEC          0X60
#define _iTERN         0x61

#define _kRAND         0x6A
#define _kDISPLAY      0x6B
#define _kSTARTLOG     0x6C
#define _kWRITELOG     0x6D
#define _kCLOSELOG     0x6E
#define _kUSIN         0x6F
#define _kBIND         0x70
#define _kCOPY         0x71
#define _kSPAWN        0x72
#define _kKILL         0x73
#define _kUNBIND       0x74
#define _kGAUSS        0x75

#define _iTONEURAL     0x7A
#define _iTOSERIAL     0x7B
#define _iUSB          0x7C
#define _iFNCGEN       0x7D

#define _kAND         0x80
#define _kOR          0x81
#define _kNOT         0x82
#define _kNAND        0x83
#define _kNOR         0x84
#define _kXOR         0x85
#define _kXNOR        0x86

#define _iGRID         0x90
#define _iMATRIX       0x91
#define _iRING         0x92
#define _iLING         0x93

#define _iJUMP         0xA0
#define _iBREAK        0xA1
#define _iGOTO         0xA2

#define _iMATH         0xB0
#define _iINSERT       0xB1

#endif
