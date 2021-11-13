/************************************************************************
1.13    CXString    : �ַ���������  mStrdec
        CWinFileInfo: �ļ���Ϣ��    mFile
		CWinProcess : ������Ϣ��    mProcess
		CRegedit    : ע��������  mReg
************************************************************************/


//����ͷ�ļ�
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
//2016-7-28.txt �޸� 
#define SC_TRACE(fmt,...){\
	char* plog = new char[MAX_PATH * 0x10]; \
	memset(plog, 0,MAX_PATH * 0x100 );\
	sprintf_s(plog, MAX_PATH * 0x100 * sizeof(char), fmt, __VA_ARGS__); \
	OutputDebugString(plog); \
	printf("\n%s\n", plog); \
	delete plog; \
}
#endif

 
 

//�ҵ����ṩ��ϵͳ�ӿں���
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



//�ַ���������
//////////////////////////////////////////////////////////////////////////
#ifndef _STRING_CODE_
#define _STRING_CODE_
#if UNICODE
#define MyString wstring
#else
#define MyString string
#endif


//�ַ���ת��
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




//�ļ���Ϣ��
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
 

	//�жϺ���
public:
	//�ļ�����
	BOOL FileExits(LPCTSTR strFilePath);
	//Ŀ¼����
	BOOL FolderExits(LPCTSTR strFilePath);
	//��ȡ�ļ���С
	int  GetFileSize(LPCTSTR strFilePath);

	BOOL FileExitsA(CHAR* strFileName);

	//��������
public:
	//�����ļ�
	BOOL SaveFile    (LPCTSTR FileName,LPCTSTR szText,BOOL bNewFile);
	//��������
	BOOL Savebufer   (char* filename, char* buffer, int iLen);
	//��ȡ·��(ָ��)
	LPCTSTR GetNewPath  (TCHAR* InPath, LPCTSTR AdditionPath, TCHAR* OutPath);
	//��ȡĿ¼
	LPCTSTR GetFolder   (LPCTSTR FileName, TCHAR* OutPath);
	//��ȡ�ļ���
	LPCTSTR GetExeName  (LPCTSTR FileName, TCHAR* OutPath);
	//��ȡ��չ��
	LPCTSTR GetExeNameEx(LPCTSTR FileName, TCHAR* OutPath);

	//д�ļ�
	BOOL AppendFileText(TCHAR* filePath, TCHAR* szText);

 
	//��ȡ�ļ�
	char* ReadLocalFile(char* filepath, char* lpBuf, int *lpBufLen);

	//��ȡ�ļ������vector��
	LONGLONG ReadTxtFile(CHAR* szText, vector <string>& outList);

	void GetFileList(char * lpPath, vector<string> &filelist, bool bDeep=true);
	
};
EXTERN_C CWinFileInfo mFile;
#endif

//////////////////////////////////////////////////////////////////////////






















//������Ϣ��
//////////////////////////////////////////////////////////////////////////
#ifndef _WINPROCESS_
#define _WINPROCESS_

class CWinProcess
{
public:
	CWinProcess(void);
	~CWinProcess(void);
	
public:
	//�ȴ������Ľ��̱��������
	int MyCreateNewProcess(LPCTSTR pszExeName, int bShowWindow, int TimeOut = INFINITE);
	//ִ��
	TCHAR* ExecDosCmd( LPCTSTR cmdLine);
	//���ҽ���
	static DWORD FindTarget(LPCTSTR lpszProcess);

	DWORD FindTargetList(vector<DWORD> &pidlist, vector<string> &processnamelist);
	//ע��
	BOOL  inject(TCHAR* libpath, DWORD PID);
	//�����
	static BOOL ActiveWindow(HWND hwd);
	//��Ȩ
	BOOL TiQuan();

	//����ģ��
	DWORD EnumModule    (DWORD pid, TCHAR* ModuleName);
	BOOL  CloseProcess  (TCHAR* ProcessName);
	BOOL  CloseProcessID(DWORD PID, TCHAR* szText=NULL);
	BOOL  CheckPID      (DWORD PID);

    //HOOK
	void Hook_Fun(DWORD hookAddr,DWORD fun_add);
	void Hook_Fun1(DWORD hookAddr,DWORD fun_add);
	
	//��д�ڴ�
	BOOL ReadProcess(DWORD pid, DWORD dwBase, DWORD Readbufer, DWORD dwLen);
	int  WriteProcess(DWORD pid, DWORD dwBase, DWORD Writebufer, DWORD dwLen); 
	VOID DoEvents();
};
EXTERN_C CWinProcess  mProcess;
#endif

 

 

//////////////////////////////////////////////////////////////////////////
#ifndef __APIKEY__
#define __APIKEY__
//ע��������
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

	//�ĸ��Ĵ����߱���
	unsigned int A, B, C, D;

	//����

	int S11, S21, S31, S41;
	int S12, S22, S32, S42;
	int S13, S23, S33, S43;
	int S14, S24, S34, S44;

	//��ԭʼ��Ϣ��Ҫ׷�ӵ��ֽ���
	int m_AppendByte;

	//ԭʼ��Ϣ����,��һ��64λ������¼
	unsigned char m_MsgLen[8];

private:

	//λ�ƺ���

	unsigned int ROTATE_LEFT(unsigned int x, unsigned int n);
	unsigned int F(unsigned int x, unsigned int y, unsigned int z);
	unsigned int G(unsigned int x, unsigned int y, unsigned int z);
	unsigned int H(unsigned int x, unsigned int y, unsigned int z);
	unsigned int I(unsigned int x, unsigned int y, unsigned int z);

	//���ֱ任����

	void FFF(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);
	void GGG(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);
	void HHH(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);
	void III(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, int s, unsigned int ac);

	//��ʼ��MD5�������
	void Init();

	//����׷���ֽ�������¼ԭʼ��Ϣ����
	void Append(unsigned int MsgLen);

	//��ԭʼ��Ϣ��64�ֽڽ��з���,���д�λ����
	void Transform(unsigned char Block[64]);

	//���Ĵ���A,B,C,D����󱣴��ֵת��Ϊʮ�����Ʋ����ظ��û�
	bool ToHex(bool UpperCase, char* outstr);

public:

	//�����ַ�����MD5
	//string GetMD5OfString(string InputMessage,bool UpperCase);
	bool GetMD5OfString(char* InputMessageA, bool UpperCase, char* outbuf);

private:

	//�ļ�ָ��,�����ڴ˴�����Ϊ�б�Ҫ�ں����ⲿ�ر��ļ�ָ��
	FILE* m_pFile;

	//�ļ��Ĵ�״̬,GetMD5OfFile�������ݴ�ֵ�����Ƿ��������
	bool m_FileOpen;

public:

	//�����ļ���MD5
	string GetMD5OfFile(const string FileName, bool UpperCase);

	//�����û��Ӻ����ⲿ��ǰ������GetMD5OfFile�ĵ���
	void GetMD5OfFile_Terminate();
 

private:

	//���麯��,�ڼ����ļ�MD5�Ĺ�����,ͨ��PrcessNum��������ȴ��ݵ�������
	//virtual void OnProcessing(int PrcessNum)=0;

};
EXTERN_C ZMD5 zmd;
#endif