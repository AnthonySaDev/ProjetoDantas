#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Estrutura para representar um item no cardapio
typedef struct
{
    char nome[50];
    double preco;
} Item;

// Estrutura para representar uma categoria no cardapio
typedef struct
{
    char nome[50];
    Item produtos[50];
    int numProdutos;
} Categoria;

// Funcao para adicionar uma categoria ao cardapio
void adicionarCategoria(Categoria cardapio[], int *numCategorias)
{
    if (*numCategorias < 50)
    {
        char nomeCategoria[50];
        printf("Categorias do cardapio:\n");
        if(*numCategorias == 0){
            printf("Nenhuma categoria adicionada.\n");
        }
        for (int i = 0; i < *numCategorias; i++)
        {   
            printf("%d - %s\n", i + 1, cardapio[i].nome);
        }
        printf("Digite o nome da nova categoria: ");
        scanf("%s", nomeCategoria);

        strcpy(cardapio[*numCategorias].nome, nomeCategoria);
        cardapio[*numCategorias].numProdutos = 0;
        (*numCategorias)++;
        printf("Categoria '%s' adicionada ao cardapio.\n", nomeCategoria);
    }
    else
    {
        printf("Nao e possivel adicionar mais categorias. Limite alcancado.\n");
    }
}

// Funcao para adicionar um produto a uma categoria do cardapio
void adicionarProduto(Categoria cardapio[], int *numCategorias)
{
    printf("Categorias do cardapio:\n");
    if(*numCategorias == 0){
        printf("Nenhuma categoria adicionada.\n");
    }
    for (int i = 0; i < *numCategorias; i++)
    {
        printf("%d - %s\n", i + 1, cardapio[i].nome);
    }
    char nomeCategoria[50];
    printf("Digite o nome da categoria onde deseja adicionar o produto: ");
    scanf("%s", nomeCategoria);

    for (int i = 0; i < *numCategorias; i++)
    {
        if (strcmp(cardapio[i].nome, nomeCategoria) == 0)
        {
            if (cardapio[i].numProdutos < 50)
            {
                char nomeProduto[50];
                double precoProduto;
                printf("\nProdutos da categoria '%s':\n", cardapio[i].nome);
                printf("Digite o nome do produto: ");
                scanf("%s", nomeProduto);
                printf("Digite o preco do produto: ");
                scanf("%lf", &precoProduto);

                strcpy(cardapio[i].produtos[cardapio[i].numProdutos].nome, nomeProduto);
                cardapio[i].produtos[cardapio[i].numProdutos].preco = precoProduto;
                cardapio[i].numProdutos++;
                printf("Produto '%s' adicionado a categoria '%s'.\n", nomeProduto, nomeCategoria);
            }
            else
            {
                printf("Nao e possivel adicionar mais produtos a esta categoria. Limite alcancado.\n");
            }
            return;
        }
    }
    printf("Categoria '%s' nao encontrada no cardapio. O produto nao foi adicionado.\n", nomeCategoria);
}

// Funcao para mostrar o cardapio ao cliente
void mostrarCardapio(Categoria cardapio[], int numCategorias)
{
    int op = 1;
    double conta = 0.0; // Inicialize a conta como zero

    printf("Bem-vindo ao restaurante!\n");

    while (op != 0)
    {
        printf("\nSelecione a categoria do item que deseja:\n");
        for (int i = 0; i < numCategorias; i++)
        {
            printf("  %d - %s\n", i + 1, cardapio[i].nome);
        }
        printf("  0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if (op >= 1 && op <= numCategorias)
        {
            int categoriaSelecionada = op - 1;
            int escolha = 1;

            while (escolha != 0)
            {
                printf("\n%s:\n", cardapio[categoriaSelecionada].nome);
                for (int i = 0; i < cardapio[categoriaSelecionada].numProdutos; i++)
                {
                    printf("  %d - %s - R$%.2lf\n", i + 1, cardapio[categoriaSelecionada].produtos[i].nome, cardapio[categoriaSelecionada].produtos[i].preco);
                }
                printf("  0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &escolha);
                if (escolha >= 1 && escolha <= cardapio[categoriaSelecionada].numProdutos)
                {
                    int itemIndex = escolha - 1;
                    printf("\n%s - R$%.2lf adicionado ao carrinho.\n", cardapio[categoriaSelecionada].produtos[itemIndex].nome, cardapio[categoriaSelecionada].produtos[itemIndex].preco);
                    conta += cardapio[categoriaSelecionada].produtos[itemIndex].preco;
                }
                else if (escolha != 0)
                {
                    printf("\nEscolha invalida. Por favor, escolha um item valido.\n");
                }
            }
        }
        else if (op != 0)
        {
            printf("\nEscolha invalida. Por favor, escolha uma categoria valida.\n");
        }
    }

    printf("\nCarrinho do cliente:\n");
    for (int i = 0; i < numCategorias; i++)
    {
        for (int j = 0; j < cardapio[i].numProdutos; j++)
        {
            printf("%s - R$%.2lf\n", cardapio[i].produtos[j].nome, cardapio[i].produtos[j].preco);
        }
    }

    // Imprima a conta total ao final
    printf("\nConta total: R$%.2lf\n", conta);
}

int main()
{
    setlocale(LC_ALL, "Portuguese"); // Configura a localizacao para exibicao correta de caracteres acentuados

    Categoria cardapio[50];
    int numCategorias = 0;

    int op = 1;

    while (op != 0)
    {
        printf("\nEscolha a opcao:\n");
        printf("  1 - Cliente\n");
        printf("  2 - Operador\n");
        printf("  0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if (op == 1)
        {
            mostrarCardapio(cardapio, numCategorias);
        }
        else if (op == 2)
        {
            printf("\nOpcões do Operador:\n");
            printf("  1 - Adicionar Categoria\n");
            printf("  2 - Adicionar Produto\n");
            printf("  0 - Voltar\n");
            printf("Opcao: ");
            scanf("%d", &op);

            if (op == 1)
            {
                adicionarCategoria(cardapio, &numCategorias);
            }
            else if (op == 2)
            {
                adicionarProduto(cardapio, &numCategorias);
            }
        }
    }

    return 0;
}
