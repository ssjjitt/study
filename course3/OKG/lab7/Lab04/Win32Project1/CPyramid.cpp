#include "CPyramid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define pi 3.14159265;
using namespace std;

CPyramid::CPyramid()
{
	this->Vertices.RedimMatrix(4, 6);	// создание матрицы с координатами точек пирамиды
	//	A	A1	B	B1	C	C1	
	//	3	1	0	0	0	0
	//	0	0	0	0	3	1
	//	0	3	0	3	0	3
	//	1	1	1	1	1	1
	this->Vertices(0, 0) = 3;		// A (ось х)
	this->Vertices(0, 1) = 1;		// A1 (ось х)
	this->Vertices(2, 1) = 3;		// A1 (ось z)
	this->Vertices(2, 3) = 3;		// B1 (ось z)
	this->Vertices(1, 4) = 3;		// C (ось y)
	this->Vertices(1, 5) = 1;		// C1 (ось у)
	this->Vertices(2, 5) = 3;		// C1 (ось z)
	for (int i = 0; i < 6; i++)
	{
		this->Vertices(3, i) = 1;
	}
}

double ScalarMultiply(CMatrix& V1, CMatrix& V2)
{
	if (V1.rows() != V2.rows() || V1.cols() > 1 || V2.cols() > 1) // Число столбцов больше одного 
	{
		char* error = "double ScalarMult(CMatrix& V1, CMatrix& V2) объект не вектор - число столбцов больше 1 ";
		MessageBoxA(NULL, error, "Ошибка", MB_ICONSTOP);
		exit(1);
	}

	return V1(0) * V2(0) + V1(1) * V2(1) + V1(2) * V2(2);
}

bool IsNegative(CPoint& V) {
	return V.x > 0 && V.y > 0;
}

void DrawLine(CDC& dc, CPoint* f, CPoint& s) {
	dc.Polygon(f, 4);
}

void CPyramid::Draw1(CDC& dc, CMatrix& PView, CRect& RW) // с удалением ребер
{
	CMatrix XV = CreateViewCoord(PView(0), PView(1), PView(2));
	CMatrix ViewVert = XV * this->Vertices;
	CRectD RectView;
	GetRect(this->Vertices, RectView);
	CMatrix MW = SpaceToWindow(RectView, RW);

	CPoint MasVert[6], A1B1C1[3], ABC[3];
	CMatrix V(3);
	V(2) = 1;

	for (int i = 0; i < 6; i++)
	{
		V(0) = ViewVert(0, i);
		V(1) = ViewVert(1, i);
		V = MW * V;
		MasVert[i].x = (int)V(0);
		MasVert[i].y = (int)V(1);
	}

	ABC[0] = MasVert[0];
	ABC[1] = MasVert[2];
	ABC[2] = MasVert[4];
	A1B1C1[0] = MasVert[1];
	A1B1C1[1] = MasVert[3];
	A1B1C1[2] = MasVert[5];

	CMatrix NormalABB1A1 = VectorMult(ViewVert.GetCol(1) - ViewVert.GetCol(0), ViewVert.GetCol(2) - ViewVert.GetCol(0));
	CMatrix NormalBCB1C1 = VectorMult(ViewVert.GetCol(2) - ViewVert.GetCol(1), ViewVert.GetCol(3) - ViewVert.GetCol(1));
	CMatrix NormalACC1A1 = VectorMult(ViewVert.GetCol(3) - ViewVert.GetCol(2), ViewVert.GetCol(0) - ViewVert.GetCol(2));

	CMatrix ObserverVector(3);
	ObserverVector(0) = 0;
	ObserverVector(1) = 0;
	ObserverVector(2) = -1; // Вектор наблюдателя

	CPen Pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&Pen);
	CBrush BottopBrush(RGB(34, 245, 206));
	CBrush TopBrush(RGB(5, 192, 34));
	CBrush BaseBrush(RGB(255, 255, 255));
	CBrush* pOldBrush = dc.SelectObject(&BottopBrush);
	dc.SelectObject(&BaseBrush);

	CPoint ABB1A1[4] = { ABC[0], ABC[1], A1B1C1[1], A1B1C1[0] };
	CPoint BCB1C1[4] = { ABC[1], ABC[2], A1B1C1[2], A1B1C1[1] };
	CPoint ACC1A1[4] = { ABC[2], ABC[0], A1B1C1[0], A1B1C1[2] };

	if (ScalarMult(NormalABB1A1, ObserverVector) > 0)
	{
		dc.Polygon(ABB1A1, 4);
	}

	if (ScalarMult(NormalBCB1C1, ObserverVector) > 0)
	{
		dc.Polygon(BCB1C1, 4);
	}

	if (ScalarMult(NormalACC1A1, ObserverVector) > 0)
	{
		dc.Polygon(ACC1A1, 4);
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

bool IsNegative(CPoint& V);
void DrawLine(CDC& dc, CPoint& f, CPoint& s) {
	
}

CPoint VectorMulty(CPoint& V1, CPoint& V2) {
	return V1;
}

CMatrix CreateViewCoord(double r, double fi, double q)			// МСК -> ВСК
{
	// сферические координаты точки наблюдения
	double fi_sphere = (fi / 180) * pi;		// азимут
	double q_sphere = (q / 180) * pi;		// зенит

	CMatrix K(4, 4);
	K(0, 0) = -sin(fi_sphere);
	K(0, 1) = cos(fi_sphere);
	K(1, 0) = -cos(q_sphere) * cos(fi_sphere);
	K(1, 1) = -cos(q_sphere) * sin(fi_sphere);
	K(1, 2) = sin(q_sphere);
	K(2, 0) = -sin(q_sphere) * cos(fi_sphere);
	K(2, 1) = -sin(q_sphere) * sin(fi_sphere);
	K(2, 2) = -cos(q_sphere);
	K(2, 3) = r;
	K(3, 3) = 1;
	return K;
}


void CPyramid::Draw1(CDC& dc, CMatrix& PView, CRect& RW, int q)			// с удалением ребер
{
	CMatrix ViewCart = SphereToCart(PView);
	CMatrix MV = CreateViewCoord(PView(0), PView(1), PView(2));
	CMatrix ViewVert = MV * Vertices;
	CRectD RectView;
	GetRect(ViewVert, RectView);
	CMatrix MW = SpaceToWindow(RectView, RW);

	CPoint MasVert[6];
	CMatrix V(3);
	V(2) = 1;
	for (int i = 0; i < 6; i++)
	{
		V(0) = ViewVert(0, i); // x
		V(1) = ViewVert(1, i); // y

		V = MW * V;
		MasVert[i].x = (int)V(0);
		MasVert[i].y = (int)V(1);
	}


	CMatrix R1(3), R2(3), VN(3);
	double sm;
	for (int i = 0; i < 3; i++)					// рисуем ребра без невидимых
	{
		CMatrix VE = Vertices.GetCol(i + 3, 0, 2);
		int k;
		if (i == 2) k = 0;
		else k = i + 1;
		R1 = Vertices.GetCol(i, 0, 2);
		R2 = Vertices.GetCol(k, 0, 2);
		CMatrix V1 = R2 - R1;
		CMatrix V2 = VE - R1;
		VN = VectorMult(V2, V1);
		sm = ScalarMult(VN, ViewCart);
		if (sm >= 0)
		{
			dc.MoveTo(MasVert[i]);
			dc.LineTo(MasVert[k]);
			dc.LineTo(MasVert[k + 3]);
			dc.LineTo(MasVert[i + 3]);
			dc.LineTo(MasVert[i]);
		}
	}

}


void CPyramid::Draw(CDC &dc, CMatrix&PView, CRect &RW)			// без удаления граней
{
	CMatrix XV = CreateViewCoord(PView(0), PView(1), PView(2));
	CMatrix ViewVert = XV * this->Vertices; // м в в
	CRectD RectView;
	GetRect(Vertices, RectView); // обл рис
	CMatrix MW = SpaceToWindow(RectView, RW); // м в о
	CPoint MasVert[6], a1b1c1[3], abc[3]; // массив хранит все вершины
	CMatrix V(3);
	V(2) = 1;
	for (int i = 0; i < 6; i++)
	{
		V(0) = ViewVert(0, i);
		V(1) = ViewVert(1, i);
		V = MW * V;
		MasVert[i].x = (int)V(0);
		MasVert[i].y = (int)V(1);
	}
	abc[0] = MasVert[0];
	abc[1] = MasVert[2];
	abc[2] = MasVert[4];
	a1b1c1[0] = MasVert[1];
	a1b1c1[1] = MasVert[3];
	a1b1c1[2] = MasVert[5];
	CPen Pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen *pOldPen = dc.SelectObject(&Pen);
	char buf[50] = "";
	sprintf(buf, "%.*f", 0, PView(1));
	dc.TextOut(10, 10, buf);
	sprintf(buf, "%.*f", 0, PView(2));
	dc.TextOut(10, 30, buf);
	dc.MoveTo(abc[0]);
	dc.LineTo(abc[1]);
	dc.MoveTo(abc[0]);
	dc.LineTo(abc[2]);
	dc.MoveTo(abc[2]);
	dc.LineTo(abc[1]);

	dc.MoveTo(a1b1c1[0]);
	dc.LineTo(a1b1c1[1]);
	dc.MoveTo(a1b1c1[0]);
	dc.LineTo(a1b1c1[2]);
	dc.MoveTo(a1b1c1[2]);
	dc.LineTo(a1b1c1[1]);

	dc.MoveTo(abc[0]);
	dc.LineTo(a1b1c1[0]);
	dc.MoveTo(abc[1]);
	dc.LineTo(a1b1c1[1]);
	dc.MoveTo(abc[2]);
	dc.LineTo(a1b1c1[2]);

	dc.SelectObject(pOldPen);
}

void  CPyramid::GetRect(CMatrix& Vert, CRectD&RectView)
{
	RectView.top = Vert.GetRow(2).MinElement();
	RectView.bottom = Vert.GetRow(2).MaxElement();
	RectView.left = Vert.GetRow(0).MinElement();
	RectView.right = Vert.GetRow(0).MaxElement();
}

CMatrix VectorMultiply(CMatrix& V1, CMatrix& V2)
{
	if (V1.rows() != V2.rows() || V1.cols() > 1 || V2.cols() > 1) // Число столбцов больше одного 
	{
		char* error = "CMatrix VectorMult(CMatrix& V1, CMatrix& V2) объект не вектор - число столбцов больше 1 ";
		MessageBoxA(NULL, error, "Ошибка", MB_ICONSTOP);
		exit(1);
	}

	CMatrix Temp = V1;
	Temp(0) = V1(1)*V2(2) - V1(2)*V2(1);
	Temp(1) = V1(2)*V2(0) - V1(0)*V2(2);
	Temp(2) = V1(0)*V2(1) - V1(1)*V2(0);

	return Temp;
}


CMatrix VectorMult(CMatrix& V1, CMatrix& V2)
// Вычисляет векторное произведение векторов V1 и V2
//Векторное произведение — это псевдовектор, перпендикулярный плоскости, построенной по двум сомножителям, 
//являющийся результатом бинарной операции «векторное умножение» над векторами в трёхмерном Евклидовом пространстве. 
//Векторное произведение полезно для «измерения» перпендикулярности векторов — длина векторного произведения двух векторов 
//равна произведению их длин, если они перпендикулярны, и уменьшается до нуля, если векторы параллельны либо антипараллельны.
{
	int b1 = (V1.cols() == 1) && (V1.rows() == 3);
	int b2 = (V2.cols() == 1) && (V2.rows() == 3);
	int b = b1 && b2;
	if (!b)
	{
		char* error = "VectorMult: неправильные размерности векторов! ";
		//MessageBox(NULL, error, "Ошибка", MB_ICONSTOP);
		exit(1);
	}
	CMatrix W(3);
	W(0) = V1(1) * V2(2) - V1(2) * V2(1);
	//double x=W(0);
	W(1) = -(V1(0) * V2(2) - V1(2) * V2(0));
	//double y=W(1);
	W(2) = V1(0) * V2(1) - V1(1) * V2(0);
	//double z=W(2);
	return W;
}
double ScalarMult(CMatrix& V1, CMatrix& V2)
// Вычисляет скалярное произведение векторов V1 и V2
//Скаля́рное произведе́ние — операция над двумя векторами, результатом которой является число (скаляр), 
//не зависящее от системы координат и характеризующее длины векторов-сомножителей и угол между ними. 
//Данной операции соответствует умножение длины вектора x на проекцию вектора y на вектор x. Эта операция 
//обычно рассматривается как коммутативная и линейная по каждому сомножителю.
{
	int b1 = (V1.cols() == 1) && (V1.rows() == 3);
	int b2 = (V2.cols() == 1) && (V2.rows() == 3);
	int b = b1 && b2;
	if (!b)
	{
		char* error = "ScalarMult: неправильные размерности векторов! ";
		//MessageBox(NULL, error, "Ошибка", MB_ICONSTOP);
		exit(1);
	}
	double p = V1(0) * V2(0) + V1(1) * V2(1) + V1(2) * V2(2);
	return p;
}

