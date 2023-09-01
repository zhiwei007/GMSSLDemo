#ifndef __UTILS_H
#define __UTILS_H

#ifndef WIN32
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void StrToHex(BYTE *pbDest, char *szSrc, DWORD dwLen);

void HexToStr(char *szDest, const BYTE *pbSrc, DWORD dwLen);

void PrintHex(char* tag, unsigned char * src, int len);

void InvertBuffer(BYTE* pBuffer, DWORD dwBufferLen);


long getCurrentTime();











#ifdef __cplusplus
}
#endif

#endif // __UTILS_H
