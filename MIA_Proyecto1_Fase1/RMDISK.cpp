#include "RMDISK.h"

RMDISK::RMDISK(QString path)
{
    this->path = path;
}

void RMDISK::Ejecutar(){
    ifstream correcto(path.toUtf8(), ifstream::in);

    if(correcto){
        QString comando = "rm " + path;
        system(comando.toUtf8().constData());
        cout<<"MENSAJE-> Se ha eliminado el disco exitosamente!"<<endl;
    }else{
        cout<<"ERROR-> El archivo no existe" << endl << "MENSAJE-> No se pudo ejecutar el comando"<<endl;
    }
}