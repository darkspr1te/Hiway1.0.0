#ifndef __T9_ENGLISH_H__
#define __T9_ENGLISH_H__

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

struct Key_index
{
    const char* KC;
    int Sy_num;
    const char** KC_Symb;
};

const char* KE_SYmb_2[]={"a","b","c", "A", "B", "C"};
const char* KE_SYmb_3[]={"d","e","f", "D", "E", "F"};
const char* KE_SYmb_4[]={"g","h", "i", "G", "H", "I"};
const char* KE_SYmb_5[]={"j","k","l", "J", "K", "L"};
const char* KE_SYmb_6[]={"m","n","o", "M", "N", "O"};
const char* KE_SYmb_7[]={"p","q","r","s", "P", "Q", "R", "S"};
const char* KE_SYmb_8[]={"t", "u", "v", "T", "U", "V"};
const char* KE_SYmb_9[]={"w","x","y","z", "W", "X", "Y", "Z"};


struct Key_index Key_index_en[]=
{
	{"2",6,KE_SYmb_2},
	{"3",6,KE_SYmb_3},
	{"4",6,KE_SYmb_4},
	{"5",6,KE_SYmb_5},
	{"6",6,KE_SYmb_6},
	{"7",8,KE_SYmb_7},
	{"8",6,KE_SYmb_8},
	{"9",8,KE_SYmb_9},
	{"end",1,NULL}
};

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__T9_ENGLISH_H__*/
