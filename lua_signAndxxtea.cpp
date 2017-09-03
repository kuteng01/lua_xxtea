#include "stdafx.h"
#include "lua_SignAndXXTEA.h"
#include <string>

#include "xxtea.h"


lua_SignAndXXTEA::lua_SignAndXXTEA()
{
}
//使用完记得释放
unsigned char * lua_SignAndXXTEA::lua_SignAndEncrypt(const char * src, size_t src_len, const char* xxteaKey, size_t xxteaKeyLen, const char* xxteaSign, size_t xxteaSignLen, size_t *retLen)
{
	void* buffer = nullptr;
	unsigned char* ret = nullptr;


	size_t len = 0;
	buffer = xxtea_encrypt(src, (size_t)src_len, (unsigned char*)xxteaKey, &len);
	ret = (unsigned char*)malloc(len + xxteaSignLen + 1);
	memcpy(ret, xxteaSign, xxteaSignLen);
	memcpy(ret + xxteaSignLen, buffer, len);
	ret[len + xxteaSignLen] = '\0';
	free(buffer);
	buffer = nullptr;
	*retLen = len + xxteaSignLen;
	return ret;

	
}


//使用完记得释放
unsigned char*  lua_SignAndXXTEA::lua_SignAndDecrypt(const char * src, size_t src_len, const char* xxteaKey, size_t xxteaKeyLen, const char* xxteaSign, size_t xxteaSignLen, size_t *retLen)
{
	unsigned char* buffer = nullptr;

	size_t len = 0;
	buffer = (unsigned char*)xxtea_decrypt(src + xxteaSignLen, src_len - xxteaSignLen, xxteaKey, &len);

	*retLen = len;
	return buffer;
}