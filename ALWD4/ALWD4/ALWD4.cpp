#include <iostream>

int main()
{
    __int8 A[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    __int8 B[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    __int8 C[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    __int16 D[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    __int32 F[8] = {};
    __int32 AMinB[8] = {};
    __int64 temp = 0;


    __asm {
            xorpd xmm0, xmm0
            xorpd xmm1, xmm1
            xorpd xmm2, xmm2
            xorpd xmm3, xmm3
            xorpd xmm4, xmm4
            xorpd xmm5, xmm5
            xorpd xmm6, xmm6


            movupd xmm0, [A]
            movupd xmm1, [B]

            punpcklbw xmm0, xmm4
            punpcklbw xmm1, xmm4

            psubw xmm0, xmm1

            movupd xmm1, [C]
            movupd xmm2, [C]
            movupd xmm3, [C]
            movupd xmm4, [D]

            punpcklbw xmm1, xmm5
            punpcklbw xmm2, xmm5
            punpcklbw xmm3, xmm5

            pmullw xmm1, xmm4
            pmullw xmm2, xmm4
            pmulhw xmm3, xmm4

            paddw xmm1, xmm0
            paddw xmm2, xmm0

            punpcklwd xmm1, xmm3
            punpckhwd xmm2, xmm3


            paddq xmm2, xmm3

            pmullw xmm0, xmm2

            movupd[F + 16], xmm2
            movupd[F], xmm1
    }

    std::cout << "A:\n";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << (int)A[i] << " ";
    }
    std::cout << "\nB:\n";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << (int)B[i] << " ";
    }
    std::cout << "\nC:\n";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << (int)C[i] << " ";
    }
    std::cout << "\nD:\n";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << D[i] << " ";
    }
    std::cout << "\nF:\n";
    for (size_t i = 0; i < 8; i++)
    {
        std::cout << F[i] << " ";
    }
}
