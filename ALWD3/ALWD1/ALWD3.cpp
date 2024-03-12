#include<iostream>

//		F[i]=A[i] -B[i] +C[i] *D[i] , i = 1..8
int main() {
    __int8 A[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    __int8 B[8] = { 9, 10, 11, 12, 13, 14, 15, 16 };
    __int8 C[8] = { 17, 18, 19, 20, 21, 22, 23, 24 };
    __int16 D[8] = { 25, 26, 27, 28, 29, 30, 31, 32 };
    __int32 F[8] = {};
    __int32 cmuld[8] = { 0 };

    __int64 AminusB;

    __asm {
        ; A - B
        movq mm0, A
        movq mm1, B
        psubb mm0, mm1
        movq AminusB, mm0
        ; C* D
        movq mm0, C
        movq mm1, C
        movq mm2, C
        movq mm3, C
        pxor mm6, mm6

        punpcklbw mm0, mm6
        punpcklbw mm1, mm6
        punpckhbw mm2, mm6
        punpckhbw mm3, mm6

        movq mm4, D
        movq mm5, D + 8

        pmulhw mm0, mm4
        pmullw mm1, mm4
        pmulhw mm2, mm5
        pmullw mm3, mm5

        movq mm4, AminusB
        movq mm5, AminusB

        punpcklbw mm4, mm6
        punpcklbw mm5, mm6

        paddw mm1, mm4
        paddw mm3, mm5

        movq cmuld, mm0
        movq cmuld + 8, mm1
        movq cmuld + 16, mm2
        movq cmuld + 24, mm3

        movq mm0, cmuld
        movq mm1, cmuld
        movq mm2, cmuld + 8
        movq mm3, cmuld + 8

        punpckhwd mm0, mm2
        punpcklwd mm1, mm3


        movq mm2, cmuld + 16
        movq mm3, cmuld + 16
        movq mm4, cmuld + 24
        movq mm5, cmuld + 24

        punpckhwd mm2, mm4
        punpcklwd mm4, mm5



        emms
        ; () + ()
    }

    return 0;
}
