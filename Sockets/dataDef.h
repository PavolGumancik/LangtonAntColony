//
// Created by luka3 on 6. 1. 2023.
//

#ifndef KLIENTSERVER_DATADEF_H
#define KLIENTSERVER_DATADEF_H
#include <pthread.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define USER_LENGTH 380//maximalny pocet policok + 20 znakov na nove riadky
#define BUFFER_LENGTH 300

extern char *endMsg;

typedef struct data {
    //treba urobit pole s ulozenimy subormi
    pthread_mutex_t mutex;
    int socket;
    int stop;
} DATA;

void data_init(DATA *data, const int socket);
void data_destroy(DATA *data);
void data_stop(DATA *data);
int data_isStopped(DATA *data);
void *data_readData(void *data);
void *data_writeData(void *data);
bool data_upload_client(DATA *data);

void printError(char *str);

#ifdef	__cplusplus
}
#endif
#endif //KLIENTSERVER_DATADEF_H
