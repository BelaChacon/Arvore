#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    struct No* esquerda;
    struct No* direita;
} No;

No* criarNo(int dado){
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

No* inserir(No* raiz, int dado){
    if(raiz == NULL){
        return criarNo(dado);
    }

    if(dado < raiz->dado){
        raiz->esquerda = inserir(raiz->esquerda, dado);
    } else if (dado > raiz->dado){
        raiz->direita = inserir(raiz->direita, dado);
    }

    return raiz;
}

No* buscar(No* raiz, int dado){
    if(raiz == NULL || raiz->dado == dado){
        return raiz;
    }
    if(dado < raiz->dado){
        return buscar(raiz->esquerda, dado);
    }
    return buscar(raiz->direita, dado);
}

No* buscarMin(No* no){
    while (no->esquerda != NULL){
        no = no->esquerda;
    }
    return no;
}

No* excluir(No* raiz, int dado){
    if(raiz == NULL){
        return raiz;
    }

    if(dado < raiz->dado){
        raiz->esquerda = excluir(raiz->esquerda, dado);
    }else if(dado > raiz->dado){
        raiz->direita = excluir(raiz->direita, dado);
    }else{
        if(raiz->esquerda == NULL){
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }else if(raiz->direita == NULL){
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No* temp = buscarMin(raiz->direita);
        raiz->dado = temp->dado;
        raiz->direita = excluir(raiz->direita, temp->dado);
    }
}

void emOrdem(No* raiz){
    if(raiz != NULL){
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        emOrdem(raiz->direita);
    }
}

void preOrdem(No* raiz){
    if(raiz != NULL){
        printf("%d ", raiz->dado);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz){
    if(raiz != NULL){
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->dado);
    }
}

void invertida(No* raiz){
    if(raiz != NULL){
        invertida(raiz->direita);
        printf("%d ", raiz->dado);
        invertida(raiz->esquerda);
    }
}

typedef struct NoFila {
    No* no;
    struct NoFila* proximo;
} NoFila;

typedef struct {
    NoFila* frente;
    NoFila* tras;
} Fila;

Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->frente = fila->tras = NULL;
    return fila;
}

void enfileirar(Fila* fila, No* no) {
    NoFila* novoNo = (NoFila*)malloc(sizeof(NoFila));
    novoNo->no = no;
    novoNo->proximo = NULL;

    if (fila->tras == NULL) {
        fila->frente = fila->tras = novoNo;
    } else {
        fila->tras->proximo = novoNo;
        fila->tras = novoNo;
    }
}

No* desenfileirar(Fila* fila) {
    if (fila->frente == NULL) {
        return NULL;
    }

    NoFila* temp = fila->frente;
    No* no = temp->no;
    fila->frente = fila->frente->proximo;

    if (fila->frente == NULL) {
        fila->tras = NULL;
    }

    free(temp);
    return no;
}

void emNivel(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    Fila* fila = criarFila();
    enfileirar(fila, raiz);

    while (fila->frente != NULL) {
        No* no = desenfileirar(fila);
        printf("%d ", no->dado);

        if (no->esquerda != NULL) {
            enfileirar(fila, no->esquerda);
        }
        if (no->direita != NULL) {
            enfileirar(fila, no->direita);
        }
    }

    free(fila);
}

int soma(No* raiz){
    if(raiz == NULL){
        return 0;
    }
    return raiz->dado + soma(raiz->esquerda) + soma(raiz->direita);
}

void exibirArvore(No* raiz, int nivel){
    if(raiz == NULL){
        return;
    }
    exibirArvore(raiz->direita, nivel + 1);
    for(int i = 0; i < nivel; i++){
        printf("  ");
    }
    printf("%d\n", raiz->dado);
    exibirArvore(raiz->esquerda, nivel + 1);

}

int main(){

    No* raiz = NULL;
    int opcao, dado;

    while(1){
        printf("----------MENU-----------\n");
        printf("1. INSERIR\n2. BUSCAR\n3. EXCLUIR\n4. EXIBIR EM-ORDEM\n5. EXIBIR PRÉ-ORDEM\n6. EXIBIRPÓS-ORDEM\n7. EXIBIR DESCRESCENTE\n8. EXIBIR ÁRVORE BINÁRIA\n9. EXIBIR EM NÍVEL\n10. SOMAR\n11. SAIR\n");
        printf("-------------------------\n");
        printf("ESCOLHA UMA OPÇÃO: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("\nDIGITE O ELEMENTO A SER INSERIDO: ");
            scanf("%d", &dado);
            raiz = inserir(raiz, dado);
            break;

        case 2:
            printf("\nDIGITE O ELEMENTO QUE DESEJA BUSCAR: ");
            scanf("%d", &dado);
            if(buscar(raiz, dado)){
                printf("ELEMENTO ENCONTRADO!");
            }else{
                printf("ELEMENTO NÃO ENCONTRADO!");
            }
            break;

        case 3:
            printf("\nDIGITE O ELEMENTO QUE DESEJA EXCLUIR: ");
            scanf("%d", &dado);
            raiz = excluir(raiz, dado);
            break;

        case 4:
            printf("EXIBINDO EM-ORDEM: ");
            emOrdem(raiz);
            printf("\n");
            break;

        case 5:
            printf("EXIBINDO EM PRÉ-ORDEM: ");
            preOrdem(raiz);
            printf("\n");
            break;

        case 6:
            printf("EXIBINDO EM PÓS-ORDEM: ");
            posOrdem(raiz);
            printf("\n");
            break;

        case 7:
            printf("EXIBINDO EM DECRESCENTE(INVERTIDO): ");
            invertida(raiz);
            printf("\n");
            break;

        case 8:
            printf("ÁRVORE BINÁRIA:\n");
            exibirArvore(raiz, 0);

        case 9:
            printf("EXIBINDO EM NÍVEL: ");
            emNivel(raiz);
            printf("\n");
            break;

        case 10:
            printf("SOMA DOS ELEMENTOS: %d\n", soma(raiz));
            break;

        case 11:
            free(raiz);
            return 0;
        default:
            printf("OPÇÃO INEXISTENTE!\n");
        }
    }

    return 0;
}

