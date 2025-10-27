/*
- A pilha deve terminar com apenas um valor, que é o resultado final da expressão.
- Expressões malformadas e divisões por zero devem ser tratadas adequadamente, com mensagens de erro claras.

Para cada item da Fila de Entrada

1. Se for número
    1. Adiciona número na Fila de Saída
2. Se for '('
    1. Empilha '('
3. Se for ')'
    1. Enquanto o topo da Pilha de Operadores for diferente de '('
        1. Desempilha a Pilha de Operadores e pega o Valor
        2. Adiciona Valor à Fila de Saída
    2. Desempilha '(' (não adiciona à Fila de Saída)
4. Se for Operador (+, -, *, /, ^)
    1. Se a Pilha de Operadores está vazia
        1. Empilha o Operador
    2. Se a Pilha de Operadores não está vazia
        1. Enquanto a Pilha não está vazia **e** a Tabela[Topo_da_Pilha][Operador_Atual] retorna True
            1. Desempilha a Pilha de Operadores e pega o Valor
            2. Adiciona Valor à Fila de Saída
        2. Empilha o Operador Atual

Após percorrer toda a Fila de Entrada:

1. Enquanto a Pilha de Operadores não estiver vazia
    1. Desempilha e adiciona à Fila de Saída

# Etapa 3 - Calculo da Expressão
A Fila de Entrada é a Fila de Saída da etapa anterior

Para cada item da Fila de Entrada

1. Recupera o primeiro Valor da Fila de Entrada
2. Se o Valor for número
    1. Empilha na Pilha de Resultados
3. Se o Valor for Operador
    1. Desempilha dois Valores (Valor1 e Valor)
    2. Se um dos Valores for Operador, retorna erro de expressão mal formada
    3. Realiza o calculo com o Operador: Resultado = Valor2 * Valor1
    4. Adiciona o Resultado a Pilha de Resultados

Se a Pilha de Resultado tiver mais de um elemento deve retornar um erro de expressão mal formada

O resultado a expressão é o último item que sobrou

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fila.h"
#include "basics.h"
#include "pilha.h"

boolean ehOperador(char c) {
    return (c == '+' || 
            c == '-' || 
            c == '*' || 
            c == '/' || 
            c == '^' || 
            c == '(' || 
            c == ')');
}

boolean removeEspacosValidando(char *str) {
    int i, j = 0;
    int tamanho = strlen(str);

    for (i = 0; i < tamanho; i++) {
        if (!(isdigit((unsigned char)str[i]) || ehOperador(str[i]) || isspace((unsigned char)str[i]))) {
            printf("Erro: caractere inválido: %c\n", str[i]);
            return false;
        }
        // Verifica se o digito atual é espaço e está entre dígitos 
        if (isspace((unsigned char)str[i])) {
            if (i > 0 && isdigit((unsigned char)str[i - 1]) &&
                isdigit((unsigned char)str[i + 1])) {
                return false; 
            }
            continue;
        }
        str[j] = str[i];
        j++;
    }

    str[j] = '\0';
    return true;
}

boolean converteTokens(Fila* fila, char* expressao) {

    int tamanho = strlen(expressao);
    int i,j = 0;
    char temp[32];

    for(i = 0; i < tamanho; i++) {
        if(isdigit((unsigned char)expressao[i]) == true) {
            temp[j] = expressao[i];
            j++;

            if(isdigit((unsigned char)expressao[i + 1]) == false) {
                temp[j] = '\0';
                j = 0;
                guarde_na_fila(fila, (ElementoDeFila)strdup(temp));
            }
        } else {
            char op[2] = {expressao[i], '\0'};
            guarde_na_fila(fila, strdup(op));
        }
    }

    return true;
}

int prioridade(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Retorna true se deve desempilhar o operador do topo
boolean deveDesempilhar(char topo, char atual) {
    if (topo == '(') return false;
    int pTopo = prioridade(topo);
    int pAtual = prioridade(atual);
    if (pTopo > pAtual) return true;
    if (pTopo == pAtual && atual != '^') return true; // ^ é associativo à direita
    return false;
}

// ----------------------------------------------------
// Etapa 2: Infixa -> Pós-fixa
// ----------------------------------------------------
boolean converteParaPosfixa(Fila *entrada, Fila *saida) {
    Pilha operadores;
    nova_pilha(&operadores, 100);

    ElementoDeFila e;
    while (!fila_vazia(*entrada)) {
        recupere_da_fila(*entrada, &e);
        char *token = (char *)e;

        if (isdigit(token[0])) {
            guarde_na_fila(saida, strdup(token));
        } else if (token[0] == '(') {
            guarde_na_pilha(&operadores, strdup(token));
        } else if (token[0] == ')') {
            ElementoDePilha top;
            while (!pilha_vazia(operadores)) {
                recupere_da_pilha(operadores, &top);
                if (((char *)top)[0] == '(') {
                    remova_elemento_da_pilha(&operadores);
                    break;
                }
                guarde_na_fila(saida, strdup(top));
                remova_elemento_da_pilha(&operadores);
            }
        } else if (ehOperador(token[0])) {
            ElementoDePilha top;
            while (!pilha_vazia(operadores)) {
                recupere_da_pilha(operadores, &top);
                char topo = ((char *)top)[0];
                if (!deveDesempilhar(topo, token[0])) break;
                guarde_na_fila(saida, strdup((char *)top));
                remova_elemento_da_pilha(&operadores);
            }
            guarde_na_pilha(&operadores, strdup(token));
        }
        remova_elemento_da_fila(entrada);
    }

    // Desempilha o restante
    ElementoDePilha top;
    while (!pilha_vazia(operadores)) {
        recupere_da_pilha(operadores, &top);
        guarde_na_fila(saida, strdup((char *)top));
        remova_elemento_da_pilha(&operadores);
    }

    free_pilha(&operadores);
    return true;
}

// ----------------------------------------------------
// Etapa 3: Cálculo da expressão Pós-fixa
// ----------------------------------------------------
boolean calculaPosfixa(Fila *entrada, float *resultado) {
    Pilha resultados;
    nova_pilha(&resultados, 100);

    ElementoDeFila e;
    while (!fila_vazia(*entrada)) {
        recupere_da_fila(*entrada, &e);
        char *token = (char *)e;

        if (isdigit(token[0])) {
            float *valor = malloc(sizeof(float));
            *valor = atof(token);
            guarde_na_pilha(&resultados, valor);
        } else if (ehOperador(token[0])) {
            if (resultados.qtd_atual < 2) {
                printf("Erro: expressao malformada (faltam operandos).\n");
                return false;
            }

            float *v1, *v2;
            ElementoDePilha el1, el2;
            recupere_da_pilha(resultados, &el1);
            v1 = (float *)el1;
            remova_elemento_da_pilha(&resultados);

            recupere_da_pilha(resultados, &el2);
            v2 = (float *)el2;
            remova_elemento_da_pilha(&resultados);

            float res = 0;
            switch (token[0]) {
                case '+': res = *v2 + *v1; break;
                case '-': res = *v2 - *v1; break;
                case '*': res = *v2 * *v1; break;
                case '/':
                    if (*v1 == 0) {
                        printf("Erro: divisao por zero.\n");
                        return false;
                    }
                    res = *v2 / *v1;
                    break;
                case '^': {
                    res = 1;
                    for (int i = 0; i < (int)(*v1); i++) res *= *v2;
                    break;
                }
            }

            float *novo = malloc(sizeof(float));
            *novo = res;
            guarde_na_pilha(&resultados, novo);
        }

        remova_elemento_da_fila(entrada);
    }

    if (resultados.qtd_atual != 1) {
        printf("Erro: expressao malformada (sobraram operandos).\n");
        return false;
    }

    ElementoDePilha final;
    recupere_da_pilha(resultados, &final);
    *resultado = *((float *)final);

    free_pilha(&resultados);
    return true;
}

// ----------------------------------------------------
// Integração com o seu código existente
// ----------------------------------------------------
boolean calculaExpressao(char* expressao, float* resultado) {
    boolean ok = removeEspacosValidando(expressao);
    if (!ok) { 
        printf("Erro: expressao invalida.\n");
        return false;
    }

    Fila filaEntrada, filaPosfixa;
    nova_fila(&filaEntrada, 100);
    nova_fila(&filaPosfixa, 100);

    ok = converteTokens(&filaEntrada, expressao);
    if (!ok) return false;

    converteParaPosfixa(&filaEntrada, &filaPosfixa);

    printf("\nExpressao Posfixa:\n");
    for (unsigned int i = 0; i < filaPosfixa.qtd_atual; i++) {
        printf("%s ", (char*) filaPosfixa.vetor[i]);
    }
    printf("\n");


    ok = calculaPosfixa(&filaPosfixa, resultado);
    if (!ok) return false;

    free_fila(&filaEntrada);
    free_fila(&filaPosfixa);
    return true;
}


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
