#include <cmath>
#include <stdio.h>
#include <stdint.h>

// Computar a raiz quadrada de um argumento A por meio do uso do método
// de Newton-Rapson minimizando as multiplicações.
// Montando uma tabela de valores de A de 50 a 70, com incremento de 1,
// mostrando os valores A com a respectiva √A que foi calculada e comparando esse resultado
// com o valor produzido pela função sqrt da biblioteca math.h do C.

#define pi 3.14159265358979323846 

const float sqrt2 = 1.4142135623730950488016887; 
const float invsqrt2 = 1.0f / sqrt2;  
const int B = 127; 


typedef union {
    float x;
    struct {
        uint32_t f : 23; 
        uint32_t E : 8;  
        uint32_t s : 1;  
    } bits;
} floatIEEE;

float calcularRaizQuadrada(int x) {
    float A = static_cast<float>(x);       
    floatIEEE x1;               
    floatIEEE x0 = {A}; 

    int e = x0.bits.E - B;
    x0.bits.f >>= 1;  

    if (e & 1) {   
        x0.bits.E = ((e + 1) >> 1) + B; 
        x0.x *= invsqrt2; 
    } else {
        x0.bits.E = (e >> 1) + B;
    }
    x1.x = x0.x;   
    do {    // newton-rapson 
    x0.x = x1.x;
    x1 = {(x0.x + A/x0.x)};  
    x1.bits.E--; 
    }  while (x0.x > x1.x); 
    return x1.x;
}

int main() {
    printf("----------------------------------------------------------------------------\n");
    printf("| Numero | Raiz (Newton-Raphson)|    Raiz (sqrt)    |        Diferenca     |\n");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 50; i <= 70; i++) {
        float raizNewton = calcularRaizQuadrada(i);
        float raizMath = sqrt(i); 

        printf("| %6d | %20.15f | %10.15f | %20.15f |\n", i, raizNewton, raizMath, raizNewton - raizMath);
    }

    printf("----------------------------------------------------------------------------\n");

    return 0;
}