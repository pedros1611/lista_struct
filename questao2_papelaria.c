#include <stdio.h>
#define MAX 15

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

Produto prod[MAX];
int qtd = 0;

int buscar(int codigo) {
    for (int i = 0; i < qtd; i++)
        if (prod[i].codigo == codigo) return i;
    return -1;
}

void cadastrar(void) {
    int c;
    if (qtd >= MAX) { puts("Limite de produtos atingido."); return; }
    printf("Codigo: ");
    scanf("%d", &c);
    if (buscar(c) != -1) { puts("Codigo ja cadastrado!"); return; }
    prod[qtd].codigo = c;
    printf("Nome: ");
    scanf(" %49[^\n]", prod[qtd].nome);
    printf("Preco: ");
    scanf("%f", &prod[qtd].preco);
    printf("Quantidade em estoque: ");
    scanf("%d", &prod[qtd].estoque);
    qtd++;
    puts("Produto cadastrado!");
}

void listar(void) {
    if (qtd == 0) { puts("Nenhum produto cadastrado."); return; }
    for (int i = 0; i < qtd; i++)
        printf("Cod %d | %-20s | R$ %.2f | Estoque: %d\n",
               prod[i].codigo, prod[i].nome, prod[i].preco, prod[i].estoque);
}

void reporEstoque(Produto *p, int quantidade) {
    p->estoque += quantidade;
}

int venderProduto(Produto *p, int quantidade) {
    if (quantidade <= 0 || quantidade > p->estoque) return 0;
    p->estoque -= quantidade;
    return 1;
}

void consultar(void) {
    int c;
    printf("Codigo: ");
    scanf("%d", &c);
    int i = buscar(c);
    if (i == -1) { puts("Produto nao encontrado."); return; }
    printf("Cod %d | %s | R$ %.2f | Estoque: %d\n",
           prod[i].codigo, prod[i].nome, prod[i].preco, prod[i].estoque);
}

void relatorio(void) {
    float total = 0, maior = -1;
    int imaior = -1;
    for (int i = 0; i < qtd; i++) {
        float v = prod[i].preco * prod[i].estoque;
        total += v;
        if (v > maior) { maior = v; imaior = i; }
    }
    printf("Valor total em estoque: R$ %.2f\n", total);
    if (imaior >= 0)
        printf("Maior valor em estoque: %s (R$ %.2f)\n", prod[imaior].nome, maior);
}

int main(void) {
    int op, c, q, i;
    do {
        printf("\n===== PAPELARIA =====\n");
        printf("1-Cadastrar  2-Listar  3-Repor estoque  4-Registrar venda\n");
        printf("5-Consultar por codigo  6-Relatorio de estoque  0-Sair\nOpcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3:
                printf("Codigo: "); scanf("%d", &c);
                i = buscar(c);
                if (i == -1) { puts("Produto nao encontrado."); break; }
                printf("Quantidade a repor: "); scanf("%d", &q);
                if (q > 0) { reporEstoque(&prod[i], q); puts("Estoque atualizado."); }
                else puts("Quantidade invalida.");
                break;
            case 4:
                printf("Codigo: "); scanf("%d", &c);
                i = buscar(c);
                if (i == -1) { puts("Produto nao encontrado."); break; }
                printf("Quantidade vendida: "); scanf("%d", &q);
                if (venderProduto(&prod[i], q))
                    printf("Venda registrada. Total: R$ %.2f\n", q * prod[i].preco);
                else
                    printf("Venda invalida! Disponivel: %d\n", prod[i].estoque);
                break;
            case 5: consultar(); break;
            case 6: relatorio(); break;
            case 0: puts("Encerrando..."); break;
            default: puts("Opcao invalida.");
        }
    } while (op != 0);
    return 0;
}
