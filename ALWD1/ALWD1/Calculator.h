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
        fld qword ptr[x]
        fsin
        fstp qword ptr[result]
    }


    //std::cout << "YResult: " << result << std::endl;
    return result;
}

template<typename T>
T Calculator<T>::calculateS(T x, int n)
{
    T result = 0;
    int32_t n2_buffer = 0;
    double result_buffer = 0, decr = 1;
    

    for (int i = 1; i <= n; ++i)
    {
        __asm {
            
            pushad;
            finit
            mov eax, i
            imul eax, 2
            dec eax
            mov ecx, eax
            mov n2_buffer, eax
            fld qword ptr[x]
            fld st(0)
            dec ecx
            test ecx, ecx
            je powerend
        }
    powerloop:
        __asm {
            fmul st, st(1)
            loop powerloop
        }
    powerend:
        __asm {
            fild dword ptr [n2_buffer]
            sub dword ptr[n2_buffer], 1
            fild dword ptr[n2_buffer]
            mov ecx, dword ptr[n2_buffer]
            test ecx, ecx
            je endfuc
        }

    faclup:
        __asm {
            fmul st(1), st
            fsub qword ptr[decr]
            loop faclup
        }
    endfuc:
        __asm{
            fld st(1)
            fld st(3)
            fdiv st, st(1)

            mov eax, i
            test eax, 1
            jne calculatesend
            fchs
        }
    calculatesend:
        __asm {

            fstp qword ptr[result_buffer]
            popad
        }
        result += result_buffer;
    }
    //std::cout << "SResult: " << result << std::endl;
    return result;
}
   

template<typename T>
std::pair<T, T> Calculator<T>::Calculate(T x, T precision)
{
    int counter = 0;
    T Y = calculateY(x);
    T S;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1;; ++i, ++counter)
    {
        S = calculateS(x, i);
        T error = abs(Y - S);
        if (error < precision)
            break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\n----------->\ntime: " << duration << "\niterations: " << counter
        << "\nY: " << Y << "\nS: " << S << "\nX: " << x;

    return std::pair<int, double>(counter, duration);
}





