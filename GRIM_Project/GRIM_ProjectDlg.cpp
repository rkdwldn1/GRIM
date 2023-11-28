
// GRIM_ProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GRIM_Project.h"
#include "GRIM_ProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGRIMProjectDlg 대화 상자



CGRIMProjectDlg::CGRIMProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIM_PROJECT_DIALOG, pParent)
	, m_circleSize(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGRIMProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CIRCLE, m_circleSize);
}

BEGIN_MESSAGE_MAP(CGRIMProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CGRIMProjectDlg::OnBnClickedButtonApply)
END_MESSAGE_MAP()


// CGRIMProjectDlg 메시지 처리기

BOOL CGRIMProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGRIMProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGRIMProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGRIMProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGRIMProjectDlg::OnBnClickedButtonApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientDC dc(this);

	UpdateData(TRUE);
	if (m_image.IsNull()) {
		m_image.Create(480, 480, 24);
	}
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nBpp = m_image.GetBPP();
	
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			unsigned char* pixel = fm + j * nPitch + i * 3;
			pixel[0] = pixel[1] = pixel[2] = 0;
		}
	}

	int rand_x = rand() % 480;
	int rand_y = rand() % 480;
	if (rand_x + m_circleSize > 480) {
		rand_x -= m_circleSize;
	}
	if (rand_y + m_circleSize > 480) {
		rand_y -= m_circleSize;
	}

	CRect rect(rand_x, rand_y, rand_x + m_circleSize, rand_y + m_circleSize);
	int centerX = (rect.left + rect.right) / 2;
	int centerY = (rect.top + rect.bottom) / 2;
	int radius = min((rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			int dx = i - centerX;
			int dy = j - centerY;
			int distance = static_cast<int>(sqrt(dx * dx + dy * dy));

			if (distance == radius) {
				unsigned char* pixel = fm + j * nPitch + i * 3;
				pixel[0] = 0;
				pixel[1] = 255;
				pixel[2] = 255;
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	int dCenterX = nSumX / nCount;
	int dCenterY = nSumY / nCount;

	// 수평 선
	for (int i = dCenterX - (radius / 5); i < dCenterX + (radius / 5); i++) {
		unsigned char* pixel = fm + dCenterY * nPitch + i * 3;
		pixel[0] = pixel[1] = pixel[2] = 255;
	}
	// 수직 선
	for (int i = dCenterY - (radius / 5); i < dCenterY + (radius / 5); i++) {
		unsigned char* pixel = fm + i * nPitch + dCenterX * 3;
		pixel[0] = pixel[1] = pixel[2] = 255;
	}

	m_image.Draw(dc, 0, 0);
}