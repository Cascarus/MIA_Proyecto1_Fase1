#ifndef MKDISK_H
#define MKDISK_H
#include <QString>
#include <QChar>
#include <stdio.h>
#include <Nodo_MBR.h>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <dirent.h>
#include <QStringList>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

using namespace std;

class MKDISK
{
public:
    int size;
    char fit;
    char unit;
    QString path;
    QString pathRAID;
    //bool error;

    MKDISK(int size, char fit, char unit, QString path);
    void Ejecutar();
    void Verificar_Directorio(QString path);
};

#endif // MKDISK_H