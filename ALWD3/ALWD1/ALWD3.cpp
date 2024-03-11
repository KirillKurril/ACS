#include<iostream>

//		F[i]=A[i] -B[i] +C[i] *D[i] , i = 1..8

void input(int8_t** A, int8_t** B, int8_t** C, int16_t** D);
void printInputMessage(std::string arrname);
template<typename T>
void getArrayvalues(T** arr);
void createDummies(int8_t** A, int8_t** B, int8_t** C, int16_t** D);
int16_t* calculate(int8_t* A, int8_t* B, int8_t* C, int16_t* D);


int main() {
    /*int8_t * A, * B, * C;
    int16_t* D, * F;

    createDummies(&A, &B, &C, &D);
    F = calculate(A, B, C, D);*/
    __int8 A[8] = { 1, 1, 1, 1, 2, 2, 2, 2 };
    __int8 B[8] = { 3, 3, 3, 3, 4, 4, 4, 4 };
    __int8 C[8] = { 5, 5, 5, 5, 6, 6, 6, 6 };
    __int16 D[8] = { 7, 7, 7, 7, 8, 8, 8, 8 };
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

        emms
        ; () + ()
    }

    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] F;

    return 0;
}

int16_t* calculate(int8_t* A, int8_t* B, int8_t* C, int16_t* D)
{       
    int16_t* result = new int16_t[8];

    __asm {
        ; A - B
        movq mm0, A
        movq mm1, B
        psubb mm0, mm1
        ; C* D
        movq mm2, C
        pxor mm3, mm3
        punpcklbw mm3, mm2
        ; () + ()
    }

    return result;
}


void createDummies(int8_t** A, int8_t** B, int8_t** C, int16_t** D)
{
    *A = new int8_t[8]{ 10, 10, 10, 10, 10, 10, 10, 10 };
    *B = new int8_t[8]{ 11, 11, 11, 11, 11, 11, 11, 11 };
    *C = new int8_t[8]{ 12, 12, 12, 12, 12, 12, 12, 12 };
    *D = new int16_t[8]{ 13, 13, 13, 13, 13, 13, 13, 13 };
}

void input(int8_t** A, int8_t** B, int8_t** C, int16_t** D)
{
    printInputMessage("A");
    getArrayvalues(A);
    printInputMessage("B");
    getArrayvalues(B);
    printInputMessage("C");
    getArrayvalues(C);
    printInputMessage("D");
    getArrayvalues(D);
}

void printInputMessage(std::string arrname) {
    std::cout << "\nEnter " << arrname << " array values";
}

template<typename T>
void getArrayvalues(T** arr) {
    *arr = new T[8];
    for (int i = 0; i < 8; ++i) {
        T buffer;
        std::cin >> buffer;
        (*arr)[i] = buffer;
    }
}