#include <stdlib.h>
#include "pilha.h"

boolean nova_pilha (Pilha* p, unsigned int capacidade)
{
    if (capacidade<=0) return false;

    // (*p).capacidade_inicial=capacidade;
    p->capacidade_inicial=capacidade;

    // (*p).capacidade=capacidade;
    p->capacidade=capacidade;

    // (*p).vetor=(ElementoDePilha*)malloc(capacidade*sizeof(ElementoDePilha));
    p->vetor=(ElementoDePilha*)malloc(capacidade*sizeof(ElementoDePilha));

    //(*p).qtd_atual=0;
    p->qtd_atual=0;

    return true;
}

boolean guarde_na_pilha (Pilha* p, ElementoDePilha e)
{
    /*
    if ((*p).qtd_atual==(*p).capacidade)
    {
        //(*p).capacidade*=2;
        p->capacidade*=2;
        (*p).vetor=(ElementoDePilha*)realloc((*p).capacidade*sizeof(ElementoDePilha));
        p->vetor=(ElementoDePilha*)realloc(p->capacidade*sizeof(ElementoDePilha));
    }
    */
    if (p->qtd_atual==p->capacidade)
    {
        p->capacidade*=2;
        p->vetor=(ElementoDePilha*)realloc(p->vetor,p->capacidade*sizeof(ElementoDePilha));
    }

    //(*p).vetor[(*p).qtd_atual]=e;
    p->vetor[p->qtd_atual]=e;

    //(*p).qtd_atual++;
    p->qtd_atual++;

    return true;
}

boolean recupere_da_pilha (Pilha p, ElementoDePilha* e)
{
    if (p.qtd_atual==0) return false;

    *e=p.vetor[p.qtd_atual-1];
    return true;
}

boolean remova_elemento_da_pilha (Pilha* p)
{
    //if ((*p).qtd_atual==0) return false;
    if (p->qtd_atual==0) return false;

    //(*p).qtd_atual--;
    p->qtd_atual--;

    //(*p).vetor[(*p).qtd_atual]=NULL;
    p->vetor[p->qtd_atual]=NULL;

    if (p->qtd_atual<=0.25*p->capacidade && p->capacidade>p->capacidade_inicial)
    {
        p->capacidade/=2;
        p->vetor=(ElementoDePilha*)realloc(p->vetor,p->capacidade*sizeof(ElementoDePilha));
    }  

    return true;
}

boolean pilha_cheia (Pilha p)
{
    /*
    if (p.qtd_atual==p.capacidade)
        return true;
    else
        return false;
    */
    return p.qtd_atual==p.capacidade;
}

boolean pilha_vazia (Pilha p)
{
    /*
    if (p.qtd_atual==0)
        return true;
    else
        return false;
    */
    return p.qtd_atual==0;
}

boolean free_pilha (Pilha* p)
{
    if (p->vetor==NULL) return false;
    /*
    //for (int i=0; i<(*p).qtd_atual; i++)
    for (int i=0; i<p->qtd_atual; i++)
    {
        //(*p).qtd_atual--;
        p->qtd_atual--;
        //free((*p).vetor[(*p).qtd_atual]);
        free(p->vetor[p->qtd_atual]);
        //(*p).vetor[(*p).qtd_atual]=NULL;
        p->vetor[p->qtd_atual]=NULL;
    }
    */

    //for (int i=0; i<(*p).qtd_atual; i++)
    for (int i=0; i<p->qtd_atual; i++)
    {
        //free((*p).vetor[--((*p).qtd_atual)]);
        free(p->vetor[--(p->qtd_atual)]);
        //(*p).vetor[(*p).qtd_atual]=NULL;
        p->vetor[p->qtd_atual]=NULL;
    }

    //free((*p).vetor);
    free(p->vetor);
    //(*p).vetor=NULL;
    p->vetor=NULL;

    return true;
}
