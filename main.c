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


// ======== ESTRUTURA: AVL ========

typedef struct NoUsuario {
    char email[100]; 
    char nome[100];
    int altura;
    struct NoUsuario* esq;
    struct NoUsuario* dir;
} NoUsuario;

int alturaUsuario(NoUsuario* n) {
    return n ? n->altura : 0;
}

int maxUsuario(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamentoUsuario(NoUsuario* n) {
    return n ? alturaUsuario(n->esq) - alturaUsuario(n->dir) : 0;
}

NoUsuario* rotacaoDireitaUsuario(NoUsuario* y) {
    NoUsuario* x = y->esq;
    NoUsuario* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = maxUsuario(alturaUsuario(y->esq), alturaUsuario(y->dir)) + 1;
    x->altura = maxUsuario(alturaUsuario(x->esq), alturaUsuario(x->dir)) + 1;

    return x;
}

NoUsuario* rotacaoEsquerdaUsuario(NoUsuario* x) {
    NoUsuario* y = x->dir;
    NoUsuario* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = maxUsuario(alturaUsuario(x->esq), alturaUsuario(x->dir)) + 1;
    y->altura = maxUsuario(alturaUsuario(y->esq), alturaUsuario(y->dir)) + 1;

    return y;
}

NoUsuario* inserirUsuarioAVL(NoUsuario* raiz, const char* email, const char* nome) {
    if (raiz == NULL) {
        NoUsuario* novo = (NoUsuario*) malloc(sizeof(NoUsuario));
        strcpy(novo->email, email);
        strcpy(novo->nome, nome);
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if (strcmp(email, raiz->email) < 0)
        raiz->esq = inserirUsuarioAVL(raiz->esq, email, nome);
    else if (strcmp(email, raiz->email) > 0)
        raiz->dir = inserirUsuarioAVL(raiz->dir, email, nome);
    else
        return raiz; 

    raiz->altura = 1 + maxUsuario(alturaUsuario(raiz->esq), alturaUsuario(raiz->dir));
    int fb = fatorBalanceamentoUsuario(raiz);

    if (fb > 1 && strcmp(email, raiz->esq->email) < 0)
        return rotacaoDireitaUsuario(raiz);
    if (fb < -1 && strcmp(email, raiz->dir->email) > 0)
        return rotacaoEsquerdaUsuario(raiz);
    if (fb > 1 && strcmp(email, raiz->esq->email) > 0) {
        raiz->esq = rotacaoEsquerdaUsuario(raiz->esq);
        return rotacaoDireitaUsuario(raiz);
    }
    if (fb < -1 && strcmp(email, raiz->dir->email) < 0) {
        raiz->dir = rotacaoDireitaUsuario(raiz->dir);
        return rotacaoEsquerdaUsuario(raiz);
    }

    return raiz;
}

void listarUsuariosAVL(NoUsuario* raiz) {
    if (raiz != NULL) {
        listarUsuariosAVL(raiz->esq);
        printf("-> %s (%s)\n", raiz->nome, raiz->email);
        listarUsuariosAVL(raiz->dir);
    }
}

void liberarUsuariosAVL(NoUsuario* raiz) {
    if (raiz) {
        liberarUsuariosAVL(raiz->esq);
        liberarUsuariosAVL(raiz->dir);
        free(raiz);
    }
}

// ======== ÁRVORE RUBRO-NEGRA ========

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRN {
    char titulo[100];
    Cor cor;
    struct NoRN* esq;
    struct NoRN* dir;
    struct NoRN* pai;
} NoRN;

typedef struct {
    NoRN* raiz;
    NoRN* nil; 
} ArvoreRN;

NoRN* criarNoNil() {
    NoRN* nil = (NoRN*) malloc(sizeof(NoRN));
    nil->cor = PRETO;
    nil->esq = nil->dir = nil->pai = NULL;
    strcpy(nil->titulo, "");
    return nil;
}

ArvoreRN* criarArvoreRN() {
    ArvoreRN* arv = (ArvoreRN*) malloc(sizeof(ArvoreRN));
    arv->nil = criarNoNil();
    arv->raiz = arv->nil;
    return arv;
}

NoRN* criarNoRN(ArvoreRN* arv, const char* titulo) {
    NoRN* no = (NoRN*) malloc(sizeof(NoRN));
    strcpy(no->titulo, titulo);
    no->cor = VERMELHO;
    no->esq = no->dir = arv->nil;
    no->pai = NULL;
    return no;
}

void rotacaoEsquerdaRN(ArvoreRN* arv, NoRN* x) {
    NoRN* y = x->dir;
    x->dir = y->esq;
    if (y->esq != arv->nil)
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        arv->raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

void rotacaoDireitaRN(ArvoreRN* arv, NoRN* y) {
    NoRN* x = y->esq;
    y->esq = x->dir;
    if (x->dir != arv->nil)
        x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        arv->raiz = x;
    else if (y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;
    x->dir = y;
    y->pai = x;
}

void corrigirInsercaoRN(ArvoreRN* arv, NoRN* z) {
    while (z->pai != NULL && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            NoRN* y = z->pai->pai->dir;
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsquerdaRN(arv, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireitaRN(arv, z->pai->pai);
            }
        } else {
            NoRN* y = z->pai->pai->esq;
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoDireitaRN(arv, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerdaRN(arv, z->pai->pai);
            }
        }
    }
    arv->raiz->cor = PRETO;
}

void inserirRN(ArvoreRN* arv, const char* titulo) {
    NoRN* z = criarNoRN(arv, titulo);
    NoRN* y = NULL;
    NoRN* x = arv->raiz;

    while (x != arv->nil) {
        y = x;
        if (strcmp(z->titulo, x->titulo) < 0)
            x = x->esq;
        else
            x = x->dir;
    }

    z->pai = y;
    if (y == NULL)
        arv->raiz = z;
    else if (strcmp(z->titulo, y->titulo) < 0)
        y->esq = z;
    else
        y->dir = z;

    z->esq = arv->nil;
    z->dir = arv->nil;
    z->cor = VERMELHO;

    corrigirInsercaoRN(arv, z);
}

void inorderRN(ArvoreRN* arv, NoRN* no) {
    if (no != arv->nil) {
        inorderRN(arv, no->esq);
        printf("-> %s (%s)\n", no->titulo, no->cor == VERMELHO ? "VERMELHO" : "PRETO");
        inorderRN(arv, no->dir);
    }
}

void liberarNosRN(ArvoreRN* arv, NoRN* no) {
    if (no != arv->nil) {
        liberarNosRN(arv, no->esq);
        liberarNosRN(arv, no->dir);
        free(no);
    }
}

void liberarArvoreRN(ArvoreRN* arv) {
    liberarNosRN(arv, arv->raiz);
    free(arv->nil);
    free(arv);
}

int main() {
    Livro* arvore = NULL;
    Lista* disponiveis = criarLista();
    Fila* filaEspera = criarFila();
    Pilha* historico = criarPilha();
    NoUsuario* usuarios = NULL;
    ArvoreRN* arvoreRN = criarArvoreRN();

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
        printf("9. Cadastrar Usuario\n");
        printf("10. Listar Usuarios\n");
        printf("11. Cadastrar Livro na Arvore Rubro-Negra\n");
        printf("12. Listar Livros da Arvore Rubro-Negra\n");
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
            case 9:
                printf("Nome do Usuario: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Email do usuario: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                usuarios = inserirUsuarioAVL(usuarios, titulo, nome);
                printf("Usuario cadastrado com sucesso!\n");
                break;
            case 10:
                printf("Lista de usuarios:\n");
                listarUsuariosAVL(usuarios);
                break;
            case 11:
                printf("Titulo do livro: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                inserirRN(arvoreRN, titulo);
                printf("Livro inserido na Arvore Rubro-Negra\n");
                break;
            case 12:
                printf("\nLivros na Arvore Rubro-Negra: \n");
                inorderRN(arvoreRN, arvoreRN->raiz);
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
    liberarUsuariosAVL(usuarios);
    liberarArvoreRN(arvoreRN);

    return 0;
}