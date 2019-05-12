// Register.h: interface for the CRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTER_H__D120BB14_0795_4E07_B504_9EB06007D8C1__INCLUDED_)
#define AFX_REGISTER_H__D120BB14_0795_4E07_B504_9EB06007D8C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	SHLM	HKEY_LOCAL_MACHINE
#define	SHCU	HKEY_CURRENT_USER
#define SHCR	HKEY_CLASSES_ROOT

class CRegister
{
private:
	HKEY HiveKey;
	TCHAR Root[MAX_PATH];
public:
	CRegister(LPCTSTR aRoot, HKEY aHive=SHCU)
	{
		HiveKey = aHive;
		lstrcpy(Root, aRoot);
		if(Root[lstrlen(Root)] == '\\')
		{
			Root[lstrlen(Root)] = 0;
		}
	}

	static int ReadInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT nDefault);
	static BOOL ReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize);
	static BOOL WriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, UINT nData);
	static BOOL WriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData);
	static BOOL DeleteKey(HKEY hKey, LPCTSTR lpKey);

	int ReadInt(LPCTSTR lpKey, LPCTSTR lpValue, INT nDefault);
	BOOL ReadString(LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize);
	BOOL WriteInt(LPCTSTR lpKey, LPCTSTR lpValue, UINT nData);
	BOOL WriteString(LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData);
};

#endif // !defined(AFX_REGISTER_H__D120BB14_0795_4E07_B504_9EB06007D8C1__INCLUDED_)
