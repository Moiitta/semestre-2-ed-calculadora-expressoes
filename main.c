#include <stdio.h>
#include "basics.h"
#include <string.h>

boolean calculaExpressao(char* expressao, float* resultado);

int main() {
    char texto[100];
    float resultado;

    printf("Digite uma expressao: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0';

    if (calculaExpressao(texto, &resultado) == false) {
        return 1;
    }

    printf("Resultado = %.2f\n", resultado);
    return 0;
}
