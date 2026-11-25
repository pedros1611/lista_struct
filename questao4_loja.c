#include <stdio.h>
#define MAXP 10
#define MAXV 20

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

typedef struct {
    Produto produto;   /* dados do produto vendido */
    int quantidade;
    float total;
} Venda;

Produto prod[MAXP];
Venda vendas[MAXV];
int nProd = 0, nVendas = 0;

int buscar(int codigo) {
    for (int i = 0; i < nProd; i++)
        if (prod[i].codigo == codigo) return i;
    return -1;
}

void cadastrarProduto(void) {
    int c;
    if (nProd >= MAXP) { puts("Limite de produtos atingido."); return; }
    printf("Codigo: "); scanf("%d", &c);
    if (buscar(c) != -1) { puts("Codigo ja cadastrado!"); return; }
    prod[nProd].codigo = c;
    printf("Nome: "); scanf(" %49[^\n]", prod[nProd].nome);
    printf("Preco: "); scanf("%f", &prod[nProd].preco);
    printf("Estoque: "); scanf("%d", &prod[nProd].estoque);
    nProd++;
    puts("Produto cadastrado!");
}

void registrarVenda(void) {
    int c, q;
    if (nVendas >= MAXV) { puts("Limite de vendas atingido."); return; }
    if (nProd == 0) { puts("Cadastre produtos primeiro."); return; }
    for (int i = 0; i < nProd; i++)
        printf("Cod %d | %-20s | R$ %.2f | Estoque: %d\n",
               prod[i].codigo, prod[i].nome, prod[i].preco, prod[i].estoque);
    printf("Codigo do produto: "); scanf("%d", &c);
    int i = buscar(c);
    if (i == -1) { puts("Produto nao cadastrado."); return; }
    printf("Quantidade: "); scanf("%d", &q);
    if (q <= 0 || q > prod[i].estoque) {
        printf("Quantidade invalida! Disponivel: %d\n", prod[i].estoque);
        return;
    }
    prod[i].estoque -= q;                 /* atualiza o estoque */
    vendas[nVendas].produto = prod[i];
    vendas[nVendas].quantidade = q;
    vendas[nVendas].total = q * prod[i].preco;
    printf("Venda registrada. Total: R$ %.2f\n", vendas[nVendas].total);
    nVendas++;
}

void relatorio(void) {
    float fatTotal = 0, maior = -1;
    int imaior = -1;
    for (int i = 0; i < nProd; i++) {
        float fat = 0;
        for (int j = 0; j < nVendas; j++)
            if (vendas[j].produto.codigo == prod[i].codigo) fat += vendas[j].total;
        fatTotal += fat;
        if (fat > maior) { maior = fat; imaior = i; }
        printf("%-20s Faturamento: R$ %.2f | Estoque atual: %d\n",
               prod[i].nome, fat, prod[i].estoque);
    }
    printf("\nFaturamento total: R$ %.2f\n", fatTotal);
    if (imaior >= 0 && maior > 0)
        printf("Produto com maior faturamento: %s (R$ %.2f)\n", prod[imaior].nome, maior);
}

int main(void) {
    int op;
    do {
        printf("\n===== LOJA =====\n1-Cadastrar produto  2-Registrar venda  3-Relatorio  0-Sair\nOpcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1: cadastrarProduto(); break;
            case 2: registrarVenda(); break;
            case 3: relatorio(); break;
            case 0: puts("Encerrando..."); break;
            default: puts("Opcao invalida.");
        }
    } while (op != 0);
    return 0;
}
