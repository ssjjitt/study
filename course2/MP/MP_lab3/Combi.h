#pragma once 

namespace combi
{
    struct  permutation                 // ���������   ������������     
    {
        const static bool L = true;      // ����� ������� 
        const static bool R = false;     // ������ �������   

        short  n,                        // ���������� ��������� ��������� ��������� 
            * sset;                    // ������ �������� ������� ������������
        bool* dart;                    // ������  ������� (�����-L � ������-R) 

        permutation(short n = 1);       // ����������� (���������� ��������� ��������� ���������) 

        void reset();                    // �������� ���������, ������ ������� 

        __int64 getfirst();              // ������������ ������ ������ ��������    
        __int64 getnext();               // ������������ ��������� ������ ��������  

        short ntx(short i);              // �������� i-� ������� ������ �������� 
        unsigned __int64 np;             // ����� ������������ 0,... count()-1 

        unsigned __int64 count() const;  // ��������� ����� ���. ������������    
    };

};