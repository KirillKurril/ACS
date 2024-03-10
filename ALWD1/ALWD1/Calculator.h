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
        fld qword ptr[x]; Загружаем значение x в стек FPU
        fsin; Вычисляем синус от x
        fstp qword ptr[result]
    }

   /* __asm {
        fld qword ptr[x]; Загрузка значения переменной x в регистр FPU
        fsincos; Вычисление cos(x) и sin(x) в стеке FPU
        fcos; Вычисление cos(sin(x)) из стека FPU
        fld qword ptr[x]; Загрузка значения переменной x в регистр FPU
        fcos; Вычисление cos(x) из стека FPU
        fyl2x; Вычисление log2(exp(cos(x))) из стека FPU
        fld qword ptr[x]; Загрузка значения переменной x в регистр FPU
        f2xm1; Вычисление exp(x) из стека FPU
        faddp st(1), st; Сложение exp(x) и 1 из стека FPU
        fmulp st(1), st; Умножение exp ^ (cos(x))* cos(sin(x)) из стека FPU
        fstp tbyte ptr[result]; Сохранение результата в переменную result
        fstsw ax; Сохранение состояния FPU в регистре AX
        sahf; Запись состояния FPU в регистре AH
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
        sub esp, 20; Выделяем 20 байт памяти для локальных переменных

        fld qword ptr[ebp + 8]; Загружаем x в стек FPU
        fld1; Загружаем 1.0 в стек FPU
        fst qword ptr[ebp - 8]; Сохраняем 1.0 в локальной переменной result
        fst qword ptr[ebp - 16]; Сохраняем 1.0 в локальной переменной factorial
        fld1; Загружаем 1.0 в стек FPU
        fst qword ptr[ebp - 24]; Сохраняем 1.0 в локальной переменной k

        mov ecx, dword ptr[ebp + 12]; Загружаем n в ecx
        cmp ecx, 0; Сравниваем n с 0
        jle endLoop; Если n <= 0, переходим к endLoop

        loopStart :
        fld qword ptr[ebp + 8]; Загружаем x в стек FPU
            fmul qword ptr[ebp - 24]; Умножаем x на k
            fcos; Вычисляем cos(k * x)
            fdiv qword ptr[ebp - 16]; Делим cos(k * x) на factorial
            fadd qword ptr[ebp - 8]; Добавляем результат к сумме

            fmul qword ptr[ebp - 24]; Умножаем k на 1.0
            fadd qword ptr[ebp - 16]; Добавляем 1.0 к factorial
            fst qword ptr[ebp - 16]; Сохраняем обновленное значение factorial
            fadd qword ptr[ebp - 24]; Добавляем 1.0 к k
            fst qword ptr[ebp - 24]; Сохраняем обновленное значение k

            loop loopStart; Продолжаем цикл до тех пор, пока ecx не станет равным нулю

            endLoop :
        fstp tbyte ptr[ebp - 8]; Сохраняем конечный результат в переменной result

            add esp, 20; Восстанавливаем указатель стека
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





