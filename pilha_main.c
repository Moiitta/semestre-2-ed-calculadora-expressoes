#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main()
{
    Pilha pil;
    nova_pilha (&pil,10);
    
    int*  i;

    i=(int*)malloc(sizeof(int));
    *i=2;
    guarde_na_pilha (&pil,(ElementoDePilha)i);
    i=NULL;

    i=(int*)malloc(sizeof(int));
    *i=3;
    guarde_na_pilha (&pil,(ElementoDePilha)i);
    i=NULL;

    i=(int*)malloc(sizeof(int));
    *i=5;
    guarde_na_pilha (&pil,(ElementoDePilha)i);
    i=NULL;

    while (!pilha_vazia(pil))
    {
        recupere_da_pilha(pil,(ElementoDePilha*)&i);
        remova_elemento_da_pilha(&pil);
        printf("%d ",*i);
        free(i);
        i=NULL;
    }

    free_pilha(&pil);

    return 0;
}

