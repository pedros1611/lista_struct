#include <stdio.h>
#define MAXP 15
#define MAXC 30

typedef struct { int dia, mes, ano; } Data;

typedef struct {
    int codigo;
    char nome[50];
} Paciente;

typedef struct {
    Paciente paciente;
    Data data;
    char descricao[100];
} Consulta;

Paciente pac[MAXP];
Consulta cons[MAXC];
int nPac = 0, nCons = 0;

int buscarPaciente(int codigo) {
    for (int i = 0; i < nPac; i++)
        if (pac[i].codigo == codigo) return i;
    return -1;
}

int mesmaData(Data a, Data b) {
    return a.dia == b.dia && a.mes == b.mes && a.ano == b.ano;
}

void cadastrarPaciente(void) {
    int c;
    if (nPac >= MAXP) { puts("Limite de pacientes atingido."); return; }
    printf("Codigo: "); scanf("%d", &c);
    if (buscarPaciente(c) != -1) { puts("Codigo ja cadastrado!"); return; }
    pac[nPac].codigo = c;
    printf("Nome: "); scanf(" %49[^\n]", pac[nPac].nome);
    nPac++;
    puts("Paciente cadastrado!");
}

void registrarConsulta(void) {
    int c;
    if (nCons >= MAXC) { puts("Limite de consultas atingido."); return; }
    printf("Codigo do paciente: "); scanf("%d", &c);
    int i = buscarPaciente(c);
    if (i == -1) { puts("Paciente nao encontrado."); return; }
    cons[nCons].paciente = pac[i];
    printf("Data (dd mm aaaa): ");
    scanf("%d %d %d", &cons[nCons].data.dia, &cons[nCons].data.mes, &cons[nCons].data.ano);
    printf("Descricao do atendimento: ");
    scanf(" %99[^\n]", cons[nCons].descricao);
    nCons++;
    puts("Consulta registrada!");
}

void imprimirConsulta(Consulta c) {
    printf("%02d/%02d/%04d | %d - %s | %s\n", c.data.dia, c.data.mes, c.data.ano,
           c.paciente.codigo, c.paciente.nome, c.descricao);
}

void pesquisarPorPaciente(void) {
    int c, achou = 0;
    printf("Codigo do paciente: "); scanf("%d", &c);
    for (int i = 0; i < nCons; i++)
        if (cons[i].paciente.codigo == c) { imprimirConsulta(cons[i]); achou = 1; }
    if (!achou) puts("Nenhuma consulta encontrada.");
}

void listarPorData(void) {
    Data d;
    int achou = 0;
    printf("Data (dd mm aaaa): "); scanf("%d %d %d", &d.dia, &d.mes, &d.ano);
    for (int i = 0; i < nCons; i++)
        if (mesmaData(cons[i].data, d)) { imprimirConsulta(cons[i]); achou = 1; }
    if (!achou) puts("Nenhuma consulta nessa data.");
}

void relatorio(void) {
    int maior = 0, imaior = -1;
    for (int i = 0; i < nPac; i++) {
        int total = 0;
        for (int j = 0; j < nCons; j++)
            if (cons[j].paciente.codigo == pac[i].codigo) total++;
        printf("%d - %-20s Consultas: %d\n", pac[i].codigo, pac[i].nome, total);
        if (total > maior) { maior = total; imaior = i; }
    }
    if (imaior >= 0)
        printf("\nPaciente com mais atendimentos: %s (%d)\n", pac[imaior].nome, maior);
}

int main(void) {
    int op;
    do {
        printf("\n===== CLINICA =====\n");
        printf("1-Cadastrar paciente  2-Registrar consulta  3-Consultas de um paciente\n");
        printf("4-Consultas por data  5-Consultas por paciente / maior  0-Sair\nOpcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1: cadastrarPaciente(); break;
            case 2: registrarConsulta(); break;
            case 3: pesquisarPorPaciente(); break;
            case 4: listarPorData(); break;
            case 5: relatorio(); break;
            case 0: puts("Encerrando..."); break;
            default: puts("Opcao invalida.");
        }
    } while (op != 0);
    return 0;
}
