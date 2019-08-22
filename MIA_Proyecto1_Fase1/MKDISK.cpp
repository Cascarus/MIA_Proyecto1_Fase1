#include "MKDISK.h"

MKDISK::MKDISK(int size, char fit, char unit, QString path)
{
    this->size = size;
    this->fit = fit;
    this->unit = unit;
    this->path = path;
    //this->pathDisco = "";
    this->pathRAID = "";
}

void MKDISK::Ejecutar(){

    Nodo_MRB Disco_nuevo;

    Verificar_Directorio(path);

    //Disco_nuevo.mbr_tamanio = size;
    Disco_nuevo.mbr_disk_signature = rand() % 100 + 1;;
    Disco_nuevo.disk_fit = fit;

    struct tm *tm;
    char fecha_hora[100];

    tm = localtime(&Disco_nuevo.mbr_fecha_creacion);
    strftime(fecha_hora,100,"%d/%m/%Y %H:%M:%S",tm);
    //cout<< fecha_hora <<endl;

    char Kb[1024];
    char Mb[1024*1024];

    ifstream correcto(path.toUtf8(),ifstream::in);

    if(!correcto){
        ofstream file(path.toUtf8(),ios::out | ios::binary);

        if(unit == 'k'){
            Disco_nuevo.mbr_tamanio = size*1024;
            for (int i=0;i<size;i++)
                file.write(reinterpret_cast<char*>(&Kb),sizeof(Kb));
        }else if(unit == 'm'){
            Disco_nuevo.mbr_tamanio = size*1024*1024;
            for (int i=0;i<size;i++)
                file.write(reinterpret_cast<char*>(&Mb),sizeof(Mb));
        }

        file.seekp(0);
        file.write(reinterpret_cast<char*>(&Disco_nuevo),sizeof(Nodo_MRB));
        file.close();

        ofstream file2(pathRAID.toUtf8(),ios::out | ios::binary);

        if(unit == 'k'){
            for (int i=0;i<size;i++)
                file2.write(reinterpret_cast<char*>(&Kb),sizeof(Kb));
        }else if(unit == 'm'){
            for (int i=0;i<size;i++)
                file2.write(reinterpret_cast<char*>(&Mb),sizeof(Mb));
        }

        file2.seekp(0);
        file2.write(reinterpret_cast<char*>(&Disco_nuevo),sizeof(Nodo_MRB));
        file2.close();

        cout<<"MENSAJE: El disco se ha creado exitosamente!"<<endl;

    }else{
        cout<<"ERROR: El disco ya existe!"<<endl;
    }
}

void MKDISK::Verificar_Directorio(QString path){
    QStringList ruta = path.split('/', QString::SkipEmptyParts);
    QString Directorio = "";

    for(int a = 0; a<ruta.count()-1; a++){
        //cout<<ruta[a].toUtf8().constData()<<" "<<endl;
        Directorio += "/" + ruta[a];
        DIR *dir = opendir(Directorio.toUtf8());

        if(!dir){
            QString comando = "mkdir " + Directorio;
            //system(comando.toUtf8().constData());
            auto result = mkdir(Directorio.toUtf8().constData(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
    }

    //cout<<"1. "<<Directorio.toUtf8().constData()<<endl;

    QStringList nombreRaid = ruta[ruta.count()-1].split(".");

    pathRAID = Directorio + "/" + nombreRaid[0] + "_ra1" + ".disk";

    //cout<<"2. "<<pathRAID.toUtf8().constData()<<endl;

    
}
