; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWheeler2Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Wheeler2.h"

ClassCount=8
Class1=CWheeler2App
Class2=CWheeler2Dlg
Class3=CAboutDlg

ResourceCount=10
Resource1=IDD_CAPTURE_PRESS (Neutral)
Resource2=IDR_MAINFRAME
Resource3=IDD_PROCESS
Resource4=IDD_FILE
Resource5=IDD_PROGRAM
Resource6=IDD_CAPTURE_TOGGLE (Neutral)
Class4=CProgram
Class5=CFileDlg
Class6=CCapturePress
Resource7=IDD_WHEELER2_DIALOG
Resource8=IDD_ABOUTBOX
Class7=CProcessDlg
Resource9=IDD_CAPTURE_WINDOW (Neutral)
Class8=CCaptureWindow
Resource10=IDR_MENU

[CLS:CWheeler2App]
Type=0
HeaderFile=Wheeler2.h
ImplementationFile=Wheeler2.cpp
Filter=N
LastObject=CWheeler2App

[CLS:CWheeler2Dlg]
Type=0
HeaderFile=Wheeler2Dlg.h
ImplementationFile=Wheeler2Dlg.cpp
Filter=D
LastObject=IDC_MOUSE_EXP
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=Wheeler2Dlg.h
ImplementationFile=Wheeler2Dlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WHEELER2_DIALOG]
Type=1
Class=CWheeler2Dlg
ControlCount=22
Control1=IDC_TITLE,button,1342177287
Control2=IDC_TITLE_NONE,button,1342308361
Control3=IDC_TITLE_ZOOM,button,1342177289
Control4=IDC_TITLE_MINI,button,1342177289
Control5=IDC_TITLE_CLOSE,button,1342177289
Control6=IDC_ISCAPTURE,button,1342373891
Control7=IDC_CAPTURE_PRESS,button,1342308361
Control8=IDC_CAPTURE_TOGGLE,button,1342177289
Control9=IDC_CAPTURE_WINDOW,button,1342177289
Control10=IDC_CAPTURE,button,1342177287
Control11=IDC_ADDON_NONE,button,1342308361
Control12=IDC_ADDON_PROGRAM,button,1342177289
Control13=IDC_ADDON_FILE,button,1342177289
Control14=IDC_ADDON,button,1342177287
Control15=IDC_CLOSE,button,1342242819
Control16=IDC_DOUBLE,button,1342177287
Control17=IDC_DOUBLE_TRAY,button,1342242819
Control18=IDC_DOUBLE_ICON,button,1342242819
Control19=IDC_DOUBLE_CLOCK,button,1342242819
Control20=IDC_MOUSE,button,1342177287
Control21=IDC_MOUSE_EXP,button,1342242819
Control22=IDC_MOUSE_DIALOG,button,1342242819

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_HELP
Command2=IDOK
CommandCount=2

[DLG:IDD_PROGRAM]
Type=1
Class=CProgram
ControlCount=2
Control1=IDC_PROGRAM_SEL,button,1342242816
Control2=IDC_PROGRAM_ONE,button,1342242819

[DLG:IDD_FILE]
Type=1
Class=CFileDlg
ControlCount=3
Control1=IDC_FILE_FOLDER,button,1342242816
Control2=IDC_FILE_JPEG,button,1342308361
Control3=IDC_FILE_PNG,button,1342177289

[CLS:CProgram]
Type=0
HeaderFile=Program.h
ImplementationFile=Program.cpp
BaseClass=CDialog
Filter=D
LastObject=CProgram
VirtualFilter=dWC

[CLS:CFileDlg]
Type=0
HeaderFile=FileDlg1.h
ImplementationFile=FileDlg1.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FILE_JPEG
VirtualFilter=dWC

[DLG:IDD_CAPTURE_PRESS (Neutral)]
Type=1
Class=CCapturePress
ControlCount=0

[CLS:CCapturePress]
Type=0
HeaderFile=CapturePress.h
ImplementationFile=CapturePress.cpp
BaseClass=CDialog
Filter=D
LastObject=CCapturePress
VirtualFilter=dWC

[DLG:IDD_CAPTURE_TOGGLE (Neutral)]
Type=1
Class=?
ControlCount=0

[DLG:IDD_PROCESS]
Type=1
Class=CProcessDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,SysListView32,1350631431
Control3=IDC_FIND,button,1342242816
Control4=IDC_EDIT1,edit,1342244864
Control5=IDC_STATIC,static,1342308352

[CLS:CProcessDlg]
Type=0
HeaderFile=ProcessDlg.h
ImplementationFile=ProcessDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CProcessDlg
VirtualFilter=dWC

[DLG:IDD_CAPTURE_WINDOW (Neutral)]
Type=1
Class=CCaptureWindow
ControlCount=0

[CLS:CCaptureWindow]
Type=0
HeaderFile=CaptureWindow.h
ImplementationFile=CaptureWindow.cpp
BaseClass=CDialog
Filter=D
LastObject=CCaptureWindow
VirtualFilter=dWC

