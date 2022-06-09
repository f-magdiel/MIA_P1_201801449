#ifndef MIA_P1_201801449_EBR_H
#define MIA_P1_201801449_EBR_H

#include <iostream>

using namespace std;
typedef struct EBR : public error_code {
    char part_fit[3];
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}EBR;

#endif //MIA_P1_201801449_EBR_H
