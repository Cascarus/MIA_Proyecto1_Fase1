#include "Graficar.h"

Graficar::Graficar(Nodo_AST *root)
{
    this->root = root;
    this->Grafica = "";
    this->contador = 0;
}

QString Graficar::getGrafica(){
    Grafica = "digraph G{\n";
    Grafica += "node[shape=\"box\"];";
    Grafica += "nodo0[label=\"" + root->value +"\"];\n";
    contador = 1;
    RecorrerAST("nodo0", root);
    Grafica += "}";
    return Grafica;
}

void Graficar::RecorrerAST(QString padre, Nodo_AST *hijos){
    for(int x=0; x<hijos->hijos.count(); x++){
        //Nodo_AST nodo = hijos->hijos[x];
        QString nombreHijo = "nodo" + QString::number(contador);
        Grafica += nombreHijo + "[label=\"" + escapar(hijos->hijos[x].value) + " \"];\n";
        Grafica += padre + "->" + nombreHijo + ";\n";
        contador++;
        RecorrerAST(nombreHijo,&hijos->hijos[x]);
    }
}

QString Graficar::escapar(QString texto){
    texto = texto.replace("\\","\\\\");
    texto = texto.replace("\"", "\\\"");
    return texto;
}

void Graficar::GenerarGrafica(){
    QString path = "/home/cascarus/Documentos/QT/MIA_Proyecto1_Fase1/";
    QFile file(path + "AST.dot");
    QString contenido = getGrafica();
    //QString contenido = "HOla KHe \n hace";
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << contenido;
        file.close();
    }
    QString comando = "dot -Tpng " + path + "AST.dot -o" + path + "AST.png";
    system(comando.toUtf8().constData());
}
