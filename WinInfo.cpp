#include "StdAfx.h"
#include "WinInfo.h"
/*
2016-9-19 调整为支持UNICODE 同时去掉reg类
*/





//////////////////////////////////////////////////////////////////////////
//字符串处理模块
CXString  mStrdec;

//构造
CXString::CXString()
{
	ArrRetA.clear();
	ArrRetW.clear();
}

//析构
CXString::~CXString()
{
}



//unicode字符串转ansi字符串
int CXString::ustr_astr( WCHAR* Unicodestr, char *Ansistr )
{
	int iLen = 0;
	WCHAR* pbuf = new WCHAR[wcslen(Unicodestr) * sizeof(WCHAR)+1];
	swprintf(pbuf,wcslen(Unicodestr) * sizeof(WCHAR), L"%s", Unicodestr);
	int result = 0;
	try
	{
		int needlen = WideCharToMultiByte( CP_ACP, 0, Unicodestr, -1, NULL, 0, NULL, NULL );
		if( needlen < 0 )
		{
			iLen=  needlen;
			goto Lend;
		}

		result = WideCharToMultiByte( CP_ACP, 0, Unicodestr, -1, Ansistr, needlen + 1, NULL, NULL );
		if( result < 0 )
		{
			iLen =  result;
			goto Lend;
		}

	}
	catch( ... )
	{
		//DebugPrint(L"ustr_astr Err");
	}
Lend:
	delete pbuf;

	return result;
}

//ansi字符串转unicode字符串
int CXString::astr_ustr( char *Ansistr, WCHAR* Unicodestr )
{
	int result = 0;
	try
	{
		//size_t len = strlen( Ansistr );
		int needlen = MultiByteToWideChar( CP_ACP, 0, Ansistr, -1, NULL, 0 );
		if( needlen < 0 )
		{
			result =  needlen;
			goto Lend;
		}

		result = MultiByteToWideChar( CP_ACP, 0, Ansistr, -1, Unicodestr, needlen + 1 );
		if( result < 0 )
		{
			result =  result;
			goto Lend;
		}
		result = wcslen( Unicodestr );
	}
	catch( ... )
	{
		//DebugPrint(L"astr_ustr Err");
	}


Lend:

	return result;
}


//分割A
BOOL CXString::SplitA(string SourceStr, string LimitStr)
{
	BOOL bRet = TRUE;
	string tCode;
	int   LimitLen = LimitStr.size();

	ArrRetA.clear();
	if (SourceStr.size() && LimitLen)
	{
		string strcc = SourceStr.substr(SourceStr.size() - LimitLen,LimitLen);
		if(strcc != LimitStr)
		{
			tCode = SourceStr + LimitStr;	
		}
		else
		{
			tCode = SourceStr ;
		}

		int   pre_pos=0, pos    = 0, i = -1;
		while( -1 != pos )
		{
			pre_pos = pos;
			pos = tCode.find(LimitStr,(pos+1));
			if (-1 == pos)
			{
				bRet = FALSE;
				break;
			}

			if (pre_pos==0)
			{
				ArrRetA.push_back(tCode.substr(pre_pos , pos-pre_pos));
			}
			else
			{
				ArrRetA.push_back(tCode.substr(pre_pos+LimitLen , pos-pre_pos- LimitLen));
			}
		}

	}
	return bRet;
}


//分割W
BOOL CXString::SplitW(wstring SourceStr, wstring LimitStr)
{
	BOOL bRet = TRUE;
	wstring tCode;
	int  LimitLen = LimitStr.size();

	ArrRetW.clear();
	if (SourceStr.size() && LimitLen)
	{
		wstring strcc = SourceStr.substr(SourceStr.size() - LimitLen,LimitLen);
		if(strcc != LimitStr)
		{
			tCode = SourceStr + LimitStr;	
		}
		else
		{
			tCode = SourceStr ;
		}

		int   pre_pos=0, pos    = 0, i = -1;
		while( -1 != pos )
		{
			pre_pos = pos;
			pos = tCode.find(LimitStr,(pos+1));
			if (-1 == pos)
			{
				bRet = FALSE;
				break;
			}

			if (pre_pos==0)
			{
				ArrRetW.push_back(tCode.substr(pre_pos , pos-pre_pos));
			}
			else
			{
				ArrRetW.push_back(tCode.substr(pre_pos+LimitLen , pos-pre_pos- LimitLen));
			}
		}
	}
	return bRet;
}

//宽字符处理
BOOL CXString::SplitExA(string SourceStr,string LimitStr, vector<string> &ArrRet)
{
	BOOL    bRet = TRUE;
	string  tCode;
	string  strcc;
	int   LimitLen = LimitStr.size();

	ArrRet.clear();
	if (SourceStr.size() && LimitLen)
	{
		strcc = SourceStr.substr(SourceStr.size() - LimitLen,LimitLen);
		if(strcc != LimitStr)
		{
			tCode = SourceStr + LimitStr;	
		}
		else
		{
			tCode = SourceStr ;
		}

		int   pre_pos=0, pos    = 0, i = -1;
		while( -1 != pos )
		{
			pre_pos = pos;
			pos = tCode.find(LimitStr,(pos+1));

			if (-1 == pos)
			{
				bRet = FALSE;
				break;
			}
			if (pre_pos==0)
			{
				ArrRet.push_back(tCode.substr(pre_pos , pos-pre_pos));
			}
			else
			{
				ArrRet.push_back(tCode.substr(pre_pos+LimitLen , pos-pre_pos- LimitLen));
			}
		}
	}
	return bRet;
}


BOOL  CXString:: SplitExW(wstring SourceStr,wstring LimitStr, vector<wstring> &ArrRet)
{

	BOOL     bRet = TRUE;
	wstring  tCode;
	wstring  strcc;
	int   LimitLen = LimitStr.size();

	ArrRet.clear();
	if (SourceStr.size() && LimitLen)
	{
		strcc = SourceStr.substr(SourceStr.size() - LimitLen,LimitLen);
		if(strcc != LimitStr)
		{
			tCode = SourceStr + LimitStr;	
		}
		else
		{
			tCode = SourceStr ;
		}

		int   pre_pos=0, pos    = 0, i = -1;
		while( -1 != pos )
		{
			pre_pos = pos;
			pos = tCode.find(LimitStr,(pos+1));

			if (-1 == pos)
			{
				bRet = FALSE;
				break;
			}
			if (pre_pos==0)
			{
				ArrRet.push_back(tCode.substr(pre_pos , pos-pre_pos));
			}
			else
			{
				ArrRet.push_back(tCode.substr(pre_pos+LimitLen , pos-pre_pos- LimitLen));
			}
		}
	}
	return bRet;
}

//获取随机
int CXString::GetRnd(int Min,int Max)
{
	int iRnd = 0;
	int iDivv = Max - Min ;
	if(iDivv > 1)
	{
		__asm 
		{
			RDTSC
			MOV EDX,0
			MOV ECX,iDivv
			IDIV ECX
			MOV ECX,Min
			Add EDX,ECX
			MOV iRnd,EDX
		}
	}
	return iRnd;
}

BYTE CXString:: GetStrToByte(char* pStr, int iLen)
{
	BYTE bRet = 0;
	char buf[MAX_PATH] = {0};

	if (iLen != 2 && iLen != 1) return 0;

	strcpy_s(buf,pStr);
	buf[iLen] = '\0';
	if (buf)
	{

		bRet = strtoul(buf,0,0x10) & 0xFF;
	}
	return bRet;

}

//如果是全数字或者全英文返回假否则返回真
//0 :混合类型
//1 :纯数字
//2 :纯英文

int CXString:: CheckStrInvalid(CDuiStringEx& Account)
{
	int bRet = 0;
	int iNum = 1;
	int iStr = 1;
	CDuiStringEx tStr = Account;

	tStr.MakeLower();

	if (tStr.GetLength() == 0)
	{
		iNum = 0;
		iStr = 0;
	}

	for (int i=0; i<tStr.GetLength(); i++)
	{
		if (iNum == 1)
		{
			if (tStr.GetAt(i) < '0' || tStr.GetAt(i) > '9')
			{
				iNum = 0;
			}
		}


		if (iStr == 1)
		{
			if (tStr.GetAt(i) < 'a' || tStr.GetAt(i) > 'z')
			{
				iStr = 0;
			}
		}
	}

	if (iNum==1)
	{
		bRet = 1;
	}
	else if(iStr==1)
	{
		bRet = 2;
	}
	else
	{
		bRet = 0;
	}
	return bRet;
}



//混合字符串 2位以上管用
//1 ： 纯数组混合英文
//2 ： 纯英文混合数字
BOOL CXString:: SetRndInvalidStr(CDuiStringEx &inStr, int iType)
{
	BOOL bRet = FALSE;
	int  iRnd = GetRnd(0, inStr.GetLength());
	int  iRndTxt = 0;

	if (inStr.GetLength() > 2)
	{

		if (iType==1)
		{
			iRndTxt = GetRnd('a', 'z');
			inStr.SetAt(iRnd, iRndTxt);
			bRet = TRUE;
		}
		if (iType==2)
		{
			iRndTxt = GetRnd('0', '9');
			inStr.SetAt(iRnd, iRndTxt);
			bRet = TRUE;
		}
	}

	return bRet;
}



/************************************************************************/
/* 代码转换                                                             */
/************************************************************************/


/* {{{ php_htoi
*/
static int php_htoi(char *s)
{
	int value;
	int c;

	c = ((unsigned char *)s)[0];
	if (isupper(c))
		c = tolower(c);
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = ((unsigned char *)s)[1];
	if (isupper(c))
		c = tolower(c);
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return (value);
}
/* }}} */

/* {{{ URL解码，提取自PHP 5.2.17
用法：string urldecode(string str_source)
时间：2012-8-14 By Dewei
*/
string CXString::urldecode(string &str_source)
{
	char const *in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	char *str;

	str = _strdup(in_str);
	char *dest = str;
	char *data = str;

	while (in_str_len--) {
		if (*data == '+') {
			*dest = ' ';
		}
		else if (*data == '%' && in_str_len >= 2 && isxdigit((int)*(data + 1))
			&& isxdigit((int)*(data + 2))) {
			*dest = (char)php_htoi(data + 1);
			data += 2;
			in_str_len -= 2;
		}
		else {
			*dest = *data;
		}
		data++;
		dest++;
	}
	*dest = '\0';
	out_str_len = dest - str;
	out_str = str;
	free(str);
	return out_str;
}
/* }}} */



string&   replace_all(string&   str, const   string&   old_value, const   string&   new_value)
{
	while (true)   {
		string::size_type   pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}
string&    CXString::replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

/* {{{ URL编码，提取自PHP
用法：string urlencode(string str_source)
说明：仅不编码 -_. 其余全部编码，空格会被编码为 +
时间：2012-8-13 By Dewei
*/
string CXString::urlencode(string &str_source)
{
	char const *in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	register unsigned char c;
	unsigned char *to, *start;
	unsigned char const *from, *end;
	unsigned char hexchars[] = "0123456789ABCDEF";

	from = (unsigned char *)in_str;
	end = (unsigned char *)in_str + in_str_len;
	start = to = (unsigned char *)malloc(3 * in_str_len + 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
		}
		else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else {
			*to++ = c;
		}
	}
	*to = 0;

	out_str_len = to - start;
	out_str = (char *)start;
	free(start);

	out_str = replace_all(out_str, "+", "%20");
	return out_str;
}
/* }}} */
// 
// /* {{{ URL编码CString版，提取自PHP 5.2.17
// 用法：CString urlencode(CString str_source)
// 说明：仅不编码 -_. 其余全部编码，空格会被编码为 +
// 时间：2012-8-13 By Dewei
// */
// CString urlencode(CString &str_source)
// {
// 	char const *in_str = str_source;
// 	int in_str_len = strlen(in_str);
// 	int out_str_len = 0;
// 	CString out_str = '\0';
// 	register unsigned char c;
// 	unsigned char *to, *start;
// 	unsigned char const *from, *end;
// 	unsigned char hexchars[] = "0123456789ABCDEF";
// 
// 	from = (unsigned char *)in_str;
// 	end = (unsigned char *)in_str + in_str_len;
// 	start = to = (unsigned char *) malloc(3*in_str_len+1);
// 
// 	while (from < end) {
// 		c = *from++;
// 
// 		if (c == ' ') {
// 			*to++ = '+';
// 		} else if ((c < '0' && c != '-' && c != '.') ||
// 			(c < 'A' && c > '9') ||
// 			(c > 'Z' && c < 'a' && c != '_') ||
// 			(c > 'z')) { 
// 				to[0] = '%';
// 				to[1] = hexchars[c >> 4];
// 				to[2] = hexchars[c & 15];
// 				to += 3;
// 		} else {
// 			*to++ = c;
// 		}
// 	}
// 	*to = 0;
// 
// 	out_str_len = to - start;
// 	out_str = (char *) start;
// 	free(start);
// 	return out_str;
// }

// 
// 
// string CXString::MakeUpper(string szText)
// {
// 	string sRet;
// 	return sRet;
// }
// string  CXString::LEFT(string szText)
// {
// 	string sRet;
// 	return sRet;
// }
// string  CXString::MID(string szText)
// {
// 	string sRet;
// 	return sRet;
// }
// string  CXString::Replace(string szText, TCHAR* oldTxt, TCHAR* NewTxt)
// {
// 	string sRet;
// 	return sRet;
// }
// 
// string  CXString::Remove(string szText, TCHAR* oldTxt)
// {
// 	string sRet;
// 	return sRet;
// }
// string  CXString::Trim(string szText)
// {
// 	string sRet;
// 	return sRet;
// }




// 注释：多字节包括GBK和UTF-8
int CXString::GBK2UTF8(char *szGbk, char *szUtf8, int utf8OutLen)
{
	// 先将多字节GBK（CP_ACP或ANSI）转换成宽字符UTF-16
	// 得到转换后，所需要的内存字符数
	int n = MultiByteToWideChar(CP_ACP, 0, szGbk, -1, NULL, 0);
	// 字符数乘以 sizeof(WCHAR) 得到字节数
	WCHAR *str1 = new WCHAR[sizeof(WCHAR)* n];
	// 转换
	MultiByteToWideChar(CP_ACP,  // MultiByte的代码页Code Page
		0,            //附加标志，与音标有关
		szGbk,        // 输入的GBK字符串
		-1,           // 输入字符串长度，-1表示由函数内部计算
		str1,         // 输出
		n             // 输出所需分配的内存
		);

	// 再将宽字符（UTF-16）转换多字节（UTF-8）
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	if (n > utf8OutLen)
	{
		delete[]str1;
		return -1;
	}
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, szUtf8, n, NULL, NULL);
	delete[]str1;
	str1 = NULL;

	return 0;
}



//UTF-8 GBK
int CXString::UTF82GBK(char *szUtf8, char *szGbk, int GbkOutLen)
{
	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);
	WCHAR * wszGBK = new WCHAR[sizeof(WCHAR)* (n+1)];
	memset(wszGBK, 0, sizeof(WCHAR)* (n+1));
	MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, wszGBK, n);

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	if (n > GbkOutLen)
	{
		delete[]wszGBK;
		return -1;
	}

	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGbk, n, NULL, NULL);

	delete[]wszGBK;
	wszGBK = NULL;

	return 0;
}








//base64 start



static const CHAR* DATA_BIN2ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 
 

void CXString::Base64_encode(char *src, int src_len, char *dst)

{

	int i = 0, j = 0;

	char base64_map[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 

	for (; i < src_len - src_len % 3; i += 3) {

		dst[j++] = base64_map[(src[i] >> 2) & 0x3F];

		dst[j++] = base64_map[((src[i] << 4) & 0x30) + ((src[i + 1] >> 4) & 0xF)];

		dst[j++] = base64_map[((src[i + 1] << 2) & 0x3C) + ((src[i + 2] >> 6) & 0x3)];

		dst[j++] = base64_map[src[i + 2] & 0x3F];

	}



	if (src_len % 3 == 1) {

		dst[j++] = base64_map[(src[i] >> 2) & 0x3F];

		dst[j++] = base64_map[(src[i] << 4) & 0x30];

		dst[j++] = '=';

		dst[j++] = '=';

	}

	else if (src_len % 3 == 2) {

		dst[j++] = base64_map[(src[i] >> 2) & 0x3F];

		dst[j++] = base64_map[((src[i] << 4) & 0x30) + ((src[i + 1] >> 4) & 0xF)];

		dst[j++] = base64_map[(src[i + 1] << 2) & 0x3C];

		dst[j++] = '=';

	}



	dst[j] = '\0';

}



void CXString::Base64_decode(char *src, int src_len, char *dst)

{

	int i = 0, j = 0;

	unsigned char base64_decode_map[256] = {

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 62, 255, 255, 255, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255,

		255, 0, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,

		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255, 255, 26, 27, 28,

		29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,

		49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};



		for (; i < src_len; i += 4) {

			dst[j++] = base64_decode_map[src[i]] << 2 |

				base64_decode_map[src[i + 1]] >> 4;

			dst[j++] = base64_decode_map[src[i + 1]] << 4 |

				base64_decode_map[src[i + 2]] >> 2;

			dst[j++] = base64_decode_map[src[i + 2]] << 6 |

				base64_decode_map[src[i + 3]];

		}



		dst[j+=6] = L'\0';

}


//base64 end







///////////////////////////////////////MSTRDEC END/////////////////////////////////



































///////////////////////////////////////md5START/////////////////////////////////
ZMD5 zmd;

#define FILE_BUFFER_READ 1048576 //读取文件的缓冲区,这个值必须是64的整数倍
ZMD5::ZMD5()
{
	m_FileOpen = false;
}

ZMD5::~ZMD5()
{
	if (m_FileOpen)
		fclose(m_pFile);
}

unsigned int ZMD5::ROTATE_LEFT(unsigned int x, unsigned int n)
{
	return (((x) << (n)) | ((x) >> (32 - (n))));
}

unsigned int ZMD5::F(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) | ((~x) & z));
}
unsigned int ZMD5::G(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & z) | (y & (~z)));
}

unsigned int ZMD5::H(unsigned int x, unsigned int y, unsigned int z)
{
	return x ^ y ^ z;
}

unsigned int ZMD5::I(unsigned int x, unsigned int y, unsigned int z)
{
	return (y ^ (x | (~z)));
}

void ZMD5::FFF(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac)
{
	(a) += F((b), (c), (d)) + (x)+(ac);
	(a) = ROTATE_LEFT((a), (s));
	(a) += (b);
}

void ZMD5::GGG(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac)
{
	(a) += G((b), (c), (d)) + (x)+(ac);
	(a) = ROTATE_LEFT((a), (s));
	(a) += (b);
}

void ZMD5::HHH(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac)
{
	(a) += H((b), (c), (d)) + (x)+(ac);
	(a) = ROTATE_LEFT((a), (s));
	(a) += (b);
}

void ZMD5::III(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac)
{
	(a) += I((b), (c), (d)) + (x)+(ac);
	(a) = ROTATE_LEFT((a), (s));
	(a) += (b);
}

void ZMD5::Init()
{
	S11 = 7;	S21 = 5;	S31 = 4;	S41 = 6;
	S12 = 12;	S22 = 9;	S32 = 11;	S42 = 10;
	S13 = 17;	S23 = 14;	S33 = 16;	S43 = 15;
	S14 = 22;	S24 = 20;	S34 = 23;	S44 = 21;

	A = 0x67452301;  // in memory, this is 0x01234567
	B = 0xEFCDAB89;  // in memory, this is 0x89ABCDEF
	C = 0x98BADCFE;  // in memory, this is 0xFEDCBA98
	D = 0x10325476;  // in memory, this is 0x76543210
}

void ZMD5::Append(unsigned int MsgLen)
{
	//计算要补位的字节数
	int m = MsgLen % 64;
	if (m == 0)
		m_AppendByte = 56;
	else if (m<56)
		m_AppendByte = 56 - m;
	else
		m_AppendByte = 64 - m + 56;

	/*
	记录原始信息长度(单位:bit),以下过程将一个32位的字节数转
	换为64位的bit数,这个计算过程和rfc1321.txt中的略有不同.
	*/

	//截取传入长度的高十六位和低十六位
	int hWord = (MsgLen & 0xFFFF0000) >> 16;
	int lWord = MsgLen & 0x0000FFFF;

	//将低十六位和高十六位分别乘以八(1byte=8bit)
	int hDiv = hWord * 8;
	int lDiv = lWord * 8;

	//
	m_MsgLen[0] = lDiv & 0xFF;
	m_MsgLen[1] = (lDiv >> 8) & 0xFF;
	m_MsgLen[2] = ((lDiv >> 16) & 0xFF) | (hDiv & 0xFF);
	m_MsgLen[3] = (hDiv >> 8) & 0xFF;
	m_MsgLen[4] = (hDiv >> 16) & 0xFF;
	m_MsgLen[5] = (hDiv >> 24) & 0xFF;
	m_MsgLen[6] = 0;
	m_MsgLen[7] = 0;
}

void ZMD5::Transform(unsigned char Block[64])
{
	//将64字节位转换为16个字节
	unsigned long x[16];
	for (int i = 0, j = 0; j<64; i++, j += 4)
		x[i] = Block[j] | Block[j + 1] << 8 | Block[j + 2] << 16 | Block[j + 3] << 24;

	//初始化临时寄存器变量
	unsigned int a, b, c, d;
	a = A; b = B; c = C; d = D;

	//第一轮计算
	FFF(a, b, c, d, x[0], S11, 0xD76AA478); //  1
	FFF(d, a, b, c, x[1], S12, 0xE8C7B756); //  2
	FFF(c, d, a, b, x[2], S13, 0x242070DB); //  3
	FFF(b, c, d, a, x[3], S14, 0xC1BDCEEE); //  4
	FFF(a, b, c, d, x[4], S11, 0xF57C0FAF); //  5
	FFF(d, a, b, c, x[5], S12, 0x4787C62A); //  6
	FFF(c, d, a, b, x[6], S13, 0xA8304613); //  7
	FFF(b, c, d, a, x[7], S14, 0xFD469501); //  8
	FFF(a, b, c, d, x[8], S11, 0x698098D8); //  9
	FFF(d, a, b, c, x[9], S12, 0x8B44F7AF); // 10 
	FFF(c, d, a, b, x[10], S13, 0xFFFF5BB1); // 11 
	FFF(b, c, d, a, x[11], S14, 0x895CD7BE); // 12 
	FFF(a, b, c, d, x[12], S11, 0x6B901122); // 13 
	FFF(d, a, b, c, x[13], S12, 0xFD987193); // 14 
	FFF(c, d, a, b, x[14], S13, 0xA679438E); // 15 
	FFF(b, c, d, a, x[15], S14, 0x49B40821); // 16 

	//第二轮计算
	GGG(a, b, c, d, x[1], S21, 0xF61E2562); // 17 
	GGG(d, a, b, c, x[6], S22, 0xC040B340); // 18 
	GGG(c, d, a, b, x[11], S23, 0x265E5A51); // 19 
	GGG(b, c, d, a, x[0], S24, 0xE9B6C7AA); // 20 
	GGG(a, b, c, d, x[5], S21, 0xD62F105D); // 21 
	GGG(d, a, b, c, x[10], S22, 0x2441453); // 22 
	GGG(c, d, a, b, x[15], S23, 0xD8A1E681); // 23 
	GGG(b, c, d, a, x[4], S24, 0xE7D3FBC8); // 24 
	GGG(a, b, c, d, x[9], S21, 0x21E1CDE6); // 25 
	GGG(d, a, b, c, x[14], S22, 0xC33707D6); // 26 
	GGG(c, d, a, b, x[3], S23, 0xF4D50D87); // 27 
	GGG(b, c, d, a, x[8], S24, 0x455A14ED); // 28 
	GGG(a, b, c, d, x[13], S21, 0xA9E3E905); // 29 
	GGG(d, a, b, c, x[2], S22, 0xFCEFA3F8); // 30 
	GGG(c, d, a, b, x[7], S23, 0x676F02D9); // 31 
	GGG(b, c, d, a, x[12], S24, 0x8D2A4C8A); // 32 

	//第三轮计算
	HHH(a, b, c, d, x[5], S31, 0xFFFA3942); // 33 
	HHH(d, a, b, c, x[8], S32, 0x8771F681); // 34 
	HHH(c, d, a, b, x[11], S33, 0x6D9D6122); // 35 
	HHH(b, c, d, a, x[14], S34, 0xFDE5380C); // 36 
	HHH(a, b, c, d, x[1], S31, 0xA4BEEA44); // 37 
	HHH(d, a, b, c, x[4], S32, 0x4BDECFA9); // 38 
	HHH(c, d, a, b, x[7], S33, 0xF6BB4B60); // 39 
	HHH(b, c, d, a, x[10], S34, 0xBEBFBC70); // 40 
	HHH(a, b, c, d, x[13], S31, 0x289B7EC6); // 41 
	HHH(d, a, b, c, x[0], S32, 0xEAA127FA); // 42 
	HHH(c, d, a, b, x[3], S33, 0xD4EF3085); // 43 
	HHH(b, c, d, a, x[6], S34, 0x4881D05); // 44 
	HHH(a, b, c, d, x[9], S31, 0xD9D4D039); // 45 
	HHH(d, a, b, c, x[12], S32, 0xE6DB99E5); // 46 
	HHH(c, d, a, b, x[15], S33, 0x1FA27CF8); // 47 
	HHH(b, c, d, a, x[2], S34, 0xC4AC5665); // 48 

	//第四轮计算
	III(a, b, c, d, x[0], S41, 0xF4292244); // 49 
	III(d, a, b, c, x[7], S42, 0x432AFF97); // 50 
	III(c, d, a, b, x[14], S43, 0xAB9423A7); // 51 
	III(b, c, d, a, x[5], S44, 0xFC93A039); // 52 
	III(a, b, c, d, x[12], S41, 0x655B59C3); // 53 
	III(d, a, b, c, x[3], S42, 0x8F0CCC92); // 54 
	III(c, d, a, b, x[10], S43, 0xFFEFF47D); // 55 
	III(b, c, d, a, x[1], S44, 0x85845DD1); // 56 
	III(a, b, c, d, x[8], S41, 0x6FA87E4F); // 57 
	III(d, a, b, c, x[15], S42, 0xFE2CE6E0); // 58 
	III(c, d, a, b, x[6], S43, 0xA3014314); // 59 
	III(b, c, d, a, x[13], S44, 0x4E0811A1); // 60 
	III(a, b, c, d, x[4], S41, 0xF7537E82); // 61 
	III(d, a, b, c, x[11], S42, 0xBD3AF235); // 62 
	III(c, d, a, b, x[2], S43, 0x2AD7D2BB); // 63 
	III(b, c, d, a, x[9], S44, 0xEB86D391); // 64 

	//保存当前寄存器结果
	A += a; B += b; C += c; D += d;
}

/*********************************************
将寄存器ABCD的最终值转换为十六进制返回给用户
注意:低位在前高位在后
*********************************************/
bool ZMD5::ToHex(bool UpperCase, char* outstr)
{
	//CString strResult;

	string strResult = "";
	//char strResult[MAX_PATH] = { 0 };
	char Buf[33] = { 0 };

	int ResultArray[4] = { A, B, C, D };

	for (int i = 0; i<4; i++)
	{
		memset(Buf, 0, 3);
		sprintf_s(Buf, 3, ("%02x"), ResultArray[i] & 0x00FF);
		strResult+=Buf;
		//strcat(strResult, Buf);
		 

		memset(Buf, 0, 3);
		sprintf_s(Buf, 3, ("%02x"), (ResultArray[i] >> 8) & 0x00FF);
		strResult+=Buf;
		//strcat(strResult, Buf);
	
		memset(Buf, 0, 3);
		sprintf_s(Buf, 3, ("%02x"), (ResultArray[i] >> 16) & 0x00FF);
		strResult+=Buf;
		//strcat(strResult, Buf);

		memset(Buf, 0, 3);
		sprintf_s(Buf, 3, ("%02x"), (ResultArray[i] >> 24) & 0x00FF);
		strResult+=Buf;
		//strcat(strResult, Buf);
	}
	//if(UpperCase) 
	//CharUpper((char *)strResult.c_str());
	//strResult.MakeUpper();
	strcpy(outstr, strResult.c_str());
	outstr[33] = 0;
	//::MessageBox(0, strResult, 0, 0x40);
	//sprintf_s(outstr, 50,"%s", strResult);//	strcpy(outstr, strResult);
	return true;//strResult.LockBuffer();
}

  
/**************************************
MD5的主要计算过程可以参照这个函数
**************************************/
bool ZMD5::GetMD5OfString(char* InputMessageA, bool UpperCase, char* outbuf)
{

	string InputMessage = InputMessageA;
	//初始化MD5所需常量
	Init();

	//计算追加长度
	Append(InputMessage.length());

	//对原始信息进行补位
	for (int i = 0; i<m_AppendByte; i++)
	{
		if (i == 0)
			InputMessage += (char)0x80;
		else
			InputMessage += (char)0x0;
	}

	//将原始信息长度附加在补位后的数据后面
	for (int i = 0; i<8; i++) InputMessage += m_MsgLen[i];

	//位块数组
	unsigned char x[64] = { 0 };

	//循环,将原始信息以64字节为一组拆分进行处理
	for (UINT i = 0, Index = -1; i< InputMessage.length(); i++)
	{
		x[++Index] = InputMessage[i];
		if (Index == 63)
		{
			Index = -1;
			Transform(x);
		}
	}
	ToHex(UpperCase, outbuf);

	return true;
}

/************************************************************************
对文件做MD5运算的道理和对字符串的道理一样,只不过数据来源于磁盘文件而已
记事:以为自己对文件操作很熟悉,不小心把"rb"写成"wb",唉,后果可想而知!
************************************************************************/
string ZMD5::GetMD5OfFile(const string FileName, bool UpperCase)
{
	//定义读取文件的缓冲区
	char* ReadBuf = new char[FILE_BUFFER_READ + 1];
	memset(ReadBuf, 0, FILE_BUFFER_READ);

	try
	{
		//检查文件是否存在
		if ((_access(FileName.c_str(), 0)) == -1) return "";

		//二进制方式读取文件
		fopen_s(&m_pFile, FileName.c_str(), "rb");
		if (!m_pFile)
		{
			return "";
		}
		//if (m_pFile = fopen(FileName.c_str(), "rb"), m_pFile == NULL) return "";
		m_FileOpen = true;

		//获取文件大小
		unsigned long FileSize = 0xFFFF;
		WIN32_FIND_DATAA  win32_find_data;
		HANDLE hFile;
		if ((hFile = FindFirstFileA(FileName.c_str(), &win32_find_data)) != INVALID_HANDLE_VALUE)
		if (hFile == NULL) return "";
		if (FileSize = win32_find_data.nFileSizeLow, FileSize == 0xFFFF || FileSize == 0) return "";
		FindClose(hFile);

		//初始化MD5所需常量
		Init();

		//通过文件长度计算追加长度
		Append(FileSize);

		//位块数组
		unsigned char x[64] = { 0 };

		//本次读取字节数
		int ReadSize = fread(ReadBuf, 1, FILE_BUFFER_READ, m_pFile);

		//读取次数
		int ReadCount = 0;

		while (ReadSize == FILE_BUFFER_READ)
		{
			/*
			如果用户开启了另一个线程调用此函数,则允许用户从外部结
			束此函数,为安全起见,没有在这个类的内部开启线程,可以最
			大限度的保正了文件安全关闭
			*/
			if (!m_FileOpen)
			{
				fclose(m_pFile);
				return "";
			}

			//将处理进度返回给用户
			ReadCount++;
			//OnProcessing((int)(FILE_BUFFER_READ * ReadCount / (FileSize / 100)));

			//将原始信息以64字节为一组拆分进行处理
			for (int i = 0, Index = -1; i<FILE_BUFFER_READ; i++)
			{
				x[++Index] = ReadBuf[i];
				if (Index == 63)
				{
					Index = -1;
					Transform(x);
				}
			}
			memset(ReadBuf, 0, FILE_BUFFER_READ); // 重置缓冲区
			ReadSize = fread(ReadBuf, 1, FILE_BUFFER_READ, m_pFile);
		} // end while

		/*
		处理不能被整除的剩余部分数据,此时要对剩
		余部分数据进行补位及长原始信息长度追加
		*/

		/*
		如果最后一次读取数据的长度为零,说明文件已被读完,
		则直接将补位数据及原信息长度送入Transform处理
		*/
		if (ReadSize == 0)
		{
			string strData;
			for (int i = 0; i<m_AppendByte; i++)
			{
				if (i == 0)
					strData += (char)0x80;
				else
					strData += (char)0x0;
			}

			for (int i = 0; i<8; i++) strData += m_MsgLen[i];

			for (UINT i = 0, Index = -1; i<strData.length(); i++)
			{
				x[++Index] = strData[i];
				if (Index == 63)
				{
					Index = -1;
					Transform(x);
				}
			}
		}
		else // 将剩余数据处理完再补位
		{
			for (int i = 0, Index = -1; i<ReadSize + m_AppendByte + 8; i++)
			{
				//将原始信息以64字节为一组,进行拆分处理
				if (i<ReadSize)
					x[++Index] = ReadBuf[i];
				else if (i == ReadSize)
					x[++Index] = (unsigned char)0x80;
				else if (i<ReadSize + m_AppendByte)
					x[++Index] = (unsigned char)0x0;
				else if (i == ReadSize + m_AppendByte)
					x[++Index] = m_MsgLen[0];
				else if (i == ReadSize + m_AppendByte + 1)
					x[++Index] = m_MsgLen[1];
				else if (i == ReadSize + m_AppendByte + 2)
					x[++Index] = m_MsgLen[2];
				else if (i == ReadSize + m_AppendByte + 3)
					x[++Index] = m_MsgLen[3];
				else if (i == ReadSize + m_AppendByte + 4)
					x[++Index] = m_MsgLen[4];
				else if (i == ReadSize + m_AppendByte + 5)
					x[++Index] = m_MsgLen[5];
				else if (i == ReadSize + m_AppendByte + 6)
					x[++Index] = m_MsgLen[6];
				else if (i == ReadSize + m_AppendByte + 7)
					x[++Index] = m_MsgLen[7];

				if (Index == 63)
				{
					Index = -1;
					Transform(x);
				}
			}
		}
		//OnProcessing(100);	//处理进度百分之百
		fclose(m_pFile);	//关闭文件
		m_FileOpen = false;	//文件打开状态为false
		delete[] ReadBuf;	//释放动态申请的内存
	}
	catch (...)
	{
		if (m_FileOpen)
			fclose(m_pFile);	//关闭文件
		m_FileOpen = false;	//文件打开状态为false
		delete[] ReadBuf;	//释放动态申请的内存
		return "";
	}

	char nBuf[MAX_PATH] = { 0 };

	ToHex(UpperCase, nBuf);

	return nBuf;
}

///////////////////////////////////////md5END/////////////////////////////////

//////////////////////////////////////////////////////////////////////////















//////////////////////////////////////////////////////////////////////////
//文件处理相关模块
CWinFileInfo mFile;


//构造
CWinFileInfo::CWinFileInfo()
{
	memset(m_Buf, 0, sizeof(m_Buf));
}

//析构
CWinFileInfo::~CWinFileInfo()
{

}


//文件存在
BOOL CWinFileInfo::FileExits(LPCTSTR strFileName)
{
	BOOL bRet = FALSE;
#if UNICODE
	USES_CONVERSION;
	if (_access(W2A(strFileName), 6) == 0)  // 6是否可读写  0 是否存在 F_OK
	{
		bRet = TRUE;
	}
#else
	if (_access((strFileName), 6) == 0)  
	{
		bRet = TRUE;
	}
#endif

	return bRet;
}

//文件存在
BOOL CWinFileInfo::FileExitsA(CHAR* strFileName)
{
	BOOL bRet = FALSE;
 
	if (_access((strFileName), 6) == 0)  
	{
		bRet = TRUE;
	}
 

	return bRet;
}
//目录存在
BOOL CWinFileInfo::FolderExits(LPCTSTR strFileName)
{
	WIN32_FIND_DATA wfd;
	BOOL   rValue = FALSE;
	HANDLE hFind  = FindFirstFile(strFileName,&wfd);
	if ((hFind!=INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = true;
	}
	FindClose(hFind);

	return rValue;
}

//获取文件大小
int CWinFileInfo::GetFileSize(LPCTSTR strFilePath)
{
#pragma warning(disable:4996)
#if UNICODE
	USES_CONVERSION;
	FILE* pFile = fopen(W2A(strFilePath), "r");
#else
	FILE* pFile = fopen(strFilePath, "r");
#endif
	int iRet = 0;
	if( pFile )
	{
		fseek(pFile, 0, SEEK_END);
		iRet = ftell(pFile);
		fclose(pFile);
	}
	return iRet;	
}


//保存文件
BOOL CWinFileInfo::SaveFile(LPCTSTR FileName,LPCTSTR szText,BOOL bNewFile)
{
	FILE* fp = _tfopen(FileName, _T("a+"));
	if (fp)
	{
		_fputts(szText, fp);
		fclose(fp);
	}
	return TRUE;
}

//保存数据
BOOL CWinFileInfo::Savebufer(char* filename, char* buffer, int iLen)
{
	BOOL b_Ret = FALSE;
	FILE *fObj = NULL;
#pragma warning(disable:4996)

	//_ASSERT(buffer);
	fObj  = fopen(filename,"a+");
	if (fObj)
	{
		fseek(fObj,0,SEEK_END);
		fseek(fObj,0,SEEK_SET);
		fwrite((char *)buffer, 1, iLen , fObj);
		fclose(fObj);
		b_Ret = TRUE;
	}
	return b_Ret;
}

//写入文件
BOOL CWinFileInfo::AppendFileText(TCHAR* filePath, TCHAR* szText)
{
	FILE* fp = _tfopen(filePath, _T("a+"));
	if (fp)
	{
		_fputts(szText, fp);
		fclose(fp);
	}
	return TRUE;
}



//读取文件到TXT
//多种调用方法 未完成，现不要用
char* CWinFileInfo::ReadLocalFile(char* filepath, char* lpBuf, int *lpBufLen)
{
	//读文件部分
	int ifLen = 0;

	//file
	//if (!FileExits(filepath))
	{
	//	return NULL;
	}


	FILE *fR = fopen(filepath, "rb");

	//file
	if (!fR)
	{
		if (lpBuf) lpBuf[0] = 0;
		if (lpBufLen) lpBufLen[0] = 0;
		return NULL;
	}
 
	//OutputDebugStringA("1");
	//ilen
	if (NULL == lpBufLen)
	{
		fseek(fR, 0, SEEK_END);
		ifLen = ftell(fR);      //如果传入NULL 表示这里需要自己去获取长度
	}
	else
	{
		ifLen = *lpBufLen;
	}
	if (ifLen <= 0)
	{
		if (lpBuf) lpBuf[0] = 0;
		if (lpBufLen) lpBufLen[0] = 0;
		fclose(fR);
		return NULL;
	}

	//OutputDebugStringA("2");


	//free buf
	if (m_lpbuf)
	{
		free(m_lpbuf);
		m_lpbuf = NULL;
	}
	m_lpbuf = (char*)malloc(ifLen);
	memset(m_lpbuf, 0, ifLen);



	//data
	fseek(fR, 0, SEEK_SET);
	fread(m_lpbuf, 1, ifLen, fR);



	//ret
	if (lpBuf)
	{
		memcpy(lpBuf, m_lpbuf, ifLen);
		lpBuf[ifLen] = 0;
	}
	else
	{
		lpBuf = m_lpbuf;
	}

	if (lpBufLen) *lpBufLen = ifLen;

	fclose(fR);
	
	return m_lpbuf;

}

LONGLONG  CWinFileInfo:: ReadTxtFile(char* szText, vector <string>& outList)
{
	LONGLONG ret = 0;

	if (mFile.FileExitsA(szText))
	{
		//outList.clear();
		char xBuf[0x5000] = { 0 };

		FILE* f = fopen(szText, "r");
		if (f)
		{
			memset(xBuf, 0, sizeof(xBuf));
			while (fgets(xBuf, 0x5000, f))
			{
		 
				int k = 0;
				int iLen = strlen(xBuf);
				if (iLen <= 0)
				{
					continue;
				}

				for (int i = 0; i < iLen; i++)
				{
					if (xBuf[i] != '\r'  && xBuf[i] != '\n')  //' && xBuf[i] != '\t'
					{
						xBuf[k] = xBuf[i];
						k++;
					}
				}
				if (k != iLen)
				{
					xBuf[k] = 0;
				}
				if(strlen(xBuf)>0)
				{
					outList.push_back(xBuf);
				}
			}
			ret = outList.size();
			fclose(f);
		}
	}
	return ret;
}


void CWinFileInfo:: GetFileList(char * lpPath, vector<string> &filelist, bool bDeep)
{
	char szFind[MAX_PATH]={0};
	char szFile[MAX_PATH]={0};
	WIN32_FIND_DATAA FindFileData;
	string str = lpPath;
	strcpy(szFind,lpPath);
	strcat(szFind,"*.*");
	if (lpPath[strlen(lpPath)-1] != '\\'){return;}
	HANDLE hFind=::FindFirstFileA(szFind,&FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)return;
	while(TRUE)
	{
		if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			
			if(FindFileData.cFileName[0] != '.'  && bDeep)
			{
				
				strcpy(szFile,lpPath);
				strcat(szFile,"");
				strcat(szFile,FindFileData.cFileName);
				strcat(szFile,"\\");
				str = szFile;
				//str.append(FindFileData.cFileName);
				//printf("%s\n",str.c_str());
				GetFileList((char*)str.c_str(),filelist,bDeep);
			}
		}
		else
		{
			str = lpPath;
			str.append(FindFileData.cFileName);
			//cout << lpPath;
			//cout << FindFileData.cFileName;
			//printf("\n");
			filelist.push_back( str);
		}
		if(!FindNextFileA(hFind,&FindFileData))break;
	}
	FindClose(hFind);
}


//获取路径(指定)
LPCTSTR CWinFileInfo::GetNewPath(TCHAR* inPath, LPCTSTR AdditionPath, TCHAR* OutPath)
{
	TCHAR nPath[MAX_PATH]= {0};

	//_ASSERT(OutPath);
	if (inPath==NULL)
		::GetModuleFileName( NULL, nPath, sizeof(nPath) );
	else
		_stprintf_s( nPath, MAX_PATH, _T("%s"), inPath);
		//strcpy(nPath, inPath);



	memset(m_Buf, 0, sizeof(m_Buf));


	if(_tcslen(nPath)>0)
	{
		LPTSTR szPos = _tcsrchr( nPath,_T('\\') );
		if (szPos == NULL)
		{
			::GetModuleFileName( NULL, nPath, sizeof(nPath) );
			szPos = _tcsrchr( nPath,_T('\\') );
		}
		szPos++;
		*szPos = _T('\0');
		if (_tcslen(AdditionPath))
		{
			//2016-7-28.txt
			if( MAX_PATH > (_tcslen(nPath) + _tcslen(AdditionPath)))
			{
				_stprintf_s( m_Buf,   MAX_PATH, _T("%s%s"), nPath, AdditionPath);
				_stprintf_s( OutPath, MAX_PATH, _T("%s"), m_Buf);
				//return m_Buf;
			}
		}
		else
		{
			if( MAX_PATH > (_tcslen(nPath) ))
			{
				_stprintf_s( m_Buf,   MAX_PATH, _T("%s"), nPath);
				_stprintf_s( OutPath, MAX_PATH, _T("%s"), m_Buf);
				//return m_Buf;
			}
		}

	}
	return m_Buf;
}
//获取目录
LPCTSTR CWinFileInfo::GetFolder(LPCTSTR FileName, TCHAR* OutPath)
{
	TCHAR nPath[MAX_PATH]= {0};
	memset(m_Buf, 0, sizeof(m_Buf));

	//_ASSERT(OutPath);
	if (FileName==NULL)
		::GetModuleFileName( NULL, nPath, sizeof(nPath) );
	else
		_stprintf_s( nPath, MAX_PATH, _T("%s"), FileName);

	if(_tcslen(nPath)>0)
	{
		LPTSTR szPos = _tcsrchr( nPath,_T('\\') );
		szPos++;
		*szPos = _T('\0');
		_stprintf_s( m_Buf,   MAX_PATH, _T("%s"), nPath);
		_stprintf_s( OutPath, MAX_PATH, _T("%s"), nPath);
		//return m_Buf;
	}
	return m_Buf;
}

//获取文件名
LPCTSTR CWinFileInfo::GetExeName(LPCTSTR FileName, TCHAR* OutPath)
{
	TCHAR nPath[MAX_PATH]= {0};
	memset(m_Buf, 0, sizeof(m_Buf));

	//_ASSERT(OutPath);
	if (FileName==NULL)
		::GetModuleFileName( NULL, nPath, sizeof(nPath) );
	else
		_stprintf_s( nPath, MAX_PATH, _T("%s"), FileName);

	if(_tcslen(nPath)>0)
	{
		LPTSTR szPos = _tcsrchr( nPath,_T('\\') );
		szPos++;
		//*szPos = _T('\0');
		_stprintf_s( m_Buf,   MAX_PATH, _T("%s"), szPos);
		_stprintf_s( OutPath, MAX_PATH, _T("%s"), szPos);
		//return m_Buf;
	}
	return m_Buf;
}
//获取扩展名
LPCTSTR CWinFileInfo::GetExeNameEx(LPCTSTR FileName, TCHAR* OutPath)
{
	TCHAR nPath[MAX_PATH] = {0};

	//_ASSERT(OutPath);
	GetExeName(FileName,nPath);
	_stprintf_s( OutPath, MAX_PATH, _T("%s"), _tcsstr(FileName, _T(".")));
	_stprintf_s( m_Buf,   MAX_PATH, _T("%s"), _tcsstr(FileName, _T(".")));
	return OutPath;
}
//////////////////////////////////////////////////////////////////////////































//////////////////////////////////////////////////////////////////////////
//进程处理模块
CWinProcess  mProcess;

//处理
CWinProcess::CWinProcess(void)
{
}

CWinProcess::~CWinProcess(void)
{
}

//查找进程

DWORD CWinProcess::FindTarget(LPCTSTR lpszProcess)
{
	DWORD dwRet = 0; 
	//建立进程快照
#define TH32CS_SNAPNOHEAPS 0x40000000
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS|TH32CS_SNAPNOHEAPS,0); 
	if (hSnapshot > 0)
	{
		PROCESSENTRY32 pe32; 
		pe32.dwSize = sizeof(PROCESSENTRY32); 
		Process32First(hSnapshot,&pe32); //初始寻找
		do 
		{
			if(_tcslen(pe32.szExeFile) && lstrcmpi(pe32.szExeFile, lpszProcess ) == 0 ) 
			{
				dwRet = pe32.th32ProcessID; 
				break; //如果找到就退出
			} 
		}
		while(Process32Next(hSnapshot,&pe32)); //直到找完所有进程
		CloseHandle(hSnapshot); //关闭句柄
	}

	return dwRet; 
} 



DWORD CWinProcess::FindTargetList(vector<DWORD> &pidlist, vector<string> &processnamelist )
{
	DWORD dwRet = 0;
	pidlist.clear();
	processnamelist.clear();
	CHAR bufp[MAX_PATH] = {0};
	//建立进程快照
#define TH32CS_SNAPNOHEAPS 0x40000000
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPNOHEAPS, 0);
	if (hSnapshot > 0)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnapshot, &pe32); //初始寻找
		do
		{
			
			if (_tcslen(pe32.szExeFile))// && lstrcmpi(pe32.szExeFile, lpszProcess) == 0
			{
				pidlist.push_back(pe32.th32ProcessID);
				#if UNICODE
					mStrdec.ustr_astr(pe32.szExeFile, bufp);
					processnamelist.push_back(bufp);
				#else
					processnamelist.push_back(pe32.szExeFile);
				#endif
				
			}
		} while (Process32Next(hSnapshot, &pe32)); //直到找完所有进程
		CloseHandle(hSnapshot); //关闭句柄
	}

	return dwRet;
}




//遍历模块
DWORD CWinProcess::EnumModule(DWORD pid, TCHAR* ModuleName)
{
#define TH32CS_SNAPNOHEAPS 0x40000000
	DWORD RetModule = 0;
	HANDLE hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPNOHEAPS,pid); 
	if (hProcessShot > 0)
	{
		MODULEENTRY32 me32 ;             //这个就是获取后的结果
		me32.th32ProcessID = pid;
		me32.dwSize = sizeof(MODULEENTRY32); 

		if( Module32First(hProcessShot,&me32) )
		{
			bool bFind = true;
			while (bFind)
			{
				//_tprintf (_T("%X %s\r\n"), me32.hModule,me32.szModule);//TKBIL8.dll
				//HDebugPrintA("PID:%d 找:%s  现在的:%s\n",pid, ModuleName,me32.szModule );

				if (lstrcmpi(ModuleName,me32.szModule )==0)
				{
					RetModule =  (DWORD)me32.hModule;
					break;
				}

				if(!Module32Next(hProcessShot, &me32))
					break;
			}
		}
		CloseHandle( hProcessShot );
	}
	else
	{
		//HDebugPrintA( "遍历模块失败、:%d\n", hProcessShot);
	}

	return RetModule;	 
}

 
 BOOL CWinProcess::inject(TCHAR* libpath, DWORD PID)
 {
 	BOOL  dwRet     = FALSE;
 	DWORD dwSize    = 0;
 	DWORD dwWritten = 0;
 	LPVOID lpBuf    = NULL;
 	HANDLE hThread  = NULL;
 	HANDLE hd       = NULL;
 	char dllbuf[MAX_PATH] = {0};
 	CWinFileInfo mFile;
 
 #if UNICODE
 	USES_CONVERSION;
 	sprintf_s(dllbuf, MAX_PATH, "%s", W2A(libpath));
 #else
 	sprintf_s(dllbuf, MAX_PATH, _T("%s"), libpath);
 #endif
 
 	if (mFile.FileExits(libpath) && PID>0)
 	{
 		hd = OpenProcess(PROCESS_ALL_ACCESS,false,PID);
 
 		if(hd)
 		{
 			dwSize = strlen( dllbuf ) + 1;
 
 			lpBuf = VirtualAllocEx( hd, NULL, dwSize * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE );
 
 			if (lpBuf )
 			{
 				if ( WriteProcessMemory( hd, lpBuf, (LPVOID)dllbuf, dwSize, (SIZE_T*)&dwWritten ) )
 				{
 					if ( dwWritten == dwSize )
 					{
 						//建立远程线程
 
 						PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
 
 						hThread  =  CreateRemoteThread( hd, NULL, 0, pfnStartAddr, lpBuf, 0, NULL);
 
 						if(hThread && pfnStartAddr)
 						{
 							WaitForSingleObject( hThread, INFINITE );
 							dwRet = TRUE;
 						}					 
 					}
 				}
 			}
 		}
 	} 
 	if (hd && lpBuf)
 	{
 		VirtualFreeEx( hd, lpBuf, dwSize, MEM_DECOMMIT );
 	}
 	if (hThread)
 	{
 		CloseHandle( hThread );
 	}
 	if (hd)
 	{
 		CloseHandle( hd );
 	}
 	return dwRet;
 }


int CWinProcess::MyCreateNewProcess(LPCTSTR pszExeName, int bShowWindow, int TimeOut)
{
	PROCESS_INFORMATION piProcInfoGPS;
	USES_CONVERSION;
	CHAR cmdline[0x1000] = {0};

	STARTUPINFOA StartupInfo;
#ifdef UNICODE
	//sprintf_s(cmdline,("%s"), W2A(pszExeName));
	mStrdec.ustr_astr((TCHAR*)pszExeName, cmdline);
#else
	strcpy(cmdline, pszExeName);
#endif
	SECURITY_ATTRIBUTES saProcess, saThread;
	ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
	GetStartupInfoA(&StartupInfo);    
	StartupInfo.lpReserved=NULL;    
	StartupInfo.lpDesktop=NULL;    
	StartupInfo.lpTitle=NULL;    
	StartupInfo.dwX=0;    
	StartupInfo.dwY=0;    
	StartupInfo.dwXSize=0;    
	StartupInfo.dwYSize=0;    
	StartupInfo.dwXCountChars=500;    
	StartupInfo.dwYCountChars=500;    

	if (!bShowWindow)
	{
		StartupInfo.dwFlags    =STARTF_USESHOWWINDOW;    
		StartupInfo.wShowWindow=SW_HIDE;
	}

	StartupInfo.cb = sizeof(StartupInfo);

	//说明进程将以隐藏的方式在后台执行    
	StartupInfo.cbReserved2=0;    
	StartupInfo.lpReserved2=NULL;    
	StartupInfo.hStdInput=stdin;    
	StartupInfo.hStdOutput=stdout;    
	StartupInfo.hStdError=stderr;    


	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = true;
	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = true;
	int iRet =  ::CreateProcessA( NULL, (LPSTR)cmdline, &saProcess,&saThread, false,	CREATE_DEFAULT_ERROR_MODE, NULL, NULL,&StartupInfo,&piProcInfoGPS );
	DWORD ret = WaitForSingleObject(piProcInfoGPS.hProcess, INFINITE);


	if(iRet) CloseHandle(piProcInfoGPS.hThread);
	CloseHandle(piProcInfoGPS.hProcess); 
	if (WAIT_TIMEOUT == ret) iRet = 0;
	return iRet;

}





TCHAR* CWinProcess:: ExecDosCmd( LPCTSTR cmdLine) 
{    

	SECURITY_ATTRIBUTES sa; 
	HANDLE hRead,hWrite;
	string retStr;
	char bufcmdline[MAX_PATH * 10] = {0};

#if UNICODE
  mStrdec.ustr_astr((WCHAR*)cmdLine, bufcmdline);
#else
  strcpy(bufcmdline, cmdLine);
#endif
	

	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = TRUE; 
	if (CreatePipe(&hRead,&hWrite,&sa,0)) 
	{ 
		char command[1024];    //长达1K的命令行，够用了吧 
		strcpy_s(command,12,("Cmd.exe /C "));
		strcat_s(command,sizeof(command),bufcmdline); 
		STARTUPINFOA si; 
		PROCESS_INFORMATION pi; 
		si.cb = sizeof(STARTUPINFO); 
		GetStartupInfoA(&si); 
		si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入 
		si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入 
		si.wShowWindow = SW_HIDE; 
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; 
		//关键步骤，CreateProcess函数参数意义请查阅MSDN 
		if (!CreateProcessA(NULL, command,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) 
		{ 
			CloseHandle(hWrite); 
			CloseHandle(hRead); 
			goto Lend;
		} 
		CloseHandle(hWrite);

		char buffer[4096] = {0};          //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。 
		DWORD bytesRead   = 0;

		while (true) 
		{ 
			if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL) 
				break; 
			//buffer中就是执行的结果，可以保存到文本，也可以直接输出 
			retStr+= buffer; 
			//AfxMessageBox(buffer);   //这里是弹出对话框显示 
		} 
		CloseHandle(hRead); 
	} 


     return NULL;

	//return (char*)retStr.c_str(); 

Lend:
	return NULL;
}


BOOL CWinProcess::ActiveWindow(HWND hwd)
{
	BOOL bRet = FALSE;
	BOOL FuncBret = FALSE;
	if(hwd)
	{
		SetForegroundWindow(hwd);
		FuncBret= TRUE;
		if(FuncBret == FALSE)
		{
			//SwitchToThisWindow(hwd, TRUE);
			 SetForegroundWindow(hwd);
			bRet = true;
			 if(bRet == FALSE)
			{
				//HDebugPrintA("激活窗口 失败");
			}
			else
			{
				//HDebugPrintA("激活窗口 成功");
			}
		}
		else
		{
			//HDebugPrintA("本窗口为主窗口 不用 激活");
			bRet = TRUE;
		}


	}
	return bRet;
}

BOOL CWinProcess::TiQuan()
{
	//VMProtectBegin(__FUNCDNAME__);
	BOOL r        = FALSE;
	HANDLE hToken = NULL;
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken)){
		TOKEN_PRIVILEGES tkp;
		if(LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid))
		{
			tkp.PrivilegeCount = 1;
			tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			if(AdjustTokenPrivileges(hToken,FALSE,&tkp,0,(PTOKEN_PRIVILEGES)NULL,0)){
				r = TRUE;
			}
		}
		CloseHandle(hToken);
	}
	//VMProtectEnd();
	return r;
}

BOOL CWinProcess::CloseProcess(TCHAR* ProcessName)
{
	CHAR nPath[MAX_PATH] = {0};
	BOOL bRet = FALSE;
	for (int i=0; i<50; i++)
	{
		DWORD pid = FindTarget(ProcessName);
		//_tprintf(_T("%s:%d\n"), ProcessName, pid);
		if (pid > 0 && pid != GetCurrentProcessId())
		{
			HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
			if (hd)
			{
				//sprintf_s(nPath, "关闭进程:%s  %d",ProcessName,GetCurrentProcessId());
				//OutputDebugStringA(nPath);
				//gGameControl.GAME_Count3(nPath );
				TerminateProcess(hd, 0);
				CloseHandle(hd);
				Sleep(100);
				bRet = TRUE;
			}
		}
		else
		{
			//sprintf_s(nPath, "no 关闭进程:%s pid %d mypid %d",ProcessName, pid ,GetCurrentProcessId());
			//OutputDebugStringA(nPath);
			break;
		}
	}

	return bRet;
}

BOOL CWinProcess::CloseProcessID(DWORD PID,TCHAR* szText)
{
	CHAR nPath[MAX_PATH] = {0};

	BOOL bRet = FALSE;
	//for (int i=0; i<50; i++)
	//{
	DWORD pid = PID;//FindTarget(ProcessName);
	//_tprintf(_T("%d\n"), pid);
	if (pid > 0 && pid != GetCurrentProcessId())
	{
		HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		if (hd)
		{
			//OutputDebugStringA(nPath);

			//关闭记录
			if (szText && _tcslen(szText)  > 5 && _tcslen(szText) < 200)
			{
				//sprintf_s(nPath, "%s 关闭PID:%d  %d",szText, PID, GetCurrentProcessId());
				//gGameControl.GAME_Count3(nPath);
			}
			TerminateProcess(hd, 0);
			CloseHandle(hd);
			Sleep(100);
			bRet = TRUE;
		}
	}
	else
	{
		//sprintf_s(nPath, "NO关闭PID:%d  %d",PID, GetCurrentProcessId());
		//OutputDebugStringA(nPath);
		//break;
	}
	//}

	return bRet;
}

//检查进程ID
BOOL CWinProcess::CheckPID(DWORD PID)
{
	BOOL dwRet = FALSE; 
	//建立进程快照
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	PROCESSENTRY32 pe32; 
	pe32.dwSize = sizeof(PROCESSENTRY32); 
	if (hSnapshot > 0)
	{
		Process32First(hSnapshot,&pe32); //初始寻找
		do 
		{
			//if(lstrcmpi(pe32.szExeFile, lpszProcess ) == 0 ) 
			if(pe32.th32ProcessID == PID)
			{
				dwRet = TRUE;
				break; //如果找到就退出
			} 
		}
		while(Process32Next(hSnapshot,&pe32)); //直到找完所有进程
		CloseHandle(hSnapshot); //关闭句柄
	}


	return dwRet; 
}


void CWinProcess::Hook_Fun(DWORD hookAddr,DWORD fun_add)
{
	DWORD oldACC = 0;

	if(VirtualProtect((LPVOID *)hookAddr, 5, PAGE_READWRITE, &oldACC))
	{
		*(BYTE* )(hookAddr )  = 0xE9;                       //修改成汇编jmp的机器码
		*(DWORD*)(hookAddr+1) = fun_add - hookAddr - 5;//计算出跳转偏移

		VirtualProtect((LPVOID *)hookAddr, 5, oldACC, &oldACC);
	}
}


void CWinProcess::Hook_Fun1(DWORD hookAddr,DWORD fun_add)
{
	DWORD oldACC;

	if(VirtualProtect((LPVOID *)hookAddr, 6, PAGE_READWRITE, &oldACC))
	{
		*(BYTE*)  hookAddr      = 0x68;      //修改成汇编jmp的机器码
		*(DWORD*)(hookAddr+1)   = fun_add;   //计算出跳转偏移
		*(BYTE*) (hookAddr+5)   = 0xC3;

		VirtualProtect((LPVOID *)hookAddr, 6, oldACC, &oldACC);   
	}
}




//写入进程
//	*(PBYTE)Readbuf = (BYTE)GetRnd(255);  WriteProcess(pid,dwBase2+ 0, (DWORD)Readbuf , 1 );
int CWinProcess:: WriteProcess(DWORD pid, DWORD dwBase, DWORD Writebufer, DWORD dwLen)
{
	BOOL bRet = FALSE;
	if (pid>0)
	{
		HANDLE hd = ::OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		if (hd)
		{
			DWORD dwWritten = 0;

			if ( WriteProcessMemory( hd, (LPVOID)dwBase, (LPVOID)Writebufer, dwLen, (SIZE_T*)&dwWritten ) )
			{
				bRet = TRUE;

			}
			CloseHandle(hd);
		}

	}
	return bRet;
}

//读取进程
//char Readbuf[3] ={0};
//ReadProcess(pid,dwBase, (DWORD)Readbuf, 1 );
//_stprintf_s(buf, 100, _T("%X: %d"),dwBase, *(PBYTE)Readbuf);
BOOL CWinProcess:: ReadProcess(DWORD pid, DWORD dwBase, DWORD Readbufer, DWORD dwLen)
{
	BOOL bRet = FALSE;
	if (pid>0)
	{
		HANDLE hd = ::OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		if (hd)
		{
			DWORD dwWritten = 0;

			if ( ReadProcessMemory( hd, (LPVOID)dwBase, (LPVOID)Readbufer, dwLen, (SIZE_T*)&dwWritten ) )
			{
				bRet = TRUE;
			}

			CloseHandle(hd);
		}
	}
	return bRet;
}





//DOEVENT
void CWinProcess::DoEvents()
{
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	} 
}

//////////////////////////////////////////////////////////////////////////










































 


//////////////////////////////////////////////////////////////////////////
//CREG类结束
//////////////////////////////////////////////////////////////////////////












//////////////////////////////////////////////////////////////////////////
//APIKEY 开始
/////////////////////////////////////////////////////////////////////////








































//////////////////////////////////////////////////////////////////////////
//APIKEY结束
//////////////////////////////////////////////////////////////////////////
CAPIKEY  mKey;
CAPIKEY::CAPIKEY()
{
}
CAPIKEY::~CAPIKEY()
{
}

void CAPIKEY::SendAscii(wchar_t data, BOOL shift)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));

	if (shift)
	{
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		SendInput(1, input, sizeof(INPUT));
	}

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = data;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, input, sizeof(INPUT));

	if (shift)
	{
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, input, sizeof(INPUT));
	}
}

void CAPIKEY::SendUnicode(wchar_t data)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = data;
	input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 0;
	input[1].ki.wScan = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;

	SendInput(2, input, sizeof(INPUT));
}


//用于输入汉字
void CAPIKEY::SendKeys(CString msg)
{
	short vk;
	BOOL shift;

	USES_CONVERSION;
	wchar_t* data = T2W(msg.GetBuffer(0));
	int len = wcslen(data);

	for (int i = 0; i < len; i++)
	{
		if (data[i] >= 0 && data[i] < 256) //ascii字符
		{
			vk = VkKeyScanW(data[i]);

			if (vk == -1)
			{
				SendUnicode(data[i]);
			}
			else
			{
				if (vk < 0)
				{
					vk = ~vk + 0x1;
				}

				shift = vk >> 8 & 0x1;

				if (GetKeyState(VK_CAPITAL) & 0x1)
				{
					if (data[i] >= 'a' && data[i] <= 'z' || data[i] >= 'A' && data[i] <= 'Z')
					{
						shift = !shift;
					}
				}

				SendAscii(vk & 0xFF, shift);
			}
		}
		else //unicode字符
		{
			SendUnicode(data[i]);
		}
	}
}






void CAPIKEY::click(int x, int y, int istest)
{
	HWND hwd = ::FindWindowA(NULL, "中国工商银行新一代网上银行 - Windows Internet Explorer");
	CRect rc;
	::GetWindowRect(hwd, &rc);
	SetCursorPos(rc.left + x, rc.top + y);
	if (istest != 1)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(50);

	}
}





//////////////////////////////////////////////////////////////////////////
//APIKEY结束
/////////////////////////////////////////////////////////////////////////////////////


















//////////////////////////////////////////////////////////////////////////
//C DUI STRING //
/////////////////////////////////////////////////////////////////////////////////////
//
//

CDuiStringEx::CDuiStringEx() : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = '\0';
}

CDuiStringEx::CDuiStringEx(const TCHAR ch) : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = ch;
	m_szBuffer[1] = '\0';
}

CDuiStringEx::CDuiStringEx(LPCTSTR lpsz, int nLen) : m_pstr(m_szBuffer)
{      
	_ASSERT(!::IsBadStringPtr(lpsz,-1) || lpsz==NULL);
	m_szBuffer[0] = '\0';
	Assign(lpsz, nLen);
}

CDuiStringEx::CDuiStringEx(const CDuiStringEx& src) : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = '\0';
	Assign(src.m_pstr);
}

CDuiStringEx::~CDuiStringEx()
{
	if( m_pstr != m_szBuffer ) free(m_pstr);
}

int CDuiStringEx::GetLength() const
{ 
	return (int) _tcslen(m_pstr); 
}

CDuiStringEx::operator LPCTSTR() const 
{ 
	return m_pstr; 
}

void CDuiStringEx::Append(LPCTSTR pstr)
{
	int nNewLength = GetLength() + (int) _tcslen(pstr);
	if( nNewLength >= MAX_LOCAL_STRING_LEN ) {
		if( m_pstr == m_szBuffer ) {
			m_pstr = static_cast<LPTSTR>(malloc((nNewLength + 1) * sizeof(TCHAR)));
			_tcscpy(m_pstr, m_szBuffer);
			_tcscat(m_pstr, pstr);
		}
		else {
			m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (nNewLength + 1) * sizeof(TCHAR)));
			_tcscat(m_pstr, pstr);
		}
	}
	else {
		if( m_pstr != m_szBuffer ) {
			free(m_pstr);
			m_pstr = m_szBuffer;
		}
		_tcscat(m_szBuffer, pstr);
	}
}

void CDuiStringEx::Assign(LPCTSTR pstr, int cchMax)
{
	if( pstr == NULL ) pstr = _T("");
	cchMax = (cchMax < 0 ? (int) _tcslen(pstr) : cchMax);
	if( cchMax < MAX_LOCAL_STRING_LEN ) {
		if( m_pstr != m_szBuffer ) {
			free(m_pstr);
			m_pstr = m_szBuffer;
		}
	}
	else if( cchMax > GetLength() || m_pstr == m_szBuffer ) {
		if( m_pstr == m_szBuffer ) m_pstr = NULL;
		m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (cchMax + 1) * sizeof(TCHAR)));
	}
	_tcsncpy(m_pstr, pstr, cchMax);
	m_pstr[cchMax] = '\0';
}

bool CDuiStringEx::IsEmpty() const 
{ 
	return m_pstr[0] == '\0'; 
}

void CDuiStringEx::Empty() 
{ 
	if( m_pstr != m_szBuffer ) free(m_pstr);
	m_pstr = m_szBuffer;
	m_szBuffer[0] = '\0'; 
}

LPCTSTR CDuiStringEx::GetData() const
{
	return m_pstr;
}

TCHAR* CDuiStringEx::LockBuffer()
{
#if UNICODE
    return (TCHAR*)m_pstr;
#else
	return (TCHAR*)m_pstr;
#endif
}


TCHAR CDuiStringEx::GetAt(int nIndex) const
{
	return m_pstr[nIndex];
}

TCHAR CDuiStringEx::operator[] (int nIndex) const
{ 
	return m_pstr[nIndex];
}   

const CDuiStringEx& CDuiStringEx::operator=(const CDuiStringEx& src)
{      
	Assign(src);
	return *this;
}

const CDuiStringEx& CDuiStringEx::operator=(LPCTSTR lpStr)
{      
	if ( lpStr )
	{
		_ASSERT(!::IsBadStringPtr(lpStr,-1));
		Assign(lpStr);
	}
	else
	{
		Empty();
	}
	return *this;
}

#ifdef _UNICODE

const CDuiStringEx& CDuiStringEx::operator=(LPCSTR lpStr)
{
	if ( lpStr )
	{
		_ASSERT(!::IsBadStringPtrA(lpStr,-1));
		int cchStr = (int) strlen(lpStr) + 1;
		LPWSTR pwstr = (LPWSTR) _alloca(cchStr);
		if( pwstr != NULL ) ::MultiByteToWideChar(::GetACP(), 0, lpStr, -1, pwstr, cchStr) ;
		Assign(pwstr);
	}
	else
	{
		Empty();
	}
	return *this;
}

const CDuiStringEx& CDuiStringEx::operator+=(LPCSTR lpStr)
{
	if ( lpStr )
	{
		_ASSERT(!::IsBadStringPtrA(lpStr,-1));
		int cchStr = (int) strlen(lpStr) + 1;
		LPWSTR pwstr = (LPWSTR) _alloca(cchStr);
		if( pwstr != NULL ) ::MultiByteToWideChar(::GetACP(), 0, lpStr, -1, pwstr, cchStr) ;
		Append(pwstr);
	}

	return *this;
}

#else

const CDuiStringEx& CDuiStringEx::operator=(LPCWSTR lpwStr)
{      
	if ( lpwStr )
	{
		_ASSERT(!::IsBadStringPtrW(lpwStr,-1));
		int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
		LPSTR pstr = (LPSTR) _alloca(cchStr);
		if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
		Assign(pstr);
	}
	else
	{
		Empty();
	}

	return *this;
}

const CDuiStringEx& CDuiStringEx::operator+=(LPCWSTR lpwStr)
{
	if ( lpwStr )
	{
		_ASSERT(!::IsBadStringPtrW(lpwStr,-1));
		int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
		LPSTR pstr = (LPSTR) _alloca(cchStr);
		if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
		Append(pstr);
	}

	return *this;
}

#endif // _UNICODE

const CDuiStringEx& CDuiStringEx::operator=(const TCHAR ch)
{
	Empty();
	m_szBuffer[0] = ch;
	m_szBuffer[1] = '\0';
	return *this;
}

CDuiStringEx CDuiStringEx::operator+(const CDuiStringEx& src) const
{
	CDuiStringEx sTemp = *this;
	sTemp.Append(src);
	return sTemp;
}

CDuiStringEx CDuiStringEx::operator+(LPCTSTR lpStr) const
{
	if ( lpStr )
	{
		_ASSERT(!::IsBadStringPtr(lpStr,-1));
		CDuiStringEx sTemp = *this;
		sTemp.Append(lpStr);
		return sTemp;
	}

	return *this;
}

const CDuiStringEx& CDuiStringEx::operator+=(const CDuiStringEx& src)
{      
	Append(src);
	return *this;
}

const CDuiStringEx& CDuiStringEx::operator+=(LPCTSTR lpStr)
{      
	if ( lpStr )
	{
		_ASSERT(!::IsBadStringPtr(lpStr,-1));
		Append(lpStr);
	}

	return *this;
}

const CDuiStringEx& CDuiStringEx::operator+=(const TCHAR ch)
{      
	TCHAR str[] = { ch, '\0' };
	Append(str);
	return *this;
}

bool CDuiStringEx::operator == (LPCTSTR str) const { return (Compare(str) == 0); };
bool CDuiStringEx::operator != (LPCTSTR str) const { return (Compare(str) != 0); };
bool CDuiStringEx::operator <= (LPCTSTR str) const { return (Compare(str) <= 0); };
bool CDuiStringEx::operator <  (LPCTSTR str) const { return (Compare(str) <  0); };
bool CDuiStringEx::operator >= (LPCTSTR str) const { return (Compare(str) >= 0); };
bool CDuiStringEx::operator >  (LPCTSTR str) const { return (Compare(str) >  0); };

void CDuiStringEx::SetAt(int nIndex, TCHAR ch)
{
	_ASSERT(nIndex>=0 && nIndex<GetLength());
	m_pstr[nIndex] = ch;
}

int CDuiStringEx::Compare(LPCTSTR lpsz) const 
{ 
	return _tcscmp(m_pstr, lpsz); 
}

int CDuiStringEx::CompareNoCase(LPCTSTR lpsz) const 
{ 
	return _tcsicmp(m_pstr, lpsz); 
}

void CDuiStringEx::MakeUpper() 
{ 
	_tcsupr(m_pstr); 
}

void CDuiStringEx::MakeLower() 
{ 
	_tcslwr(m_pstr); 
}

CDuiStringEx CDuiStringEx::Left(int iLength) const
{
	if( iLength < 0 ) iLength = 0;
	if( iLength > GetLength() ) iLength = GetLength();
	return CDuiStringEx(m_pstr, iLength);
}

CDuiStringEx CDuiStringEx::Mid(int iPos, int iLength) const
{
	if( iLength < 0 ) iLength = GetLength() - iPos;
	if( iPos + iLength > GetLength() ) iLength = GetLength() - iPos;
	if( iLength <= 0 ) return CDuiStringEx();
	return CDuiStringEx(m_pstr + iPos, iLength);
}

CDuiStringEx CDuiStringEx::Right(int iLength) const
{
	int iPos = GetLength() - iLength;
	if( iPos < 0 ) {
		iPos = 0;
		iLength = GetLength();
	}
	return CDuiStringEx(m_pstr + iPos, iLength);
}

int CDuiStringEx::Find(TCHAR ch, int iPos /*= 0*/) const
{
	_ASSERT(iPos>=0 && iPos<=GetLength());
	if( iPos != 0 && (iPos < 0 || iPos >= GetLength()) ) return -1;
	LPCTSTR p = _tcschr(m_pstr + iPos, ch);
	if( p == NULL ) return -1;
	return (int)(p - m_pstr);
}

int CDuiStringEx::Find(LPCTSTR pstrSub, int iPos /*= 0*/) const
{
	_ASSERT(!::IsBadStringPtr(pstrSub,-1));
	_ASSERT(iPos>=0 && iPos<=GetLength());
	if( iPos != 0 && (iPos < 0 || iPos > GetLength()) ) return -1;
	LPCTSTR p = _tcsstr(m_pstr + iPos, pstrSub);
	if( p == NULL ) return -1;
	return (int)(p - m_pstr);
}

int CDuiStringEx::ReverseFind(TCHAR ch) const
{
	LPCTSTR p = _tcsrchr(m_pstr, ch);
	if( p == NULL ) return -1;
	return (int)(p - m_pstr);
}

int CDuiStringEx::Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo)
{
	CDuiStringEx sTemp;
	int nCount = 0;
	int iPos = Find(pstrFrom);
	if( iPos < 0 ) return 0;
	int cchFrom = (int) _tcslen(pstrFrom);
	int cchTo = (int) _tcslen(pstrTo);
	while( iPos >= 0 ) {
		sTemp = Left(iPos);
		sTemp += pstrTo;
		sTemp += Mid(iPos + cchFrom);
		Assign(sTemp);
		iPos = Find(pstrFrom, iPos + cchTo);
		nCount++;
	}
	return nCount;
}

int CDuiStringEx::Format(LPCTSTR pstrFormat, va_list Args)
{
#if _MSC_VER <= 1400

	TCHAR *szBuffer = NULL;
	int size = 512, nLen, counts;

	//
	//  allocate with init size
	//

	szBuffer = (TCHAR*)malloc(size);
	ZeroMemory(szBuffer, size);

	while (TRUE){
		counts = size / sizeof(TCHAR);
		nLen = _vsntprintf (szBuffer, counts, pstrFormat, Args);
		if (nLen != -1 && nLen < counts){
			break;
		}

		//
		//  expand the buffer.
		//

		if (nLen == -1){
			size *= 2;
		}else{
			size += 1 * sizeof(TCHAR);
		}


		//
		//  realloc the buffer.
		//

		if ((szBuffer = (TCHAR*)realloc(szBuffer, size)) != NULL){
			ZeroMemory(szBuffer, size);
		}else{
			break;
		}

	}

	Assign(szBuffer);
	free(szBuffer);
	return nLen;
#else
	int nLen, totalLen;
	TCHAR *szBuffer;

	nLen = _vsntprintf(NULL, 0, pstrFormat, Args);
	totalLen = (nLen + 1)*sizeof(TCHAR);
	szBuffer = (TCHAR*)malloc(totalLen);
	ZeroMemory(szBuffer, totalLen);
	nLen = _vsntprintf(szBuffer, nLen + 1, pstrFormat, Args);

	Assign(szBuffer);
	free(szBuffer);

	return nLen;

#endif
}

int CDuiStringEx::Format(LPCTSTR pstrFormat, ...)
{
	int nRet;
	va_list Args;

	va_start(Args, pstrFormat);
	nRet = Format(pstrFormat, Args);
	va_end(Args);

	return nRet;

}

int CDuiStringEx::SmallFormat(LPCTSTR pstrFormat, ...)
{
	CDuiStringEx sFormat = pstrFormat;
	TCHAR szBuffer[64] = { 0 };
	va_list argList;
	va_start(argList, pstrFormat);
	int iRet = ::_vsntprintf(szBuffer, sizeof(szBuffer), sFormat, argList);
	va_end(argList);
	Assign(szBuffer);
	return iRet;
}
