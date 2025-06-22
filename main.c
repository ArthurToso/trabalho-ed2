#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ======== ÁRVORE BINÁRIA DE LIVROS ========

typedef struct Livro {
    char titulo[100];
    struct Livro* esq;
    struct Livro* dir;
} Livro;

Livro* criarLivro(const char* titulo) {
    Livro* novo = (Livro*) malloc(sizeof(Livro));
    strcpy(novo->titulo, titulo);
    novo->esq = novo->dir = NULL;
    return novo;
}

Livro* inserirLivro(Livro* raiz, const char* titulo) {
    if (raiz == NULL) return criarLivro(titulo);
    if (strcmp(titulo, raiz->titulo) < 0) {
        raiz->esq = inserirLivro(raiz->esq, titulo);
    } else {
        raiz->dir = inserirLivro(raiz->dir, titulo);
    }
    return raiz;
}

Livro* buscarLivro(Livro* raiz, const char* titulo) {
    if (raiz == NULL || strcmp(raiz->titulo, titulo) == 0)
        return raiz;
    if (strcmp(titulo, raiz->titulo) < 0)
        return buscarLivro(raiz->esq, titulo);
    else
        return buscarLivro(raiz->dir, titulo);
}

void listarLivrosEmOrdem(Livro* raiz) {
    if (raiz != NULL) {
        listarLivrosEmOrdem(raiz->esq);
        printf("-> %s\n", raiz->titulo);
        listarLivrosEmOrdem(raiz->dir);
    }
}

void liberarArvore(Livro* raiz) {
    if (raiz) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

// ======== ESTRUTURA: LISTA DE LIVROS DISPONÍVEIS ========

typedef struct NoLista {
    char titulo[100];
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* inicio;
} Lista;

Lista* criarLista() {
    Lista* nova = (Lista*) malloc(sizeof(Lista));
    nova->inicio = NULL;
    return nova;
}

void adicionarLivroNaLista(Lista* lista, const char* titulo) {
    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));
    strcpy(novo->titulo, titulo);
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

void removerLivroDaLista(Lista* lista, const char* titulo) {
    NoLista *anterior = NULL, *atual = lista->inicio;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return;
    if (anterior == NULL)
        lista->inicio = atual->prox;
    else
        anterior->prox = atual->prox;
    free(atual);
}

int livroDisponivel(Lista* lista, const char* titulo) {
    NoLista* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void imprimirLista(Lista* lista) {
    NoLista* atual = lista->inicio;
    printf("\nLivros disponiveis:\n");
    while (atual != NULL) {
        printf("-> %s\n", atual->titulo);
        atual = atual->prox;
    }
}

void liberarLista(Lista* lista) {
    NoLista* atual = lista->inicio;
    while (atual != NULL) {
        NoLista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

// ======== ESTRUTURA: FILA DE ESPERA ========

typedef struct NoFila {
    char nomeUsuario[100];
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
} Fila;

Fila* criarFila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void enfileirar(Fila* fila, const char* nomeUsuario) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    strcpy(novo->nomeUsuario, nomeUsuario);
    novo->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

void desenfileirar(Fila* fila) {
    if (fila->inicio == NULL) return;
    NoFila* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;
    free(temp);
}

void imprimirFila(Fila* fila) {
    NoFila* atual = fila->inicio;
    printf("\nFila de espera: \n");
    while (atual != NULL) {
        printf("-> %s\n", atual->nomeUsuario);
        atual = atual->prox;
    }
}

void liberarFila(Fila* fila) {
    while (fila->inicio != NULL) {
        desenfileirar(fila);
    }
    free(fila);
}

// ======== ESTRUTURA: PILHA DE EMPRÉSTIMOS ========

typedef struct NoPilha {
    char tituloLivro[100];
    char nomeUsuario[100];
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

Pilha* criarPilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void empilhar(Pilha* pilha, const char* tituloLivro, const char* nomeUsuario) {
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    strcpy(novo->tituloLivro, tituloLivro);
    strcpy(novo->nomeUsuario, nomeUsuario);
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

void desempilhar(Pilha* pilha) {
    if (pilha->topo == NULL) return;
    NoPilha* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);
}

void imprimirPilha(Pilha* pilha) {
    NoPilha* atual = pilha->topo;
    printf("\nHistorico de Emprestimos:\n");
    while (atual != NULL) {
        printf("-> %s emprestou \"%s\"\n", atual->nomeUsuario, atual->tituloLivro);
        atual = atual->prox;
    }
}

void liberarPilha(Pilha* pilha) {
    while (pilha->topo != NULL) {
        desempilhar(pilha);
    }
    free(pilha);
}

int main() {
    Livro* arvore = NULL;
    Lista* disponiveis = criarLista();
    Fila* filaEspera = criarFila();
    Pilha* historico = criarPilha();

    int opcao;
    char titulo[100];
    char nome[100];

    do {
        printf("\nMENU BIBLIOTECA\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Adicionar livro a lista de disponiveis\n");
        printf("4. Ver lista de livros disponiveis\n");
        printf("5. Emprestar livro\n");
        printf("6. Ver fila de espera\n");
        printf("7. Historico de emprestimos\n");
        printf("8. Desfazer ultimo emprestimo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Titulo do livro: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                arvore = inserirLivro(arvore, titulo);
                printf("Livro cadastrado.\n");
                break;
            case 2:
                printf("\nLivros cadastrados:\n");
                listarLivrosEmOrdem(arvore);
                break;
            case 3:
                printf("Titulo do livro a adicionar na lista: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                adicionarLivroNaLista(disponiveis, titulo);
                printf("Livro disponivel para emprestimo.\n");
                break;
            case 4:
                imprimirLista(disponiveis);
                break;
            case 5:
                printf("Titulo do livro: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                if (!livroDisponivel(disponiveis, titulo)) {
                    printf("Livro indisponivel! Digite seu nome para entrar na fila: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    enfileirar(filaEspera, nome);
                } else {
                    printf("Nome do usuario: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    empilhar(historico, titulo, nome);
                    removerLivroDaLista(disponiveis, titulo);
                    printf("Livro emprestado com sucesso!\n");
                }
                break;
            case 6:
                imprimirFila(filaEspera);
                break;
            case 7:
                imprimirPilha(historico);
                break;
            case 8:
                printf("Desfazendo ultimo emprestimo...\n");
                desempilhar(historico);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    liberarArvore(arvore);
    liberarLista(disponiveis);
    liberarFila(filaEspera);
    liberarPilha(historico);

    return 0;
}