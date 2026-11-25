#include <stdio.h>
#define N 10

typedef struct {
    int matricula;
    char nome[50];
    float nota1, nota2, media;
} Aluno;

float calcularMedia(float n1, float n2) {
    return (n1 + n2) / 2.0f;
}

int main(void) {
    Aluno turma[N];
    float soma = 0, mediaGeral;
    int imaior = 0, imenor = 0, acima = 0;

    for (int i = 0; i < N; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);
        printf("Matricula: ");
        scanf("%d", &turma[i].matricula);
        printf("Nome: ");
        scanf(" %49[^\n]", turma[i].nome);
        printf("Nota 1: ");
        scanf("%f", &turma[i].nota1);
        printf("Nota 2: ");
        scanf("%f", &turma[i].nota2);
        turma[i].media = calcularMedia(turma[i].nota1, turma[i].nota2);
        soma += turma[i].media;
        if (turma[i].media > turma[imaior].media) imaior = i;
        if (turma[i].media < turma[imenor].media) imenor = i;
    }

    mediaGeral = soma / N;

    printf("\n===== SITUACAO DOS ALUNOS =====\n");
    for (int i = 0; i < N; i++) {
        printf("%d - %-20s Media: %.2f - %s\n", turma[i].matricula, turma[i].nome,
               turma[i].media, turma[i].media >= 6.0f ? "APROVADO" : "REPROVADO");
        if (turma[i].media > mediaGeral) acima++;
    }

    printf("\nMaior media: %s (%.2f)\n", turma[imaior].nome, turma[imaior].media);
    printf("Menor media: %s (%.2f)\n", turma[imenor].nome, turma[imenor].media);
    printf("Media geral da turma: %.2f\n", mediaGeral);
    printf("Alunos acima da media geral: %d\n", acima);
    return 0;
}
