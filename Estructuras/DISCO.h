#ifndef MIA_P1_201801449_DISCO_H
#define MIA_P1_201801449_DISCO_H

#include <iostream>
#include <ctime>
//estructuras
typedef struct EBRS{
    char part_fit[3];
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
    char id[10];

}EBRS;

typedef struct PART{
    char part_status;
    char part_type;
    char part_fit[3];
    int part_start;
    int part_size;
    char part_name[16];
    char id[10];
    char formato[10];
}PART;

typedef struct DISCO{
    int mbr_tamano;
    time_t  mbr_fecha_creacion;
    int mbr_disk_signature;
    PART mbr_particion[4];
    EBRS ebr_logicas[24];
    char letra;
    char path[100];
    int numeral;//asignar numero al disco apra ir agregando al mount dba1->> este numm
}DISCO;

#endif //MIA_P1_201801449_DISCO_H
