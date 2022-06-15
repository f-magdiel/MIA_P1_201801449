#ifndef MIA_P1_201801449_SUPER_BLOQUE_H
#define MIA_P1_201801449_SUPER_BLOQUE_H

#include <ctime>
#include "../Estructuras/BLOQUECARPETA.h"

typedef struct SUPER_BLOQUE{
    int s_filesystem_type;
    int s_inode_count;
    int s_block_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;

}SUPER_BLOQUE;

#endif //MIA_P1_201801449_SUPER_BLOQUE_H
