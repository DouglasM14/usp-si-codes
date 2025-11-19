#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 32
#define MAX_LINE 128
#define NUM_PRIORITIES 5
#define NUM_CATEGORIES 2

typedef struct
{
    char priority[MAX_STRING];
    char category[MAX_STRING];
    int priorityID;
    int categoryID;
    int waitTime;
} Patient;

typedef struct
{
    int size;
    Patient *patients;
} Data;

// Funcoes que acham o id compativel de acordo com a string
int priorityID(char *string);
int categoryID(char *string);
// Funcao que reclassifica a propridade do paciente de acordo com o quanto tempo ele esta esperando
void reclassify(Data *data, int i, int priority, int time);
// Funcao que ordena todos os dados pela maior tempo de espera
int countingSortTime(Data *data, int size);
// Funcao que ordena todos os dados pela categoria do menor id para o maior
int countingSortCategory(Data *data, int size);
// Funcao que ordena todos os dados pela prioridade do menor id para o maior
int countingSortPriority(Data *data, int size);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("Parametros insuficientes\n");
        return 1;
    }

    FILE *data_csv;
    data_csv = fopen(argv[1], "r");

    if (!data_csv) {
        perror("Falha ao ler o arquivo\n");
        return 1;
    }

    Data data;
    data.size = 0;

    char bufferLine[MAX_LINE];
    char *token;
    int maxWaitTime = 1;

    while (fgets(bufferLine, sizeof(bufferLine), data_csv))
        data.size++;

    data.patients = (Patient *)malloc(data.size * sizeof(Patient));

    if (!data.patients) {
        perror("Erro ao alocar memoria");
        fclose(data_csv);
        return 1;
    }

    rewind(data_csv);

    for (int i = 0; (fgets(bufferLine, sizeof(bufferLine), data_csv)); i++) {
        bufferLine[strcspn(bufferLine, "\n")] = 0;

        token = strtok(bufferLine, ",");
        if (token != NULL) {
            strcpy(data.patients[i].priority, token);
            data.patients[i].priorityID = priorityID(data.patients[i].priority);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(data.patients[i].category, token);
            data.patients[i].categoryID = categoryID(data.patients[i].category);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            data.patients[i].waitTime = atoi(token);
            if (maxWaitTime < data.patients[i].waitTime) 
                maxWaitTime = data.patients[i].waitTime;
        }

        if (data.patients[i].priorityID != 0)
            reclassify(&data, i, data.patients[i].priorityID, data.patients[i].waitTime);
    }

    fclose(data_csv);

    if (countingSortTime(&data, maxWaitTime))
        return 1;

    if (countingSortCategory(&data, NUM_CATEGORIES))
        return 1;

    if (countingSortPriority(&data, NUM_PRIORITIES))
        return 1;

    FILE *OrdemDeAtendimentos;
    OrdemDeAtendimentos = fopen("OrdemDeAtendimentos.csv", "w");

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
    free(data.patients);
    return 0;
}

int priorityID(char *string)
{
    if (strcmp(string, "Vermelho") == 0)
        return 0;
    if (strcmp(string, "Laranja") == 0)
        return 1;
    if (strcmp(string, "Amarelo") == 0)
        return 2;
    if (strcmp(string, "Verde") == 0)
        return 3;
    if (strcmp(string, "Azul") == 0)
        return 4;
    return -1;
}

int categoryID(char *string)
{
    if (strcmp(string, "N/A") == 0)
        return 1;
    return 0;
}

void reclassify(Data *data, int i, int priority, int time)
{
    switch (priority) {
    case 1:
        if (time > 10) {
            strcpy(data->patients[i].priority, "Vermelho");
            data->patients[i].priorityID = 0;
        }
        break;
    case 2:
        if (time > 60) {
            strcpy(data->patients[i].priority, "Laranja");
            data->patients[i].priorityID = 1;
        }
        break;
    case 3:
        if (time > 120) {
            strcpy(data->patients[i].priority, "Amarelo");
            data->patients[i].priorityID = 2;
        }
        break;
    case 4:
        if (time > 240) {
            strcpy(data->patients[i].priority, "Verde");
            data->patients[i].priorityID = 3;
        }
        break;
    default:
        break;
    }
}

int countingSortTime(Data *data, int size)
{
    size++;
    int *count = (int *)malloc(size * sizeof(int));

    if (!count) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    for (int i = 0; i < size; i++)
        count[i] = 0;

    for (int i = 0; i < data->size; i++)
        count[data->patients[i].waitTime]++;

    for (int i = size - 2; i >= 0; i--)
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

int countingSortCategory(Data *data, int size)
{
    Patient *selectData = (Patient *)malloc(data->size * sizeof(Patient));

    int *indicesSelectData = (int *)malloc(data->size * sizeof(int));

    int sizeSelectData = 0;

    if (!selectData || !indicesSelectData) {
        perror("Erro ao alocar memoria para extracao");
        free(selectData);
        free(indicesSelectData);
        return 1;
    }

    for (int i = 0; i < data->size; i++) {
        if (data->patients[i].priorityID != 0 && data->patients[i].priorityID != 1) {
            selectData[sizeSelectData] = data->patients[i];
            indicesSelectData[sizeSelectData] = i;
            sizeSelectData++;
        }
    }

    if (sizeSelectData == 0) {
        free(selectData);
        free(indicesSelectData);
        return 0;
    }

    int *count = (int *)malloc(size * sizeof(int));

    if (!count) {
        perror("Erro ao alocar memoria para 'count'");
        free(selectData);
        free(indicesSelectData);
        return 1;
    }

    for (int i = 0; i < size; i++)
        count[i] = 0;

    for (int i = 0; i < sizeSelectData; i++)
        count[selectData[i].categoryID]++;

    for (int i = 1; i < size; i++)
        count[i] = count[i] + count[i - 1];

    Patient *arrayJaOrdenado = (Patient *)malloc(sizeSelectData * sizeof(Patient));
    if (!arrayJaOrdenado) {
        perror("Erro ao alocar memoria para 'arrayJaOrdenado'");
        free(selectData);
        free(indicesSelectData);
        free(count);
        return 1;
    }

    for (int i = sizeSelectData - 1; i >= 0; i--) {
        arrayJaOrdenado[count[selectData[i].categoryID] - 1] = selectData[i];
        count[selectData[i].categoryID]--;
    }

    free(selectData);
    free(count);

    for (int i = 0; i < sizeSelectData; i++)
        data->patients[indicesSelectData[i]] = arrayJaOrdenado[i];

    free(indicesSelectData);
    free(arrayJaOrdenado);

    return 0;
}

int countingSortPriority(Data *data, int size)
{
    size++;
    int *count = (int *)malloc(size * sizeof(int));

    if (!count) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    for (int i = 0; i < size; i++)
        count[i] = 0;

    for (int i = 0; i < data->size; i++)
        count[data->patients[i].priorityID]++;

    for (int i = 1; i < size; i++)
        count[i] = count[i] + count[i - 1];

    Patient *sortedData = (Patient *)malloc(data->size * sizeof(Patient));

    if (!sortedData) {
        perror("Erro ao alocar memoria");
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