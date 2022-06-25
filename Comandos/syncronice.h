#ifndef MIA_P1_201801449_SYNCRONICE_H
#define MIA_P1_201801449_SYNCRONICE_H
#include <iostream>
#include <string>
#include "../Estructuras/DISCO.h"
#include "../Estructuras/INODOS.h"
#include "../Estructuras/BLOQUECARPETA.h"
#include "../Estructuras/BLOQUEARCHIVO.h"
#include "../Estructuras/APUNTADORES.h"
using namespace std;
void analisisSyncronice(char []);
void ejecutarSyncronice(DISCO *disco,char [], char[]);
string inodoJson(int indice,INODOS * inode,int tree);
string folderJson(int indice,BLOQUECARPETA *carpeta,int tree);
string archivoJson(int indice,BLOQUEARCHIVO *archivo ,int tree);
string apuntadorJson(int indice,APUNTADORES *apuntador,int tree);

#endif //MIA_P1_201801449_SYNCRONICE_H
