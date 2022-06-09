
#ifndef MIA_P1_201801449_MBR_H
#define MIA_P1_201801449_MBR_H
#include <iostream>
#include <ctime>
typedef struct PARTICION{
    char part_status;
    char part_type;
    char part_fit[3];
    int part_start;
    int part_size;
    char part_name[16];
}PARTICION;

typedef struct MBR{
    int mbr_tamano;
    time_t  mbr_fecha_creacion;
    int mbr_disk_signature;
    PARTICION mbr_particion[4];
}MBR;


#endif //MIA_P1_201801449_MBR_H
