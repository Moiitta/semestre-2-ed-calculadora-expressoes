#include <stdlib.h>
#include "fila.h"

boolean nova_fila (Fila* f, unsigned int capacidade)
{
    if (capacidade<=0) return false;

    // (*f).capacidade=capacidade;
    f->capacidade=capacidade;

    // (*f).vetor=(ElementoDeFila*)malloc(capacidade*sizeof(ElementoDeFila));
    f->vetor=(ElementoDeFila*)malloc(capacidade*sizeof(ElementoDeFila));

    //(*f).qtd_atual=0;
    f->qtd_atual=0;

    return true;
}

boolean guarde_na_fila (Fila* f, ElementoDeFila e)
{
    //if ((*f).qtd_atual==(*f).capacidade) return false;
    if (f->qtd_atual==f->capacidade) return false;

    //(*f).vetor[(*f).qtd_atual]=e;
    f->vetor[f->qtd_atual]=e;

    //(*f).qtd_atual++;
    f->qtd_atual++;

    return true;
}

boolean recupere_da_fila (Fila f, ElementoDeFila* e)
{
    if (f.qtd_atual==0) return false;

    *e=f.vetor[0];
    return true;
}

boolean remova_elemento_da_fila (Fila* f)
{
    //if ((*f).qtd_atual==0) return false;
    if (f->qtd_atual==0) return false;

    //for (int posicao=1; posicao<(*f).qtd_atual; posicao++)
    for (int posicao=1; posicao<f->qtd_atual; posicao++)
        //(*f).vetor[posicao-1]=(*f).vetor[posicao];
        f->vetor[posicao-1]=f->vetor[posicao];

    f->qtd_atual--;
    f->vetor[f->qtd_atual]=NULL;
	
    return true;
}

boolean fila_cheia (Fila f)
{
    /*
    if (f.qtd_atual==f.capacidade)
        return true;
    else
        return false;
    */
    return f.qtd_atual==f.capacidade;
}

boolean fila_vazia (Fila f)
{
    /*
    if (f.qtd_atual==0)
        return true;
    else
        return false;
    */
    return f.qtd_atual==0;
}

boolean free_fila (Fila* f)
{
    if (f->vetor==NULL) return false;
    /*
    for (int i=0; i<f->qtd_atual; i++)
    {
        f->qtd_atual--;
        free(f->vetor[f->qtd_atual];
    }
    */

    for (int i=0; i<f->qtd_atual; i++)
        free(f->vetor[--f->qtd_atual]);

    free(f->vetor);
    f->vetor=NULL;

    return true;
}
