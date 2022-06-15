#ifndef MIA_P1_201801449_JOURNALING_H
#define MIA_P1_201801449_JOURNALING_H
#include <ctime>

typedef struct JOURNALING{
    char jorunal_tipo_operacion[10];
    char journal_tipo;
    char journal_nombre[10];
    char journal_contenido[10];
    time_t journal_fecha;
    char journal_propietario[10];
    char journal_persimo[10];

}JOURNALING;

#endif //MIA_P1_201801449_JOURNALING_H
