#ifndef __2410ADDR_H__
#define __2410ADDR_H__

// PWM TIMER
#define rTCFG0		(0x51000000) //Timer 0 configuration
#define rTCFG1		(0x51000004) //Timer 1 configuration
#define rTCON		(0x51000008) //Timer control
#define rTCNTB0		(0x5100000c) //Timer count buffer 0
#define rTCMPB0		(0x51000010) //Timer compare buffer 0
#define rTCNTO0		(0x51000014) //Timer count observation 0
#define rTCNTB1		(0x51000018) //Timer count buffer 1
#define rTCMPB1		(0x5100001c) //Timer compare buffer 1
#define rTCNTO1		(0x51000020) //Timer count observation 1
#define rTCNTB2		(0x51000024) //Timer count buffer 2
#define rTCMPB2		(0x51000028) //Timer compare buffer 2
#define rTCNTO2		(0x5100002c) //Timer count observation 2
#define rTCNTB3		(0x51000030) //Timer count buffer 3
#define rTCMPB3		(0x51000034) //Timer compare buffer 3
#define rTCNTO3		(0x51000038) //Timer count observation 3
#define rTCNTB4		(0x5100003c) //Timer count buffer 4
#define rTCNTO4		(0x51000040) //Timer count observation 4

// I/O PORT 
#define rGPACON    (0x56000000) //Port A control
#define rGPADAT    (0x56000004) //Port A data
                        
#define rGPBCON    (0x56000010) //Port B control
#define rGPBDAT    (0x56000014) //Port B data
#define rGPBUP     (0x56000018) //Pull-up control B
                        
#define rGPCCON    (0x56000020) //Port C control
#define rGPCDAT    (0x56000024) //Port C data
#define rGPCUP     (0x56000028) //Pull-up control C
                        
#define rGPDCON    (0x56000030) //Port D control
#define rGPDDAT    (0x56000034) //Port D data
#define rGPDUP     (0x56000038) //Pull-up control D
                        
#define rGPECON    (0x56000040) //Port E control
#define rGPEDAT    (0x56000044) //Port E data
#define rGPEUP     (0x56000048) //Pull-up control E
                        
#define rGPFCON    (0x56000050) //Port F control
#define rGPFDAT    (0x56000054) //Port F data
#define rGPFUP     (0x56000058) //Pull-up control F
                        
#define rGPGCON    (0x56000060) //Port G control
#define rGPGDAT    (0x56000064) //Port G data
#define rGPGUP     (0x56000068) //Pull-up control G
                        
#define rGPHCON    (0x56000070) //Port H control
#define rGPHDAT    (0x56000074) //Port H data

#endif  //__2410ADDR_H__
