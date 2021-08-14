#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CONSTANTES
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#define MAX_FILA 10
#define ERRO_ALOCACAO "\n\tERRO: Erro de alocação de memória!\n"
#define ERRO_FILA_VAZIA "\n\tERRO: Fila Vazia!\n"
#define ERRO_FILA_CHEIA "\n\tERRO: Fila Cheia!\n"

#define ERRO_VALOR_NAO_ENCONTRADO "\n\tERRO: Valor não encontrado!\n"
#define ERRO_ENTRADA "\n\tERRO: Entrada inválido! Apenas valores maiores que 0, por favor.\n"

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
STRUCTS
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

typedef struct Fila {
    int dados[MAX_FILA];
    int fim;
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
    int i;
    for (i = 0; i < MAX_FILA; i++)
        fila->dados[i] = 0;
    fila->fim = 0;
}

void enfileira(Fila *fila, int dado) {
    if (fila->fim == MAX_FILA) {
        printf(ERRO_FILA_CHEIA);
    } else {
        fila->dados[fila->fim] = dado;
        fila->fim++;
    }
}

int desenfileira(Fila *fila) {
    int dado = NULL;

    if (fila->fim == 0) {
        printf(ERRO_FILA_VAZIA);
        return dado;
    }
    dado = fila->dados[0];
    for (int i = 0; i < fila->fim; i++)
        fila->dados[i] = fila->dados[i+1];
    fila->fim--;

    return dado;
}

void inverterFila(Fila *fila) {
    int *suporte = (int*) malloc (fila->fim * sizeof(int));

    if (suporte == NULL) {
        printf(ERRO_ALOCACAO);
        return;
    }

    for (int i = 1; i <= fila->fim; i++) {
        suporte[fila->fim - i] = fila->dados[i - 1];
    }
    for (int i = 0; i < fila->fim; i++) {
        fila->dados[i] = suporte[i];
    }

    free(suporte);
}

int furarFila(Fila *fila, int dado) {
    int *suporte = (int*) malloc (fila->fim * sizeof(int));
    int i = 0, j = 0, removeu = 0;

    if (fila->fim == 0) {
        printf(ERRO_FILA_VAZIA);
        return 0;
    }
    if (suporte == NULL) {
        printf(ERRO_ALOCACAO);
        return 0;
    }

    while (i < fila->fim) {
        if (fila->dados[i] == dado && !removeu) {
            removeu = 1;
            i++;
        } else {
            suporte[j] = fila->dados[i];
            i++;
            j++;
        }
    }
    
    if (removeu) {
        fila->fim--;
        for (i = 0; i < fila->fim; i++) {
            fila->dados[i] = suporte[i];
        }
        fila->dados[i] = 0;
    }

    free(suporte);
    return removeu;
}

void imprimirFila(Fila *fila) {
    int i;

    printf("\nFila[ ");
    for (i = 0 ; i < fila->fim; i++) {
        printf("%d", fila->dados[i]);
        if (i+1 < fila->fim)
            printf(" | ");
    }
    printf(" ](%d)\n", fila->fim);
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