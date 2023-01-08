//
// Created by luka3 on 8. 1. 2023.
//

#ifndef LANGTONANTCOLONY_DATADEFSERVER_H
#define LANGTONANTCOLONY_DATADEFSERVER_H
#ifdef	__cplusplus
extern "C" {
#endif

#define USER_LENGTH 360//maximalny pocet policok
#define BUFFER_LENGTH 10
extern char *endMsg;

typedef struct data {
    char pole[USER_LENGTH + 1];
    pthread_mutex_t mutex;
    int socket;
    int stop;
} DATA;
typedef struct serverData {

} SERVERDATA;
void data_init(DATA *data, const int socket);
void data_destroy(DATA *data);
void data_stop(DATA *data);
int data_isStopped(DATA *data);
void *data_readData(void *data);
void *data_writeData(void *data);

void printError(char *str);

#ifdef	__cplusplus
}
#endif //LANGTONANTCOLONY_DATADEFSERVER_H
