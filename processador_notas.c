#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOTAS 10
#define MAX_NOME 50
#define ARQUIVO_ENTRADA "./DadosEntrada.csv"
#define ARQUIVO_SAIDA "SituacaoFinal.csv"

typedef struct {
    char nome[MAX_NOME];
    float notas[MAX_NOTAS];
    int num_notas;
    float media;
    char situacao[20];
} Aluno;

void lerDados(Aluno alunos[], int *num_alunos);
void calcularMedia(Aluno *aluno);
void determinarSituacao(Aluno *aluno);
void escreverSituacaoFinal(Aluno alunos[], int num_alunos);
void executarTestes();

int main() {
    Aluno alunos[MAX_ALUNOS];
    int num_alunos = 0;

    executarTestes();

    lerDados(alunos, &num_alunos);

    for (int i = 0; i < num_alunos; i++) {
        calcularMedia(&alunos[i]);
        determinarSituacao(&alunos[i]);
    }

    escreverSituacaoFinal(alunos, num_alunos);

    printf("Processamento concluído. Resultados foram salvos em %s\n", ARQUIVO_SAIDA);

    return 0;
}

void lerDados(Aluno alunos[], int *num_alunos) {
    FILE *arquivo = fopen(ARQUIVO_ENTRADA, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    while ((*num_alunos < MAX_ALUNOS) && fscanf(arquivo, "%[^,],", alunos[*num_alunos].nome) != EOF) {
        fscanf(arquivo, "%*[^,],"); // Ignorar telefone
        fscanf(arquivo, "%*[^,],"); // Ignorar curso
        alunos[*num_alunos].num_notas = 0;
        while (fscanf(arquivo, "%f,", &alunos[*num_alunos].notas[alunos[*num_alunos].num_notas]) == 1) {
            alunos[*num_alunos].num_notas++;
        }
        (*num_alunos)++;
    }

    fclose(arquivo);
}

void calcularMedia(Aluno *aluno) {
    float soma = 0.0;
    for (int i = 0; i < aluno->num_notas; i++) {
        soma += aluno->notas[i];
    }
    aluno->media = soma / aluno->num_notas;
}

void determinarSituacao(Aluno *aluno) {
    if (aluno->media >= 7.0) {
        strcpy(aluno->situacao, "APROVADO");
    } else {
        strcpy(aluno->situacao, "REPROVADO");
    }
}

void escreverSituacaoFinal(Aluno alunos[], int num_alunos) {
    FILE *arquivo = fopen(ARQUIVO_SAIDA, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        exit(1);
    }

    for (int i = 0; i < num_alunos; i++) {
        fprintf(arquivo, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    fclose(arquivo);
}


void executarTestes() {
    printf("Executando testes...\n");

    // Teste 1
    Aluno teste1;
    strcpy(teste1.nome, "João");
    teste1.notas[0] = 7.0;
    teste1.notas[1] = 7.0;
    teste1.notas[2] = 7.0;
    teste1.notas[3] = 7.0;
    teste1.num_notas = 4;
    calcularMedia(&teste1);
    determinarSituacao(&teste1);
    printf("Teste 1: %s, %.2f, %s\n", teste1.nome, teste1.media, teste1.situacao);

    // Teste 2
    Aluno teste2;
    strcpy(teste2.nome, "Maria");
    teste2.notas[0] = 3.0;
    teste2.notas[1] = 3.0;
    teste2.notas[2] = 3.0;
    teste2.notas[3] = 3.0;
    teste2.num_notas = 4;
    calcularMedia(&teste2);
    determinarSituacao(&teste2);
    printf("Teste 2: %s, %.2f, %s\n", teste2.nome, teste2.media, teste2.situacao);

    // Teste 3
    Aluno teste3;
    strcpy(teste3.nome, "José");
    teste3.notas[0] = 6.0;
    teste3.notas[1] = 7.0;
    teste3.notas[2] = 8.0;
    teste3.notas[3] = 9.0;
    teste3.num_notas = 4;
    calcularMedia(&teste3);
    determinarSituacao(&teste3);
    printf("Teste 3: %s, %.2f, %s\n", teste3.nome, teste3.media, teste3.situacao);

}