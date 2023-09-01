/*
 * log.h
 *
 *  Created on: 2014-2-14
 *      Author: song
 */

#ifndef LOG_H_
#define LOG_H_

#include "utils.h"
#include <android/log.h>
#include <string>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "gmssl", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "gmssl", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "gmssl", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "gmssl", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "gmssl", __VA_ARGS__)

#define DEBUG
#if defined(DEBUG) || defined(_DEBUG)
#define TRACE0(s) { LOGE(s); }
#define TRACE1(s, p1) { LOGE(s, p1); }
#define TRACE2(s, p1, p2) { LOGE(s, p1, p2); }
void printHex(const char *szTag,const BYTE *pbBuff, DWORD dwLen);
#define TRACE3(s, p1, p2, p3) { LOGE(s, p1, p2, p3); }
#else

#endif

using namespace std;


#endif /* LOG_H_ */
