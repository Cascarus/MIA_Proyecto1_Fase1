#ifndef FDISK_H
#define FDISK_H
#include <QString>
#include <QChar>
#include <stdio.h>
#include <Nodo_MBR.h>
#include <Nodo_Particion.h>
#include <Nodo_EBR.h>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <dirent.h>
#include <QStringList>

using namespace std;

class FDISK
{
public:
    int size;
    char unit;
    QString path;
    char type;
    char fit; 
    QString eliminar;
    QString name;
    int add;
    //bool elim;
    int opcion_exe;
    
    FDISK(int size, char unit, QString path, char type, char fit, QString eliminar, QString name, int add, int opcion);
    void Ejecutar();
    int asignar_size(char type);
    int buscar_primer_EBR(Nodo_MRB disco_actual);
    int Espacio_disponible(Nodo_MRB MBR_actual);
};

#endif // FDISK_H 
