#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "lista.h"
#include "fila.h"

int main() {

/*    Ponteiros com Alocação Dinamica e Arvore Binária */
    Livro* biblioteca = NULL;

    biblioteca = inserirLivro(biblioteca, "Livro A");
    biblioteca = inserirLivro(biblioteca, "Livro B");
    biblioteca = inserirLivro(biblioteca, "Livro C");

    printf("Arvore Binaria\n");
    printf("Livros em ordem alfabetica:\n");
    listarLivrosEmOrdem(biblioteca);

    Livro* l = buscarLivro(biblioteca, "Livro B");
    if (l) {
        printf("Livro encontrado: %s\n", l->titulo);
    }

    liberarArvore(biblioteca);

/* Lista de Livros Disponíveis */

    print("Lista de livros disponiveis\n");
    Lista* disponiveis = criarLista();
    adicionarLivroNaLista(disponiveis, "Dom Quixote");
    adicionarLivroNaLista(disponiveis, "Pequeno Principe");

    imprimirLista(disponiveis);

    removerLivroDaLista(disponiveis, "Pequeno Principe");

    printf("\nLista apos a remocao:\n");
    imprimirLista(disponiveis);

    liberarLista(disponiveis);

/* Fila de Espera para um Livro */

    Fila* filaEsperandoLivro = criarFila();

    enfileirar(filaEsperandoLivro, "Arthur");
    enfileirar(filaEsperandoLivro, "Mariana");
    enfileirar(filaEsperandoLivro, "Theo");

    imprimirFila(filaEsperandoLivro);

    printf("\nDesenfileirando 1..\n");
    desenfileirar(filaEsperandoLivro);
    imprimirFila(filaEsperandoLivro);

    liberarFila(filaEsperandoLivro);

    return 0;
}