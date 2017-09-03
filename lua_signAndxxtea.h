
class lua_SignAndXXTEA
{
public:
	lua_SignAndXXTEA();	// 标准构造函数
public:
	static unsigned char*  lua_SignAndEncrypt(const char * src, size_t src_len, const char* xxteaKey, size_t xxteaKeyLen, const char* xxteaSign, size_t xxteaSignLen, size_t *retLen);
	static unsigned char*  lua_SignAndDecrypt(const char * src, size_t src_len, const char* xxteaKey, size_t xxteaKeyLen, const char* xxteaSign, size_t xxteaSignLen, size_t *retLen);
};
