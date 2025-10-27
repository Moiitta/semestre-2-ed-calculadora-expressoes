#include "unity.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "basics.h"
#include "fila.h"
#include "pilha.h"

void setUp(void) {}
void tearDown(void) {}

boolean calculaExpressao(char* expressao, float* resultado);

// Função auxiliar: roda cada teste em um processo separado
void run_isolated(void (*test_func)(void)) {
    pid_t pid = fork();
    if (pid == 0) {  // processo filho
        UNITY_BEGIN();
        test_func();
        UNITY_END();
        exit(0);
    } else {
        int status;
        waitpid(pid, &status, 0);
        TEST_ASSERT_EQUAL(0, WEXITSTATUS(status));
    }
}

// ---- testes (iguais aos anteriores) ----
void test_soma_simples(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("1+1", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(2.0, resultado);
}

void test_subtracao(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("5-2", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(3.0, resultado);
}

void test_multiplicacao(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("3*4", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(12.0, resultado);
}

void test_divisao(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("8/2", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(4.0, resultado);
}

void test_potencia(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("2^3", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(8.0, resultado);
}

void test_parenteses_simples(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("(2+3)*4", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(20.0, resultado);
}

void test_parenteses_aninhados(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("((2+3)*(4-1))", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(15.0, resultado);
}

void test_expressao_complexa(void) {
    float resultado;
    TEST_ASSERT_TRUE(calculaExpressao("10+(2*3-4)^2/4+6*2", &resultado));
    TEST_ASSERT_EQUAL_FLOAT(23.0, resultado);
}

void test_divisao_por_zero(void) {
    float resultado;
    TEST_ASSERT_FALSE(calculaExpressao("5/0", &resultado));
}

void test_expressao_malformada(void) {
    float resultado;
    TEST_ASSERT_FALSE(calculaExpressao("5+", &resultado));
}

// ---- runner isolado ----
int main(void) {
    run_isolated(test_soma_simples);
    run_isolated(test_subtracao);
    run_isolated(test_multiplicacao);
    run_isolated(test_divisao);
    run_isolated(test_potencia);
    run_isolated(test_parenteses_simples);
    run_isolated(test_parenteses_aninhados);
    run_isolated(test_expressao_complexa);
    run_isolated(test_divisao_por_zero);
    run_isolated(test_expressao_malformada);
    return 0;
}
