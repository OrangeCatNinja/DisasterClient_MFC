
// DisasterClient_MFC.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CDisasterClientMFCApp:
// 有关此类的实现，请参阅 DisasterClient_MFC.cpp
//
#define GETNETWORK()	NetWork::NetWorkManager::GetInstance().GetNetWork()

class CDisasterClientMFCApp : public CWinApp
{
public:
	CDisasterClientMFCApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

private:
	//MFC部分的初始化
	bool InitMFC();
	//网络部分的初始化
	bool InitNetWork();
	//参数部分的初始化
	bool InitParams();
};

extern CDisasterClientMFCApp theApp;
