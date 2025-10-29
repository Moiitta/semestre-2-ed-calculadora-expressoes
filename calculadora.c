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

boolean ehDecimal(char c) {
    return (c == '.');
}

static boolean ehTokenNumero(const char* tk) {
    if (!tk || !tk[0]) return false;
    if (isdigit((unsigned char)tk[0])) return true;
    if (tk[0] == '.' && isdigit((unsigned char)tk[1])) return true;
    return false;
}

boolean removeEspacosValidando(char *str) {
    int i, j = 0;
    int tamanho = strlen(str);

    for (i = 0; i < tamanho; i++) {
        if (!(isdigit((unsigned char)str[i]) || ehDecimal(str[i]) || ehOperador(str[i]) || isspace((unsigned char)str[i]))) {
            printf("Erro: caractere inválido: %c\n", str[i]);
            return false;
        }
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

    // 0.5 + 0.5
    // temp = 0

    for(i = 0; i < tamanho; i++) {
        if(isdigit((unsigned char)expressao[i]) == true || ehDecimal(expressao[i])) {
            temp[j] = expressao[i];
            j++;

            if(isdigit((unsigned char)expressao[i + 1]) == false && !ehDecimal((unsigned char)expressao[i + 1])) {
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

static int idx(char op) {
    switch (op) {
        case '(': return 0;
        case '^': return 1;
        case '*': return 2;
        case '/': return 3;
        case '+': return 4;
        case '-': return 5;
        case ')': return 6;
        default:  return -1;
    }
}

static const int TABELA[7][7] = {
/* topo\atual     (  ^  *  /  +  -  ) */
 /* ( */        { 0, 0, 0, 0, 0, 0, 1 },
 /* ^ */        { 0, 0, 1, 1, 1, 1, 1 },
 /* * */        { 0, 0, 1, 1, 1, 1, 1 },
 /* / */        { 0, 0, 1, 1, 1, 1, 1 },
 /* + */        { 0, 0, 0, 0, 1, 1, 1 },
 /* - */        { 0, 0, 0, 0, 1, 1, 1 },
 /* ) */        { 0, 0, 0, 0, 0, 0, 0 },
};

static boolean deveDesempilharPorTabela(char topo, char atual) {
    int i = idx(topo);
    int j = idx(atual);
    if (i < 0 || j < 0) return false;
    return TABELA[i][j] ? true : false;
}


boolean converteParaPosfixa(Fila *entrada, Fila *saida) {
    Pilha operadores;
    nova_pilha(&operadores, 100);

    ElementoDeFila e;
    while (!fila_vazia(*entrada)) {
        recupere_da_fila(*entrada, &e);
        char *token = (char *)e;

        if (ehTokenNumero(token)) {
            guarde_na_fila(saida, strdup(token));
        } else if (token[0] == '(') {
            guarde_na_pilha(&operadores, strdup(token));
        } else if (token[0] == ')') {
            // Enquanto topo != '(' → desempilha para saída
            ElementoDePilha top;
            boolean achouAbre = false;
            while (!pilha_vazia(operadores)) {
                recupere_da_pilha(operadores, &top);
                if (((char*)top)[0] == '(') {
                    remova_elemento_da_pilha(&operadores); // descarta '('
                    achouAbre = true;
                    break;
                }
                guarde_na_fila(saida, strdup((char*)top));
                remova_elemento_da_pilha(&operadores);
            }
            if (!achouAbre) {
                printf("Erro: parenteses desbalanceados.\n");
                return false;
            }
        } else if (ehOperador(token[0])) {
            // Enquanto pilha não vazia E Tabela[topo][atual] == T → desempilha topo para saída
            ElementoDePilha top;
            while (!pilha_vazia(operadores)) {
                recupere_da_pilha(operadores, &top);
                char topoChar = ((char*)top)[0];
                if (!deveDesempilharPorTabela(topoChar, token[0])) break;
                guarde_na_fila(saida, strdup((char*)top));
                remova_elemento_da_pilha(&operadores);
            }
            guarde_na_pilha(&operadores, strdup(token));
        } else {
            printf("Erro: token invalido: %s\n", token);
            return false;
        }

        remova_elemento_da_fila(entrada); // consome o token de entrada
    }

    // Desempilha o restante
    ElementoDePilha top;
    while (!pilha_vazia(operadores)) {
        recupere_da_pilha(operadores, &top);
        if (((char*)top)[0] == '(' || ((char*)top)[0] == ')') {
            printf("Erro: parenteses desbalanceados.\n");
            return false;
        }
        guarde_na_fila(saida, strdup((char*)top));
        remova_elemento_da_pilha(&operadores);
    }

    free_pilha(&operadores);
    return true;
}

boolean calculaPosfixa(Fila *entrada, float *resultado) {
    Pilha resultados;
    nova_pilha(&resultados, 100);

    ElementoDeFila e;
    while (!fila_vazia(*entrada)) {
        recupere_da_fila(*entrada, &e);
        char *token = (char *)e;

        if (ehTokenNumero(token)) {
            float *valor = (float*)malloc(sizeof(float));
            *valor = (float)atof(token);
            guarde_na_pilha(&resultados, valor);
        } else if (ehOperador(token[0])) {
            // 1) Desempilha dois valores (Valor1 e Valor2)
            if (resultados.qtd_atual < 2) {
                printf("Erro: expressao malformada (faltam operandos).\n");
                return false;
            }

            ElementoDePilha el1, el2;
            recupere_da_pilha(resultados, &el1); remova_elemento_da_pilha(&resultados);
            recupere_da_pilha(resultados, &el2); remova_elemento_da_pilha(&resultados);
            float *v1 = (float*)el1; // primeiro desempilhado = Valor1 (da direita)
            float *v2 = (float*)el2; // segundo desempilhado = Valor2 (da esquerda)

            // 2) Se um dos valores for operador → erro (aqui nunca é, só empilhamos números)
            // 3) Resultado = Valor2 (op) Valor1
            float res = 0.0f;
            switch (token[0]) {
                case '+': res = *v2 + *v1; break;
                case '-': res = *v2 - *v1; break;
                case '*': res = *v2 * *v1; break;
                case '/':
                    if (*v1 == 0.0f) {
                        printf("Erro: divisao por zero.\n");
                        return false;
                    }
                    res = *v2 / *v1; break;
                case '^': {
                    // expoente inteiro (conforme aula), simples e fiel
                    int exp = (int)(*v1);
                    res = 1.0f;
                    for (int i = 0; i < exp; i++) res *= *v2;
                    break;
                }
                default:
                    printf("Erro: operador invalido: %c\n", token[0]);
                    return false;
            }

            float *novo = (float*)malloc(sizeof(float));
            *novo = res;
            guarde_na_pilha(&resultados, novo);
        } else {
            printf("Erro: token invalido na posfixa: %s\n", token);
            return false;
        }

        remova_elemento_da_fila(entrada); // consome token
    }

    // Ao final, a pilha deve ter exatamente 1 valor
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

    // free_fila(&filaEntrada);
    // free_fila(&filaPosfixa);
    return true;
}

