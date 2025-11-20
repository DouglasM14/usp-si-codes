#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define NUM_PRIORITIES 5
#define NUM_CATEGORIES 2

const char *PRIORITIES[] = {"Vermelho", "Laranja", "Amarelo", "Verde", "Azul"};
const int TIME_LIMITS[] = {0, 10, 60, 120, 240}; // Limites para reclassificação

typedef struct
{
    char priority[32];
    char category[32];
    int priorityID;
    int categoryID;
    int waitTime;
} Patient;

typedef struct
{
    int size;
    int maxWaitTime;
    Patient *patients;
} Data;


// Funcoes que acham o id compativel de acordo com a string
int priorityID(char *string);
int categoryID(char *string);
// Funcao que reclassifica a propridade do paciente de acordo com o quanto tempo ele esta esperando
void reclassify(Patient *p);
// Funcao que le o arquivo e escreve ele em uma variavel
int readData(Data *data, char *file);
// Funcao que ordena todos os dados pela maior tempo de espera
int countingSortTime(Data *data, int size);
// Funcao que ordena os dados que tem priorityID maior que 1 pelas categorias de menor id para a maior
int countingSortCategory(Data *data, int size);
// Funcao que ordena todos os dados pela prioridade do menor id para o maior
int countingSortPriority(Data *data, int size);
// Funcao que escreve os dados ordenados em um aquivo csv
int writeSortedData(Data data, char *string);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("Parametros insuficientes\n");
        return 1;
    }

    Data data;

    if (readData(&data, argv[1]))
        return 1;

    if (countingSortTime(&data, data.maxWaitTime))
        return 1;

    if (countingSortCategory(&data, NUM_CATEGORIES))
        return 1;

    if (countingSortPriority(&data, NUM_PRIORITIES))
        return 1;

    if (writeSortedData(data, "OrdemDeAtendimentos.csv")) 
        return 1;

    free(data.patients);
    return 0;
}

int priorityID(char *string)
{
    for (int i = 0; i < NUM_PRIORITIES; i++) {
        if (strcmp(string, PRIORITIES[i]) == 0)
            return i;
    }
    return -1;
}

int categoryID(char *string)
{
    if (strcmp(string, "N/A") == 0)
        return 1;
    return 0;
}

void reclassify(Patient *p)
{
    if(p->waitTime > TIME_LIMITS[p->priorityID]) {
        p->priorityID--;
        strcpy(p->priority, PRIORITIES[p->priorityID]);
    }
}

int readData(Data *data, char *file) {
    FILE *data_csv;
    data_csv = fopen(file, "r");

    if (!data_csv) {
        perror("Falha ao ler o arquivo\n");
        return 1;
    }
    
    char bufferLine[MAX_LINE];
    
    data->size = 0;
    data->maxWaitTime = 0;

    while (fgets(bufferLine, sizeof(bufferLine), data_csv))
        data->size++;

    data->patients = (Patient *)malloc(data->size * sizeof(Patient));

    if (!data->patients) {
        perror("Erro ao alocar memoria");
        fclose(data_csv);
        return 1;
    }

    rewind(data_csv);

    for (int i = 0; (fgets(bufferLine, sizeof(bufferLine), data_csv)); i++) {
        bufferLine[strcspn(bufferLine, "\n")] = 0;

        char *p = strtok(bufferLine, ",");
        char *c = strtok(NULL, ",");
        char *t = strtok(NULL, ",");

        if (p && c && t) {
            strcpy(data->patients[i].priority, p);
            strcpy(data->patients[i].category, c);
            data->patients[i].waitTime = atoi(t);
            
            data->patients[i].priorityID = priorityID(data->patients[i].priority);
            data->patients[i].categoryID = categoryID(data->patients[i].category);

            if (data->maxWaitTime < data->patients[i].waitTime) 
                data->maxWaitTime = data->patients[i].waitTime;

            if (data->patients[i].priorityID > 0)
                reclassify(&data->patients[i]);
        }
    }

    fclose(data_csv);
    return 0;
}

int countingSortTime(Data *data, int maxWaitTime)
{
    maxWaitTime++;
    int *count = (int *)calloc(maxWaitTime, sizeof(int));

    if (!count) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    for (int i = 0; i < data->size; i++)
        count[data->patients[i].waitTime]++;

    for (int i = maxWaitTime - 2; i >= 0; i--)
        count[i] = count[i] + count[i + 1];

    Patient *sortedData = (Patient *)malloc(data->size * sizeof(Patient));

    if (!sortedData) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    for (int i = data->size - 1; i >= 0; i--) {
        sortedData[count[data->patients[i].waitTime] - 1] = data->patients[i];
        count[data->patients[i].waitTime]--;
    }

    free(data->patients);
    data->patients = sortedData;
    free(count);

    return 0;
}

int countingSortCategory(Data *data, int quantCategories)
{
    Patient *selectData = (Patient *)malloc(data->size * sizeof(Patient));
    int *idx = (int *)malloc(data->size * sizeof(int));

    if (!selectData || !idx) {
        perror("Erro ao alocar memoria para extracao");
        free(selectData);
        free(idx);
        return 1;
    }

    int subSize = 0;

    for (int i = 0; i < data->size; i++) {
        if (data->patients[i].priorityID > 1) {
            selectData[subSize] = data->patients[i];
            idx[subSize] = i;
            subSize++;
        }
    }

    if (subSize > 0) {
        int *count = (int *)calloc(quantCategories, sizeof(int));
        Patient *sortedSubset = (Patient *)malloc(subSize * sizeof(Patient));

        if (!count || !sortedSubset) {
            perror("Erro ao alocar buffers de ordenacao'");
            free(selectData);
            free(idx);
            free(count);
            free(sortedSubset);
            return 1;
        }

        for (int i = 0; i < subSize; i++)
            count[selectData[i].categoryID]++;

        for (int i = 1; i < quantCategories; i++)
            count[i] = count[i] + count[i - 1];

        for (int i = subSize - 1; i >= 0; i--) {
            sortedSubset[count[selectData[i].categoryID] - 1] = selectData[i];
            count[selectData[i].categoryID]--;
        }

        for (int i = 0; i < subSize; i++)
            data->patients[idx[i]] = sortedSubset[i];

        free(sortedSubset);
        free(count);
    }
    
    free(selectData);
    free(idx);
    return 0;
}

int countingSortPriority(Data *data, int quantPriorities)
{
    quantPriorities++;
    int *count = (int *)calloc(quantPriorities, sizeof(int));

    if (!count) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    for (int i = 0; i < quantPriorities; i++)
        count[i] = 0;

    for (int i = 0; i < data->size; i++)
        count[data->patients[i].priorityID]++;

    for (int i = 1; i < quantPriorities; i++)
        count[i] = count[i] + count[i - 1];

    Patient *sortedData = (Patient *)malloc(data->size * sizeof(Patient));

    if (!sortedData) {
        perror("Erro ao alocar memoria");
        free(count);
        return 1;
    }

    for (int i = data->size - 1; i >= 0; i--) {
        sortedData[count[data->patients[i].priorityID] - 1] = data->patients[i];
        count[data->patients[i].priorityID]--;
    }

    free(data->patients);
    data->patients = sortedData;
    free(count);
    return 0;
}

int writeSortedData(Data data, char *string) {
    FILE *OrdemDeAtendimentos;
    OrdemDeAtendimentos = fopen(string, "w");

    if (!OrdemDeAtendimentos) {
        perror("Falha ao escrever o arquivo\n");
        return 1;
    }

    for (int i = 0; i < data.size; i++) {
        fprintf(OrdemDeAtendimentos, "%s,%s,%d\n",
                data.patients[i].priority,
                data.patients[i].category,
                data.patients[i].waitTime);
    }

    fclose(OrdemDeAtendimentos);
    return 0;
}