#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_NULL_SYMBOL 0

#define BUFFER_LEN 100
#define CURRENT_YEAR 2025

char databasePath[BUFFER_LEN] = "YOUR_PATH";

typedef struct information {
    char *name;
    int year;
} INFORMATION;

typedef struct stackElement {
    struct stackElement *previous;
    INFORMATION info;
    struct stackElement *next;
} STACK_ELEMENT;

typedef struct queueElement {
    INFORMATION info;
    struct queueElement *next;
} QUEUE_ELEMENT;

typedef enum DataSource {
    FROM_KEYBOARD = 1,
    FROM_TXT_FILE = 2
} DATASOURCE;

void inputDataFromKeyboard();
void inputDataFromFile(FILE *pFile);

void addNewElementToStack(INFORMATION *newElementInfo);
void transferElementsToQueue();
void freeQueue();

void printStackElements();
void printQueueElements();

STACK_ELEMENT *pStackBeginning;
QUEUE_ELEMENT *pQueueBeginning;

int main() {
    DATASOURCE dataSource;

    printf("How do you want to enter movies (1 - Keyboard, 2 - From .txt file): ");
    while (scanf("%d", &dataSource) != 1 || dataSource > FROM_TXT_FILE || dataSource < FROM_KEYBOARD) {
        rewind(stdin);
        printf("Please enter a valid data source: ");
    }

    if (dataSource == FROM_KEYBOARD) {
        inputDataFromKeyboard();
    } else {
        FILE *pFile = fopen(databasePath, "r");

        if (pFile == NULL) {
            printf("The database file was not found. Please try again.\n");
            return 1;
        }

        inputDataFromFile(pFile);
        fclose(pFile);
    }

    printStackElements();

    transferElementsToQueue();
    printQueueElements();

    freeQueue();

    return 0;
}

void inputDataFromKeyboard() {
    INFORMATION *newElementInfo = malloc(sizeof(INFORMATION));
    char buffer[BUFFER_LEN] = "1";
    int year;

    int isWorking = 1;

    printf("Enter movies (enter empty line to end):\n");

    while (isWorking == 1) {
        printf("\nEnter name of the movie: ");

        rewind(stdin);
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = ASCII_NULL_SYMBOL;

        if (buffer[0] == ASCII_NULL_SYMBOL) {
            isWorking = 0;
            break;
        }
        newElementInfo->name = strdup(buffer);

        printf("Enter year of the movie: ");
        while (scanf("%d", &year) != 1 || year < 0 || year > CURRENT_YEAR) {
            printf("Please enter a valid year: ");
        }
        newElementInfo->year = year;

        addNewElementToStack(newElementInfo);
    }
}

void inputDataFromFile(FILE *pFile) {
    char buffer[BUFFER_LEN];
    char name[BUFFER_LEN];
    int year;

    rewind(pFile);

    while (fgets(buffer, BUFFER_LEN, pFile) != NULL) {
        if (sscanf(buffer, "%[^|]|%d", name, &year) == 2) {
            INFORMATION *newElementInfo = malloc(sizeof(INFORMATION));

            newElementInfo->name = strdup(name);
            newElementInfo->year = year;
            addNewElementToStack(newElementInfo);

            free(newElementInfo);
        } else {
            printf("ERROR PARSING LINE: %s", buffer);
            return;
        }
    }
}

void addNewElementToStack(INFORMATION *newElementInfo) {
    STACK_ELEMENT *newElement = malloc(sizeof(STACK_ELEMENT));
    if (newElement == NULL) {
        printf("Memory allocation error");
        exit(1);
    }

    newElement->info = *newElementInfo;

    if (pStackBeginning == NULL) {
        newElement->previous = NULL;
        newElement->next = NULL;
        pStackBeginning = newElement;
    } else {
        newElement->previous = NULL;
        newElement->next = pStackBeginning;
        pStackBeginning->previous = newElement;
        pStackBeginning = newElement;
    }
}

void printStackElements() {
    STACK_ELEMENT *stackElement = pStackBeginning;
    STACK_ELEMENT *lastElement = NULL;

    if (stackElement == NULL) {
        printf("\nSTACK IS EMPTY!\n");
        return;
    }

    // Printing forwards
    printf("\nSTACK PRINTED FORWARDS:");
    while (stackElement != NULL) {
        lastElement = stackElement;
        printf("\n%s - %d", stackElement->info.name, stackElement->info.year);
        stackElement = stackElement->next;
    }

    // Printing backwards
    printf("\n\nSTACK PRINTED BACKWARDS:");
    while (lastElement != NULL) {
        printf("\n%s - %d", lastElement->info.name, lastElement->info.year);
        lastElement = lastElement->previous;
    }
}

void printQueueElements() {
    QUEUE_ELEMENT *queueElement = pQueueBeginning;

    if (queueElement == NULL) {
        printf("\nQUEUE IS EMPTY!\n");
        exit(2);
    }

    printf("\n\nQUEUE ELEMENTS (sorted by years):");

    while (queueElement != NULL) {
        printf("\n%s - %d", queueElement->info.name, queueElement->info.year);
        queueElement = queueElement->next;
    }
}

void transferElementsToQueue() {
    if (pStackBeginning == NULL) {
        printf("STACK IS EMPTY!\n");
        return;
    }

    while (pStackBeginning != NULL) {
        STACK_ELEMENT *pCurrentStackElement = pStackBeginning;
        INFORMATION info = pCurrentStackElement->info;

        pStackBeginning = pStackBeginning->next;
        if (pStackBeginning != NULL) {
            pStackBeginning->previous = NULL;
        }
        // Free previous element in stack
        free(pCurrentStackElement);

        QUEUE_ELEMENT *pNewQueueElement = malloc(sizeof(QUEUE_ELEMENT));
        if (pNewQueueElement == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        pNewQueueElement->info = info;
        pNewQueueElement->next = NULL;

        // Inserting in the queue by years
        if (pQueueBeginning == NULL || info.year > pQueueBeginning->info.year) {
            // Inserting to the start of the queue
            pNewQueueElement->next = pQueueBeginning;
            pQueueBeginning = pNewQueueElement;
        } else {
            // Inserting in the middle or end of the queue
            QUEUE_ELEMENT *pCurrentQueueElement = pQueueBeginning;
            while (pCurrentQueueElement->next != NULL && pCurrentQueueElement->next->info.year >= info.year) {
                pCurrentQueueElement = pCurrentQueueElement->next;
            }

            pNewQueueElement->next = pCurrentQueueElement->next;
            pCurrentQueueElement->next = pNewQueueElement;
        }
    }
}

void freeQueue() {
    if (pQueueBeginning == NULL) {
        printf("QUEUE IS EMPTY!");
        return;
    }

    QUEUE_ELEMENT *queueElement = pQueueBeginning;

    while (queueElement != NULL) {
        queueElement = pQueueBeginning->next;
        free(pQueueBeginning->info.name);
        free(pQueueBeginning);
        pQueueBeginning = queueElement;
    }

    printf("\n\nALL ELEMENTS FROM QUEUE ARE DELETED!\n");
}
