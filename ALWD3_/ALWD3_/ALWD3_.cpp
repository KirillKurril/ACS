#include <iostream>

int main()
{
    __int8 A[8] = { 1, 2, 3, 4, 5, 6, 7, 8};
    __int8 B[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    __int8 C[8] = { 1, 2, 3, 4, 5, 6, 7, 8};
    __int16 D[8] = { 1, 2, 3, 4, 5, 6, 7, 8};
    __int32 F[8] = {};
    __int32 AMinB[8] = {};
    __int64 temp = 0;
    

    __asm {
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        movq mm1, C
        movq mm0, C
        pxor mm7, mm7

        movq mm2, D + 8


        punpckhbw mm1, mm7
        movq temp, mm1
        movq mm3, temp

        pmullw mm1, mm2

        movq temp, mm1
        movq mm4, temp

        pmulhw mm3, mm2



        punpcklwd mm1, mm3
        punpckhwd mm4, mm3

        movq F + 16, mm1
        movq F + 24, mm4

        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        movq mm2, D

        punpcklbw mm0, mm7
        movq temp, mm0
        movq mm3, temp

        pmullw mm0, mm2
        movq temp, mm0
        movq mm4, temp

        pmulhw mm3, mm2

        punpcklwd mm0, mm3
        punpckhwd mm4, mm3

        movq F, mm0
        movq F + 8, mm4
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        movq mm1, B
        movq mm0, A

        psubsb mm0, mm1

        movq temp, mm0
        movq mm1, temp
        
        movq mm3, F
        movq mm4, F + 8

        packssdw mm3, mm4

        movq mm4, F + 16
        movq mm5, F + 24
        packssdw mm4, mm5

        punpcklbw mm0, mm7
        punpckhbw mm1, mm7

        paddw mm0, mm3
        paddw mm1, mm4

        movq temp, mm0
        movq mm2, temp

        movq temp, mm1
        movq mm3, temp

        punpcklwd mm0, mm7
        punpcklwd mm1, mm7
        punpckhwd mm2, mm7
        punpckhwd mm3, mm7


        movq F, mm0
        movq F + 16, mm1
        movq F + 8, mm2
        movq F + 24, mm3
        emms
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
