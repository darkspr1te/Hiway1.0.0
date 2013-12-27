#ifndef __T9_CHINA_H__
#define __T9_CHINA_H__

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

	typedef const char* CONST_STRING;

	struct Key_index
	{
		const char* KC;
		int Sy_num;
		const char **KC_Symb;
	};
	CONST_STRING KC_SYmb_2[]={"a","b","c"};
	CONST_STRING KC_SYmb_22[]={"ba","ca"};
	CONST_STRING KC_SYmb_23[]={"be","ce"};
	CONST_STRING KC_SYmb_24[]={"ai","bi","ch","ci"};
	CONST_STRING KC_SYmb_26[]={"an","ao","bo","co"};
	CONST_STRING KC_SYmb_28[]={"bu","cu"};
	CONST_STRING KC_SYmb_224[]={"bai","cai"};
	CONST_STRING KC_SYmb_226[]={"ban","bao","can","cao"};
	CONST_STRING KC_SYmb_234[]={"bei"};
	CONST_STRING KC_SYmb_236[]={"ben","cen"};
	CONST_STRING KC_SYmb_242[]={"bia","cha"};
	CONST_STRING KC_SYmb_243[]={"bie","che"};
        CONST_STRING KC_SYmb_244[]={"chi"};
	CONST_STRING KC_SYmb_246[]={"bin","cho"};
	CONST_STRING KC_SYmb_248[]={"chu"};
	CONST_STRING KC_SYmb_264[]={"ang"};
	CONST_STRING KC_SYmb_266[]={"con"};
	CONST_STRING KC_SYmb_268[]={"cou"};
	CONST_STRING KC_SYmb_284[]={"cui"};
	CONST_STRING KC_SYmb_286[]={"cun","cuo"};
	CONST_STRING KC_SYmb_2264[]={"bang","cang"};
	CONST_STRING KC_SYmb_2364[]={"beng","ceng"};
	CONST_STRING KC_SYmb_2424[]={"chai"};
	CONST_STRING KC_SYmb_2426[]={"bian","biao","chan","chao"};
	CONST_STRING KC_SYmb_2436[]={"chen"};
	CONST_STRING KC_SYmb_2464[]={"bing"};
	CONST_STRING KC_SYmb_2466[]={"chon"};
	CONST_STRING KC_SYmb_2468[]={"chou"};
	CONST_STRING KC_SYmb_2482[]={"chua"};
	CONST_STRING KC_SYmb_2484[]={"chui"};
	CONST_STRING KC_SYmb_2486[]={"chun","chuo"};
	CONST_STRING KC_SYmb_2664[]={"cong"};
        CONST_STRING KC_SYmb_2826[]={"cuan"};
	CONST_STRING KC_SYmb_24264[]={"chang"};
	CONST_STRING KC_SYmb_24364[]={"cheng"};
	CONST_STRING KC_SYmb_24664[]={"chong"};
	CONST_STRING KC_SYmb_24824[]={"chuai"};
	CONST_STRING KC_SYmb_24826[]={"chuan"};
	CONST_STRING KC_SYmb_248264[]={"chuang"};
	CONST_STRING KC_SYmb_3[]={"d","e","f"};
	CONST_STRING KC_SYmb_32[]={"da","fa"};
	CONST_STRING KC_SYmb_33[]={"de","fe"};
	CONST_STRING KC_SYmb_34[]={"di","ei"};
	CONST_STRING KC_SYmb_36[]={"do","en","fo"};
	CONST_STRING KC_SYmb_37[]={"er"};
	CONST_STRING KC_SYmb_38[]={"du","fu"};
	CONST_STRING KC_SYmb_324[]={"dai"};
	CONST_STRING KC_SYmb_326[]={"dan","dao","fan"};
	CONST_STRING KC_SYmb_334[]={"dei","fei"};
	CONST_STRING KC_SYmb_336[]={"den","fen"};
	CONST_STRING KC_SYmb_342[]={"dia"};
	CONST_STRING KC_SYmb_343[]={"die"};
	CONST_STRING KC_SYmb_346[]={"din"};
	CONST_STRING KC_SYmb_348[]={"diu"};
	CONST_STRING KC_SYmb_366[]={"don"};
	CONST_STRING KC_SYmb_368[]={"dou","fou"};
	CONST_STRING KC_SYmb_382[]={"dua"};
	CONST_STRING KC_SYmb_384[]={"dui"};
	CONST_STRING KC_SYmb_386[]={"dun","duo"};
	CONST_STRING KC_SYmb_3264[]={"dang","fang"};
	CONST_STRING KC_SYmb_3364[]={"deng","feng"};
	CONST_STRING KC_SYmb_3426[]={"dian","diao"};
	CONST_STRING KC_SYmb_3464[]={"ding"};
	CONST_STRING KC_SYmb_3664[]={"dong"};
	CONST_STRING KC_SYmb_3826[]={"duan"};
	CONST_STRING KC_SYmb_34264[]={"diang"};
	CONST_STRING KC_SYmb_4[]={"g","h"};
	CONST_STRING KC_SYmb_42[]={"ga","ha"};
	CONST_STRING KC_SYmb_43[]={"ge","he"};
	CONST_STRING KC_SYmb_46[]={"go","ho"};
	CONST_STRING KC_SYmb_48[]={"gu","hu"};
	CONST_STRING KC_SYmb_424[]={"gai","hai"};
	CONST_STRING KC_SYmb_426[]={"gan","gao","han","hao"};
	CONST_STRING KC_SYmb_434[]={"gei","hei"};
	CONST_STRING KC_SYmb_436[]={"gen","hen"};
	CONST_STRING KC_SYmb_466[]={"gon","hon"};
	CONST_STRING KC_SYmb_468[]={"gou","hou"};
	CONST_STRING KC_SYmb_482[]={"gua","hua"};
	CONST_STRING KC_SYmb_484[]={"gui","hui"};
	CONST_STRING KC_SYmb_486[]={"gun","guo","hun","huo"};
	CONST_STRING KC_SYmb_4264[]={"gang","hang"};
	CONST_STRING KC_SYmb_4364[]={"geng","heng"};
	CONST_STRING KC_SYmb_4664[]={"gong","hong"};
	CONST_STRING KC_SYmb_4824[]={"guai","huai"};
	CONST_STRING KC_SYmb_4826[]={"guan","huan"};
	CONST_STRING KC_SYmb_48264[]={"guang","huang"};
	CONST_STRING KC_SYmb_5[]={"j","k","l"};
	CONST_STRING KC_SYmb_52[]={"ka","la"};
	CONST_STRING KC_SYmb_53[]={"ke","le"};
	CONST_STRING KC_SYmb_54[]={"ji","li"};
	CONST_STRING KC_SYmb_56[]={"ko","lo"};
	CONST_STRING KC_SYmb_58[]={"ju","ku","lu","lv"};
	CONST_STRING KC_SYmb_524[]={"kai","lai"};
	CONST_STRING KC_SYmb_526[]={"kan","kao","lan","lao"};
	CONST_STRING KC_SYmb_534[]={"kei","lei"};
	CONST_STRING KC_SYmb_536[]={"ken","len"};
	CONST_STRING KC_SYmb_542[]={"jia","lia"};
	CONST_STRING KC_SYmb_543[]={"jie","lie"};
	CONST_STRING KC_SYmb_546[]={"jin","jio","lin"};
	CONST_STRING KC_SYmb_548[]={"jiu","liu"};
	CONST_STRING KC_SYmb_566[]={"kon","lon"};
	CONST_STRING KC_SYmb_568[]={"kou","lou"};
	CONST_STRING KC_SYmb_582[]={"jua","kua","lua"};
	CONST_STRING KC_SYmb_583[]={"jue","lue"};
	CONST_STRING KC_SYmb_584[]={"kui"};
	CONST_STRING KC_SYmb_586[]={"jun","kun","kuo","lun","luo"};
	CONST_STRING KC_SYmb_5264[]={"kang","lang"};
	CONST_STRING KC_SYmb_5364[]={"keng","leng"};
	CONST_STRING KC_SYmb_5426[]={"jian","jiao","lian","liao"};
	CONST_STRING KC_SYmb_5464[]={"jing","ling"};
	CONST_STRING KC_SYmb_5466[]={"jion"};
	CONST_STRING KC_SYmb_5664[]={"kong","long"};
	CONST_STRING KC_SYmb_5824[]={"kuai"};
	CONST_STRING KC_SYmb_5826[]={"juan","kuan","luan"};
	CONST_STRING KC_SYmb_54264[]={"jiang","liang"};
	CONST_STRING KC_SYmb_54664[]={"jiong"};
	CONST_STRING KC_SYmb_58264[]={"kuang"};
	CONST_STRING KC_SYmb_6[]={"m","n","o"};
	CONST_STRING KC_SYmb_62[]={"ma","na"};
	CONST_STRING KC_SYmb_63[]={"me","ne"};
	CONST_STRING KC_SYmb_64[]={"mi","ni"};
	CONST_STRING KC_SYmb_66[]={"mo","no"};
	CONST_STRING KC_SYmb_68[]={"mu","nu","nv","ou"};
	CONST_STRING KC_SYmb_624[]={"mai","nai"};
	CONST_STRING KC_SYmb_626[]={"man","mao","nan","nao"};
	CONST_STRING KC_SYmb_634[]={"mei","nei"};
	CONST_STRING KC_SYmb_636[]={"men","nen"};
	CONST_STRING KC_SYmb_642[]={"mia","nia"};
	CONST_STRING KC_SYmb_643[]={"mie","nie"};
	CONST_STRING KC_SYmb_646[]={"min","nin"};
	CONST_STRING KC_SYmb_648[]={"miu","niu"};
	CONST_STRING KC_SYmb_666[]={"non"};
	CONST_STRING KC_SYmb_668[]={"mou","nou"};
	CONST_STRING KC_SYmb_682[]={"nua"};
	CONST_STRING KC_SYmb_683[]={"nue"};
	CONST_STRING KC_SYmb_686[]={"nuo"};
	CONST_STRING KC_SYmb_6264[]={"mang","nang"};
	CONST_STRING KC_SYmb_6364[]={"meng","neng"};
	CONST_STRING KC_SYmb_6426[]={"mian","miao","nian","niao"};
	CONST_STRING KC_SYmb_6464[]={"ming","ning"};
	CONST_STRING KC_SYmb_6664[]={"nong"};
	CONST_STRING KC_SYmb_6826[]={"nuan"};
	CONST_STRING KC_SYmb_64264[]={"niang"};
	CONST_STRING KC_SYmb_7[]={"p","q","r","s"};
	CONST_STRING KC_SYmb_72[]={"pa","ra","sa"};
	CONST_STRING KC_SYmb_73[]={"pe","re","se"};
	CONST_STRING KC_SYmb_74[]={"pi","qi","ri","si","sh"};
	CONST_STRING KC_SYmb_76[]={"po","ro","so"};
	CONST_STRING KC_SYmb_78[]={"pu","qu","ru","su"};
	CONST_STRING KC_SYmb_724[]={"pai","sai"};
	CONST_STRING KC_SYmb_726[]={"pan","pao","ran","rao","san","sao"};
	CONST_STRING KC_SYmb_734[]={"pei"};
	CONST_STRING KC_SYmb_736[]={"pen","ren","sen"};
	CONST_STRING KC_SYmb_742[]={"pia","qia","sha"};
	CONST_STRING KC_SYmb_743[]={"pie","qie","she"};
	CONST_STRING KC_SYmb_744[]={"shi"};
	CONST_STRING KC_SYmb_746[]={"pin","qin","qio","sho"};
	CONST_STRING KC_SYmb_748[]={"qiu","shu"};
	CONST_STRING KC_SYmb_766[]={"ron","son"};
	CONST_STRING KC_SYmb_768[]={"pou","rou","sou"};
	CONST_STRING KC_SYmb_782[]={"qua","rua","sua"};
	CONST_STRING KC_SYmb_783[]={"que"};
	CONST_STRING KC_SYmb_784[]={"rui","sui"};
	CONST_STRING KC_SYmb_786[]={"qun","run","ruo","sun","suo"};
	CONST_STRING KC_SYmb_7264[]={"pang","rang","sang"};
	CONST_STRING KC_SYmb_7364[]={"peng","reng","seng"};
	CONST_STRING KC_SYmb_7424[]={"shai"};
	CONST_STRING KC_SYmb_7426[]={"pian","piao","qian","qiao","shan","shao"};
	CONST_STRING KC_SYmb_7434[]={"shei"};
	CONST_STRING KC_SYmb_7436[]={"shen"};
	CONST_STRING KC_SYmb_7464[]={"ping","qing"};
	CONST_STRING KC_SYmb_7466[]={"qion"};
	CONST_STRING KC_SYmb_7468[]={"shou"};
	CONST_STRING KC_SYmb_7482[]={"shua"};
	CONST_STRING KC_SYmb_7484[]={"shui"};
	CONST_STRING KC_SYmb_7486[]={"shun","shuo"};
	CONST_STRING KC_SYmb_7664[]={"rong","song"};
	CONST_STRING KC_SYmb_7826[]={"quan","ruan","suan"};
	CONST_STRING KC_SYmb_74264[]={"qiang","shang"};
	CONST_STRING KC_SYmb_74364[]={"sheng"};
	CONST_STRING KC_SYmb_74664[]={"qiong"};
	CONST_STRING KC_SYmb_74824[]={"shuai"};
	CONST_STRING KC_SYmb_74826[]={"shuan"};
	CONST_STRING KC_SYmb_748264[]={"shuang"};
	CONST_STRING KC_SYmb_8[]={"t"};
	CONST_STRING KC_SYmb_82[]={"ta"};
	CONST_STRING KC_SYmb_83[]={"te"};
	CONST_STRING KC_SYmb_84[]={"ti"};
	CONST_STRING KC_SYmb_86[]={"to"};
	CONST_STRING KC_SYmb_88[]={"tu"};
	CONST_STRING KC_SYmb_824[]={"tai"};
	CONST_STRING KC_SYmb_826[]={"tan","tao"};
	CONST_STRING KC_SYmb_834[]={"tei"};
	CONST_STRING KC_SYmb_836[]={"ten"};
	CONST_STRING KC_SYmb_842[]={"tia"};
	CONST_STRING KC_SYmb_843[]={"tie"};
	CONST_STRING KC_SYmb_846[]={"tin"};
	CONST_STRING KC_SYmb_866[]={"ton"};
	CONST_STRING KC_SYmb_868[]={"tou"};
	CONST_STRING KC_SYmb_882[]={"tua"};
	CONST_STRING KC_SYmb_884[]={"tui"};
	CONST_STRING KC_SYmb_886[]={"tun","tuo"};
	CONST_STRING KC_SYmb_8264[]={"tang"};
	CONST_STRING KC_SYmb_8364[]={"teng"};
	CONST_STRING KC_SYmb_8426[]={"tian","tiao"};
	CONST_STRING KC_SYmb_8464[]={"ting"};
	CONST_STRING KC_SYmb_8664[]={"tong"};
	CONST_STRING KC_SYmb_8826[]={"tuan"};
	CONST_STRING KC_SYmb_9[]={"w","x","y","z"};
	CONST_STRING KC_SYmb_92[]={"wa","ya","za"};
	CONST_STRING KC_SYmb_93[]={"we","ye","ze"};
	CONST_STRING KC_SYmb_94[]={"xi","yi","zh","zi"};
	CONST_STRING KC_SYmb_96[]={"wo","yo","zo"};
	CONST_STRING KC_SYmb_98[]={"wu","xu","yu","zu"};
	CONST_STRING KC_SYmb_924[]={"wai","zai"};
	CONST_STRING KC_SYmb_926[]={"wan","yan","yao","zan","zao"};
	CONST_STRING KC_SYmb_934[]={"wei","zei"};
	CONST_STRING KC_SYmb_936[]={"wen","zen"};
	CONST_STRING KC_SYmb_942[]={"xia","zha"};
	CONST_STRING KC_SYmb_943[]={"xie","zhe"};
	CONST_STRING KC_SYmb_944[]={"zhi"};
	CONST_STRING KC_SYmb_946[]={"xin","xio","yin","zho"};
	CONST_STRING KC_SYmb_948[]={"xiu","zhu"};
	CONST_STRING KC_SYmb_966[]={"yon","zon"};
	CONST_STRING KC_SYmb_968[]={"you","zou"};
	CONST_STRING KC_SYmb_982[]={"xua","yua","zua"};
	CONST_STRING KC_SYmb_983[]={"xue","yue"};
	CONST_STRING KC_SYmb_984[]={"zui"};
	CONST_STRING KC_SYmb_986[]={"xun","yun","zun","zuo"};
	CONST_STRING KC_SYmb_9264[]={"wang","yang","zang"};
	CONST_STRING KC_SYmb_9364[]={"weng","zeng"};
	CONST_STRING KC_SYmb_9424[]={"zhai"};
	CONST_STRING KC_SYmb_9426[]={"xian","xiao","zhan","zhao"};
	CONST_STRING KC_SYmb_9436[]={"zhen"};
	CONST_STRING KC_SYmb_9464[]={"xing","ying"};
	CONST_STRING KC_SYmb_9466[]={"xion","zhon"};
        CONST_STRING KC_SYmb_9468[]={"zhou"};
	CONST_STRING KC_SYmb_9482[]={"zhua"};
	CONST_STRING KC_SYmb_9484[]={"zhui"};
	CONST_STRING KC_SYmb_9486[]={"zhun","zhuo"};
	CONST_STRING KC_SYmb_9664[]={"yong","zong"};
	CONST_STRING KC_SYmb_9826[]={"xuan","yuan","zuan"};
	CONST_STRING KC_SYmb_94264[]={"xiang","zhang"};
	CONST_STRING KC_SYmb_94364[]={"zheng"};
	CONST_STRING KC_SYmb_94664[]={"xiong","zhong"};
	CONST_STRING KC_SYmb_94824[]={"zhuai"};
	CONST_STRING KC_SYmb_94826[]={"zhuan"};
	CONST_STRING KC_SYmb_948264[]={"zhuang"};


	struct Key_index Key_index_2[]=
	{{"2",3,KC_SYmb_2},
		{"22",2,KC_SYmb_22},
		{"23",2,KC_SYmb_23},
		{"24",4,KC_SYmb_24},
		{"26",4,KC_SYmb_26},
		{"28",2,KC_SYmb_28},
		{"224",2,KC_SYmb_224},
		{"226",4,KC_SYmb_226},
		{"234",1,KC_SYmb_234},
		{"236",2,KC_SYmb_236},
		{"242",2,KC_SYmb_242},
		{"243",2,KC_SYmb_243},
                {"244",1,KC_SYmb_244},
		{"246",2,KC_SYmb_246},
		{"248",1,KC_SYmb_248},
		{"264",1,KC_SYmb_264},
		{"266",1,KC_SYmb_266},
		{"268",1,KC_SYmb_268},
		{"284",1,KC_SYmb_284},
		{"286",2,KC_SYmb_286},
		{"2264",2,KC_SYmb_2264},
		{"2364",2,KC_SYmb_2364},
		{"2424",1,KC_SYmb_2424},
		{"2426",4,KC_SYmb_2426},
		{"2436",1,KC_SYmb_2436},
		{"2464",1,KC_SYmb_2464},
		{"2466",1,KC_SYmb_2466},
		{"2468",1,KC_SYmb_2468},
		{"2482",1,KC_SYmb_2482},
		{"2484",1,KC_SYmb_2484},
		{"2486",2,KC_SYmb_2486},
		{"2664",1,KC_SYmb_2664},
                {"2826",1,KC_SYmb_2826},
		{"24264",1,KC_SYmb_24264},
		{"24364",1,KC_SYmb_24364},
		{"24664",1,KC_SYmb_24664},
		{"24824",1,KC_SYmb_24824},
		{"24826",1,KC_SYmb_24826},
		{"248264",1,KC_SYmb_248264},
		{"end",1,NULL}
	};
	struct Key_index Key_index_3[]=
	{{"3",3,KC_SYmb_3},
		{"32",2,KC_SYmb_32},
		{"33",2,KC_SYmb_33},
		{"34",2,KC_SYmb_34},
		{"36",3,KC_SYmb_36},
		{"37",1,KC_SYmb_37},
		{"38",2,KC_SYmb_38},
		{"324",1,KC_SYmb_324},
		{"326",3,KC_SYmb_326},
		{"334",2,KC_SYmb_334},
		{"336",2,KC_SYmb_336},
		{"342",1,KC_SYmb_342},
		{"343",1,KC_SYmb_343},
		{"346",1,KC_SYmb_346},
		{"348",1,KC_SYmb_348},
		{"366",1,KC_SYmb_366},
		{"368",2,KC_SYmb_368},
		{"382",1,KC_SYmb_382},
		{"384",1,KC_SYmb_384},
		{"386",2,KC_SYmb_386},
		{"3264",2,KC_SYmb_3264},
		{"3364",2,KC_SYmb_3364},
		{"3426",2,KC_SYmb_3426},
		{"3464",1,KC_SYmb_3464},
		{"3664",1,KC_SYmb_3664},
		{"3826",1,KC_SYmb_3826},
		{"34264",1,KC_SYmb_34264},
		{"end",1,NULL}
	};
	struct Key_index Key_index_4[]=
	{{"4",2,KC_SYmb_4},
		{"42",2,KC_SYmb_42},
		{"43",2,KC_SYmb_43},
		{"46",2,KC_SYmb_46},
		{"48",2,KC_SYmb_48},
		{"424",2,KC_SYmb_424},
		{"426",4,KC_SYmb_426},
		{"434",2,KC_SYmb_434},
		{"436",2,KC_SYmb_436},
		{"466",2,KC_SYmb_466},
		{"468",2,KC_SYmb_468},
		{"482",2,KC_SYmb_482},
		{"484",2,KC_SYmb_484},
		{"486",4,KC_SYmb_486},
		{"4264",2,KC_SYmb_4264},
		{"4364",2,KC_SYmb_4364},
		{"4664",2,KC_SYmb_4664},
		{"4824",2,KC_SYmb_4824},
		{"4826",2,KC_SYmb_4826},
		{"48264",2,KC_SYmb_48264},
		{"end",1,NULL}
	};
	struct Key_index Key_index_5[]=
	{{"5",3,KC_SYmb_5},
		{"52",2,KC_SYmb_52},
		{"53",2,KC_SYmb_53},
		{"54",2,KC_SYmb_54},
		{"56",2,KC_SYmb_56},
		{"58",4,KC_SYmb_58},
		{"524",2,KC_SYmb_524},
		{"526",4,KC_SYmb_526},
		{"534",2,KC_SYmb_534},
		{"536",2,KC_SYmb_536},
		{"542",2,KC_SYmb_542},
		{"543",2,KC_SYmb_543},
		{"546",3,KC_SYmb_546},
		{"548",2,KC_SYmb_548},
		{"566",2,KC_SYmb_566},
		{"568",2,KC_SYmb_568},
		{"582",3,KC_SYmb_582},
		{"583",2,KC_SYmb_583},
		{"584",1,KC_SYmb_584},
		{"586",5,KC_SYmb_586},
		{"5264",2,KC_SYmb_5264},
		{"5364",2,KC_SYmb_5364},
		{"5426",4,KC_SYmb_5426},
		{"5464",2,KC_SYmb_5464},
		{"5466",1,KC_SYmb_5466},
		{"5664",2,KC_SYmb_5664},
		{"5824",1,KC_SYmb_5824},
		{"5826",3,KC_SYmb_5826},
		{"54264",2,KC_SYmb_54264},
		{"54664",1,KC_SYmb_54664},
		{"58264",1,KC_SYmb_58264},
		{"end",1,NULL}
	};
	struct Key_index Key_index_6[]=
	{{"6",3,KC_SYmb_6},
		{"62",2,KC_SYmb_62},
		{"63",2,KC_SYmb_63},
		{"64",2,KC_SYmb_64},
		{"66",2,KC_SYmb_66},
		{"68",4,KC_SYmb_68},
		{"624",2,KC_SYmb_624},
		{"626",4,KC_SYmb_626},
		{"634",2,KC_SYmb_634},
		{"636",2,KC_SYmb_636},
		{"642",2,KC_SYmb_642},
		{"643",2,KC_SYmb_643},
		{"646",2,KC_SYmb_646},
		{"648",2,KC_SYmb_648},
		{"666",1,KC_SYmb_666},
		{"668",2,KC_SYmb_668},
		{"682",1,KC_SYmb_682},
		{"683",1,KC_SYmb_683},
		{"686",1,KC_SYmb_686},
		{"6264",2,KC_SYmb_6264},
		{"6364",2,KC_SYmb_6364},
		{"6426",4,KC_SYmb_6426},
		{"6464",2,KC_SYmb_6464},
		{"6664",1,KC_SYmb_6664},
		{"6826",1,KC_SYmb_6826},
		{"64264",1,KC_SYmb_64264},
		{"end",1,NULL}
	};
	struct Key_index Key_index_7[]=
	{{"7",4,KC_SYmb_7},
		{"72",3,KC_SYmb_72},
		{"73",3,KC_SYmb_73},
		{"74",5,KC_SYmb_74},
		{"76",3,KC_SYmb_76},
		{"78",4,KC_SYmb_78},
		{"724",2,KC_SYmb_724},
		{"726",6,KC_SYmb_726},
		{"734",1,KC_SYmb_734},
		{"736",3,KC_SYmb_736},
		{"742",3,KC_SYmb_742},
		{"743",3,KC_SYmb_743},
		{"744",1,KC_SYmb_744},
		{"746",4,KC_SYmb_746},
		{"748",2,KC_SYmb_748},
		{"766",2,KC_SYmb_766},
		{"768",3,KC_SYmb_768},
		{"782",3,KC_SYmb_782},
		{"783",1,KC_SYmb_783},
		{"784",2,KC_SYmb_784},
		{"786",5,KC_SYmb_786},
		{"7264",3,KC_SYmb_7264},
		{"7364",3,KC_SYmb_7364},
		{"7424",1,KC_SYmb_7424},
		{"7426",6,KC_SYmb_7426},
		{"7434",1,KC_SYmb_7434},
		{"7436",1,KC_SYmb_7436},
		{"7464",2,KC_SYmb_7464},
		{"7466",1,KC_SYmb_7466},
		{"7468",1,KC_SYmb_7468},
		{"7482",1,KC_SYmb_7482},
		{"7484",1,KC_SYmb_7484},
		{"7486",2,KC_SYmb_7486},
		{"7664",2,KC_SYmb_7664},
		{"7826",3,KC_SYmb_7826},
		{"74264",2,KC_SYmb_74264},
		{"74364",1,KC_SYmb_74364},
		{"74664",1,KC_SYmb_74664},
		{"74824",1,KC_SYmb_74824},
		{"74826",1,KC_SYmb_74826},
		{"748264",1,KC_SYmb_748264},
		{"end",1,NULL}
	};
	struct Key_index Key_index_8[]=
	{{"8",1,KC_SYmb_8},
		{"82",1,KC_SYmb_82},
		{"83",1,KC_SYmb_83},
		{"84",1,KC_SYmb_84},
		{"86",1,KC_SYmb_86},
		{"88",1,KC_SYmb_88},
		{"824",1,KC_SYmb_824},
		{"826",2,KC_SYmb_826},
		{"834",1,KC_SYmb_834},
		{"836",1,KC_SYmb_836},
		{"842",1,KC_SYmb_842},
		{"843",1,KC_SYmb_843},
		{"846",1,KC_SYmb_846},
		{"866",1,KC_SYmb_866},
		{"868",1,KC_SYmb_868},
		{"882",1,KC_SYmb_882},
		{"884",1,KC_SYmb_884},
		{"886",2,KC_SYmb_886},
		{"8264",1,KC_SYmb_8264},
		{"8364",1,KC_SYmb_8364},
		{"8426",2,KC_SYmb_8426},
		{"8464",1,KC_SYmb_8464},
		{"8664",1,KC_SYmb_8664},
		{"8826",1,KC_SYmb_8826},
		{"end",1,NULL}
	};
	struct Key_index Key_index_9[]=
	{{"9",4,KC_SYmb_9},
		{"92",3,KC_SYmb_92},
		{"93",3,KC_SYmb_93},
		{"94",4,KC_SYmb_94},
		{"96",3,KC_SYmb_96},
		{"98",4,KC_SYmb_98},
		{"924",2,KC_SYmb_924},
		{"926",5,KC_SYmb_926},
		{"934",2,KC_SYmb_934},
		{"936",2,KC_SYmb_936},
		{"942",2,KC_SYmb_942},
		{"943",2,KC_SYmb_943},
		{"944",1,KC_SYmb_944},
		{"946",4,KC_SYmb_946},
		{"948",2,KC_SYmb_948},
		{"966",2,KC_SYmb_966},
		{"968",2,KC_SYmb_968},
		{"982",3,KC_SYmb_982},
		{"983",2,KC_SYmb_983},
		{"984",1,KC_SYmb_984},
		{"986",4,KC_SYmb_986},
		{"9264",3,KC_SYmb_9264},
		{"9364",2,KC_SYmb_9364},
		{"9424",1,KC_SYmb_9424},
		{"9426",4,KC_SYmb_9426},
		{"9436",1,KC_SYmb_9436},
		{"9464",2,KC_SYmb_9464},
		{"9466",2,KC_SYmb_9466},
                {"9468",1,KC_SYmb_9468},
		{"9482",1,KC_SYmb_9482},
		{"9484",1,KC_SYmb_9484},
		{"9486",2,KC_SYmb_9486},
		{"9664",2,KC_SYmb_9664},
		{"9826",3,KC_SYmb_9826},
		{"94264",2,KC_SYmb_94264},
		{"94364",1,KC_SYmb_94364},
		{"94664",2,KC_SYmb_94664},
		{"94824",1,KC_SYmb_94824},
		{"94826",1,KC_SYmb_94826},
		{"948264",1,KC_SYmb_948264},
		{"end",1,NULL}
	};
	struct Key_index *Key_index_headkey[]=
	{
		Key_index_2,
		Key_index_3,
		Key_index_4,
		Key_index_5,
		Key_index_6,
		Key_index_7,
		Key_index_8,
		Key_index_9
	};

	struct PY_index
	{
		const char* PY;
		const char* PY_mb;
	};
	char PY_mb_a[]={"阿啊呵腌嗄锕吖"};//7
	char PY_mb_ai[]={"爱哀挨碍埃癌艾唉矮哎皑呆蔼隘暧霭捱嗳瑷嫒锿嗌砹"};//23   
	char PY_mb_an[]={"安案按暗岸俺谙黯鞍氨庵桉鹌胺厂广铵揞犴埯"};//20           
	char PY_mb_ang[]={"昂肮盎"};//3
	char PY_mb_ao[]={"奥澳傲熬敖凹袄懊坳嗷拗鏖骜鳌翱岙廒遨獒聱媪螯鏊嚣"};//24  	
        char PY_mb_ba[]={"把八吧巴爸罢拔叭芭霸靶扒疤跋坝笆耙粑灞茇菝魃岜捌钯鲅"};//26
	char PY_mb_bai[]={"百白败摆伯拜柏呗掰捭佰稗"};//12
	char PY_mb_ban[]={"办半版般班板伴搬扮斑颁瓣拌扳绊阪坂瘢钣舨癍"};//21
	char PY_mb_bang[]={"帮邦棒膀榜傍绑磅谤浜梆镑蚌蒡"};//14
	char PY_mb_bao[]={"报保包暴宝抱薄胞爆鲍饱堡曝刨褒豹雹苞葆褓孢煲鸨龅趵剥炮瀑"};//28
	char PY_mb_bei[]={"被北备背悲辈杯倍贝碑卑蓓惫悖狈呗焙鹎孛邶陂埤碚褙鐾鞴萆钡臂"};//29
	char PY_mb_ben[]={"本奔笨苯夯畚贲锛坌"};//9
	char PY_mb_beng[]={"崩甭绷蹦迸甏泵嘣蚌"};//9
	char PY_mb_bi[]={"比必笔毕币避闭鼻彼逼壁臂弊碧鄙毙蔽庇匕璧敝陛弼篦婢愎痹妣濞铋裨俾髀萆薜哔狴庳秕滗舭毖吡嬖蓖贲畀荸埤筚箅芘襞跸荜辟秘泌"};//58
	char PY_mb_bian[]={"编便边变遍辩辨贬鞭辫扁卞砭苄匾汴蝙笾碥窆褊弁鳊忭煸缏髟"};//27
	char PY_mb_biao[]={"表标彪镖膘骠镳裱杓飙瘭髟飚婊飑鳔"};//16
	char PY_mb_bie[]={"别憋瘪蹩鳖"};//5
	char PY_mb_bin[]={"宾滨彬斌鬓缤殡濒槟摈膑傧玢豳髌镔"};//16
	char PY_mb_bing[]={"并病兵冰饼丙柄秉炳禀邴摒屏槟"};//14
	char PY_mb_bo[]={"波播博伯勃薄拨泊柏剥玻驳卜脖搏膊饽簸掰舶跛礴菠帛铂钵渤檗钹擘箔趵孛鹁踣亳啵"};//37
	char PY_mb_bu[]={"不部布步补捕怖卜簿哺埔卟埠钸逋醭晡瓿钚堡"};//20
	char PY_mb_ca[]={"擦嚓礤拆"};//4
	char PY_mb_cai[]={"才采菜财材彩裁猜蔡踩睬"};//11
	char PY_mb_can[]={"参餐残惨灿惭掺蚕璨孱骖黪粲"};//13
	char PY_mb_cang[]={"藏苍仓沧舱伧"};//6
	char PY_mb_cao[]={"草操曹糙嘈槽螬艚漕"};//9
	char PY_mb_ce[]={"策测侧厕册恻"};//6
	char PY_mb_cen[]={"参岑涔"};//3
	char PY_mb_ceng[]={"曾层蹭噌"};//4
	char PY_mb_cha[]={"查察差茶插刹叉诧茬碴喳岔嚓衩杈楂槎檫镲搽锸猹馇汊姹"};//25
	char PY_mb_chai[]={"差柴拆豺钗侪虿瘥"};//8
	char PY_mb_chan[]={"产颤缠禅蝉馋铲搀阐掺潺忏蟾婵谄谗廛孱澶冁躔蒇骣觇镡羼单铲"};//28
	char PY_mb_chang[]={"长场常唱厂尝昌肠偿畅倡倘敞怅娼猖嫦伥氅徜昶鲳阊菖苌鬯惝裳"};//28
	char PY_mb_chao[]={"超朝潮炒吵抄嘲钞绰巢晁焯怊耖剿"};//15
	char PY_mb_che[]={"车彻撤扯澈掣坼砗尺"};//9
	char PY_mb_chen[]={"称陈沉晨尘臣趁衬辰郴谶琛忱嗔伧抻谌宸榇龀碜橙辰"};//23
	char PY_mb_cheng[]={"成城程称承诚盛乘呈撑惩澄秤瞠橙噌逞铛丞骋埕枨塍铖裎酲柽蛏晟"};//29
	char PY_mb_chi[]={"吃持迟尺赤斥池痴齿驰耻翅匙侈哧嗤啻弛蚩炽笞敕叱饬踟鸱褫豉坻墀茌篪傺媸螭彳眵魑瘛"};//39
	char PY_mb_chong[]={"重冲充崇虫宠憧忡艟茺舂铳涌种"};//14
	char PY_mb_chou[]={"抽愁仇丑筹臭酬绸踌瞅惆畴稠雠俦帱瘳"};//17
	char PY_mb_chu[]={"出处除初楚触储础厨畜躇橱雏矗怵锄杵搐绌黜褚蜍蹰刍滁楮憷亍樗"};//29
	char PY_mb_chuai[]={"揣啜踹嘬膪搋"};//6
	char PY_mb_chuan[]={"传穿川船串喘舛遄舡巛氚椽钏"};//13
	char PY_mb_chuang[]={"创窗床闯幢疮怆"};//7
	char PY_mb_chui[]={"吹垂炊锤捶陲槌棰椎"};//9
	char PY_mb_chun[]={"春纯唇蠢醇淳椿鹑蝽莼"};//10
	char PY_mb_chuo[]={"绰戳啜辍踔龊"};//6
	char PY_mb_ci[]={"此次词差刺辞慈磁赐瓷兹茨雌祠疵呲鹚糍茈"};//19
	char PY_mb_cong[]={"从匆聪丛葱囱琮淙枞苁骢璁"};//12
	char PY_mb_cou[]={"凑楱辏腠"};//4
	char PY_mb_cu[]={"促粗簇醋卒猝蹴蹙徂殂蔟酢"};//12
	char PY_mb_cuan[]={"攒窜篡蹿撺镩汆爨"};//8
	char PY_mb_cui[]={"脆粹催摧崔萃翠瘁悴璀隹淬毳榱啐"};//15
	char PY_mb_cun[]={"存村寸忖皴"};//5   少“蹲”
	char PY_mb_cuo[]={"错措搓挫撮磋蹉矬嵯脞痤瘥鹾厝锉"};//15
	char PY_mb_da[]={"大打达答搭瘩嗒沓耷褡鞑笪靼怛妲哒疸塔"};//18
	char PY_mb_dai[]={"大代带待戴袋呆贷逮歹殆黛怠玳岱迨傣呔骀绐埭甙"};//22
	char PY_mb_dan[]={"但单担弹淡旦蛋胆诞丹耽惮眈啖澹掸殚箪瘅赕疸聃氮萏郸儋石"};//27
	char PY_mb_dang[]={"当党荡档挡裆铛宕凼菪谠砀"};//12
	char PY_mb_dao[]={"到道导倒岛刀悼盗蹈捣祷叨稻忉帱氘纛焘"};//18
	char PY_mb_de[]={"的得德锝地底"};//6
	char PY_mb_deng[]={"等登灯邓凳瞪蹬噔磴戥镫簦嶝澄"};//14
	char PY_mb_di[]={"地第提底低帝弟敌抵递滴迪蒂堤笛缔涤嘀诋谛狄邸睇嫡翟砥娣棣荻羝坻柢觌骶氐绨镝碲籴"};//39
	char PY_mb_dia[]={"嗲"};//1  
	char PY_mb_dian[]={"点电店典颠甸淀垫殿滇奠惦掂碘癫巅踮佃玷簟阽坫靛钿癜丶"};//26
	char PY_mb_diao[]={"调掉吊雕刁钓凋叼貂碉铫铞鲷鸟"};//14
	char PY_mb_die[]={"爹跌叠迭碟谍蝶喋佚踮牒耋蹀堞瓞揲垤鲽"};//18
	char PY_mb_ding[]={"定订顶丁盯钉鼎叮町铤腚酊仃锭疔啶玎碇耵"};//19
	char PY_mb_diu[]={"丢铥"};//2
	char PY_mb_dong[]={"动东懂冬洞冻董栋咚恫侗氡硐鸫岽垌峒胨胴"};//19
	char PY_mb_dou[]={"都斗豆抖逗兜陡窦蔸蚪篼痘"};//12 
	char PY_mb_du[]={"都读度独毒督渡肚杜睹堵赌妒嘟渎笃牍镀犊黩髑椟芏蠹顿"};//25
	char PY_mb_duan[]={"断段短端锻缎煅椴簖"};//9
	char PY_mb_dui[]={"对队堆兑碓憝怼镦敦"};//9
	char PY_mb_dun[]={"顿盾吨敦蹲钝炖遁盹沌囤墩趸镦礅砘不"};//17
	char PY_mb_duo[]={"多夺朵躲舵堕踱咄跺哆剁惰垛驮掇铎裰哚缍沲柁"};//21
	char PY_mb_e[]={"额俄恶饿哦鹅扼愕遏噩娥峨呃厄鄂讹婀蛾轭颚鳄锷谔屙锇阏垩腭苊鹗萼莪"};//32
	char PY_mb_ei[]={"诶"};//1
	char PY_mb_en[]={"恩摁蒽"};//3
	char PY_mb_er[]={"而二儿尔耳迩饵洱鸸珥铒鲕贰佴"};//14
	char PY_mb_fa[]={"发法罚乏伐阀砝筏垡珐"};//10
	char PY_mb_fan[]={"反饭犯翻范凡烦返番贩繁泛帆藩幡梵樊燔蕃畈钒蘩矾蹯"};//24
	char PY_mb_fang[]={"方放房访防仿芳妨纺彷坊肪舫钫鲂邡枋"};//17
	char PY_mb_fei[]={"非费飞废肥啡沸菲肺匪诽腓扉吠霏绯妃斐翡蜚痱淝悱鲱篚芾狒镄榧"};//29
	char PY_mb_fen[]={"分份纷奋愤粉氛芬坟焚粪忿吩汾棼鼢玢酚偾瀵鲼"};//21
	char PY_mb_feng[]={"风封丰峰疯锋逢奉缝凤讽冯蜂枫烽俸砜唪酆葑沣"};//21
	char PY_mb_fo[]={"佛"};//1
	char PY_mb_fou[]={"否缶"};//2
	char PY_mb_fu[]={"夫府服复父负副福富付妇市附佛幅伏符赴腐浮扶腹抚覆肤赋弗傅辅拂甫俯斧缚咐脯袱俘敷阜芙釜孚腑匐孵辐涪讣氟桴蜉芾苻茯莩菔幞怫拊滏黼艴麸绂绋趺祓砩黻罘蚨跗蝠呋凫郛稃驸赙馥蝮鲋鳆"};//84
	char PY_mb_ga[]={"咖尬嘎噶轧伽旮钆尕尜胳夹呷"};//13
	char PY_mb_gai[]={"改该概盖丐钙赅溉垓陔戤芥"};//12
	char PY_mb_gan[]={"感干敢赶甘肝杆尴赣橄竿秆擀坩苷柑泔矸澉疳酐淦绀旰"};//24
	char PY_mb_gang[]={"刚港钢岗纲缸扛杠冈肛罡戆筻"};//13
	char PY_mb_gao[]={"高告稿搞糕膏皋羔睾槁藁缟篙镐诰槔杲郜锆"};//19
	char PY_mb_ge[]={"个革各歌格哥戈隔葛割阁胳搁疙咯鸽嗝骼颌屹搿膈镉纥袼仡鬲塥圪哿舸铬硌虼蛤盖合"};//37
	char PY_mb_gei[]={"给"};//1
	char PY_mb_gen[]={"根跟亘艮哏茛"};//6
	char PY_mb_geng[]={"更耿耕颈庚羹梗哽赓鲠埂绠"};//12
	char PY_mb_gong[]={"工公共供功攻宫贡恭巩躬龚弓拱肱汞蚣珙觥红"};//20
	char PY_mb_gou[]={"够购构狗沟勾苟句钩觏篝垢佝岣诟鞲笱枸遘媾缑彀"};//22
	char PY_mb_gu[]={"故古顾股鼓姑骨固孤谷估雇辜咕沽箍菇汩轱锢蛊梏鸪毂鹄臌瞽罟钴觚鹘菰蛄嘏诂崮酤牿牯痼鲴贾呱"};//43
	char PY_mb_gua[]={"挂瓜刮寡呱褂卦剐鸹栝胍诖"};//12
	char PY_mb_guai[]={"怪乖拐掴"};//4
	char PY_mb_guan[]={"关观管官馆惯冠贯罐灌棺莞倌纶掼盥涫鳏鹳矜"};//20
	char PY_mb_guang[]={"广光逛犷咣胱桄"};//7
	char PY_mb_gui[]={"规归贵鬼桂跪柜轨瑰诡刽龟硅闺皈傀癸圭晷簋妫鲑匦庋宄炔刿桧炅鳜"};//30
	char PY_mb_gun[]={"滚棍鲧绲磙辊衮"};//7
	char PY_mb_guo[]={"国过果锅郭裹帼蝈聒馘掴埚虢呙崞猓椁蜾涡"};//19
	char PY_mb_ha[]={"哈蛤铪虾"};//4
	char PY_mb_hai[]={"还海孩害嘿咳亥骇骸嗨胲醢氦"};//13
	char PY_mb_han[]={"汉喊含寒汗韩憾涵函翰撼罕旱捍酣悍憨晗瀚鼾顸阚焊蚶焓颔菡撖邗邯"};//30
	char PY_mb_hang[]={"行航巷杭夯沆颃绗珩吭"};//10
	char PY_mb_hao[]={"好号毫豪浩耗皓嚎昊郝壕蒿貉灏镐嗥嚆薅濠蚝颢"};//21
	char PY_mb_he[]={"和何合河喝赫核吓贺盒呵禾荷鹤壑阂褐诃涸阖嗬貉曷颌劾盍纥蚵翮菏"};//30
	char PY_mb_hei[]={"黑嘿嗨"};//3
	char PY_mb_hen[]={"很恨狠痕"};//4
	char PY_mb_heng[]={"行横衡恒哼亨蘅珩桁"};//9
	char PY_mb_hong[]={"红轰洪鸿哄宏虹弘烘泓闳薨讧蕻訇黉荭"};//17
	char PY_mb_hou[]={"后候後厚侯喉吼猴逅糇骺堠瘊篌鲎"};//15
	char PY_mb_hu[]={"乎护呼胡户湖忽互糊虎壶狐沪惚浒唬葫弧蝴囫瑚斛祜猢鹄醐戽扈唿笏琥滹鹕轷烀冱岵怙鹘槲觳瓠鹱煳戏核和"};//47
	char PY_mb_hua[]={"话华化花划画滑哗桦猾砉铧骅豁"};//14
	char PY_mb_huai[]={"怀坏徊淮槐踝划"};//7
	char PY_mb_huan[]={"欢换还环缓患幻唤宦焕痪寰鬟涣浣奂桓缳豢锾郇萑圜洹擐獾漶逭鲩"};//29
	char PY_mb_huang[]={"黄皇荒晃慌煌惶恍谎璜徨簧凰幌潢蝗蟥遑隍肓磺癀湟篁鳇"};//25
	char PY_mb_hui[]={"会回汇挥辉灰惠毁悔恢慧绘徽讳贿徊晦秽诲诙晖彗麾烩荟卉茴喙蛔恚洄珲蕙哕咴浍虺缋桧隳蟪"};//41
	char PY_mb_hun[]={"婚混魂昏浑馄荤诨溷阍珲"};//11
	char PY_mb_huo[]={"和或活火获货伙祸惑霍豁夥锪耠劐钬攉藿嚯镬蠖"};//21
	char PY_mb_ji[]={"几给己机记及计即基济辑级极寄际技集纪击奇系革期其齐急激继既积籍鸡吉挤迹季寂绩疾饥祭缉忌剂圾姬矶肌嫉讥藉叽脊冀稽妓棘骥畸蓟汲悸岌伎笈跻瘠亟诘暨霁羁稷偈戟嵇楫唧鲫髻荠箕觊蒺畿虮齑殛墼佶掎芨丌麂蕺咭嵴芰笄哜洎乩戢屐剞跽玑鲚赍犄"};//110
	char PY_mb_jia[]={"家加价假架甲佳驾夹嫁嘉贾稼茄佼挟颊皎侥枷珈戛迦伽浃痂胛笳荚葭钾镓嘏郏挢岬徼湫敫袈瘕恝铗袷蛱跏"};//46
	char PY_mb_jian[]={"见间件建简坚监减渐检健兼剑艰肩键荐尖鉴剪践奸捡箭舰拣贱溅煎俭槛碱歼缄茧笺柬谏蹇僭涧菅謇硷睑锏饯毽鲣鞯蒹搛谫囝湔缣枧戬戋犍裥笕翦趼楗牮鹣腱踺"};//69
	char PY_mb_jiang[]={"将讲江奖降强虹蒋疆酱姜浆僵匠犟缰绛桨耩礓洚豇茳糨"};//24
	char PY_mb_jiao[]={"教交觉校叫较角脚焦骄郊轿搅嚼胶缴绞饺椒矫娇佼狡浇跤姣窖剿侥皎蕉酵礁鲛徼湫敫僬鹪峤蛟铰艽茭挢噍醮"};//47
	char PY_mb_jie[]={"界解接结节街姐阶介借戒杰届皆捷截洁揭劫竭藉睫诫嗟拮孑碣秸诘桀芥偈颉讦疖疥婕羯鲒蚧骱喈家价桔楷"};//46
	char PY_mb_jin[]={"进今金近尽仅紧禁劲津斤谨锦筋晋巾浸襟瑾矜靳缙烬噤觐馑堇衿荩廑妗卺赆槿"};//34
	char PY_mb_jing[]={"经京精境警竟静惊景敬睛镜竞净井径晶荆兢颈憬靖鲸泾阱儆旌痉迳茎胫腈菁粳獍肼弪婧刭靓"};//40  
	char PY_mb_jiong[]={"窘炯迥扃炅"};//5
	char PY_mb_jiu[]={"就九究酒久旧救纠揪疚舅韭赳鸠灸咎啾臼鹫阄僦厩玖柩桕鬏蹴"};//27
	char PY_mb_ju[]={"局据居句举具剧巨聚拒俱车柜且趄距惧菊拘矩桔驹鞠咀沮瞿锯炬飓趄掬踽踞遽橘倨疽龃屦犋裾钜苴雎鞫椐讵苣锔狙榘莒枸榉窭醵琚"};//57
	char PY_mb_juan[]={"捐卷倦眷娟圈隽绢鹃涓镌锩鄄狷桊蠲"};//16
	char PY_mb_jue[]={"角觉绝决脚嚼掘诀崛爵抉倔獗嗟厥蹶攫谲矍撅噱孓橛噘珏桷劂爝镢蕨觖"};//31
	char PY_mb_jun[]={"军均君俊峻钧隽筠菌郡骏竣麇皲捃浚"};//16
	char PY_mb_ka[]={"咯卡咖喀咔佧胩"};//7
	char PY_mb_kai[]={"开慨凯铠揩楷恺垲蒈锎剀锴忾"};//13
	char PY_mb_kan[]={"看刊侃堪嵌砍坎槛勘瞰龛阚莰戡"};//14
	char PY_mb_kang[]={"抗康慷扛炕亢糠伉闶钪"};//10
	char PY_mb_kao[]={"考靠铐烤拷犒栲尻"};//8
	char PY_mb_ke[]={"可克科客刻课颗渴柯呵棵恪咳苛磕壳坷嗑瞌轲稞疴蝌溘髁钶窠颏珂岢骒缂氪锞蚵"};//35
	char PY_mb_ken[]={"肯恳啃垦龈裉"};//6
	char PY_mb_keng[]={"坑吭铿"};//3
	char PY_mb_kong[]={"空恐控孔倥崆箜"};//7
	char PY_mb_kou[]={"口扣抠寇叩蔻眍芤筘"};//9
	char PY_mb_ku[]={"苦哭库裤酷枯窟骷刳堀喾绔"};//12
	char PY_mb_kua[]={"夸跨垮挎胯侉"};//6
	char PY_mb_kuai[]={"会快块筷脍蒯哙侩狯浍郐"};//11
	char PY_mb_kuan[]={"款宽髋"};//3
	char PY_mb_kuang[]={"况狂矿框旷眶筐匡哐邝诓夼诳圹纩贶"};//16
	char PY_mb_kui[]={"亏愧溃窥魁馈睽盔逵葵奎匮傀喟聩岿馗夔篑喹悝暌隗蒉蝰愦揆跬"};//28
	char PY_mb_kun[]={"困昆捆坤鲲悃髡锟醌阃琨"};//11
	char PY_mb_kuo[]={"括阔扩廓栝蛞适"};//7
	char PY_mb_la[]={"拉啦辣腊喇垃蜡剌邋旯瘌砬蓝落"};//14
	char PY_mb_lai[]={"来赖莱睐癞籁徕涞赉铼崃濑"};//12
	char PY_mb_lan[]={"兰蓝栏烂懒览滥拦篮揽澜榄婪缆斓岚阑褴镧罱谰漤"};//22
	char PY_mb_lang[]={"浪狼朗郎廊琅螂榔啷莨锒稂阆蒗"};//14
	char PY_mb_lao[]={"老劳牢捞姥佬潦唠烙酪涝崂痨醪铹栳铑耢落络"};//20
	char PY_mb_le[]={"了乐勒肋叻泐鳓仂"};//8
	char PY_mb_lei[]={"类泪累雷蕾垒磊勒擂肋儡羸诔镭嘞檑嫘缧酹耒"};//20
	char PY_mb_leng[]={"冷愣楞棱塄"};//5
	char PY_mb_li[]={"里理力利立李历离例礼丽励黎厉璃莉哩笠粒俐漓栗狸梨隶吏沥篱厘犁雳罹莅戾鲤俚砺藜俪蜊黧郦痢枥逦娌詈骊荔鳢喱鹂嫠蠡鬲鲡悝坜苈砾藓呖唳猁溧澧栎轹蓠傈缡疠疬蛎锂篥粝跞醴"};//79
	char PY_mb_lia[]={"俩"};//1
	char PY_mb_lian[]={"联连脸练恋怜莲廉炼帘链敛涟镰殓琏楝裢裣蠊鲢濂臁潋蔹奁"};//26
	char PY_mb_liang[]={"两量良亮辆梁俩凉粮谅粱晾踉莨墚魉椋靓"};//18
	char PY_mb_liao[]={"了料聊疗辽僚廖寥镣潦撩撂缭燎寮嘹钌獠鹩蓼尥"};//21
	char PY_mb_lie[]={"列烈裂劣猎咧趔冽洌捩埒躐鬣"};//13
	char PY_mb_lin[]={"林临邻琳淋拎霖麟凛吝鳞磷躏赁嶙辚檩遴粼蔺懔瞵啉膦廪"};//25
	char PY_mb_ling[]={"领令另灵零龄凌玲铃陵岭拎伶聆囹棱菱翎苓瓴棂绫呤柃鲮酃泠羚蛉"};//29
	char PY_mb_liu[]={"六留流陆刘溜柳碌瘤榴浏硫琉遛馏镏骝绺锍旒熘鎏鹨"};//23
	char PY_mb_long[]={"龙隆笼胧拢咙聋垄珑窿陇癃茏栊泷垅砻弄"};//18
	char PY_mb_lou[]={"楼陋漏搂喽篓偻娄髅蝼镂蒌嵝耧瘘"};//15  
	char PY_mb_lu[]={"六绿路陆录卢露鲁炉鹿碌庐芦噜颅禄辘卤虏麓泸赂漉戮簏轳鹭掳潞鲈撸栌垆胪蓼渌鸬逯璐辂橹镥舻氇"};//44
	char PY_mb_luan[]={"乱卵峦挛孪栾銮娈滦鸾脔"};//11
	char PY_mb_lun[]={"论轮伦沦仑抡囵纶"};//8
	char PY_mb_luo[]={"落罗络洛逻裸骆萝螺锣箩摞烙捋珞骡猡镙椤倮蠃荦瘰泺漯脶硌雒咯"};//29
	char PY_mb_lv[]={"律旅绿率虑履屡侣缕驴吕榈滤捋铝褛闾膂氯稆偻"};//21
	char PY_mb_lue[]={"略掠锊"};//3
	char PY_mb_m[]={"呒"};//1
	char PY_mb_ma[]={"马吗妈码麻骂嘛抹玛蚂蟆唛杩犸嬷摩"};//16
	char PY_mb_mai[]={"买卖麦埋迈脉霾劢荬"};//9
	char PY_mb_man[]={"满慢漫曼蛮馒瞒蔓颟谩墁幔螨鞔鳗缦熳镘埋"};//19
	char PY_mb_mang[]={"忙茫盲芒氓莽蟒邙漭硭"};//10
	char PY_mb_mao[]={"毛冒猫贸矛帽貌茅茂髦卯耄瑁锚懋袤铆峁牦蟊泖昴茆旄蝥瞀"};//26
	char PY_mb_me[]={"么麽"};//2
	char PY_mb_mei[]={"没美每妹眉梅媒枚魅煤昧霉玫媚寐糜袂酶莓嵋楣湄猸镅浼鹛镁"};//27
	char PY_mb_men[]={"们门闷扪懑焖钔"};//7
	char PY_mb_meng[]={"梦蒙猛盟朦孟萌勐懵檬蠓瞢甍礞蜢虻艋艨锰氓"};//20
	char PY_mb_mi[]={"密米秘迷弥谜觅眯蜜靡咪谧泌糜汨宓麋醚弭敉芈祢脒幂縻嘧蘼猕糸"};//29
	char PY_mb_mian[]={"面免棉眠缅绵勉腼冕娩湎沔眄黾渑"};//15
	char PY_mb_miao[]={"妙描秒庙苗渺瞄藐缪淼缈喵眇邈鹋杪"};//16
	char PY_mb_mie[]={"灭蔑篾咩乜蠛"};//6
	char PY_mb_min[]={"民敏悯闽泯珉皿抿闵苠岷缗玟愍黾鳘"};//16
	char PY_mb_ming[]={"名明命鸣铭冥茗溟酩瞑暝螟"};//12  
	char PY_mb_miu[]={"谬缪"};//2
	char PY_mb_mo[]={"默莫模麽末磨摸摩寞漠墨抹魔陌嘿沫膜蓦蘑茉馍摹貉谟嫫秣镆殁瘼耱貊貘"};//32  
	char PY_mb_mou[]={"某谋眸缪鍪哞侔蛑牟"};//9
	char PY_mb_mu[]={"目母木幕姆慕牧墓募暮牟亩穆睦拇沐牡仫坶苜毪钼"};//22  
	char PY_mb_n[]={"嗯唔"};//2
	char PY_mb_na[]={"那拿呢哪纳娜呐捺钠镎肭衲"};//12
	char PY_mb_nai[]={"乃奶奈耐氖艿鼐佴萘柰"};//10  
	char PY_mb_nan[]={"难南男楠喃囡囝腩蝻赧"};//10
	char PY_mb_nang[]={"囊囔馕攮曩"};//5
	char PY_mb_nao[]={"脑闹恼挠瑙淖呶猱铙孬硇蛲垴"};//13
	char PY_mb_ne[]={"呢讷"};//2  
	char PY_mb_nei[]={"内馁"};//2  
	char PY_mb_nen[]={"嫩恁"};//2
	char PY_mb_neng[]={"能"};//1
	char PY_mb_ni[]={"你呢尼泥逆倪匿拟腻妮霓昵溺旎睨鲵坭猊怩伲祢慝铌"};//23
	char PY_mb_nian[]={"年念廿粘碾捻蔫撵拈黏鲶鲇辇埝"};//14
	char PY_mb_niang[]={"娘酿"};//2
	char PY_mb_niao[]={"鸟尿袅嬲茑脲"};//6
	char PY_mb_nie[]={"捏涅聂孽蹑嗫啮镊镍乜陧颞臬蘖"};//14
	char PY_mb_nin[]={"您恁"};//2
	char PY_mb_ning[]={"宁凝拧泞咛狞柠佞聍苎甯"};//11
	char PY_mb_niu[]={"牛纽扭妞钮拗忸狃"};//8
	char PY_mb_nong[]={"农弄浓侬哝脓"};//6
	char PY_mb_nou[]={"耨"};//1
	char PY_mb_nu[]={"怒努奴弩驽胬孥"};//7
	char PY_mb_nuan[]={"暖"};//1
	char PY_mb_nuo[]={"诺挪懦糯喏搦傩锘"};//8  
	char PY_mb_nv[]={"女钕恧衄"};//4
	char PY_mb_nue[]={"虐疟谑"};//2  
	char PY_mb_o[]={"哦噢喔"};//3
	char PY_mb_ou[]={"区欧偶殴呕鸥讴瓯藕沤耦怄"};//11  
	char PY_mb_pa[]={"怕爬帕扒趴啪琶葩耙杷钯筢"};//12
	char PY_mb_pai[]={"派排牌拍徘湃俳蒎哌迫"};//10
	char PY_mb_pan[]={"番判盘盼叛畔潘攀拚蹒磐爿蟠襻袢泮"};//16
	char PY_mb_pang[]={"旁庞胖乓膀磅彷螃滂耪逄"};//11
	char PY_mb_pao[]={"跑炮抛泡袍刨咆狍疱脬庖匏"};//12
	char PY_mb_pei[]={"配陪培佩赔沛裴呸胚醅锫辔帔旆霈"};//15
	char PY_mb_pen[]={"盆喷湓"};//3
	char PY_mb_peng[]={"朋鹏碰彭捧棚蓬膨烹抨篷砰澎怦堋蟛嘭硼"};//18
	char PY_mb_pi[]={"批否皮屁披疲辟啤脾匹僻劈譬坯痞癖琵毗霹噼媲郫裨纰丕鼙圮蚍蜱貔陂陴砒仳埤擗吡庀邳疋芘枇罴淠铍甓睥"};//47
	char PY_mb_pian[]={"便片篇偏骗翩扁犏谝蹁骈缏胼"};//13
	char PY_mb_piao[]={"票漂飘瓢嫖瞟骠嘌剽螵缥莩殍朴"};//14
	char PY_mb_pie[]={"撇瞥氕丿苤"};//5
	char PY_mb_pin[]={"品贫拼频聘拚姘嫔榀颦牝"};//11
	char PY_mb_ping[]={"平评瓶凭萍乒屏苹坪枰娉俜鲆冯"};//14
	char PY_mb_po[]={"破迫颇婆坡泊泼魄粕珀叵攴钷笸钋陂泺鄱皤朴"};//20
	char PY_mb_pou[]={"剖裒掊"};//3
	char PY_mb_pu[]={"普铺扑朴谱浦葡蒲仆脯瀑菩溥匍璞噗圃埔氆镨蹼镤濮莆曝堡暴"};//27
	char PY_mb_qi[]={"起其期气七奇妻企器汽棋齐旗弃启骑欺歧岂戚凄泣契琪乞祈漆迄脐栖沏祺崎祁琦蹊砌憩淇汔亟绮讫嘁岐萋俟杞芪荠耆槭颀芑屺欹桤綮萁蛴蜞綦鳍麒蕲柒亓骐葺畦圻碛稽缉"};//74
	char PY_mb_qia[]={"恰洽掐伽袷葜髂"};//7
	char PY_mb_qian[]={"前钱千签欠牵浅潜迁谦遣歉纤嵌乾谴铅虔钳骞倩堑黔掮悭芊缱愆荨芡阡佥搴褰肷钎仟犍钤岍箝鬈扦慊椠"};//45
	char PY_mb_qiang[]={"强枪墙抢腔呛锵跄羌蔷戕襁樯炝蜣嫱锖戗羟镪将"};//21
	char PY_mb_qiao[]={"桥悄乔巧侨瞧敲翘俏窍峭锹撬跷憔樵鞘橇诮愀谯荞峤缲硗鞒劁"};//27  
	char PY_mb_qie[]={"切且窃怯茄趄妾砌惬伽锲挈郄箧慊"};//15
	char PY_mb_qin[]={"亲钦琴侵秦勤芹擒寝覃沁禽噙揿檎锓芩嗪螓衾廑溱吣矜"};//24
	char PY_mb_qing[]={"情请青清轻晴庆倾卿擎顷氢罄蜻磬謦苘圊檠黥鲭氰箐綮"};//24  
	char PY_mb_qiong[]={"穷琼穹茕邛蛩筇跫銎"};//9
	char PY_mb_qiu[]={"求球秋邱囚丘酋蚯裘俅虬鳅逑遒赇泅楸犰湫蝤巯鼽糗仇龟"};//25
	char PY_mb_qu[]={"去取区曲趣屈趋驱渠躯娶觑瞿岖戌蛐衢蛆癯麴阒祛磲鸲诎蠼劬蕖蘧龋苣黢璩氍朐"};//35
	char PY_mb_quan[]={"全权圈劝泉券拳犬诠颧蜷绻荃铨痊鬈辁悛畎醛筌"};//21
	char PY_mb_que[]={"却确缺雀瘸榷鹊阕阙炔悫"};//11
	char PY_mb_qun[]={"群裙逡麇"};//4
	char PY_mb_ran[]={"然染燃冉髯苒蚺"};//7
	char PY_mb_rang[]={"让嚷攘壤瓤穰禳"};//7
	char PY_mb_rao[]={"扰绕饶娆桡荛"};//6
	char PY_mb_re[]={"热惹喏若"};//4
	char PY_mb_ren[]={"人任认忍仁韧刃纫饪壬仞稔葚荏妊轫衽"};//17
	char PY_mb_reng[]={"仍扔"};//2
	char PY_mb_ri[]={"日"};//1
	char PY_mb_rong[]={"容荣融蓉溶绒熔榕戎嵘茸冗肜蝾狨"};//15
	char PY_mb_rou[]={"肉柔揉蹂鞣糅"};//6
	char PY_mb_ru[]={"如入辱儒乳汝褥嚅茹濡蠕孺缛襦颥薷蓐洳溽铷"};//20
	char PY_mb_ruan[]={"软阮朊"};//3
	char PY_mb_rui[]={"瑞锐芮睿蕤枘蕊蚋"};//8
	char PY_mb_run[]={"润闰"};//2
	char PY_mb_ruo[]={"若弱偌箬"};//4
	char PY_mb_sa[]={"洒撒萨卅仨飒挲脎"};//8
	char PY_mb_sai[]={"赛塞腮噻思鳃"};//6
	char PY_mb_san[]={"三散伞叁毵馓糁霰"};//8
	char PY_mb_sang[]={"丧桑嗓搡磉颡"};//6
	char PY_mb_sao[]={"扫骚嫂梢臊搔缲缫鳋埽瘙"};//11
	char PY_mb_se[]={"色塞涩瑟啬铯穑"};//7
	char PY_mb_sen[]={"森"};//1
	char PY_mb_seng[]={"僧"};//1
	char PY_mb_sha[]={"杀沙啥傻厦刹纱莎煞砂杉霎嗄挲歃鲨唼痧裟铩"};//20
	char PY_mb_shai[]={"晒筛酾色"};//4
	char PY_mb_shan[]={"山善闪衫删煽扇陕珊杉擅单掺膳栅讪跚汕姗赡潸缮嬗掸膻骟芟埏剡钐鄯舢苫髟疝蟮鳝"};//37
	char PY_mb_shang[]={"上商伤尚赏殇裳晌觞熵墒绱垧汤"};//14
	char PY_mb_shao[]={"少绍烧稍勺哨邵梢捎韶苕鞘潲劭杓芍蛸筲艄"};//19
	char PY_mb_she[]={"社设舍涉射摄舌折蛇奢赦慑佘赊麝畲厍滠歙猞"};//20
	char PY_mb_shei[]={"谁"};//1
	char PY_mb_shen[]={"什身深神参甚申审沈伸慎渗绅肾呻婶莘蜃葚娠渖矧诜砷糁谂椹胂哂"};//29
	char PY_mb_sheng[]={"生声省胜升圣乘盛剩牲绳甥笙渑眚嵊晟"};//17
	char PY_mb_shi[]={"是时十事实使世市识始士师诗式失什似殖史视示食室势试石释施适氏驶饰尸拾逝湿誓狮嗜蚀嘘屎侍匙峙仕恃柿轼矢噬拭虱弑蓍埘莳炻谥鲥豕贳铈螫舐筮鲺酾"};//68
	char PY_mb_shou[]={"手受收首授守售瘦寿兽狩绶艏熟"};//14
	char PY_mb_shu[]={"书数术属输树述熟束署殊舒叔鼠疏淑抒薯梳暑竖蜀恕墅孰漱枢俞赎黍蔬曙倏庶戍塾澍姝纾秫毹殳疋菽丨沭摅腧"};//48
	char PY_mb_shua[]={"刷耍唰"};//3
	char PY_mb_shuai[]={"率衰摔甩帅蟀"};//6
	char PY_mb_shuan[]={"涮栓拴闩"};//4
	char PY_mb_shuang[]={"双爽霜孀泷"};//5
	char PY_mb_shui[]={"水谁税睡说"};//5
	char PY_mb_shun[]={"顺舜瞬吮"};//4
	char PY_mb_shuo[]={"说数朔硕烁铄妁蒴槊搠"};//10
	char PY_mb_si[]={"四死思斯司似私丝寺厕食撕肆厮嘶伺饲嗣祀巳驷鸶俟汜泗厶兕蛳咝姒澌缌耜笥锶"};//35
	char PY_mb_song[]={"送松宋诵耸颂讼悚怂忪淞菘崧嵩凇竦"};//16
	char PY_mb_sou[]={"搜艘嗽擞馊薮嗾叟嗖溲飕锼瞍螋"};//14
	char PY_mb_su[]={"苏诉速素俗肃缩宿塑稣溯酥粟簌夙嗉谡僳愫涑蔌觫"};//22
	char PY_mb_suan[]={"算酸蒜狻"};//4
	char PY_mb_sui[]={"岁随虽碎遂祟隧髓邃穗隋绥睢荽燧谇眭濉尿"};//19
	char PY_mb_sun[]={"孙损笋荪狲飧榫隼"};//8
	char PY_mb_suo[]={"所索缩锁琐梭嗦唆挲娑睃唢嗍蓑羧桫莎"};//17
	char PY_mb_ta[]={"他她它踏塔塌榻嗒蹋沓遢挞鳎闼铊趿漯溻獭拓"};//20
	char PY_mb_tai[]={"太台态泰抬胎汰苔呔鲐邰薹酞骀炱跆肽钛"};//18
	char PY_mb_tan[]={"谈探弹坦叹坛摊贪滩毯谭潭瘫炭覃痰忐坍袒碳澹檀昙镡郯锬钽"};//27
	char PY_mb_tang[]={"堂唐汤躺糖趟倘烫淌膛塘棠搪溏螳瑭樘螗铴醣镗耥饧傥帑羰"};//26
	char PY_mb_tao[]={"讨套逃涛掏陶桃淘滔萄焘啕韬饕洮绦鼗叨"};//18
	char PY_mb_te[]={"特忑忒慝铽"};//5
	char PY_mb_tei[]={"忒"};//1
	char PY_mb_teng[]={"腾疼藤誊滕"};//5
	char PY_mb_ti[]={"体提题替踢梯啼涕蹄剔剃惕屉嚏悌醍缇鹈锑荑倜绨逖裼"};//24
	char PY_mb_tian[]={"天田填甜添腆舔恬钿阗畋忝殄掭佃"};//15
	char PY_mb_tiao[]={"条调跳挑迢眺鲦佻苕窕髫粜笤龆祧蜩"};//16
	char PY_mb_tie[]={"铁贴帖餮萜"};//5
	char PY_mb_ting[]={"听停庭厅挺亭婷廷艇町霆汀铤蜓莛梃葶烃"};//18
	char PY_mb_tong[]={"同通统痛童彤筒铜桶捅桐瞳佟恸酮恫侗砼嗵仝垌茼峒潼"};//24
	char PY_mb_tou[]={"头投偷透钭骰"};//6
	char PY_mb_tu[]={"土突图途徒屠涂吐兔秃凸荼酴钍菟堍"};//16
	char PY_mb_tuan[]={"团湍抟疃彖"};//5
	char PY_mb_tui[]={"推退腿褪颓蜕忒煺"};//8
	char PY_mb_tun[]={"吞屯饨褪臀囤豚暾氽"};//9
	char PY_mb_tuo[]={"托脱拖妥拓陀驼唾椭砣驮沱跎坨鸵乇鼍橐佗庹铊酡柁柝箨"};//25
	char PY_mb_wa[]={"瓦挖袜娃哇凹娲蛙洼佤腽"};//11
	char PY_mb_wai[]={"外歪崴"};//3
	char PY_mb_wan[]={"万完晚湾玩碗弯挽娩蔓顽腕婉惋宛丸蜿莞畹剜豌皖纨琬脘烷芄菀绾"};//29
	char PY_mb_wang[]={"望王往网忘亡汪旺枉妄惘罔尢辋魍"};//15
	char PY_mb_wei[]={"为位未委维味围卫威微伟谓唯危慰尾违魏玮蔚伪畏胃喂炜韦惟巍纬萎娓苇尉帷渭猥偎薇痿猬逶帏韪煨鲔桅潍隈圩囗诿隗崴洧葳嵬闱沩涠艉軎"};//61
	char PY_mb_wen[]={"文问闻温稳吻纹蚊雯紊瘟汶刎阌璺"};//15
	char PY_mb_weng[]={"翁瓮嗡蓊蕹"};//5  
	char PY_mb_wo[]={"我握窝卧渥沃涡斡蜗幄喔倭挝莴肟硪龌"};//17
	char PY_mb_wu[]={"无五物务武午舞於误恶吴屋伍悟吾污乌雾侮捂巫毋呜诬勿梧坞戊兀唔晤芜鹜钨妩痦鹉忤寤骛邬牾鼯圬浯仵阢芴庑婺怃杌焐蜈迕鋈"};//56
	char PY_mb_xi[]={"西系息希喜席习细戏吸洗惜稀悉析夕牺袭昔熙兮溪隙嘻锡晰媳樨熄膝郗犀禧曦奚羲蹊唏淅嬉皙汐徙茜玺熹烯翕蟋屣檄浠僖穸蜥隰觋螅铣菥葸蓰舾矽粞硒醯欷鼷歙饩阋禊舄腊栖裼"};//77
	char PY_mb_xia[]={"下夏吓峡厦侠狭霞瞎暇虾唬辖遐匣黠瑕呷狎柙硖瘕罅"};//23
	char PY_mb_xian[]={"现先显线险限县鲜献闲宪陷贤仙嫌咸羡掀弦纤娴衔馅涎舷腺跣暹岘猃蚬筅跹莶锨鹇痫铣氙祆籼冼藓酰苋燹霰见"};//48
	char PY_mb_xiang[]={"想相向象香乡像响项享降箱详祥巷厢湘橡翔镶飨襄饷骧葙庠鲞芗缃蟓"};//30
	char PY_mb_xiao[]={"小笑校消效晓销潇肖萧孝宵削嚣啸逍硝霄淆哮枭骁箫筱哓枵绡魈蛸崤"};//30
	char PY_mb_xie[]={"些写谢协鞋携斜泄胁歇谐邪械叶契解血屑卸挟懈泻亵蟹偕邂榭撷楔瀣蝎颉勰薤燮躞缬獬绁廨榍渫"};//42
	char PY_mb_xin[]={"心新信欣辛薪馨鑫芯衅昕忻锌歆镡囟寻莘"};//18
	char PY_mb_xing[]={"行性形兴星型姓幸刑醒腥杏悻惺邢猩荇擤荥饧硎陉"};//22
	char PY_mb_xiong[]={"雄兄胸凶熊匈汹芎"};//8
	char PY_mb_xiu[]={"修休秀袖宿臭羞绣朽锈嗅咻貅髹馐庥鸺岫溴"};//19
	char PY_mb_xu[]={"许续需须徐序虚绪吁蓄叙畜嘘恤絮浒墟旭婿栩戌诩胥酗煦砉盱糈醑顼勖洫溆圩蓿"};//35
	char PY_mb_xuan[]={"选宣旋悬券喧轩玄炫渲绚眩萱漩暄璇谖铉儇痃泫煊楦癣碹揎镟"};//27
	char PY_mb_xue[]={"学血雪削穴谑靴薛踅噱泶鳕"};//12
	char PY_mb_xun[]={"寻询训迅讯巡逊循旬熏勋驯荤殉醺巽徇埙荀峋洵薰汛郇曛窨恂獯浔鲟蕈浚"};//32
	char PY_mb_ya[]={"亚压雅牙呀押涯讶鸦哑鸭崖丫芽衙轧痖睚娅蚜伢疋岈琊垭揠迓桠氩砑"};//30
	char PY_mb_yan[]={"眼言严演研烟验延沿掩颜厌炎燕阎宴盐咽岩雁焰艳焉淹衍阉奄谚俨檐蜒彦腌焱晏唁妍砚嫣胭湮筵堰赝餍鼹芫偃魇闫崦厣剡恹阏兖郾琰罨鄢谳滟阽鼽酽菸"};//66   
	char PY_mb_yang[]={"样洋阳央杨养扬仰羊痒漾泱氧鸯秧殃恙疡烊佯鞅怏徉炀蛘"};//25
	char PY_mb_yao[]={"要摇药耀遥邀腰姚咬尧谣瑶窑夭肴妖吆钥侥杳窈鹞曜舀铫幺爻徭繇鳐珧轺崾疟陶约"};//36
	char PY_mb_ye[]={"也业夜爷叶野页液耶咽曳拽揶噎烨冶椰掖腋谒邺靥晔铘"};//24
	char PY_mb_yi[]={"一以意已义议医易衣艺依译移异益亦亿疑遗忆宜椅伊仪谊抑翼矣役艾乙溢毅蛇裔逸姨夷轶怡蚁弈倚翌颐疫绎彝咦佚奕熠贻漪诣迤弋懿呓驿咿揖旖屹痍薏噫镒刈沂臆缢邑胰猗羿钇舣劓仡酏佾埸诒圯荑壹挹嶷饴嗌峄怿悒铱欹殪黟苡肄镱瘗癔翊蜴眙翳蛾食尾"};//110
	char PY_mb_yin[]={"因音引印银隐饮阴姻瘾吟寅殷淫茵荫尹蚓垠喑湮胤鄞氤霪圻铟狺吲夤堙龈洇茚窨"};//35
	char PY_mb_ying[]={"应英影营迎硬映赢盈颖鹰婴蝇樱莹荧膺萤萦莺罂瀛楹缨颍嬴鹦瑛茔嘤璎荥撄郢瘿蓥滢潆媵"};//39
	char PY_mb_yo[]={"哟唷育"};//3
	char PY_mb_yong[]={"用永拥勇涌踊泳庸佣咏俑雍恿甬臃邕镛痈壅鳙饔喁墉蛹慵"};//25
	char PY_mb_you[]={"有又由友游右油优邮幽尤忧犹悠幼诱佑黝攸呦酉柚鱿莠囿鼬铀卣猷牖铕疣蚰蝣釉蝤繇莜侑莸宥蚴尢"};//43
	char PY_mb_yu[]={"于与语育余遇狱雨於欲预予鱼玉愈域誉吁宇寓豫愚舆粥郁喻羽娱裕愉禹浴馀御逾渔渝俞萸瑜隅驭迂揄圄谕榆屿淤毓虞禺谀妪腴峪竽芋妤臾欤龉觎盂昱煜熨燠窬蝓嵛狳伛俣舁圉庾菀蓣饫阈鬻瘐窳雩瘀纡聿钰鹆鹬蜮谷蔚尉"};//95
	char PY_mb_yuan[]={"员元原院远愿园源圆怨缘援冤袁渊苑猿鸳辕垣媛沅橼芫爰螈鼋眢圜鸢箢塬垸掾瑗"};//35
	char PY_mb_yue[]={"月乐越约阅跃曰说悦岳粤钥刖瀹栎樾龠钺"};//18
	char PY_mb_yun[]={"运云允韵晕孕匀员蕴酝筠芸耘陨纭殒愠氲狁熨郓恽昀韫郧"};//25
	char PY_mb_za[]={"杂扎砸咋咂匝拶咱"};//8
	char PY_mb_zai[]={"在再载灾仔宰哉栽崽甾"};//10
	char PY_mb_zan[]={"咱赞暂攒簪糌瓒拶昝趱錾"};//11
	char PY_mb_zang[]={"藏脏葬赃臧锗奘驵"};//8
	char PY_mb_zao[]={"早造遭糟澡灶躁噪凿枣皂燥蚤藻缲唣"};//16
	char PY_mb_ze[]={"则责泽择咋啧仄迮笮箦舴帻赜昃侧"};//15
	char PY_mb_zei[]={"贼"};//1
	char PY_mb_zen[]={"怎谮"};//2
	char PY_mb_zeng[]={"综曾增赠憎缯罾甑锃"};//7   少“综、曾”
	char PY_mb_zha[]={"炸扎咋诈乍眨渣札栅轧闸榨喳揸柞楂哳吒铡砟齄咤痄蚱猹查蜡喋"};//27
	char PY_mb_zhai[]={"摘债宅窄斋寨翟砦瘵择侧祭"};//12
	char PY_mb_zhan[]={"战展站占沾斩颤辗粘盏崭瞻绽蘸湛詹毡栈谵搌旃"};//21
	char PY_mb_zhang[]={"长张章丈掌涨帐障账胀仗杖彰璋蟑樟瘴漳嶂鄣獐仉幛嫜"};//24
	char PY_mb_zhao[]={"着找照招朝赵召罩兆昭肇沼诏钊啁棹笊爪嘲"};//19
	char PY_mb_zhe[]={"这着者折哲浙遮辙辄谪蔗蛰褶鹧锗磔摺蜇赭柘"};//20
	char PY_mb_zhen[]={"真阵镇震针珍圳振诊枕斟贞侦赈甄臻箴疹砧桢缜畛轸胗稹祯浈溱蓁椹榛朕鸩"};//33
	char PY_mb_zheng[]={"政正证整争征挣郑症睁徵蒸怔筝拯铮峥狰诤鲭钲帧丁"};//23
	char PY_mb_zhi[]={"之只知至制直治指支志职致值织纸止质执智置址枝秩植旨滞徵帜稚挚汁掷殖芝吱肢脂峙侄窒蜘趾炙痔咫芷栉枳踯桎帙栀祉轾贽痣豸卮轵埴陟郅黹忮彘骘酯摭絷跖膣雉鸷胝蛭踬祗觯抵识氏"};//81
	char PY_mb_zhong[]={"中种重众终钟忠衷肿仲锺踵盅冢忪舯螽"};//17
	char PY_mb_zhou[]={"周州洲粥舟皱骤轴宙咒昼肘帚胄纣诌绉妯碡啁荮籀繇酎"};//24
	char PY_mb_zhu[]={"主住注助著逐诸朱驻珠祝猪筑竹煮嘱柱烛铸株瞩蛛伫拄贮洙诛褚铢箸蛀茱炷躅竺杼翥渚潴麈槠橥苎侏瘃疰邾舳鹘属术"};//51
	char PY_mb_zhua[]={"抓爪挝"};//3
	char PY_mb_zhuai[]={"拽嘬"};//2
	char PY_mb_zhuan[]={"传专转赚撰砖篆啭馔颛沌"};//11
	char PY_mb_zhuang[]={"装状壮庄撞妆幢桩奘僮戆"};//11
	char PY_mb_zhui[]={"追坠缀锥赘隹椎惴骓缒"};//10
	char PY_mb_zhun[]={"准谆窀肫屯"};//5
	char PY_mb_zhuo[]={"着桌捉卓琢灼酌拙浊濯茁啄斫镯涿焯浞倬禚诼擢缴"};//22
	char PY_mb_zi[]={"子自字资咨紫滋仔姿吱兹孜梓渍籽姊恣滓谘龇秭呲辎锱眦笫髭淄茈觜訾缁耔鲻嵫赀孳粢趑"};//39
	char PY_mb_zong[]={"总宗纵踪综棕粽鬃偬腙枞"};//11
	char PY_mb_zou[]={"走奏邹揍驺鲰诹陬鄹"};//9
	char PY_mb_zu[]={"组足族祖租阻卒诅俎镞菹"};//11
	char PY_mb_zuan[]={"赚钻攥纂躜缵"};//6
	char PY_mb_zui[]={"最罪嘴醉咀觜蕞堆"};//8
	char PY_mb_zun[]={"尊遵樽鳟撙"};//5
	char PY_mb_zuo[]={"作做坐座左昨琢佐凿撮柞嘬怍胙唑笮阼祚酢"};//19
	char PY_mb_space[] ={""};

	struct PY_index PY_index_a[]=
	{          {"",PY_mb_a},
		{"i",PY_mb_ai},
		{"n",PY_mb_an},
		{"ng",PY_mb_ang},
		{"o",PY_mb_ao}
	};
	struct PY_index PY_index_b[]=
	{          {"",PY_mb_ba},
		{"a",PY_mb_ba},
		{"ai",PY_mb_bai},
		{"an",PY_mb_ban},
		{"ang",PY_mb_bang},
		{"ao",PY_mb_bao},
		{"ei",PY_mb_bei},
		{"en",PY_mb_ben},
		{"eng",PY_mb_beng},
		{"i",PY_mb_bi},
		{"ian",PY_mb_bian},
		{"iao",PY_mb_biao},
		{"ie",PY_mb_bie},
		{"in",PY_mb_bin},
		{"ing",PY_mb_bing},
		{"o",PY_mb_bo},
		{"u",PY_mb_bu}
	};
	struct PY_index PY_index_c[]=
	{          {"",PY_mb_ca},
		{"a",PY_mb_ca},
		{"ai",PY_mb_cai},
		{"an",PY_mb_can},
		{"ang",PY_mb_cang},
		{"ao",PY_mb_cao},
		{"e",PY_mb_ce},
                {"en",PY_mb_cen},
		{"eng",PY_mb_ceng},
		{"ha",PY_mb_cha},
		{"hai",PY_mb_chai},
		{"han",PY_mb_chan},
		{"hang",PY_mb_chang},
		{"hao",PY_mb_chao},
		{"he",PY_mb_che},
		{"hen",PY_mb_chen},
		{"heng",PY_mb_cheng},
		{"hi",PY_mb_chi},
		{"hong",PY_mb_chong},
		{"hou",PY_mb_chou},
		{"hu",PY_mb_chu},
		{"huai",PY_mb_chuai},
		{"huan",PY_mb_chuan},
		{"huang",PY_mb_chuang},
		{"hui",PY_mb_chui},
		{"hun",PY_mb_chun},
		{"huo",PY_mb_chuo},
		{"i",PY_mb_ci},
		{"ong",PY_mb_cong},
		{"ou",PY_mb_cou},
		{"u",PY_mb_cu},
		{"uan",PY_mb_cuan},
		{"ui",PY_mb_cui},
		{"un",PY_mb_cun},
		{"uo",PY_mb_cuo}
	};
	struct PY_index PY_index_d[]=
	{          {"",PY_mb_da},
		{"a",PY_mb_da},
		{"ai",PY_mb_dai},
		{"an",PY_mb_dan},
		{"ang",PY_mb_dang},
		{"ao",PY_mb_dao},
		{"e",PY_mb_de},
		{"eng",PY_mb_deng},
		{"i",PY_mb_di},
		{"ian",PY_mb_dian},
		{"iao",PY_mb_diao},
		{"ie",PY_mb_die},
		{"ing",PY_mb_ding},
		{"iu",PY_mb_diu},
		{"ong",PY_mb_dong},
		{"ou",PY_mb_dou},
		{"u",PY_mb_du},
		{"uan",PY_mb_duan},
		{"ui",PY_mb_dui},
		{"un",PY_mb_dun},
		{"uo",PY_mb_duo}
	};
	struct PY_index PY_index_e[]=
	{          {"",PY_mb_e},
		{"n",PY_mb_en},
		{"r",PY_mb_er}
	};
	struct PY_index PY_index_f[]=
	{          {"",PY_mb_fa},
		{"a",PY_mb_fa},
		{"an",PY_mb_fan},
		{"ang",PY_mb_fang},
		{"ei",PY_mb_fei},
		{"en",PY_mb_fen},
		{"eng",PY_mb_feng},
		{"o",PY_mb_fo},
		{"ou",PY_mb_fou},
		{"u",PY_mb_fu}
	};
	struct PY_index PY_index_g[]=
	{          {"",PY_mb_ga},
		{"a",PY_mb_ga},
		{"ai",PY_mb_gai},
		{"an",PY_mb_gan},
		{"ang",PY_mb_gang},
		{"ao",PY_mb_gao},
		{"e",PY_mb_ge},
		{"ei",PY_mb_gei},
		{"en",PY_mb_gen},
		{"eng",PY_mb_geng},
		{"ong",PY_mb_gong},
		{"ou",PY_mb_gou},
		{"u",PY_mb_gu},
		{"ua",PY_mb_gua},
		{"uai",PY_mb_guai},
		{"uan",PY_mb_guan},
		{"uang",PY_mb_guang},
		{"ui",PY_mb_gui},
		{"un",PY_mb_gun},
		{"uo",PY_mb_guo}
	};
	struct PY_index PY_index_h[]=
	{          {"",PY_mb_ha},
		{"a",PY_mb_ha},
		{"ai",PY_mb_hai},
		{"an",PY_mb_han},
		{"ang",PY_mb_hang},
		{"ao",PY_mb_hao},
		{"e",PY_mb_he},
		{"ei",PY_mb_hei},
		{"en",PY_mb_hen},
		{"eng",PY_mb_heng},
		{"ong",PY_mb_hong},
		{"ou",PY_mb_hou},
		{"u",PY_mb_hu},
		{"ua",PY_mb_hua},
		{"uai",PY_mb_huai},
		{"uan",PY_mb_huan},
		{"uang ",PY_mb_huang},
		{"ui",PY_mb_hui},
		{"un",PY_mb_hun},
		{"uo",PY_mb_huo}
	};
	struct PY_index PY_index_i[]={          {"",PY_mb_space}};
	struct PY_index PY_index_j[]=
	{          {"",PY_mb_ji},
		{"i",PY_mb_ji},
		{"ia",PY_mb_jia},
		{"ian",PY_mb_jian},
		{"iang",PY_mb_jiang},
		{"iao",PY_mb_jiao},
		{"ie",PY_mb_jie},
		{"in",PY_mb_jin},
		{"ing",PY_mb_jing},
		{"iong",PY_mb_jiong},
		{"iu",PY_mb_jiu},
		{"u",PY_mb_ju},
		{"uan",PY_mb_juan},
		{"ue",PY_mb_jue},
		{"un",PY_mb_jun}
	};
	struct PY_index PY_index_k[]=
	{          {"",PY_mb_ka},
		{"a",PY_mb_ka},
		{"ai",PY_mb_kai},
		{"an",PY_mb_kan},
		{"ang",PY_mb_kang},
		{"ao",PY_mb_kao},
		{"e",PY_mb_ke},
		{"en",PY_mb_ken},
		{"eng",PY_mb_keng},
		{"ong",PY_mb_kong},
		{"ou",PY_mb_kou},
		{"u",PY_mb_ku},
		{"ua",PY_mb_kua},
		{"uai",PY_mb_kuai},
		{"uan",PY_mb_kuan},
		{"uang",PY_mb_kuang},
		{"ui",PY_mb_kui},
		{"un",PY_mb_kun},
		{"uo",PY_mb_kuo}
	};
	struct PY_index PY_index_l[]=
	{          {"",PY_mb_la},
		{"a",PY_mb_la},
		{"ai",PY_mb_lai},
		{"an",PY_mb_lan},
		{"ang",PY_mb_lang},
		{"ao",PY_mb_lao},
		{"e",PY_mb_le},
		{"ei",PY_mb_lei},
		{"eng",PY_mb_leng},
		{"i",PY_mb_li},
		{"ian",PY_mb_lian},
		{"iang",PY_mb_liang},
		{"iao",PY_mb_liao},
		{"ie",PY_mb_lie},
		{"in",PY_mb_lin},
		{"ing",PY_mb_ling},
		{"iu",PY_mb_liu},
		{"ong",PY_mb_long},
		{"ou",PY_mb_lou},
		{"u",PY_mb_lu},
		{"uan",PY_mb_luan},
		{"ue",PY_mb_lue},
		{"un",PY_mb_lun},
		{"uo",PY_mb_luo},
		{"v",PY_mb_lv}
	};
	struct PY_index PY_index_m[]=
	{          {"",PY_mb_ma},
		{"a",PY_mb_ma},
		{"ai",PY_mb_mai},
		{"an",PY_mb_man},
		{"ang",PY_mb_mang},
		{"ao",PY_mb_mao},
		{"e",PY_mb_me},
		{"ei",PY_mb_mei},
		{"en",PY_mb_men},
		{"eng",PY_mb_meng},
		{"i",PY_mb_mi},
		{"ian",PY_mb_mian},
		{"iao",PY_mb_miao},
		{"ie",PY_mb_mie},
		{"in",PY_mb_min},
		{"ing",PY_mb_ming},
		{"iu",PY_mb_miu},
		{"o",PY_mb_mo},
		{"ou",PY_mb_mou},
		{"u",PY_mb_mu}
	};
	struct PY_index PY_index_n[]=
	{          {"",PY_mb_na},
		{"a",PY_mb_na},
		{"ai",PY_mb_nai},
		{"an",PY_mb_nan},
		{"ang",PY_mb_nang},
		{"ao",PY_mb_nao},
		{"e",PY_mb_ne},
		{"ei",PY_mb_nei},
		{"en",PY_mb_nen},
		{"eng",PY_mb_neng},
		{"i",PY_mb_ni},
		{"ian",PY_mb_nian},
		{"iang",PY_mb_niang},
		{"iao",PY_mb_niao},
		{"ie",PY_mb_nie},
		{"in",PY_mb_nin},
		{"ing",PY_mb_ning},
		{"iu",PY_mb_niu},
		{"ong",PY_mb_nong},
		{"u",PY_mb_nu},
		{"uan",PY_mb_nuan},
		{"ue",PY_mb_nue},
		{"uo",PY_mb_nuo},
		{"v",PY_mb_nv}
	};
	struct PY_index PY_index_o[]=
	{          {"",PY_mb_o},
		{"u",PY_mb_ou}
	};
	struct PY_index PY_index_p[]=
	{          {"",PY_mb_pa},
		{"a",PY_mb_pa},
		{"ai",PY_mb_pai},
		{"an",PY_mb_pan},
		{"ang",PY_mb_pang},
		{"ao",PY_mb_pao},
		{"ei",PY_mb_pei},
		{"en",PY_mb_pen},
		{"eng",PY_mb_peng},
		{"i",PY_mb_pi},
		{"ian",PY_mb_pian},
		{"iao",PY_mb_piao},
		{"ie",PY_mb_pie},
		{"in",PY_mb_pin},
		{"ing",PY_mb_ping},
		{"o",PY_mb_po},
		{"ou",PY_mb_pou},
		{"u",PY_mb_pu}
	};
	struct PY_index PY_index_q[]=
	{          {"",PY_mb_qi},
		{"i",PY_mb_qi},
		{"ia",PY_mb_qia},
		{"ian",PY_mb_qian},
		{"iang",PY_mb_qiang},
		{"iao",PY_mb_qiao},
		{"ie",PY_mb_qie},
		{"in",PY_mb_qin},
		{"ing",PY_mb_qing},
		{"iong",PY_mb_qiong},
		{"iu",PY_mb_qiu},
		{"u",PY_mb_qu},
		{"uan",PY_mb_quan},
		{"ue",PY_mb_que},
		{"un",PY_mb_qun}
	};
	struct PY_index PY_index_r[]=
	{          {"",PY_mb_ran},
		{"an",PY_mb_ran},
		{"ang",PY_mb_rang},
		{"ao",PY_mb_rao},
		{"e",PY_mb_re},
		{"en",PY_mb_ren},
		{"eng",PY_mb_reng},
		{"i",PY_mb_ri},
		{"ong",PY_mb_rong},
		{"ou",PY_mb_rou},
		{"u",PY_mb_ru},
		{"uan",PY_mb_ruan},
		{"ui",PY_mb_rui},
		{"un",PY_mb_run},
		{"uo",PY_mb_ruo}
	};
	struct PY_index PY_index_s[]=
	{          {"",PY_mb_sa},
		{"a",PY_mb_sa},
		{"ai",PY_mb_sai},
		{"an",PY_mb_san},
		{"ang",PY_mb_sang},
		{"ao",PY_mb_sao},
		{"e",PY_mb_se},
		{"en",PY_mb_sen},
		{"eng",PY_mb_seng},
		{"ha",PY_mb_sha},
		{"hai",PY_mb_shai},
		{"han",PY_mb_shan},
		{"hang ",PY_mb_shang},
		{"hao",PY_mb_shao},
		{"he",PY_mb_she},
		{"hei",PY_mb_shei},
		{"hen",PY_mb_shen},
		{"heng",PY_mb_sheng},
		{"hi",PY_mb_shi},
		{"hou",PY_mb_shou},
		{"hu",PY_mb_shu},
		{"hua",PY_mb_shua},
		{"huai",PY_mb_shuai},
		{"huan",PY_mb_shuan},
		{"huang",PY_mb_shuang},
		{"hui",PY_mb_shui},
		{"hun",PY_mb_shun},
		{"huo",PY_mb_shuo},
		{"i",PY_mb_si},
		{"ong",PY_mb_song},
		{"ou",PY_mb_sou},
		{"u",PY_mb_su},
		{"uan",PY_mb_suan},
		{"ui",PY_mb_sui},
		{"un",PY_mb_sun},
		{"uo",PY_mb_suo}
	};
	struct PY_index PY_index_t[]=
	{          {"",PY_mb_ta},
		{"a",PY_mb_ta},
		{"ai",PY_mb_tai},
		{"an",PY_mb_tan},
		{"ang",PY_mb_tang},
		{"ao",PY_mb_tao},
		{"e",PY_mb_te},
		{"ei",PY_mb_tei},
		{"eng",PY_mb_teng},
		{"i",PY_mb_ti},
		{"ian",PY_mb_tian},
		{"iao",PY_mb_tiao},
		{"ie",PY_mb_tie},
		{"ing",PY_mb_ting},
		{"ong",PY_mb_tong},
		{"ou",PY_mb_tou},
		{"u",PY_mb_tu},
		{"uan",PY_mb_tuan},
		{"ui",PY_mb_tui},
		{"un",PY_mb_tun},
		{"uo",PY_mb_tuo}
	};
	struct PY_index PY_index_u[]={          {"",PY_mb_space}};
	struct PY_index PY_index_v[]={          {"",PY_mb_space}};
	struct PY_index PY_index_w[]=
	{          {"",PY_mb_wa},
		{"a",PY_mb_wa},
		{"ai",PY_mb_wai},
		{"an",PY_mb_wan},
		{"ang",PY_mb_wang},
		{"ei",PY_mb_wei},
		{"en",PY_mb_wen},
		{"eng",PY_mb_weng},
		{"o",PY_mb_wo},
		{"u",PY_mb_wu}
	};
	struct PY_index PY_index_x[]=
	{          {"",PY_mb_xi},
		{"i",PY_mb_xi},
		{"ia",PY_mb_xia},
		{"ian",PY_mb_xian},
		{"iang",PY_mb_xiang},
		{"iao",PY_mb_xiao},
		{"ie",PY_mb_xie},
		{"in",PY_mb_xin},
		{"ing",PY_mb_xing},
		{"iong",PY_mb_xiong},
		{"iu",PY_mb_xiu},
		{"u",PY_mb_xu},
		{"uan",PY_mb_xuan},
		{"ue",PY_mb_xue},
		{"un",PY_mb_xun}
	};
	struct PY_index PY_index_y[]=
	{          {"",PY_mb_ya},
		{"a",PY_mb_ya},
		{"an",PY_mb_yan},
		{"ang",PY_mb_yang},
		{"ao",PY_mb_yao},
		{"e",PY_mb_ye},
		{"i",PY_mb_yi},
		{"in",PY_mb_yin},
		{"ing",PY_mb_ying},
		{"o",PY_mb_yo},
		{"ong",PY_mb_yong},
		{"ou",PY_mb_you},
		{"u",PY_mb_yu},
		{"uan",PY_mb_yuan},
		{"ue",PY_mb_yue},
		{"un",PY_mb_yun}
	};
	struct PY_index PY_index_z[]=
	{          {"",PY_mb_za},
		{"a",PY_mb_za},
		{"ai",PY_mb_zai},
		{"an",PY_mb_zan},
		{"ang",PY_mb_zang},
		{"ao",PY_mb_zao},
		{"e",PY_mb_ze},
		{"ei",PY_mb_zei},
		{"en",PY_mb_zen},
		{"eng",PY_mb_zeng},
		{"ha",PY_mb_zha},
		{"hai",PY_mb_zhai},
		{"han",PY_mb_zhan},
		{"hang",PY_mb_zhang},
		{"hao",PY_mb_zhao},
		{"he",PY_mb_zhe},
		{"hen",PY_mb_zhen},
		{"heng",PY_mb_zheng},
		{"hi",PY_mb_zhi},
		{"hong",PY_mb_zhong},
		{"hou",PY_mb_zhou},
		{"hu",PY_mb_zhu},
		{"hua",PY_mb_zhua},
		{"huai",PY_mb_zhuai},
		{"huan",PY_mb_zhuan},
		{"huang",PY_mb_zhuang},
		{"hui",PY_mb_zhui},
		{"hun",PY_mb_zhun},
		{"huo",PY_mb_zhuo},
		{"i",PY_mb_zi},
		{"ong",PY_mb_zong},
		{"ou",PY_mb_zou},
		{"u",PY_mb_zu},
		{"uan",PY_mb_zuan},
		{"ui",PY_mb_zui},
		{"un",PY_mb_zun},
		{"uo",PY_mb_zuo}
	};
	struct PY_index PY_index_end[]={{"",PY_mb_space}};

	struct PY_index *PY_index_headletter[]=
	{
		PY_index_a,
		PY_index_b,
		PY_index_c,
		PY_index_d,
		PY_index_e,
		PY_index_f,
		PY_index_g,
		PY_index_h,
		PY_index_i,
		PY_index_j,
		PY_index_k,
		PY_index_l,
		PY_index_m,
		PY_index_n,
		PY_index_o,
		PY_index_p,
		PY_index_q,
		PY_index_r,
		PY_index_s,
		PY_index_t,
		PY_index_u,
		PY_index_v,
		PY_index_w,
		PY_index_x,
		PY_index_y,
		PY_index_z,
		PY_index_end
	};

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__T9_CHINA_H__*/
