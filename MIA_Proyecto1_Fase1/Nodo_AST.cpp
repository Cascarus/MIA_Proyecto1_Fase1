#include "Nodo_AST.h"

Nodo_AST::Nodo_AST(int linea, int columna, QString valor){
    this->line = linea;
    this->column = columna;
    this->value = valor;
}

void Nodo_AST::add(Nodo_AST nodo){
    this->hijos.append(nodo);
}