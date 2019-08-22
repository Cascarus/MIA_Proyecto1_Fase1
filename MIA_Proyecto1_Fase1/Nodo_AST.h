#ifndef NODO_AST_H
#define NODO_AST_H
#include <QList>
#include <QString>

class Nodo_AST
{
private:
    Nodo_AST(){
        value = "";
        line = 0;
        column = 0;
        hijos =  QList<Nodo_AST>();
    }

public:
    QString value;
    int line;
    int column;
    QList<Nodo_AST> hijos;

    Nodo_AST(int, int, QString);
    void add(Nodo_AST nodo);
};

#endif // NODO_AST_H