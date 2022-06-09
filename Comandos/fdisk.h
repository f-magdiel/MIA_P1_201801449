#ifndef MIA_P1_201801449_FDISK_H
#define MIA_P1_201801449_FDISK_H

#include <iostream>
#include "../Estructuras/MBR.h"
#include "../Estructuras/EBR.h"

using namespace std;
void analsisFdisk(char[]);
bool validacionSizeParticion(char[]);
bool validacionDisco(char []);
bool validacionFit(char []);
//                   size, unit, path, type, fit, name
void crearParticion(char[],char,char[],char,char[],char[]);
int contadorPrimaria(MBR* mbr);
int contadorExtendida(MBR* mbr);
bool validacionNombrePE(MBR* mbr,char[]);
string cambioPathCopia(char[]);
int contadorLogicas(MBR*mbr,EBR *ebr,FILE*file);
bool validacionNombreLogica(MBR*mbr,EBR*ebr,FILE*file,char[]);
void deleteParticion(char[],char[],char[]);
void addParticion(char[],char,char[],char[]);

#endif //MIA_P1_201801449_FDISK_H
