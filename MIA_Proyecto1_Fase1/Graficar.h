#ifndef GRAFICAR_H
#define GRAFICAR_H
#include "Nodo_AST.h"
#include <fstream>
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>

class Graficar
{
public:
    //Graficar();
    Nodo_AST *root;
    QString Grafica;
    int contador;

    Graficar(Nodo_AST *root);
    void RecorrerAST(QString padre, Nodo_AST *hijos);
    void GenerarGrafica();
    QString getGrafica();
    QString escapar(QString texto);

};

#endif // GRAFICAR_H