#include <QCoreApplication>
#include "qdebug.h"
#include "qstring.h"
#include <iostream>
#include <stdlib.h>
#include <parser.h>
#include <scanner.h>
#include <Nodo_AST.h>
#include <Graficar.h>
#include <Interprete.h>

extern int yyparse();
extern int linea;
extern int columna;
extern int yylineno;
extern Nodo_AST *raiz;

using namespace std;

int main(int argc, char *argv[])
{
    bool continuar = true;

    QCoreApplication a(argc, argv);
    cout<<"hola putos"<<endl;

    QString programa = "";
    QTextStream s(stdin);

    while (continuar)
    {
        programa = s.readLine();

        if(programa.compare("salir")!=0){
            YY_BUFFER_STATE buffer = yy_scan_string(programa.toUtf8().constData());

            linea = 0;
            columna = 0;
            yylineno = 0;

            if(yyparse()==0)
            {
                Graficar *graf = new Graficar(raiz);
                graf->GenerarGrafica();
                Interprete *interprete = new Interprete(raiz);
                interprete->ejecutar();
                //cout<< "Se completo correctamente"<<endl;
            }
        }else{
            continuar = false;
        }
    }
    
    return 0;
}
