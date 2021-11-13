/************************************************************************
1.13    CXString    : 字符串处理类  mStrdec
        CWinFileInfo: 文件信息类    mFile
		CWinProcess : 进程信息类    mProcess
		CRegedit    : 注册表操作类  mReg
************************************************************************/


//共用头文件
//////////////////////////////////////////////////////////////////////////
#include "io.h"
#include "atlconv.h"
#include <vector>
#include <string>
#include <tchar.h>
#include "process.h"
using std::vector;
using namespace std;


#ifndef __DEBUG__
#define __DEBUG__
//2016-7-28.txt 修改 
#define SC_TRACE(fmt,...){\
	char* plog = new char[MAX_PATH * 0x10]; \
	memset(plog, 0,MAX_PATH * 0x100 );\
	sprintf_s(plog, MAX_PATH * 0x100 * sizeof(char), fmt, __VA_ARGS__); \
	OutputDebugString(plog); \
	printf("\n%s\n", plog); \
	delete plog; \
}
#endif

 
 

//我的类提供的系统接口函数
#include "tlhelp32.h"
#pragma comment(lib, "Kernel32.lib")

#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

// #include "OleAuto.h"
// #pragma comment(lib, "OleAut32.lib")
// 
// #include "Objbase.h"
// #pragma comment(lib, "Ole32.lib")

// #include "shellapi.h"
// #pragma comment(lib, "Shell32.lib")

#include "winuser.h"
#pragma comment(lib, "User32.lib")

// #include "winsock.h"
// #pragma comment(lib, "ws2_32.lib")

// #include "wininet.h"
// #pragma comment(lib, "wininet.lib")

#include "mmsystem.h"
#pragma  comment (lib,"Winmm.lib")

// #include "Shlwapi.h"
// #pragma  comment (lib,"Shlwapi.lib")








#ifndef __CDuiStringClass__
#define __CDuiStringClass__

#ifndef _ASSERT
#define _ASSERT(expr)   _ASSERT_EXPR((expr), NULL)
#endif


/////////////////////////////////////////////////////////////////////////////////////
//

class CDuiStringEx
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	CDuiStringEx();
	CDuiStringEx(const TCHAR ch);
	CDuiStringEx(const CDuiStringEx& src);
	CDuiStringEx(LPCTSTR lpsz, int nLen = -1);
	~CDuiStringEx();

	void Empty();
	int GetLength() const;
	bool IsEmpty() const;
	TCHAR GetAt(int nIndex) const;
	void Append(LPCTSTR pstr);
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData() const;
	TCHAR* LockBuffer();

	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const CDuiStringEx& operator=(const CDuiStringEx& src);
	const CDuiStringEx& operator=(const TCHAR ch);
	const CDuiStringEx& operator=(LPCTSTR pstr);
#ifdef _UNICODE
	const CDuiStringEx& CDuiStringEx::operator=(LPCSTR lpStr);
	const CDuiStringEx& CDuiStringEx::operator+=(LPCSTR lpStr);
#else
	const CDuiStringEx& CDuiStringEx::operator=(LPCWSTR lpwStr);
	const CDuiStringEx& CDuiStringEx::operator+=(LPCWSTR lpwStr);
#endif
	CDuiStringEx operator+(const CDuiStringEx& src) const;
	CDuiStringEx operator+(LPCTSTR pstr) const;
	const CDuiStringEx& operator+=(const CDuiStringEx& src);
	const CDuiStringEx& operator+=(LPCTSTR pstr);
	const CDuiStringEx& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;
	int CompareNoCase(LPCTSTR pstr) const;

	void MakeUpper();
	void MakeLower();

	CDuiStringEx Left(int nLength) const;
	CDuiStringEx Mid(int iPos, int nLength = -1) const;
	CDuiStringEx Right(int nLength) const;

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	int __cdecl Format(LPCTSTR pstrFormat, ...);
	int __cdecl Format(LPCTSTR pstrFormat, va_list Args);
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};

#endif



//字符串处理类
//////////////////////////////////////////////////////////////////////////
#ifndef _STRING_CODE_
#define _STRING_CODE_
#if UNICODE
#define MyString wstring
#else
#define MyString string
#endif


//字符串转换
class CXString
{ 
public:
	CXString();
	~CXString();

public:
	//unicode to ansi
	int ustr_astr( WCHAR* Unicodestr, char *AnsiStr );
	//ansi to unicode
	int astr_ustr( char *AnsiStr, WCHAR* UnicodeStr );


	BOOL SplitA( string SourceStr, string LimitStr);
	BOOL SplitW(wstring SourceStr,wstring LimitStr);
	BOOL SplitExA( string SourceStr, string LimitStr, vector<string>  &ArrRet);
	BOOL SplitExW(wstring SourceStr,wstring LimitStr, vector<wstring> &ArrRet);
	int  GetRnd(int Min,int Max);
	BYTE GetStrToByte(char* pStr, int iLen=2);
	BOOL SetRndInvalidStr(CDuiStringEx &inStr, int iType);
	int  CheckStrInvalid(CDuiStringEx& Account);
	string&    replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value);

	string urldecode(string &str_source);
	string urlencode(string &str_source);

	int UTF82GBK(char *szUtf8, char *szGbk, int Len);
	int GBK2UTF8(char *szGbk, char *szUtf8, int Len);

	void Base64_decode(char *src, int src_len, char *dst);
	void Base64_encode(char *src, int src_len, char *dst);


public:
	vector< string>  ArrRetA;
	vector<wstring>  ArrRetW;
}; 
EXTERN_C CXString  mStrdec;
#endif
//////////////////////////////////////////////////////////////////////////




//文件信息类
//////////////////////////////////////////////////////////////////////////

#ifndef _WINFILEINFO_
#define _WINFILEINFO_
class CWinFileInfo
{ 
public:
	CWinFileInfo();
	~CWinFileInfo();
	TCHAR m_Buf[MAX_PATH];
	char* m_lpbuf;
 

	//判断函数
public:
	//文件存在
	BOOL FileExits(LPCTSTR strFilePath);
	//目录存在
	BOOL FolderExits(LPCTSTR strFilePath);
	//获取文件大小
	int  GetFileSize(LPCTSTR strFilePath);

	BOOL FileExitsA(CHAR* strFileName);

	//操作函数
public:
	//保存文件
	BOOL SaveFile    (LPCTSTR FileName,LPCTSTR szText,BOOL bNewFile);
	//保存数据
	BOOL Savebufer   (char* filename, char* buffer, int iLen);
	//获取路径(指定)
	LPCTSTR GetNewPath  (TCHAR* InPath, LPCTSTR AdditionPath, TCHAR* OutPath);
	//获取目录
	LPCTSTR GetFolder   (LPCTSTR FileName, TCHAR* OutPath);
	//获取文件名
	LPCTSTR GetExeName  (LPCTSTR FileName, TCHAR* OutPath);
	//获取扩展名
	LPCTSTR GetExeNameEx(LPCTSTR FileName, TCHAR* OutPath);

	//写文件
	BOOL AppendFileText(TCHAR* filePath, TCHAR* szText);

 
	//读取文件
	char* ReadLocalFile(char* filepath, char* lpBuf, int *lpBufLen);

	//读取文件输出到vector中
	LONGLONG ReadTxtFile(CHAR* szText, vector <string>& outList);

	void GetFileList(char * lpPath, vector<string> &filelist, bool bDeep=true);
	
};
EXTERN_C CWinFileInfo mFile;
#endif

//////////////////////////////////////////////////////////////////////////






















//进程信息类
//////////////////////////////////////////////////////////////////////////
#ifndef _WINPROCESS_
#define _WINPROCESS_

class CWinProcess
{
public:
	CWinProcess(void);
	~CWinProcess(void);
	
public:
	//等待创建的进程被运行完成
	int MyCreateNewProcess(LPCTSTR pszExeName, int bShowWindow, int TimeOut = INFINITE);
	//执行
	TCHAR* ExecDosCmd( LPCTSTR cmdLine);
	//查找进程
	static DWORD FindTarget(LPCTSTR lpszProcess);

	DWORD FindTargetList(vector<DWORD> &pidlist, vector<string> &processnamelist);
	//注入
	BOOL  inject(TCHAR* libpath, DWORD PID);
	//激活窗口
	static BOOL ActiveWindow(HWND hwd);
	//提权
	BOOL TiQuan();

	//遍历模块
	DWORD EnumModule    (DWORD pid, TCHAR* ModuleName);
	BOOL  CloseProcess  (TCHAR* ProcessName);
	BOOL  CloseProcessID(DWORD PID, TCHAR* szText=NULL);
	BOOL  CheckPID      (DWORD PID);

    //HOOK
	void Hook_Fun(DWORD hookAddr,DWORD fun_add);
	void Hook_Fun1(DWORD hookAddr,DWORD fun_add);
	
	//读写内存
	BOOL ReadProcess(DWORD pid, DWORD dwBase, DWORD Readbufer, DWORD dwLen);
	int  WriteProcess(DWORD pid, DWORD dwBase, DWORD Writebufer, DWORD dwLen); 
	VOID DoEvents();
};
EXTERN_C CWinProcess  mProcess;
#endif

 

 

//////////////////////////////////////////////////////////////////////////
#ifndef __APIKEY__
#define __APIKEY__
//注册表操作类
class CAPIKEY
{
public:
	CAPIKEY(void);
	~CAPIKEY(void);
	void SendAscii(wchar_t data, BOOL shift);
	void SendUnicode(wchar_t data);
	void SendKeys(CString msg);
	void click(int x, int y, int istest = 0);
};

EXTERN_C CAPIKEY  mKey;
#endif





//////////////////////////////////////////////////////////////////////////
#ifndef __ZMD5__
#define __ZMD5__
class ZMD5
{
public:

	ZMD5();
	virtual ~ZMD5();

private:

	//四个寄存器具变量
	unsigned int A, B, C, D;

	//常量

	int S11, S21, S31, S41;
	int S12, S22, S32, S42;
	int S13, S23, S33, S43;
	int S14, S24, S34, S44;

	//对原始信息需要追加的字节数
	int m_AppendByte;

	//原始信息长度,用一个64位整数记录
	unsigned char m_MsgLen[8];

private:

	//位移函数

	unsigned int ROTATE_LEFT(unsigned int x, unsigned int n);
	unsigned int F(unsigned int x, unsigned int y, unsigned int z);
	unsigned int G(unsigned int x, unsigned int y, unsigned int z);
	unsigned int H(unsigned int x, unsigned int y, unsigned int z);
	unsigned int I(unsigned int x, unsigned int y, unsigned int z);

	//四轮变换函数

	void FFF(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);
	void GGG(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);
	void HHH(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);
	void III(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);

	//初始化MD5所需参数
	void Init();

	//计算追加字节数及记录原始信息长度
	void Append(unsigned int MsgLen);

	//将原始信息以64字节进行分组,进行错位打乱
	void Transform(unsigned char Block[64]);

	//将寄存器A,B,C,D中最后保存的值转换为十六进制并返回给用户
	bool ToHex(bool UpperCase, char* outstr);

public:

	//计算字符串的MD5
	//string GetMD5OfString(string InputMessage,bool UpperCase);
	bool GetMD5OfString(char* InputMessageA, bool UpperCase, char* outbuf);

private:

	//文件指针,声明在此处是因为有必要在函数外部关闭文件指针
	FILE* m_pFile;

	//文件的打开状态,GetMD5OfFile函数根据此值决定是否继续计算
	bool m_FileOpen;

public:

	//计算文件的MD5
	string GetMD5OfFile(const string FileName, bool UpperCase);

	//允许用户从函数外部提前结束对GetMD5OfFile的调用
	void GetMD5OfFile_Terminate();
 

private:

	//纯虚函数,在计算文件MD5的过程中,通过PrcessNum将处理进度传递到子类中
	//virtual void OnProcessing(int PrcessNum)=0;

};
EXTERN_C ZMD5 zmd;
#endif