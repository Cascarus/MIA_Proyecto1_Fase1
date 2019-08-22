#ifndef RMDISK_H
#define RMDISK_H
#include <QString>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class RMDISK
{
public:
    QString path;

    RMDISK(QString path);
    void Ejecutar();
    //void Verificar_Directorio(QString path);
};

#endif // RMDISK_H
