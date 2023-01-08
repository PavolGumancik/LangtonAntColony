#include <bits/pthreadtypes.h>

typedef struct TitleBoard {

    const int numberOfAnts;
    //1 = extinction; 2 = solely survivor; 3 = add-on logic (inverse logic)
    const int collisionLogic;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond_ants;

    bool ants[20*80*80] = { 0 };
    bool change[20*80*80] = { 0 };
    char colour[80*80] = {' '};
    int antsOnTile = 0;
}TitleBoard;

//int getAntsOnTitle(Title p, int x, int y) {
//    int cnt = 0;
//    for (int i = 0; i < 20; i++)
//    {
//        if (p.ants[x*80 + y*20] == true)
//        {
//            cnt++;
//        }
//    }
//    return cnt;
//}
//
//void putAntOnTitle(Title p, int x, int y, int antID) {
//    p.ants[x * 80 + y * 20 + antID] = true;
//}
//
//void leaveAntFromTitle(Title p, int x, int y, int antID) {
//    p.ants[x * 80 + y * 20 + antID] = true;
//}
//
//void changeStateOfAntsTitle(Title p, int x, int y) {
//    for (int i = 0; i < 20; i++)
//    {
//        if (p.ants[x * 80 + y * 20] == true)
//        {
//            p.change[20 * 80 * 80] = true;
//        }
//    }
//    return cnt;
//}

