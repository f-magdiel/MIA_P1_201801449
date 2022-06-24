#ifndef MIA_P1_201801449_MOUNT_H
#define MIA_P1_201801449_MOUNT_H
#include "../Estructuras/DISCO.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;
//funciones
void analisisMount(char[]);
bool validacionPathMount(char []);
void montajeMount(char[],char[]);
void agregarParticionMount(char _path[],char _name[],int size,char _type, char _fit[],int _start,int _next);
void elimininarParticionMount(char _path[],char _name[]);
void showMount();
void desmontarMount(char []);
void repMbr(char [],char [],char[],char[]);
void repDisk(char [],char [],char [],char []);
string crearPathCopia(char[]);
string soloDirectorio(string);
string soloNombre(string);
int comprobarEspacios(string);
void paraRaidPath(char []);

//para el mkfs
DISCO buscarDisco(char []);



#endif //MIA_P1_201801449_MOUNT_H
