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
#define _AND          0x1A
#define _OR           0x1B
#define _NOT          0x1C
#define _NAND         0x1D
#define _NOR          0x1E
#define _XOR          0x1F
#define _XNOR         0x20
#define _EQU          0x21
#define _NEQU         0x22
#define _GTR          0x23
#define _LSS          0x24
#define _GTREQU       0x25
#define _LSSEQU       0x26
#define _WITHIN       0x27
#define _OUTSIDE      0x28

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

#define _CONST        0x40
#define _OVERRIDE     0x41
#define _NEW          0x42
#define _DELETE       0x43
#define _PERSIST      0x44

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

#define _SET          0x5A
#define _ADDSET       0x5B
#define _SUBSET       0x5C
#define _MULTSET      0x5D
#define _DIVSET       0x5E
#define _INC          0x5F
#define _DEC          0X60
#define _TERN         0x61

#define _RAND         0x6A
#define _DISPLAY      0x6B
#define _STARTLOG     0x6C
#define _WRITELOG     0x6D
#define _CLOSELOG     0x6E
#define _USIN         0x6F
#define _BIND         0x70
#define _COPY         0x71
#define _SPAWN        0x72
#define _KILL         0x73
#define _UNBIND       0x74
#define _GAUSS        0x75

#define _TONEURAL     0x7A
#define _TOSERIAL     0x7B
#define _USB          0x7C
#define _FNCGEN       0x7D

#define _kAND         0x80
#define _kOR          0x81
#define _kNOT         0x82
#define _kNAND        0x83
#define _kNAND        0x84
#define _kNOR         0x85
#define _kXOR         0x86
#define _kXNOR        0x87

#define _GRID         0x90
#define _MATRIX       0x91
#define _RING         0x92
#define _LING         0x93

#define _JUMP         0xA0
#define _BREAK        0xA1
#define _GOTO         0xA2

#define _MATH         0xB0
#define _INSERT       0xB1

#endif
