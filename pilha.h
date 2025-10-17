#ifndef PILHA
#define PILHA

#include "basics.h"

typedef void* ElementoDePilha;

typedef struct {
    ElementoDePilha* vetor; // Elemento vetor [];
    unsigned int capacidade_inicial, capacidade, qtd_atual;
} Pilha;

boolean nova_pilha (Pilha* p, unsigned int capacidade);
boolean guarde_na_pilha (Pilha* p, ElementoDePilha e);
boolean recupere_da_pilha (Pilha p, ElementoDePilha* e);
boolean remova_elemento_da_pilha (Pilha* p);
boolean pilha_cheia (Pilha p);
boolean pilha_vazia (Pilha p);
boolean free_pilha (Pilha* p);

#endif // PILHA