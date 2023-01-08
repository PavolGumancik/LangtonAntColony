#include "server.h"
#include "klient.h"
#include "string.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    //porty od 10000 - 20000 na frios
    char * newargv[argc];
    newargv[0] = argv[0];

    for (int i = 2; i < argc; ++i) {
        newargv[i-1]=argv[1];
    }
    if (strcmp(argv[1],"server")==0){
        printf("argv1: %s \n", argv[1]);
        server(argc -1,newargv);
    }
    if(strcmp(argv[1],"client")==0){
        printf("argv 1: %s \n", argv[1]);
        klient(argc -1,newargv);
    }

    //./app server 10001
    //./app client frios2.fri.uniza.sk 10001
}