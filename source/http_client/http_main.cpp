
#include "http_main.h"
#include "../gui/MessageBox.h"
//#include "../_fp.h"
//#include "../Database.h"


/*
extern void SystemReset(void);
extern void fp_setlivecheck(BOOL bCheck);
extern BOOL DbLogoSave(char *pBuffer,int size);
int HttpClient_Get(string word,char *dataP,int *len,int ramsize);
unsigned int AsciiToDec(char *str);

static  BOOL  Httpbadgepunch_Fail=0;
static FPINFO  *user_template;
	
char *mystrstr(char *haystack, char *needle)
{
	//assert(haystack != NULL && needle != NULL);
	if (strlen(haystack) < strlen(needle)) return NULL;
	char *head_n = (char *)needle;
	char *head_h = (char *)haystack;
	while (*haystack != '\0') {
		while (*needle != '\0') {
			if (*haystack != *needle) break;
			haystack++;
			needle++;
			if (*needle == '\0') return head_h;
		}
		needle = head_n;
		head_h++;
		haystack = head_h;
	}
	return NULL;
}

int TIMESTRING2ID(char* strID,int *pnID)
{
	int nLength, i;
	int nID = 0;
	unsigned char number;

	//if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
	//	return 0;

    nLength = strlen(strID);
	
	for (i=0; i<nLength; i++)
	{		

		if (strID[i] >= '0' && strID[i] <= '9')
		{
		   nID *= 10;
		   number = strID[i] - '0';
		   nID += number;
		}
// 		else if (strID[i] >= 'A' && strID[i] <= 'Z')
// 			number = 10 + strID[i] - 'A';
// 		else if (strID[i] >= 'a' && strID[i] <= 'z')
// 			number = 10 + strID[i] -'a';
		else
			break;

	}
    *pnID=nID;
	return i;
}

//String格式"2010-12-19 19:45:28"
void TimeStringGet(char* strTime,int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond)
{
	int  i=0;
	//int nID = 0;
	//int nYear,nMonth,nDay,nHour,nMinute,nSecond;
	char* pstrTime;
	
	//if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
	//	return 0;
	pstrTime=&strTime[2];
	i=TIMESTRING2ID(pstrTime,pnYear);
    pstrTime+=(i+1);
	i=TIMESTRING2ID(pstrTime,pnMonth);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnDay);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnHour);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnMinute);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnSecond);

}


void String_Remove(char *buff,char *dest)
{
    int len=strlen(dest);
    char *pos = 0;  
    char str[50];

	memset(str,0,50);
	pos = mystrstr(buff, dest);
	if(pos)
	{
      strncpy(str,&pos[len],50);
	  pos[0]=0;
	  strcat(buff,str);
	}

}
char str_out[40]; 

const char* Http_CfgstrGet(char *buff,char *dest)
{
	int dest_len;
	char *pos1 = 0;
	char *pos2 = 0;	

	dest_len=strlen(dest);	
	memset(str_out,0,sizeof(str_out));
	pos1 = mystrstr(buff, dest);
	if(pos1)
	   pos2 = mystrstr(pos1+1,(char *)" />");	
	//if(pos1)
	//	httpprintf("pos1=%s\n",pos1);
	//if(pos2)
	//	httpprintf("pos2=%s\n",pos2);	
	if(pos1 && pos2 && (pos1!=pos2))
	{
	    strncpy(str_out,pos1+dest_len+9,pos2-pos1-dest_len-10); 
	}
	else
	{
        //httpprintf("=%s\n","Http_CfgstrGet return 0");
		return 0;
	}
	//str_out = str_src.substr( pos1+dest_len, pos2-pos1-dest_len );
	//pos1 = str_src.find_last_of( "/", str_src.size() );
	//filename = str_src.substr( pos1+1, str_src.size()-pos1-1 );
	return ((const char*)str_out);

}

char* Http_CfgstrGet2(char *buff,char *dest1,char *dest2,char *ret)
{
	int dest_len;
	char *pos1 = 0;
	char *pos2 = 0;	
	//char str_out[30]; 

	dest_len=strlen(dest1);	
	//memset(str_out,0,sizeof(str_out));
	pos1 = mystrstr(buff, dest1);
	if(pos1)
	   pos2 = mystrstr(pos1+1,dest2);	
	//if(pos1)
	//	httpprintf("pos1=%s\n",pos1);
	//if(pos2)
	//	httpprintf("pos2=%s\n",pos2);	
	if(pos1 && pos2 && (pos1!=pos2))
	{
	    strncpy(ret,pos1+dest_len,pos2-pos1-dest_len); 
	}
	else
	{
        //httpprintf("=%s\n","Http_CfgstrGet return 0");
		return 0;
	}
	//str_out = str_src.substr( pos1+dest_len, pos2-pos1-dest_len );
	//pos1 = str_src.find_last_of( "/", str_src.size() );
	//filename = str_src.substr( pos1+1, str_src.size()-pos1-1 );
	//ret=str_out;
	return (pos2);

}

 char str_PunchedIn[40]; 
 char str_PunchedOut[40]; 
 char str_EmployeeName[40]; 
 char str_DepartmentName[40]; 
 char str_LastPunch[40]; 
 char str_CurrentTime[40]; 
 char str_UTCOffset[40]; 
 char str_AccountName[40]; 

 
 typedef struct _db_department
 {
	 char	 idstr[10];				 //1
	 char	 namestr[20];				 //1
 }DB_DEPARTMENT; 					
 
 DB_DEPARTMENT http_department_str[100];
static  int http_department_str_Num=0;

static unsigned char DEVICE_ID_OK=0;

unsigned char Http_BadgePunch_IsOk(void)
{
   if(Httpbadgepunch_Fail)
   	  return  0;
   else		
      return  1;
}
unsigned char Http_SyncAck(char *Client_Datap)
{
	const char *str;
	
	httpprintf("%s\n\r",Client_Datap);
	
    if(mystrstr((char *)Client_Datap,"File Not Found"))
       return 0;  
   str=Http_CfgstrGet((char *)Client_Datap,"online name");
   if(str)
	{
	       return 1;
   	}
	 return 0;  
}
unsigned char Http_DeviceId_IsOk(void)
{
   return  DEVICE_ID_OK;
}


void Http_BadgePunchDataRead(char *Client_Datap)
{
   const char *str;

   memset(str_PunchedIn,0,sizeof(str_PunchedIn));
   memset(str_EmployeeName,0,sizeof(str_EmployeeName));
   memset(str_DepartmentName,0,sizeof(str_DepartmentName));
   memset(str_LastPunch,0,sizeof(str_LastPunch));

   Httpbadgepunch_Fail=0;
   str=Http_CfgstrGet((char *)Client_Datap,"You Punched IN");
   if(str)
	{
       strcpy(str_PunchedIn,"You Punched IN: ");
	   strcat(str_PunchedIn,str);
	   httpprintf("%s\r\n",str_PunchedIn);
	}
   else
   	{
       str=Http_CfgstrGet((char *)Client_Datap,"You Punched OUT");
	   if(str)
	   	{
	   	    strcpy(str_PunchedIn,"You Punched OUT: ");
	        strcat(str_PunchedIn,str);
	        httpprintf("%s\r\n",str_PunchedIn);
	   	}
	   else
	   	{
		   str=Http_CfgstrGet((char *)Client_Datap,"Sorry");
		   if(str)
		   	{
                Httpbadgepunch_Fail=1;
				strcpy(str_PunchedIn,"Sorry ");
		        strcat(str_PunchedIn,str);
		        httpprintf("%s\r\n",str_PunchedIn);
		   	}
		   else
		      httpprintf("%s\n","You Punched IN = 0");
	   	}
   	}
   str=Http_CfgstrGet((char *)Client_Datap,"Employee Name");
   if(str)
	{  
       strcpy(str_EmployeeName,str);
	   httpprintf("Employee Name=%s\n",str_EmployeeName);
    }
   else
   	{
   	   httpprintf("%s\n","str_EmployeeName = 0");
   	}   
   str=Http_CfgstrGet((char *)Client_Datap,"Department Name");
    if(str)
	{  
       strcpy(str_DepartmentName,str);
	   httpprintf("Department Name=%s\n",str_DepartmentName);
    }
   else
   	{
   	   httpprintf("%s\n","str_DepartmentName = 0");
   	}	
   str=Http_CfgstrGet((char *)Client_Datap,"Your Last Punch");
    if(str)
	{
       strcpy(str_LastPunch,str);
	   httpprintf("Your Last Punch=%s\n",str_LastPunch); 
    }
   else
   	{
   	   httpprintf("%s\n","str_LastPunch = 0");
   	}	
}


void Http_PinPunchDataRead(char *Client_Datap)
{
   const char *str;

   memset(str_PunchedIn,0,sizeof(str_PunchedIn));
   memset(str_EmployeeName,0,sizeof(str_EmployeeName));
   memset(str_DepartmentName,0,sizeof(str_DepartmentName));
   memset(str_LastPunch,0,sizeof(str_LastPunch));

   Httpbadgepunch_Fail=0;
   str=Http_CfgstrGet((char *)Client_Datap,"Employee Name");
   if(str && (strcmp(str,"Sorry")==0))
   	{
        Httpbadgepunch_Fail=1;
		strcpy(str_EmployeeName,str);
        httpprintf("%s\r\n",str_EmployeeName);
   	}

   str=Http_CfgstrGet((char *)Client_Datap,"Employee Name");
   if(str)
	{  
       strcpy(str_EmployeeName,str);
	   strcat(str_EmployeeName,"Has Worked");
	   httpprintf("Employee Name=%s\n",str_EmployeeName);
    }
   else
   	{
   	   httpprintf("%s\n","str_EmployeeName = 0");
   	}   
   str=Http_CfgstrGet((char *)Client_Datap,"Hours Worked");
    if(str)
	{	   
	   strcpy(str_PunchedIn,str);
	   String_Remove(str_PunchedIn,"worked ");
	   httpprintf("Department Name=%s\n",str_PunchedIn);
    }
   else
   	{
   	   httpprintf("%s\n","str_PunchedIn = 0");
   	}
   if(strlen(str_EmployeeName)==0)
   	   Httpbadgepunch_Fail=1;
  
}

void Http_DepPunchDataRead(char *Client_Datap)
{
	const char *str;

   Httpbadgepunch_Fail=0;

   memset(str_PunchedOut,0,sizeof(str_PunchedOut));
   memset(str_EmployeeName,0,sizeof(str_EmployeeName));
   memset(str_DepartmentName,0,sizeof(str_DepartmentName));
   memset(str_LastPunch,0,sizeof(str_LastPunch));

   str=Http_CfgstrGet((char *)Client_Datap,"You Punched OUT");
   if(str)
	{
       strcpy(str_PunchedOut,"You Punched OUT: ");
	   strcat(str_PunchedOut,str);
	   httpprintf("%s\r\n",str_PunchedOut);
	}
   else
   	{
       str=Http_CfgstrGet((char *)Client_Datap,"You Punched IN");
	   if(str)
	   	{
            strcpy(str_PunchedOut,"You Punched IN: ");
			strcat(str_PunchedOut,str);
	        httpprintf("%s\r\n",str_PunchedOut);
	   	}
       else
       	{
		   str=Http_CfgstrGet((char *)Client_Datap,"Sorry");
		   if(str)
		   	{
                Httpbadgepunch_Fail=1;
				strcpy(str_PunchedOut,"Sorry ");
				strcat(str_PunchedOut,str);
		        httpprintf("%s\r\n",str_PunchedOut);
		   	}
		   else
		      httpprintf("%s\n","You Punched OUT = 0");
       	}

   	}   
   str=Http_CfgstrGet((char *)Client_Datap,"Employee Name");
   if(str)
	{  
       strncpy(str_EmployeeName,str,sizeof(str_EmployeeName));
	   httpprintf("Employee Name=%s\n",str_EmployeeName);
    }
   else
   	{
   	   httpprintf("%s\n","str_EmployeeName = 0");
   	}    
   str=Http_CfgstrGet((char *)Client_Datap,"Department Name");
    if(str)
	{  
       strncpy(str_DepartmentName,str,sizeof(str_DepartmentName));
	   httpprintf("Department Name=%s\n",str_DepartmentName);
    }
   else
   	{
   	   httpprintf("%s\n","str_DepartmentName = 0");
   	} 	
   str=Http_CfgstrGet((char *)Client_Datap,"Your Last Punch");
    if(str)
	{
       strncpy(str_LastPunch,str,sizeof(str_LastPunch));
	   httpprintf("Your Last Punch=%s\n",str_LastPunch); 
    }
   else
   	{
   	   httpprintf("%s\n","str_LastPunch = 0");
   	} 	
}



unsigned char Http_TimeDataRead(char *Client_Datap)
{
	const char *str;
	
   Httpbadgepunch_Fail=0;
   memset(str_CurrentTime,0,sizeof(str_CurrentTime));
   memset(str_UTCOffset,0,sizeof(str_UTCOffset));
   memset(str_AccountName,0,sizeof(str_AccountName));

    if(mystrstr((char *)Client_Datap,"File Not Found"))
       return 0;  
   str=Http_CfgstrGet((char *)Client_Datap,"Account Current Time");
   if(str)
	{
       strncpy(str_CurrentTime,str,sizeof(str_CurrentTime));
	   httpprintf("Account Current Time=%s\n",str_CurrentTime);
	}
   else
   	{
	   str=Http_CfgstrGet((char *)Client_Datap,"Sorry");
	   if(str)
		{
			Httpbadgepunch_Fail=1;
			strcpy(str_CurrentTime,"Sorry ");
			strcat(str_CurrentTime,str);
			httpprintf("%s\r\n",str_CurrentTime);
		}
	   else
		  httpprintf("%s\n","Account Current Time = 0");	   
   	}   
   str=Http_CfgstrGet((char *)Client_Datap,"Account UTC Offset");
   if(str)
	{  
       strncpy(str_UTCOffset,str,sizeof(str_UTCOffset));
	   httpprintf("Account UTC Offset=%s\n",str_UTCOffset);
    }
   else
   	{
   	   httpprintf("%s\n","Account UTC Offset = 0");
   	}    
   str=Http_CfgstrGet((char *)Client_Datap,"Account Name");
    if(str)
	{  
       strncpy(str_AccountName,str,sizeof(str_AccountName));
	   httpprintf("Account Name=%s\n",str_AccountName);
    }
   else
   	{
   	   httpprintf("%s\n","Account Name = 0");
   	} 
    return 1;
	
}


void Http_FetchDeptDataRead(char *Client_Datap)
{
	char *pos;
	int i;
	
    if(mystrstr((char *)Client_Datap,"No Data Found"))
   	{
       DEVICE_ID_OK=0;
	   return;
   	}
   else
   	{
	   DEVICE_ID_OK=1;   	
   	}	
   memset(http_department_str,0,sizeof(http_department_str));
   i=0;  
   pos=Client_Datap;
   while(i<100)
   	{
	   pos=Http_CfgstrGet2(pos,"id=\"","\"/>",http_department_str[i].idstr);
   	   if(pos==0)
			break;
       pos=Http_CfgstrGet2(pos,"name=\"","\"/>",http_department_str[i].namestr);
	   //if(pos==0)
		//	break;

	   i++;
   	}
   http_department_str_Num=i;
	
}

int Http_UploadLogoDataRead(char *Client_Datap)
{
	char *pos;
	char *dataP;
	char str_LogoName[100]; 
	int i,len,len2;
	
   memset(str_LogoName,0,sizeof(str_LogoName));
   pos=Client_Datap;
   pos=Http_CfgstrGet2(pos,"Logo\" value=\"","\" />",str_LogoName);
   if(pos==0) 
   	 return 0;
   
   dataP = new  char[1024*1024];   
   memset(dataP,0,1024*1024);
   HttpClient_Get(str_LogoName,dataP,&len,1024*1024);   
   
   httpprintf("datalen=%d\r\n",len);
   //dataP[300]=0;
   //httpprintf("%s,",dataP);  
   
   memset(str_LogoName,0,sizeof(str_LogoName));
   pos=Http_CfgstrGet2(dataP,"Content-Length: ","Content-Type:",str_LogoName);
   if(pos==0) 
   {
     delete dataP;
   	 return 0;   
   }
   httpprintf("\r\n%s\r\n",str_LogoName);   
   len2=(unsigned int)len-AsciiToDec(str_LogoName); 
   len=AsciiToDec(str_LogoName); 
   httpprintf("len=%d\r\n",len); 
   httpprintf("len2=%d\r\n",len2); 
   
   DbLogoSave(&dataP[len2],len);   

   delete dataP;
   return 1;
	
}

void  Http_FpTemplateSet(FPINFO  *pData)
{
	user_template=pData;
}
int Http_UploadFpTemplateDataRead(char *Client_Datap)
{
	char *pos;
	char *dataP;
	char str[30]; 
	
   memset(str,0,sizeof(str));
   pos=Client_Datap;
  
   pos=Http_CfgstrGet2(pos,"message =\"","\">",str);
   if(pos==0) 
   	 return 0;   
   if(strcmp(str,"Fingerprint Template Saved")!=0)
   	 return 0;
   return 1;	
}

unsigned int AsciiToInt(char *str)
{
   unsigned int a;
   sscanf(str,"%x",&a);
   return a;
}
unsigned int AsciiToDec(char *str)
{
   unsigned int a;
   sscanf(str,"%d",&a);
   return a;
}

unsigned char AsciiToNChar(char *str,unsigned char *dest,int len)
{
    unsigned int a;
    int i;
	char nstr[3];
	
	len=(len/2)*2;
	memset(nstr,0,3);
	for(i=0;i<len;i++)
	{	
       strncpy(nstr,str,2);    
	   sscanf(nstr,"%x",&a);
       dest[i]=a;  
	   str+=2;
	   //httpprintf("%x,",a);
	}
    return TRUE;
}

int Http_GetFpDataById(UINT64  id,char *dataP,int *len)
{
	string word;
	char temp[64];	

	sprintf(temp, "%d", id);
	string sid(temp);

	//http://ws.trackmytime.com/clock.cfc?method=download_template&key=AJ5P8EG3M2Z3&serial=BN3000-13335234

	word = "http://ws.trackmytime.com/clock.cfc?method=download_template&key=AJ5P8EG3M2Z3&serial=";
	//word += nUattendMachineID;//为了调试需要，暂时屏蔽
	word += "&fp=";
	word += sid;
	if(HttpClient_Get(word,dataP,len,5*1024))
		return 1;
	else
		return 0;

}




int Http_DownFpTemplateRead(char *Client_Datap)
{
	 char *pos,*pos2;
	 int i;
	 FPINFO fp;
	 UINT64  id;
	 int len;
	 int ret;
	 char *str;
	 char *str2;
	 #define  str_size  (1404*5)
	 	 
	str = (char*)malloc( str_size );
	str2 = (char*)malloc( str_size );
    if(str==0 || str2==0)
	{
		FREE(str);
		FREE(str2);
	    return 0;
	}
	ret=0; 
	i=0;
	pos=Client_Datap;
	//while(i<5000)
	for(i=0;i<5000;)
	 {
	    memset(&fp,0,sizeof(fp));		
		memset(str,0,str_size);
		httpprintf("pos=%s\r\n",pos);
		
		pos=Http_CfgstrGet2(pos,"finger_id=\"","\">",str);		
		if(pos==0)
		{
		   if(i)
	           ret=i;
			break;	
		}
		id=AsciiToDec(str); 
		memset(str,0,str_size);
		httpprintf("fp_id=%d\r\n",id);

		memset(str2,0,str_size);
		if(Http_GetFpDataById(id,str2,&len)==0)
			break;	
		pos2=str2;
		pos2=Http_CfgstrGet2(pos2,"fp_id=\"","\">",str);
		if(pos2==0)
		  continue;
		if(id!=AsciiToDec(str))
		{
		  continue;
		}
		memset(str,0,str_size);		
		pos2=Http_CfgstrGet2(pos2,"lParam=\"","\">",str);
		if(pos2==0)
		  break;	
		fp.lParam=AsciiToInt(str); 
		memset(str,0,str_size);
		httpprintf("fp.lParam=%d\r\n",fp.lParam);
		pos2=Http_CfgstrGet2(pos2,"wParam=\"","\">",str);
		if(pos2==0)
		   break;	
		fp.wParam=AsciiToInt(str); 
		memset(str,0,str_size);
		httpprintf("fp.wParam=%d\r\n",fp.wParam);
		pos2=Http_CfgstrGet2(pos2,"valid=\"","\">",str);
		if(pos2==0)
		   break;	
		fp.Valid=AsciiToInt(str); 
		memset(str,0,str_size);	
		httpprintf("fp.Valid=%d\r\n",fp.Valid);
		pos2=Http_CfgstrGet2(pos2,"reserved=\"","\">",str);
		if(pos2==0)
		  break;	
		if(strlen(str)!=(sizeof(fp.Reserved)*2))
			continue;
		AsciiToNChar((char*)str,fp.Reserved,strlen(str));	
		memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));		
		gUserInfoTemp.ID=id;
		//gUserInfoTemp.FP=UserData.dwBackupNumber;
		//gUserInfoTemp.VERIFYMODE=UserData.dwVerifymode;
		gUserInfoTemp.FLAG.members.byMgr=1;	
		if (SB_FP_IDENTIFYFPDATA((FPINFO*)&fp, NULL) >= 0)  
		{						
			continue;
		}
		httpprintf("DbUserInfoEnroll ok \r\n");
		DbUserInfoEnroll(&gUserInfoTemp, BACKUP_FINGER0, &fp, TRUE, FALSE);	
		i++;
		POST_EVENTS();
		
	 }
	FREE(str);
	FREE(str2);
	httpprintf("Http_DownFpTemplateRead exit ret=%d\r\n",ret);
	POST_EVENTS();
	return ret;
	
}

char *Http_DeptStrGet(int n,unsigned char type)
{
	if(type==1)
	{
	  return http_department_str[n].idstr;
	}
	else if(type==2)
	{
	  return http_department_str[n].namestr;
	}	
	else
	  return 0;
}
int Http_DeptStrCNTGet(void)
{
	return http_department_str_Num;
}

*/
//extern int DM9000_NetLink_OK;

extern unsigned char	dbComm_ipIsDHCP;													//1
extern unsigned char	dbComm_dhcpSuccess;		

/*
int HttpClient_Get(string word,char *dataP,int *len,int ramsize)
{
	string filename;
	string hostname;
	//string pin;
	//string dept;
	int pos1 = 0;
	int pos2 = 0;	
	char temp[64];	

	//if(DM9000_NetLink_OK==0&&WIFI_EN==0)
		//return 0;

	if (dbSetupTotal.setSystem.bDHCPUse && dbComm_dhcpSuccess==0)
		return 0;

	httpprintf("word:%s\r\n",word.c_str());

	//bulid the query for http
	string quest = "GET ";
	quest += word;
	quest += " HTTP/1.0\r\n";
	quest += "User-agent:Mozilla/4.0\r\n";
	quest += "Accept-language:zh-cn\r\n\r\n";

	//get the hostname and filename from the word
	string str_http = "http://";
	pos1 = word.find_first_of (str_http, 0);
	pos2 = word.find_first_of ("/", pos1+7);
	hostname = word.substr( pos1+7, pos2-pos1-7 );
	pos1 = word.find_last_of( "/", word.size() );
	filename = word.substr( pos1+1, word.size()-pos1-1 );

	//httpprintf("filename:%s\n",filename.c_str());
	httpprintf("hostname:%s\r\n",hostname.c_str());

	//use the hostname and port 80 to connect 
	 //Sock_instance s_client( hostname, 80, CLIENT_TYPE );
	//Sock_instance *s_client=new Sock_instance( hostname, 80, CLIENT_TYPE,1024*1024);

    BYTE* pdatabuf = (BYTE*)malloc(ramsize);
	if (!pdatabuf)
	{
		httpprintf("%s\r\n","malloc error");
		return 0;
	}
	int datalen=Sock_Receive(hostname, quest,pdatabuf,ramsize);
    if(datalen==0)
	{
	   FREE(pdatabuf);
	   return 0;
	}
    memcpy(dataP,pdatabuf, datalen);	
	*len=datalen;
	FREE(pdatabuf);
	return 1;
}


BOOL HttpRomWrite(string word)
{
	BOOL bRet = TRUE;
	BYTE* pRomImage;
	BYTE* pRomImage2;

	//string filename;
	string hostname;
	//string pin;
	//string dept;
	int pos1 = 0;
	int pos2 = 0;	
	char temp[64];
	char str_data[64];
    int len,len2;
	
	//if(DM9000_NetLink_OK==0&&WIFI_EN==0)
		//return 0;

	if (dbSetupTotal.setSystem.bDHCPUse && dbComm_dhcpSuccess==0)
		return 0; 
	
	
	//bulid the query for http
	string quest = "GET ";
	quest += word;
	quest += " HTTP/1.0\r\n";
	quest += "User-agent:Mozilla/4.0\r\n";
	quest += "Accept-language:zh-cn\r\n\r\n";

	//get the hostname and filename from the word
	string str_http = "http://";
	pos1 = word.find_first_of (str_http, 0);
	pos2 = word.find_first_of ("/", pos1+7);
	hostname = word.substr( pos1+7, pos2-pos1-7 );
	pos1 = word.find_last_of( "/", word.size() );
	//filename = word.substr( pos1+1, word.size()-pos1-1 );

	httpprintf("\r\nquest:%s\r\n",quest.c_str());
	
	pRomImage = (BYTE*)malloc(ROM_FLASH_SIZE*1024*1024);
	if (!pRomImage)
	{
		httpprintf("%s\r\n","malloc error");
		return 0;
	}
	int datalen=Sock_Receive(hostname, quest,pRomImage,ROM_FLASH_SIZE*1024*1024);
    if(datalen==0)
	{
	   FREE(pRomImage);
	   return 0;
	}
	httpprintf("%s",(const char *)pRomImage);

	memset(str_data,0,sizeof(str_data));
	if(Http_CfgstrGet2((char *)pRomImage,"Content-Length: ","Content-Type:",str_data)==0) 
	{
	  FREE(pRomImage);
	  return 0;   
	}
	httpprintf("\r\n%s\r\n",str_data);	
	len=AsciiToDec(str_data); 
	if(datalen<=len)
	{
		FREE(pRomImage);
		return 0;
	}
	len2=datalen-len; 
	httpprintf("len=%d\r\n",len); 
	httpprintf("len2=%d\r\n",len2); 
	POST_EVENTS();
	
	pRomImage2=&pRomImage[len2];
	httpprintf("pRomImage2[0]=%x\r\n",*(pRomImage2+0)); 
	httpprintf("pRomImage2[1]=%x\r\n",*(pRomImage2+1)); 
	httpprintf("pRomImage2[2]=%x\r\n",*(pRomImage2+2)); 
	httpprintf("pRomImage2[3]=%x\r\n",*(pRomImage2+3)); 
		
	bRet = _Db_FWWriteToFlash((unsigned char *)&pRomImage[len2], len);	
	
	FREE(pRomImage);

	return bRet;
}

*/

/*
int Http_UpDateFirwareRead(char *Client_Datap)
{
	char *pos;
	char *dataP;
	char str_Name[200]; 
	int i,len;
    BOOL bRet = TRUE;

   memset(str_Name,0,sizeof(str_Name));
   pos=Client_Datap;
   pos=Http_CfgstrGet2(pos,"current_fwurl>","</",str_Name);
   if(pos==0) 
   	 return 0;  

   CMessageBox *msgBox = new CMessageBox; 
   msgBox->MsgBoxProc_Message("UpdateFirmware ...");
   
   Db_FreeAllData();   
   bRet =HttpRomWrite(str_Name);
   
   if(msgBox)
	  delete msgBox;   
   //SB_EXEC("reboot"); 
  
   Db_LoadAllData(TRUE);
    SB_EXEC("reboot"); 
	while(1);
   return bRet;
	
}


string inttoascii(int num)
{
	char str[10];
	memset(str,0,sizeof(str));
	sprintf(str, "%02x" , num);
	//httpprintf("%s",str); 
	string strout(str);
	return strout;

}
*/
static unsigned char HttpLinking=0;
int HttpClient_Connecting(void)
{
	return HttpLinking;
}
void HttpClient_SetConnecting(unsigned char states)
{
	HttpLinking=states;
}

int HttpClient_Connect(string domain_name,string deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType)
{
	string word;
	//string filename;
	string hostname;
	//string pin;
	//string dept;
	int pos1 = 0;
	int pos2 = 0;	
	char temp[64];	
    int nRet;
	int i;
	BYTE* pdatabuf;
/*	
	if(DM9000_NetLink_OK==0&&WIFI_EN==0)
	{
	 httpprintf("DM9000_NetLink_OK==0&&WIFI_EN==0\r\n");	
	return 0;
		}
*/
	if (dbSetupTotal.setSystem.bDHCPUse && dbComm_dhcpSuccess==0)
	{
	 	 httpprintf("dbComm_dhcpSuccess=%d\r\n",dbComm_dhcpSuccess);	
	 
	 httpprintf("dbSetupTotal.setSystem.bDHCPUse=%d\r\n",dbSetupTotal.setSystem.bDHCPUse);	
	return 0;
		}
	nRet=1;

    if(PunchType==4)
		sprintf(temp, "%06d", nId);
    else if(PunchType==1)
		sprintf(temp, "%04d", nPin);
    else if(PunchType==2)
		//sprintf(temp, "%04d", nId);
		sprintf(temp, "%04d", nPin);
    else if(PunchType==5) //DEP+FINGER   
               sprintf(temp, "%06d", nId);
	else if(PunchType==14) //DEP+FINGER   
		{
		   	sprintf(temp, "%04d", nPin);
		}
    else 
		sprintf(temp, "%06d", nId);

	       httpprintf("nId=%d\n",nId);	
		httpprintf("nPin=%d\n",nPin);	
		httpprintf("nDept=%d\n",nDept);
		httpprintf("PunchType=%d\n",PunchType);

	
/*
	
	string pin(temp);
	sprintf(temp, "%d", nDept);
	string dept(temp);	

	hostname=domain_name;
	word = "http://";
	word += domain_name;
	word +="/clock.cfc?method=";
    if(PunchType==HTTP_BADGEPUNCH) //http://ws.trackmytime.com/sandbox.cfc?method=punch_time&key=AJ5P8EG3M2Z3&serial=CB1000-2YAMREEV&pin=1222
  	{
  	   word += "punch_time&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&pin=";
	   word += pin;
  	}
    else if(PunchType==HTTP_PINPUNCH2) //http://ws.trackmytime.com/clock.cfc?method=employee_status&key=AJ5P8EG3M2Z3&serial={DEVICEID}&pin={PIN}
  	{
		word += "employee_status&key=AJ5P8EG3M2Z3&serial=";
		word += deviceid;
		word += "&pin=";
		word += pin;
  	}		
    else if(PunchType==HTTP_DEPTPUNCH) //http://ws.trackmytime.com/sandbox.cfc?method=punch_time&key=AJ5P8EG3M2Z3&serial=CB1000-2YAMREEV&pin=1222&dept=1011
  	{
  	   word += "punch_time&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&pin=";
	   word += pin;
	   word += "&dept=";
	   word += dept;
  	}
    else if(PunchType==HTTP_TIMESET)	//http://ws.trackmytime.com/clock.cfc?method=update_time&key=AJ5P8EG3M2Z3&serial=CB1000-2YAMREEV  
  	{
	   word += "update_time&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
  	}  	
    else if(PunchType==HTTP_FINGERPUNCH)	//http://ws.trackmytime.com/clock.cfc?method=bio_punch&key=AJ5P8EG3M2Z3&serial=CB3000-3WNGS6JJ&fid=1 
  	{
  	   word += "bio_punch&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&fid=";
	   word += pin;	   
  	}  
    else if(PunchType==HTTP_FINGERPUNCH2)	//http://ws.trackmytime.com/clock.cfc?method=employee_status&key=AJ5P8EG3M2Z3&serial={DEVICEID}&fid=072866  
  	{
  	   word += "employee_status&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&fid=";
	   word += pin;	   
  	} 	
    else if(PunchType==HTTP_FINGERDEPTPUNCH)	//http://ws.trackmytime.com/clock.cfc?method=bio_punch&key=AJ5P8EG3M2Z3&serial=CB3000-3WNGS6JJ&fid=1&dept=1
  	{
  	   word += "bio_punch&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&fid=";
	   word += pin;
	   word += "&dept=";
	   word += dept;	   
  	} 
    else if(PunchType==HTTP_PINDEPTPUNCH) //http://ws.trackmytime.com/sandbox.cfc?method=punch_time&key=AJ5P8EG3M2Z3&serial=BN3000-13335234&pin=1222&dept=1011
  	{
  	   word += "bio_punch&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&pin=";
	   word += pin;
	   word += "&dept=";
	   word += dept;
  	}
    else if(PunchType==HTTP_UPLOAD_FPTEMPLATE) //http://ws.trackmytime.com/clock.cfc?method=save_templates&key=AJ5P8EG3M2Z3&serial=BN3000-13335234&userpin=1222&lParam=1&wParam=2&bof=1&valid=0&reserved={Reserved[1397]}
  	{
  	   word += "save_templates&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&userpin=";
	   word += pin;
	   word += "&lParam=";
	   word += inttoascii(user_template->lParam);	   
	   word += "&wParam=";
	   word += inttoascii(user_template->wParam); 
	   word += "&bof=1";
	   word += "&valid=";
	   word += inttoascii(user_template->Valid); 
	   word += "&reserved=";
	   for(i=0;i<1397;i++)
	   	{	   
	       word +=inttoascii(user_template->Reserved[i]);   
	   	}
	   //httpprintf("filename:%s\n",word.c_str());
  	}
    else if(PunchType==HTTP_DOWNLOAD_FPTEMPLATE) //http://ws.trackmytime.com/clock.cfc?method=download_templates&key=AJ5P8EG3M2Z3&serial=CB3000-23857217
  	{
  	   word += "download_templates&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;	 
  	}
    else if(PunchType==HTTP_UPLOAD_LOGO) //http://ws.trackmytime.com/clock.cfc?method=update_logo&key=AJ5P8EG3M2Z3&serial=BN3000-13335234
  	{
  	   word += "update_logo&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;	 
  	}
    else if(PunchType==HTTP_UPDATE_FIRMWARE) //http://ws.trackmytime.com/firmware.cfc?method=update_firmware&key=AJ5P8EG3M2Z3&serial=CB1500-13971814&version=CB3000-1.0
  	{
  	
           word= "http://ws.trackmytime.com/firmware.cfc?method=update_firmware";
	   word += "&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&version=";
           //word += LNSC_FIRMWAREVERSION;
           //word += LNSC_FIRMWAREVERSION;这个是以前的，现在需要改动一下
           //下面三行是特殊情况加入进去的
           word +="1.0";
           word +="&uk=";
           word +="1";
           xprintf("word==%s",word);

	   
  	}
	else if(PunchType==HTTP_FETCH_DEPARTMENT) //http://ws.trackmytime.com/clock.cfc?method=fetch_departments&key=AJ5P8EG3M2Z3&serial=CB3000-3WNGS6JJ
	{
	   word += "fetch_departments&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;	 
	}
			else if(PunchType==HTTP_SYNC_ACK) //ws.trackmytime.com/clock.cfc?method=check_connectivity&key=AJ5P8EG3M2Z3
	{
	   word +="check_connectivity&key=AJ5P8EG3M2Z3";//&serial=";
	  // word += deviceid;	 
	}
	else if(PunchType==HTTP_TRANSFER_DEPARTMENT) //http://ws.trackmytime.com/clock.cfc?method=transfer&key=AJ5P8EG3M2Z3&serial=CB3000-3WNGS6JJ&dept_id=2293&pin=1
	{
	   word += "transfer&key=AJ5P8EG3M2Z3&serial=";
	   word += deviceid;
	   word += "&dept_id=";
	   word += dept;   
	   word += "&pin=";
	   word += pin;
	   
	}
*/	
  	
	//cout << "enter the host name" << endl;
	//cin >> word;
	//httpprintf("word:%s\n",word.c_str());

	//bulid the query for http
	string quest = "GET ";
	quest += word;
	quest += " HTTP/1.0\r\n";
	quest += "User-agent:Mozilla/4.0\r\n";
	quest += "Accept-language:zh-cn\r\n\r\n";
	int bufsize;

	if(PunchType==HTTP_DOWNLOAD_FPTEMPLATE)
       bufsize=3*1024*1024;
	else if(PunchType==HTTP_UPDATE_FIRMWARE)
       bufsize=ROM_FLASH_SIZE*1024*1024;	
    else
    {
		bufsize=3*1024*1024;
    }

    pdatabuf = (BYTE*)malloc(bufsize);
	if (!pdatabuf)
	{
		//httpprintf("%s\r\n","malloc error");
		return 0;
	}
	int datalen=Sock_Receive(hostname, quest,pdatabuf,bufsize);
    if(datalen==0)
	{
	   FREE(pdatabuf);
	   return 0;
	}
/*
	//httpprintf("%s",(const char *)pdatabuf);
	
    if(mystrstr((char *)pdatabuf,"Account not found"))
   	{
       DEVICE_ID_OK=0;
	   nRet=0;
   	}
   else
   	{
	   DEVICE_ID_OK=1;   	
   	}
   	if(deviceid.length()==1)
   	{
		DEVICE_ID_OK=0;
		nRet=0;
   	}
	else
   	{
		DEVICE_ID_OK=1;   	
   	}
   
	if(PunchType==HTTP_BADGEPUNCH)
       Http_BadgePunchDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_PINPUNCH2)
       Http_PinPunchDataRead((char *)pdatabuf);	
	else if(PunchType==HTTP_DEPTPUNCH)
       Http_DepPunchDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_TIMESET)	
	   nRet=Http_TimeDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_FINGERPUNCH)
       Http_BadgePunchDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_FINGERPUNCH2)
       Http_PinPunchDataRead((char *)pdatabuf);	
	else if(PunchType==HTTP_FINGERDEPTPUNCH)
       Http_DepPunchDataRead((char *)pdatabuf);	
	else if(PunchType==HTTP_PINDEPTPUNCH)
       Http_DepPunchDataRead((char *)pdatabuf);		
	else if(PunchType==HTTP_FETCH_DEPARTMENT)
       Http_FetchDeptDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_UPLOAD_LOGO)
       nRet=Http_UploadLogoDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_UPLOAD_FPTEMPLATE)
       nRet=Http_UploadFpTemplateDataRead((char *)pdatabuf);
	else if(PunchType==HTTP_DOWNLOAD_FPTEMPLATE)
       nRet=Http_DownFpTemplateRead((char *)pdatabuf);	
	else if(PunchType==HTTP_UPDATE_FIRMWARE)
       nRet=Http_UpDateFirwareRead((char *)pdatabuf);	
		else if(PunchType==HTTP_SYNC_ACK)	
	   nRet=Http_SyncAck((char *)pdatabuf);
    else
    {
		nRet=0;
    }

*/	

	//httpprintf("HttpClient_Connect exit\r\n");
	FREE(pdatabuf);
	return nRet;
}

int HttpClient_main(string deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType,unsigned char MsgEn)
{
	
     HttpLinking=1;
	if(HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName[0],deviceid,nId,nPin,nDept,PunchType))
	{
	   HttpLinking=1;	
	    return 1;
	}
	else
		{
			if(HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName[0],deviceid,nId,nPin,nDept,PunchType))
			{
	   			HttpLinking=1;	
			       return 1;
			}
			else
				{
					if(HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName_1[0],deviceid,nId,nPin,nDept,PunchType))
					{
	   					HttpLinking=1;	
			   			   return 1;
				     }	
					else
						{
						     					if(HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName_2[0],deviceid,nId,nPin,nDept,PunchType))
										{
	   										HttpLinking=1;	
			   			 					  return 1;
				    						 }		
						}
				}
		}
        HttpLinking=0;
        return 0;
}


