// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8D68BBDA_6F8F_4145_BD64_FCAD8F12C91A__INCLUDED_)
#define AFX_STDAFX_H__8D68BBDA_6F8F_4145_BD64_FCAD8F12C91A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxmt.h>			// MFC CCriticalSection 지원.
#include <afxtempl.h>		// MFC 템플릿 클래스 지원.

typedef	enum { EAST, WEST, SOUTH, NORTH } mark;

// 작업창에 프로그램 닫을 때 필요한 dll 라이브러리 함수들...
#pragma comment(lib,"FindActive.lib")
extern "C" __declspec(dllimport) BOOL InstallHook(UINT iMsg);
extern "C" __declspec(dllimport) BOOL ReleaseHook();

// 여러 클래스에서 공통으로 사용하는 전역 함수들...
#define KEYBOARD	1
#define	LEFTMOUSE	2
#define RIGHTMOUSE	3
void press(int kind, DWORD vkorx, DWORD scanory);
void shortcut(BYTE special, BYTE normal, BYTE scan);
BOOL isFileDialog(HWND hWnd);
HWND getRoot(HWND hWnd, BOOL isDialog);

#ifdef _DEBUG
#include "./CxImage_Debug/ximage.h"
#pragma comment(lib,"./CxImage_Debug/cximage.lib")
#pragma comment(lib,"./CxImage_Debug/Jpeg.lib")
#pragma comment(lib,"./CxImage_Debug/jasper.lib")
#pragma comment(lib,"./CxImage_Debug/jbig.lib")
#pragma comment(lib,"./CxImage_Debug/mng.lib")
#pragma comment(lib,"./CxImage_Debug/png.lib")
#pragma comment(lib,"./CxImage_Debug/libdcr.lib")
#pragma comment(lib,"./CxImage_Debug/Tiff.lib")
#pragma comment(lib,"./CxImage_Debug/zlib.lib")
#else
#include "./CxImage_Release/ximage.h"
#pragma comment(lib,"./CxImage_Release/cximage.lib")
#pragma comment(lib,"./CxImage_Release/Jpeg.lib")
#pragma comment(lib,"./CxImage_Release/jasper.lib")
#pragma comment(lib,"./CxImage_Release/jbig.lib")
#pragma comment(lib,"./CxImage_Release/mng.lib")
#pragma comment(lib,"./CxImage_Release/png.lib")
#pragma comment(lib,"./CxImage_Release/libdcr.lib")
#pragma comment(lib,"./CxImage_Release/Tiff.lib")
#pragma comment(lib,"./CxImage_Release/zlib.lib")
#endif

#define	WM_ACTION				WM_USER+1
#define SM_XVIRTUALSCREEN		76
#define SM_YVIRTUALSCREEN		77
#define SM_CXVIRTUALSCREEN		78
#define SM_CYVIRTUALSCREEN		79

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8D68BBDA_6F8F_4145_BD64_FCAD8F12C91A__INCLUDED_)

