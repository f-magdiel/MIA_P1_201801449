#ifndef MIA_P1_201801449_MKDIR_H
#define MIA_P1_201801449_MKDIR_H
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <list>
#include "../Estructuras/SUPER_BLOQUE.h"
#include "../Estructuras/INODOS.h"
#include "../Estructuras/APUNTADORES.h"
using namespace std;
static list<string>ListaCarpetas;
static bool P=false;
static int control=0;
void analisisMkdir(char []);
void ejecutarMkdir(char[], char[]);


bool createRecursivo(FILE *file,SUPER_BLOQUE *super,list<string>*Lista,int *indice);
int searchFolder(INODOS *inodeFolder,FILE *file,SUPER_BLOQUE *super,string namecarpeta);
int searchPointerS(APUNTADORES *apuntadorsimple,FILE *file,SUPER_BLOQUE *super,int *bloquesdirectos,string namecarpeta);
int searchPointerD(APUNTADORES *apuntadordoble,FILE *file,SUPER_BLOQUE *super,int *i_apuntadorsimple,string namecarpeta);
int searchPointerT(APUNTADORES *apuntadortriple,FILE *file,SUPER_BLOQUE *super,int *i_apuntadordoble,string namecarpeta);
int createFolder(FILE *file,SUPER_BLOQUE *super,int *indiceactualinodo,string namecarpeta);
int returnBlockAvailable(SUPER_BLOQUE *super,FILE *file);
int returnInodeAvailable(SUPER_BLOQUE *super,FILE *file);

int BuscarEspacio(INODOS *inode,FILE *file,SUPER_BLOQUE *super,int *indiceactualinodo,string namecarpeta);

int buscarindirectoSimple(INODOS *inode,int indicedelinodo,FILE *file,SUPER_BLOQUE *super,string namecarpeta,int *indiceactualdeinodo);
int buscarindirectoDoble(INODOS *inode,int indicedelinodo,FILE *file,SUPER_BLOQUE *super,string namecarpeta,int *indiceactualdeinodo);
int buscarindirectoTriple(INODOS *inode,int indicedelinodo,FILE *file,SUPER_BLOQUE *super,string namecarpeta,int *indiceactualdeinodo);

#endif //MIA_P1_201801449_MKDIR_H
