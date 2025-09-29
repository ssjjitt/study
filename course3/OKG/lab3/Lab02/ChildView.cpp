
// ChildView.cpp: ���������� ������ CChildView
//
#define _USE_MATH_DEFINES

#include "stdafx.h"
#include "Lab02.h"
#include "ChildView.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_TESTS_F1, &CChildView::OnTestsF1)
	ON_COMMAND(ID_TESTS_F2, &CChildView::OnTestsF2)
	ON_COMMAND(ID_TESTS_F3, &CChildView::OnTestsF3)
	///////////////////
END_MESSAGE_MAP()



// ����������� ��������� CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

// ����������� ����
void CChildView::OnPaint()
{
	CPaintDC dc(this); // �������� ���������� ��� ���������, ����� ���� ����� ��������
	if (Index == 1) // ������� ����������� �������
	{
		Graph.Draw(dc, 0, 1);
	}

	if (Index == 2)
	{
		Graph.GetRS(RS); // ��������
		SetMyMode(dc, CRectD(1, 10, 5, 10), CRect(1, 1, 2, 2));	    // ������������� ����� ����������� MM_ANISOTROPIC 
		Graph.Draw1(dc, 1, 1);
		dc.SetMapMode(MM_TEXT);										// ������������� ����� ����������� MM_TEXT
	}
}

double CChildView::MyF1(double x)
{
	double y = sin(x) / x;
	return y;
}

double CChildView::MyF2(double x)
{
	double y = sqrt(x)* sin(x);
	return y;
}

void CChildView::OnTestsF1()	// ���������� ������� ��� ������� F1
{	// x c -3p 3p
	// ������ x = pi/36

	// ����������� ����� ������� ��������� x
	double xL = -3 * pi;

	// ����������� ������ ������� ��������� x
	double xH = -xL;

	// ����������� ����
	double dx = pi / 36;

	// ���������� ���������� �����
	int N = (xH - xL) / dx;

	// ��������� ������� ������� X � ������������ ������
	X.RedimMatrix(N + 1);

	// ��������� ������� ������� Y � ������������ ������
	Y.RedimMatrix(N + 1);

	// ���� ��� ���������� �������� X � Y
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx; // ���������� �������� X
		Y(i) = MyF1(X(i)); // ���������� �������� Y � �������������� ������� MyF1
	}

	// ��������� ���������� ���� ��� ����� �������
	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));

	// ��������� ���������� ���� ��� ���� ���������
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 255));

	// ��������� ������������� ������� ����
	RW.SetRect(200, 200, 600, 600);

	// ��������� ���������� �������
	Graph.SetParams(X, Y, RW);

	// ��������� ���������� ���� ��� ����� �������
	Graph.SetPenLine(PenLine);

	// ��������� ���������� ���� ��� ���� ���������
	Graph.SetPenAxis(PenAxis);

	// ��������� �������
	Index = 1;

	// ������ ����������� ����
	this->Invalidate();
}

void CChildView::OnTestsF2()
{
	// ������ ����������� ����
	Invalidate();

	// ��������� ��������� ���������� ��� ���������
	CPaintDC dc(this);

	// ����������� ����� ������� ��������� x
	double xL = 0;

	// ����������� ������ ������� ��������� x
	double xH = 6 * pi;

	// ����������� ����
	double dx = pi / 36;

	// ���������� ���������� �����
	int N = (xH - xL) / dx;

	// ��������� ������� ������� X � ������������ ������
	X.RedimMatrix(N + 1);

	// ��������� ������� ������� Y � ������������ ������
	Y.RedimMatrix(N + 1);

	// ���� ��� ���������� �������� X � Y
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx; // ���������� �������� X
		Y(i) = MyF2(X(i)); // ���������� �������� Y � �������������� ������� MyF2
	}

	// ��������� ���������� ���� ��� ����� �������
	PenLine.Set(PS_DASH, 3, RGB(255, 0, 0));

	// ��������� ���������� ���� ��� ���� ���������
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 0));

	// ��������� ������������� ������� ����
	RW.SetRect(200, 200, 600, 600);

	// ��������� ���������� �������
	Graph.SetParams(X - 0.01, Y, RW);

	// ��������� ���������� ���� ��� ����� �������
	Graph.SetPenLine(PenLine);

	// ��������� ���������� ���� ��� ���� ���������
	Graph.SetPenAxis(PenAxis);

	// ��������� �������
	Graph.Draw(dc, 0, 1);
}


void CChildView::OnTestsF3()
{
	Invalidate();
	CPaintDC dc(this);
	CRect rectClient;
	GetClientRect(&rectClient);

	// ������� ����� ������������� ������� ����
	int centerX = rectClient.Width() / 2;
	int centerY = rectClient.Height() / 2;

	// ������ ����������
	int radius = min(rectClient.Width(), rectClient.Height()) / 2 - 20; // ��������� ��������� ������ �� ����

	// ������������� ��������� ���� ��� ���������������
	CPen penOctagon;
	penOctagon.CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); // ������� � 3, ���� � �������, ��� ����� � ��������
	dc.SelectObject(&penOctagon);

	// ������������ ���������� ������ ���������������
	POINT points[8];
	double angle = 0;
	for (int i = 0; i < 8; ++i)
	{
		points[i].x = centerX + static_cast<int>(radius * cos(angle));
		points[i].y = centerY + static_cast<int>(radius * sin(angle));
		angle += M_PI / 4; // 45 �������� 
	}

	// ������ ��������������
	dc.Polygon(points, 8);

	// ������������� ��������� ���� ��� ����������
	CPen penCircle;
	penCircle.CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); // ������� � 2, ���� � �����, ��� ����� � ��������
	dc.SelectObject(&penCircle);

	// ������ ����������
	dc.SelectStockObject(NULL_BRUSH); // ����� ���������� ���� ������
	dc.Ellipse(centerX - radius, centerY - radius, centerX + radius, centerY + radius);
}