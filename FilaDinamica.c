#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CONSTANTES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#define ERRO_ALOCACAO "\n\tERRO: Erro de alocação de memória!\n"
#define ERRO_FILA_VAZIA "\n\tERRO: Fila Vazia!\n"

#define ERRO_VALOR_NAO_ENCONTRADO "\n\tERRO: Valor não encontrado!\n"
#define ERRO_ENTRADA "\n\tERRO: Entrada inválido! Apenas valores maiores que 0, por favor.\n"

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
STRUCTS
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct Fila {
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
DECLARAÇÕES DE FUNÇÕES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

Fila* criarFila();
void inicializarFila(Fila *fila);
void enfileira(Fila *fila, int dado);
int desenfileira(Fila *fila);
void inverterFila(Fila *fila);
int furarFila(Fila *fila, int dado);
void imprimirFila(Fila *fila);

int menu();
int validarEntrada();

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
FUNÇÕES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

Fila* criarFila() {
    Fila *novo = (Fila*)malloc(sizeof(Fila));

    if (novo == NULL) {
        printf(ERRO_ALOCACAO);
    } else {
        inicializarFila(novo);
    }

    return novo;
}

void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

void enfileira(Fila *fila, int dado) {
    No *ptr = (No*)malloc(sizeof(No));
    
    if (ptr == NULL) {
        printf(ERRO_ALOCACAO);
    } else {
        ptr->dado = dado;
        ptr->prox = NULL;

        if (fila->inicio == NULL)
            fila->inicio = ptr;
        else
            fila->fim->prox = ptr;

        fila->fim = ptr;
        fila->tamanho++;
    }
    
}

int desenfileira(Fila *fila) {
    No *ptr = fila->inicio;
    int dado = NULL;

    if (ptr == NULL) {
        printf(ERRO_FILA_VAZIA);
    } else {
        fila->inicio = ptr->prox;
        ptr->prox = NULL;
        dado = ptr->dado;
        free(ptr);
        if (fila->inicio == NULL)
            fila->fim = NULL;
        fila->tamanho--;
    }

    return dado;
}

void inverterFila(Fila *fila) {
    int *suporte = (int*) malloc (fila->tamanho * sizeof(int));
    int contador = 0;

    while (fila->tamanho > 0) {
        suporte[contador] = desenfileira(fila);
        contador++;
    }
    while (contador > 0) {
        enfileira(fila, suporte[contador - 1]);
        contador--;
    }
}

int furarFila(Fila *fila, int dado) {
    No *suporte = fila->inicio;
    No *removido;

    if (fila->tamanho == 0) {
        printf(ERRO_FILA_VAZIA);
        return 0;
    }

    if (fila->inicio->dado == dado) {
        desenfileira(fila);
        return 1;
    }

    if (fila->fim->dado == dado) {
        inverterFila(fila);
        desenfileira(fila);
        inverterFila(fila);
        return 1;
    }

    while (suporte->prox != NULL) {
        if (suporte->prox->dado == dado) {
            removido = suporte->prox;
            suporte->prox = suporte->prox->prox;
            free(removido);
            fila->tamanho--;
            return 1;
        }
        suporte = suporte->prox;
    }

    return 0;
}

void imprimirFila(Fila *fila) {
    No *ptr = fila->inicio;

    printf("\nFila[ ");
    while (ptr != NULL) {
        printf("%d", ptr->dado);
        ptr = ptr->prox;
        if (ptr != NULL)
            printf(" | ");
    }
    printf(" ](%d)\n", fila->tamanho);
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
MAIN
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

int menu() {
    int select = 0;

    printf("\n===== FILA =====");
    printf("\n1 - Inserir");
    printf("\n2 - Imprimir");
    printf("\n3 - Remover");
    printf("\n4 - Inverter");
    printf("\n5 - Furar fila");
    printf("\n0 - Sair");
    printf("\nEscolha: ");
    scanf("%d", &select);
    printf("\n================\n");

    return select;
}

int validarEntrada() {
    int valor;

    while (1) {
        printf("\nEntrada: ");
        scanf("%d", &valor);

        if (valor <= NULL) {
            printf(ERRO_ENTRADA);
        } else {
            break;
        }
    }

    return valor;
}

int main(int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    Fila *fila = criarFila();
    int valor;

    if (fila == NULL) {
        return 0;
    }

    while (1) {
        switch (menu()) {
        case 1:
            valor = validarEntrada();
            enfileira(fila, valor);
            break;
        case 2:
            imprimirFila(fila);
            break;
        case 3:
            valor = desenfileira(fila);
            if (valor != NULL) {
                printf("\nSaida: %d\n", valor);
            }
            break;
        case 4:
            inverterFila(fila);
            break;
        case 5:
            valor = validarEntrada();
            if (!furarFila(fila, valor)) {
                printf(ERRO_VALOR_NAO_ENCONTRADO);
            }
            break;
        default:
            printf("\n\tSaindo...\n\n");
            free(fila);
            return 0;
            break;
        }
    }
}