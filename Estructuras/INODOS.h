#ifndef MIA_P1_201801449_INODOS_H
#define MIA_P1_201801449_INODOS_H
#include <ctime>

typedef struct INODOS{
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block[15];
    char i_type;
}INODOS;
#endif //MIA_P1_201801449_INODOS_H
