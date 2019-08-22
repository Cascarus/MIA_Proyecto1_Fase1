#ifndef INTERPRETE_H
#define INTERPRETE_H
#include <Nodo_AST.h>
#include <fstream>
#include <QString>
#include <QChar>
#include <iostream>
#include <stdlib.h>
#include <MKDISK.h>
#include <RMDISK.h>
#include <FDISK.h>

class Interprete
{
private: 
    Nodo_AST *raiz;
    int size;
    QString fit;
    QChar unidad;
    QString path;
    QChar type;
    QString eliminar;
    QString name;
    int agregar;
    QString ID;
    bool ERROR;
    int opcion_fdisk;

public:
    Interprete(Nodo_AST *raiz);
    void ejecutar();
    void Recorrer_Arbol(Nodo_AST *raiz);
    //void Opcines_Comando(Nodo_AST *raiz);
    void Opciones_Parametro(Nodo_AST *raiz);
    char getFitChar(QString fit);
};

#endif // 