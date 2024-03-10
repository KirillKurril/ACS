#pragma once
#include <cmath>
#include <chrono>
#include <locale>

template <typename T>
class Calculator
{
private:
    T calculateY(T x);
    T calculateS(T x, int n);
public:
	Calculator() {}

    std::pair<T, T> Calculate(T x, T precision);
};

template<typename T>
T Calculator<T>::calculateY(T x)
{
    T result;

    __asm {
        fld qword ptr[x]; ��������� �������� x � ���� FPU
        fsin; ��������� ����� �� x
        fstp qword ptr[result]
    }

   /* __asm {
        fld qword ptr[x]; �������� �������� ���������� x � ������� FPU
        fsincos; ���������� cos(x) � sin(x) � ����� FPU
        fcos; ���������� cos(sin(x)) �� ����� FPU
        fld qword ptr[x]; �������� �������� ���������� x � ������� FPU
        fcos; ���������� cos(x) �� ����� FPU
        fyl2x; ���������� log2(exp(cos(x))) �� ����� FPU
        fld qword ptr[x]; �������� �������� ���������� x � ������� FPU
        f2xm1; ���������� exp(x) �� ����� FPU
        faddp st(1), st; �������� exp(x) � 1 �� ����� FPU
        fmulp st(1), st; ��������� exp ^ (cos(x))* cos(sin(x)) �� ����� FPU
        fstp tbyte ptr[result]; ���������� ���������� � ���������� result
        fstsw ax; ���������� ��������� FPU � �������� AX
        sahf; ������ ��������� FPU � �������� AH
    }*/



    std::cout << "YResult: " << result << std::endl;
    return result;
}

template<typename T>
T Calculator<T>::calculateS(T x, int n)
{
    T result = 0;

    for (int i = 1; i <= n; ++i)
    {
        __asm {

            pushad;

            fld qword ptr[x]

            fild dword ptr[i]
            fld1
            fld1
            faddp st(1), st
            fmulp st(1), st
            fld1
            fsubp st(1), st
            fstp dword ptr [ecx]
            mov eax, ecx
        }
    powerloop:
        __asm {

            fld st(0)
            fmulp st(1), st
            loop powerloop

            fild dword ptr [eax]
            fld1
            fsubp st(1), st
            fild dword ptr [eax]
            mov ecx, eax
            dec ecx
        }

    faclup:
        __asm {
            fld st(1)
            fmulp st(1), st
            fxch st(1)
            fld1
            fsubp st(1), st
            fxch st(1)
            loop faclup

            fxch st(1)
            fxch st(2)
            fdivp st(1), st

            mov eax, i
            mov ecx, 2
            xor edx, edx
            div ecx
            cmp edx, 0
            je calculatesend
            fchs
        }
    calculatesend:
        __asm {

            fstp qword ptr[result]
            popad
        }
    }
    std::cout << "SResult: " << result << std::endl;
    return result;
}
   


    /*__asm {
        pushad
        sub esp, 20; �������� 20 ���� ������ ��� ��������� ����������

        fld qword ptr[ebp + 8]; ��������� x � ���� FPU
        fld1; ��������� 1.0 � ���� FPU
        fst qword ptr[ebp - 8]; ��������� 1.0 � ��������� ���������� result
        fst qword ptr[ebp - 16]; ��������� 1.0 � ��������� ���������� factorial
        fld1; ��������� 1.0 � ���� FPU
        fst qword ptr[ebp - 24]; ��������� 1.0 � ��������� ���������� k

        mov ecx, dword ptr[ebp + 12]; ��������� n � ecx
        cmp ecx, 0; ���������� n � 0
        jle endLoop; ���� n <= 0, ��������� � endLoop

        loopStart :
        fld qword ptr[ebp + 8]; ��������� x � ���� FPU
            fmul qword ptr[ebp - 24]; �������� x �� k
            fcos; ��������� cos(k * x)
            fdiv qword ptr[ebp - 16]; ����� cos(k * x) �� factorial
            fadd qword ptr[ebp - 8]; ��������� ��������� � �����

            fmul qword ptr[ebp - 24]; �������� k �� 1.0
            fadd qword ptr[ebp - 16]; ��������� 1.0 � factorial
            fst qword ptr[ebp - 16]; ��������� ����������� �������� factorial
            fadd qword ptr[ebp - 24]; ��������� 1.0 � k
            fst qword ptr[ebp - 24]; ��������� ����������� �������� k

            loop loopStart; ���������� ���� �� ��� ���, ���� ecx �� ������ ������ ����

            endLoop :
        fstp tbyte ptr[ebp - 8]; ��������� �������� ��������� � ���������� result

            add esp, 20; ��������������� ��������� �����
            popad

    }*/


template<typename T>
std::pair<T, T> Calculator<T>::Calculate(T x, T precision)
{
    int counter = 0;
    T Y = calculateY(x);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1;; ++i, ++counter)
    {
        if (abs(Y - calculateS(x, i)) < precision)
            break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    return std::pair<int, double>(counter, duration);
}





