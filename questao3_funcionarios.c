#include <stdio.h>
#define N 8
#define HORAS_MES 160
#define ACRESCIMO_HE 0.5f
#define DESCONTO 0.10f

typedef struct {
    int codigo;
    char nome[50];
    char cargo[30];
    float salarioBase;
    float horasExtras;
} Funcionario;

float valorHora(float salarioBase) { return salarioBase / HORAS_MES; }
float valorHoraExtra(float salarioBase) { return valorHora(salarioBase) * (1 + ACRESCIMO_HE); }
float salarioBruto(Funcionario f) { return f.salarioBase + f.horasExtras * valorHoraExtra(f.salarioBase); }
float salarioLiquido(float bruto) { return bruto * (1 - DESCONTO); }

int main(void) {
    Funcionario func[N];
    float liquido[N], totalFolha = 0;
    int imaior = 0;

    for (int i = 0; i < N; i++) {
        printf("\n--- Funcionario %d ---\n", i + 1);
        printf("Codigo: "); scanf("%d", &func[i].codigo);
        printf("Nome: "); scanf(" %49[^\n]", func[i].nome);
        printf("Cargo: "); scanf(" %29[^\n]", func[i].cargo);
        printf("Salario-base: "); scanf("%f", &func[i].salarioBase);
        printf("Horas extras: "); scanf("%f", &func[i].horasExtras);
    }

    printf("\n===== FOLHA DE PAGAMENTO =====\n");
    for (int i = 0; i < N; i++) {
        float bruto = salarioBruto(func[i]);
        liquido[i] = salarioLiquido(bruto);
        totalFolha += liquido[i];
        if (liquido[i] > liquido[imaior]) imaior = i;
        printf("%d - %-15s (%s)\n   Valor hora: %.2f | Hora extra: %.2f | Bruto: %.2f | Liquido: %.2f\n",
               func[i].codigo, func[i].nome, func[i].cargo,
               valorHora(func[i].salarioBase), valorHoraExtra(func[i].salarioBase),
               bruto, liquido[i]);
    }

    printf("\nMaior salario liquido: %s (R$ %.2f)\n", func[imaior].nome, liquido[imaior]);
    printf("Custo total da folha: R$ %.2f\n", totalFolha);
    return 0;
}
