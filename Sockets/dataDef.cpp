#include "dataDef.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>

char *endMsg = ":end";
char *saveMsg = ":save";
char *fileName = "antPattern.txt";

//void data_init(DATA *data, const char* userName, const int socket) {
void data_init(DATA *data, const int socket) {
    data->socket = socket;
    data->stop = 0;
    //data->userName[USER_LENGTH] = '\0';
    //strncpy(data->userName, userName, USER_LENGTH);
    pthread_mutex_init(&data->mutex, NULL);
}

void data_destroy(DATA *data) {


    pthread_mutex_destroy(&data->mutex);
}

void data_stop(DATA *data) {
    pthread_mutex_lock(&data->mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->mutex);
}

int data_isStopped(DATA *data) {
    int stop;
    pthread_mutex_lock(&data->mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->mutex);
    return stop;
}
//toto robi server
void *data_readData(void *data) {
    DATA *pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(!data_isStopped(pdata)) {
        bzero(buffer, BUFFER_LENGTH);
        if (read(pdata->socket, buffer, BUFFER_LENGTH) > 0) {
            char *posSemi = strchr(buffer, ':');
            char *pos = strstr(posSemi + 1, endMsg);


            if (pos != NULL && pos - posSemi == 2 && *(pos + strlen(endMsg)) == '\0') {
                *(pos - 2) = '\0';
                printf("Pouzivatel ukoncil spojenie.\n", buffer);
                data_stop(pdata);
            } else if (pos != NULL && pos - posSemi == 2 && *(pos + strlen(saveMsg)) == '\0') {
                *(pos - 2) = '\0';
                printf("Pouzivatel chce ulozit obraz.\n", buffer);
                std::ofstream novySubor("serverData.txt");
                novySubor << buffer;
            } else {
                std::ofstream novySubor("serverData.txt");
                novySubor << buffer;
            }
        }
        else {
            data_stop(pdata);
        }
    }

    return NULL;
}

bool data_upload_client(DATA *data) {
    //citanie zo suboru a zapis do char
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    std::ifstream subor;
    subor.open(fileName);
    if (subor.is_open()) {
        std::string input;
        while (!subor.eof()) {
            std::string tmp;
            std::getline(subor, tmp);
            input += tmp;
        }
        snprintf(buffer, BUFFER_LENGTH, "%s" ,input.c_str());
        pthread_mutex_lock(&data->mutex);
        write(data->socket, buffer, strlen(buffer)+1);
        pthread_mutex_unlock(&data->mutex);
    } else {
        printf("Subor sa nenasiel.\n");
    }
    subor.close();
}
//toto posiela uzivatel
void *data_writeData(void *data) {
    DATA *pdata = (DATA *)data;
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';

    //pre pripad, ze chceme poslat viac dat, ako je kapacita buffra
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fd_set inputs;
    FD_ZERO(&inputs);
    struct timeval tv;
    tv.tv_usec = 0;
    while(!data_isStopped(pdata)) {
        tv.tv_sec = 1;
        FD_SET(STDIN_FILENO, &inputs);
        select(STDIN_FILENO + 1, &inputs, NULL, NULL, &tv);
        if (FD_ISSET(STDIN_FILENO, &inputs)) {

            char *textStart = buffer;
            while (fgets(textStart, BUFFER_LENGTH , stdin) != nullptr) {
                char *pos = strchr(textStart, '\n');
                if (pos != NULL) {
                    *pos = '\0';
                }
                write(pdata->socket, buffer, strlen(buffer) + 1);

                if (strstr(textStart, endMsg) == textStart && strlen(textStart) == strlen(endMsg)) {
                    printf("Koniec komunikacie.\n");
                    data_stop(pdata);
                } else if (strstr(textStart, saveMsg) == textStart && strlen(textStart) == strlen(saveMsg)) {
                    printf("Nahranie suboru.\n");
                    if (data_upload_client(pdata)) {
                        printf("Subor úspešne.\n");
                    };

                }
            }
        }
    }
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & ~O_NONBLOCK);

    return NULL;
}

void printError(char *str) {
    if (errno != 0) {
        perror(str);
    }
    else {
        fprintf(stderr, "%s\n", str);
    }
    exit(EXIT_FAILURE);
}