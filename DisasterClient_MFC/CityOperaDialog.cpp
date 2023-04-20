// CityOperaDialog.cpp: 实现文件
//

#include "pch.h"
#include "DisasterClient_MFC.h"
#include "CityOperaDialog.h"
#include "afxdialogex.h"


// CityOperaDialog 对话框

IMPLEMENT_DYNAMIC(CityOperaDialog, CDialog)

CityOperaDialog::CityOperaDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_CITY_OPERA1, pParent)
{

}

CityOperaDialog::~CityOperaDialog()
{
}

void CityOperaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CityOperaDialog, CDialog)
END_MESSAGE_MAP()


// CityOperaDialog 消息处理程序
