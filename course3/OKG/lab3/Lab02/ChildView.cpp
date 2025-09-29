
// ChildView.cpp: реализация класса CChildView
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



// Обработчики сообщений CChildView

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

// ПЕРЕРИСОВКА ОКНА
void CChildView::OnPaint()
{
	CPaintDC dc(this); // контекст устройства для рисования, через него линии рисуются
	if (Index == 1) // простое отображение графика
	{
		Graph.Draw(dc, 0, 1);
	}

	if (Index == 2)
	{
		Graph.GetRS(RS); // диапазон
		SetMyMode(dc, CRectD(1, 10, 5, 10), CRect(1, 1, 2, 2));	    // Устанавливает режим отображения MM_ANISOTROPIC 
		Graph.Draw1(dc, 1, 1);
		dc.SetMapMode(MM_TEXT);										// Устанавливает режим отображения MM_TEXT
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

void CChildView::OnTestsF1()	// Обработчик команды для функции F1
{	// x c -3p 3p
	// дельта x = pi/36

	// Определение левой границы диапазона x
	double xL = -3 * pi;

	// Определение правой границы диапазона x
	double xH = -xL;

	// Определение шага
	double dx = pi / 36;

	// Вычисление количества точек
	int N = (xH - xL) / dx;

	// Изменение размера матрицы X с уничтожением данных
	X.RedimMatrix(N + 1);

	// Изменение размера матрицы Y с уничтожением данных
	Y.RedimMatrix(N + 1);

	// Цикл для вычисления значений X и Y
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx; // Вычисление значений X
		Y(i) = MyF1(X(i)); // Вычисление значений Y с использованием функции MyF1
	}

	// Установка параметров пера для линии графика
	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));

	// Установка параметров пера для осей координат
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 255));

	// Установка прямоугольной области окна
	RW.SetRect(200, 200, 600, 600);

	// Установка параметров графика
	Graph.SetParams(X, Y, RW);

	// Установка параметров пера для линии графика
	Graph.SetPenLine(PenLine);

	// Установка параметров пера для осей координат
	Graph.SetPenAxis(PenAxis);

	// Установка индекса
	Index = 1;

	// Запрос перерисовки окна
	this->Invalidate();
}

void CChildView::OnTestsF2()
{
	// Запрос перерисовки окна
	Invalidate();

	// Получение контекста устройства для рисования
	CPaintDC dc(this);

	// Определение левой границы диапазона x
	double xL = 0;

	// Определение правой границы диапазона x
	double xH = 6 * pi;

	// Определение шага
	double dx = pi / 36;

	// Вычисление количества точек
	int N = (xH - xL) / dx;

	// Изменение размера матрицы X с уничтожением данных
	X.RedimMatrix(N + 1);

	// Изменение размера матрицы Y с уничтожением данных
	Y.RedimMatrix(N + 1);

	// Цикл для вычисления значений X и Y
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx; // Вычисление значений X
		Y(i) = MyF2(X(i)); // Вычисление значений Y с использованием функции MyF2
	}

	// Установка параметров пера для линии графика
	PenLine.Set(PS_DASH, 3, RGB(255, 0, 0));

	// Установка параметров пера для осей координат
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 0));

	// Установка прямоугольной области окна
	RW.SetRect(200, 200, 600, 600);

	// Установка параметров графика
	Graph.SetParams(X - 0.01, Y, RW);

	// Установка параметров пера для линии графика
	Graph.SetPenLine(PenLine);

	// Установка параметров пера для осей координат
	Graph.SetPenAxis(PenAxis);

	// Рисование графика
	Graph.Draw(dc, 0, 1);
}


void CChildView::OnTestsF3()
{
	Invalidate();
	CPaintDC dc(this);
	CRect rectClient;
	GetClientRect(&rectClient);

	// Находим центр прямоугольной области окна
	int centerX = rectClient.Width() / 2;
	int centerY = rectClient.Height() / 2;

	// Радиус окружности
	int radius = min(rectClient.Width(), rectClient.Height()) / 2 - 20; // Оставляем небольшой отступ от края

	// Устанавливаем параметры пера для восьмиугольника
	CPen penOctagon;
	penOctagon.CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); // Толщина – 3, цвет – красный, тип линии – сплошная
	dc.SelectObject(&penOctagon);

	// Рассчитываем координаты вершин восьмиугольника
	POINT points[8];
	double angle = 0;
	for (int i = 0; i < 8; ++i)
	{
		points[i].x = centerX + static_cast<int>(radius * cos(angle));
		points[i].y = centerY + static_cast<int>(radius * sin(angle));
		angle += M_PI / 4; // 45 градусов 
	}

	// Рисуем восьмиугольник
	dc.Polygon(points, 8);

	// Устанавливаем параметры пера для окружности
	CPen penCircle;
	penCircle.CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); // Толщина – 2, цвет – синий, тип линии – сплошная
	dc.SelectObject(&penCircle);

	// Рисуем окружность
	dc.SelectStockObject(NULL_BRUSH); // Чтобы окружность была пустой
	dc.Ellipse(centerX - radius, centerY - radius, centerX + radius, centerY + radius);
}