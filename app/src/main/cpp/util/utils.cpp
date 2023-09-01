#include "utils.h"
#include <ctype.h>
#include <map>
#include "log.h"
#include "time.h"

void StrToHex(BYTE *pbDest, char *szSrc, DWORD dwLen)
{
	char h1,h2;
	BYTE s1,s2;
	
	for (int i=0; i<dwLen; i++)
	{
		h1 = szSrc[2*i];
		h2 = szSrc[2*i+1];
		
		s1 = toupper(h1) - 0x30;
		if (s1 > 9) 
			s1 -= 7;
		
		s2 = toupper(h2) - 0x30;
		if (s2 > 9) 
			s2 -= 7;
		
		pbDest[i] = s1*16 + s2;
    }
}

void HexToStr(char *szDest, const BYTE *pbSrc, DWORD dwLen)
{
	char	ddl,ddh;
	
	for (int i=0; i<dwLen; i++)
	{
		ddh = 48 + pbSrc[i] / 16;
		ddl = 48 + pbSrc[i] % 16;
		if (ddh > 57)  ddh = ddh + 7;
		if (ddl > 57)  ddl = ddl + 7;
		szDest[i*2] = ddh;
		szDest[i*2+1] = ddl;
	}
	
	szDest[dwLen*2] = '\0';
}

void PrintHex(char* tag, unsigned char * src, int len)
{
#ifdef DEBUG

	char* s = (char*)malloc(2 * len + 1);

	for (int i = 0; i < len; i++)
	{
		s[2*i] = '0' + (src[i] >> 4);
		s[2*i+1] = '0' + (src[i] & 0x0F);
		if (s[2*i] > '9') s[2*i] += 'A' - '9' - 1;
		if (s[2*i+1] > '9') s[2*i+1] += 'A' - '9' - 1;
	}

	s[2*len] = '\0';
	TRACE2("%s:%s", tag, s);

	free(s);

#endif
}

void InvertBuffer(BYTE* pBuffer, DWORD dwBufferLen)
{
	BYTE tmp = 0;

	for(unsigned long i = 0; i < dwBufferLen / 2; ++i)
	{
		tmp = pBuffer[i];
		pBuffer[i] = pBuffer[dwBufferLen - i - 1];
		pBuffer[dwBufferLen - i - 1] = tmp;
	}	
}


long getCurrentTime(){
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
