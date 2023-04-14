#include <stdio.h>
#include <stdlib.h>


struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next; 
};


struct HashType
{
    struct RecordType *pRecord; 
};


int hash(int x, int tableSize)
{
    
    return x % tableSize;
}


int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
       
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}


void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}


void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    
    int index = hash(record->id, tableSize);

   
    if (hashTable[index].pRecord == NULL)
    {
        
        hashTable[index].pRecord = record;
    }
    else
    {
        
        struct RecordType *currRecord = hashTable[index].pRecord;
        while (currRecord->next != NULL)
        {
            currRecord = currRecord->next;
        }
        currRecord->next = record;
    }
}


void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    int i;
    struct RecordType *record;

    printf("Hash Table:\n");
    for (i = 0; i < tableSize; i++) {
        printf("Index %d -> ", i);
        record = hashTable[i].pRecord;
        if (record == NULL) {
            printf("NULL");
        }
        else {
            while (record != NULL) {
                printf("%d, %c, %d -> ", record->id, record->name, record->order);
                record = record->next;
            }
            printf("NULL");
        }
        printf("\n");
    }
}
int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    
    int hashTableSize = 10;
    struct HashType *hashTable = (struct HashType *) calloc(hashTableSize, sizeof(struct HashType));
    if (hashTable == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(-1);
    }

   
    for (int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

   
    displayRecordsInHash(hashTable, hashTableSize);

  
    free(hashTable);
    free(pRecords);

    return 0;
}
