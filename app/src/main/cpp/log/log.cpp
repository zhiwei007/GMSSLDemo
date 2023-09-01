/*
 * log.cpp
 *
 *  Created on: 2014-2-14
 *      Author: song
 */
#include "log.h"
#include <string.h>
#include <stdlib.h>
void printHex(const char *szTag, const BYTE *pbBuff, DWORD dwLen)
{
#if defined(DEBUG) || defined(_DEBUG)
	if (szTag == NULL || pbBuff == NULL || dwLen ==0) {
		return;
	}
	char *szMsg = (char*)malloc(dwLen*2);
	HexToStr(szMsg, pbBuff, dwLen);

	TRACE2("%s:%s",szTag,szMsg);

	free(szMsg);
#endif
}

