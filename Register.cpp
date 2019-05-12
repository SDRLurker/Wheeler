// Register.cpp: implementation of the CRegister class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wheeler2.h"
#include "Register.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


int CRegister::ReadInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT nDefault)
{
	HKEY key;
	DWORD dwDisp;
	int Result;
	DWORD Size = sizeof(LONG);
	if(RegCreateKeyEx(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &key, &dwDisp)!=ERROR_SUCCESS)
		return 0;
	if(RegQueryValueEx(hKey, lpValue, 0, NULL, (LPBYTE)&Result, &Size)!=ERROR_SUCCESS)
		Result = nDefault;
	RegCloseKey(hKey);
	return Result;
}

BOOL CRegister::ReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize)
{
	HKEY key;
	DWORD dwDisp;
	DWORD Size = nSize;
	if(RegCreateKeyEx(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &key, &dwDisp)!=ERROR_SUCCESS)
		return FALSE;
	if(RegQueryValueEx(hKey, lpValue, 0, NULL, (LPBYTE)&lpRet, &Size)!=ERROR_SUCCESS)
	{
		lstrcpy(lpRet, lpDefault);
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegister::WriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, UINT nData)
{
	HKEY key;
	DWORD dwDisp;
	if(RegCreateKeyEx(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp)!=ERROR_SUCCESS)
		return FALSE;
	if(RegSetValueEx(hKey, lpValue, 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT))!=ERROR_SUCCESS)
		return FALSE;
	RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegister::WriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData)
{
	HKEY key;
	DWORD dwDisp;
	if(RegCreateKeyEx(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp)!=ERROR_SUCCESS)
		return FALSE;
	if(RegSetValueEx(hKey, lpValue, 0, REG_SZ, (LPBYTE)&lpValue, lstrlen(lpData)+1)!=ERROR_SUCCESS)
		return FALSE;
	RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegister::DeleteKey(HKEY hKey, LPCTSTR lpKey)
{
	if(RegDeleteKey(hKey, lpKey)!=ERROR_SUCCESS)
		return FALSE;
	return TRUE;
}

int CRegister::ReadInt(LPCTSTR lpKey, LPCTSTR lpValue, INT nDefault)
{
	TCHAR *lpRealKey;
	lpRealKey = new TCHAR[lstrlen(Root) + lstrlen(lpKey) + 2];
	lstrcpy(lpRealKey, Root);
	lstrcat(lpRealKey, TEXT("\\"));
	lstrcat(lpRealKey, lpKey);

	int Result = CRegister::ReadInt(HiveKey, lpRealKey, lpValue, nDefault);
	
	delete []lpRealKey;
	return Result;
}

BOOL CRegister::ReadString(LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize)
{
	TCHAR *lpRealKey;
	lpRealKey = new TCHAR[lstrlen(Root) + lstrlen(lpKey) + 2];
	lstrcpy(lpRealKey, Root);
	lstrcat(lpRealKey, TEXT("\\"));
	lstrcat(lpRealKey, lpKey);

	BOOL Result = CRegister::ReadString(HiveKey, lpRealKey, lpValue, lpDefault, lpRet, nSize);

	delete []lpRealKey;
	return Result;
}

BOOL CRegister::WriteInt(LPCTSTR lpKey, LPCTSTR lpValue, UINT nData)
{
	TCHAR *lpRealKey;
	lpRealKey = new TCHAR[lstrlen(Root) + lstrlen(lpKey) + 2];
	lstrcpy(lpRealKey, Root);
	lstrcat(lpRealKey, TEXT("\\"));
	lstrcat(lpRealKey, lpKey);

	BOOL Result = CRegister::WriteInt(HiveKey, lpRealKey, lpValue, nData);

	delete []lpRealKey;
	return Result;
}

BOOL CRegister::WriteString(LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData)
{
	TCHAR *lpRealKey;
	lpRealKey = new TCHAR[lstrlen(Root) + lstrlen(lpKey) + 2];
	lstrcpy(lpRealKey, Root);
	lstrcat(lpRealKey, TEXT("\\"));
	lstrcat(lpRealKey, lpKey);

	BOOL Result = CRegister::WriteString(HiveKey, lpRealKey, lpValue, lpData);

	delete []lpRealKey;
	return Result;
}
