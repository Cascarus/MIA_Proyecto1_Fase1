#include "Interprete.h"

Interprete::Interprete(Nodo_AST *raiz)
{
    this->raiz = raiz;
    this->size = -1;
    this->fit = "ff";
    this->unidad = '0';
    this->path = "";
    this->type = 'p';
    this->eliminar = "";
    this->name = "";
    this->agregar = 0;
    this->ID = "";
    this->ERROR = false;
    this->opcion_fdisk = 0;
}

void Interprete::ejecutar(){
    Recorrer_Arbol(&raiz->hijos[0]);
}

void Interprete::Recorrer_Arbol(Nodo_AST *raiz){
    QString tipo_comando = raiz->value;

    if(tipo_comando == "MKDISK"){
        int no_hijos = raiz->hijos.count();
        
        ///QString mensaje = "Antes de empezar-> size=" + QString::number(size) + " fit=" + fit + " unit=" + unidad + " path=" + path;
        //std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
        for(int a=0; a<no_hijos; a++){
            if(ERROR == true){
                break;
            }
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        if(ERROR != true){
            if(size >0 && path != ""){
                if(unidad != 'b'){
                    char MKD_unit;
                    if(unidad != '0'){
                        MKD_unit = unidad.toLatin1();
                    }else{
                        MKD_unit = 'm';
                    }
                    char MKD_fit = getFitChar(fit);
                    
                    //cout<<"lleva la unidad: "<<MKD_unit<<endl;
                    MKDISK *DiscoNuevo = new MKDISK(size,MKD_fit,MKD_unit,path);
                    DiscoNuevo->Ejecutar();
                }else{
                    cout<<"ERROR-> No puede utilizar B para crear un disco"<<endl;    
                }
            }else{
                cout<<"ERROR-> los parametros obligatorios son incorrectos"<<endl;
            }
        }
    
    }else if(tipo_comando == "RMDISK"){
        int no_hijos = raiz->hijos.count();

        for(int a=0; a<no_hijos; a++){
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        if(ERROR != true){
            if(path != ""){
                RMDISK *EliminarDisco = new RMDISK(path);
                EliminarDisco->Ejecutar();
            }else{
                cout<<"ERROR-> los parametros obligatorios son incorrectos"<<endl;
            }
        }
         
    }else if(tipo_comando == "FDISK"){
        int no_hijos = raiz->hijos.count();
        
        //QString mensaje = "Antes de empezar-> size=" + QString::number(size) + " unit=" + unidad + " path=" + path + " type=" + type + " fit=" + fit + " delete=" + eliminar + " name=" + name + " add=" + QString::number(agregar);
        //std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
        for(int a=0; a<no_hijos; a++){
            if(ERROR == true){
                break;
            }
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        if(ERROR != true){
            char MKD_unit;
                    if(unidad != '0'){
                        MKD_unit = unidad.toLatin1();
                    }else{
                        MKD_unit = 'k';
                    }
            char MKD_fit = getFitChar(fit);
            char FD_type = type.toLatin1();
            FDISK *ParticionNueva = new FDISK(size,MKD_unit,path,FD_type,MKD_fit,eliminar,name,agregar, opcion_fdisk);
            ParticionNueva->Ejecutar();
        }

        //mensaje = "Despues de de empezar-> size=" + QString::number(size) + " unit=" + unidad + " path=" + path + " type=" + type + " fit=" + fit + " delete=" + eliminar + " name=" + name + " add=" +  QString::number(agregar);
        //std::cout<<mensaje.toUtf8().constData()<<std::endl;
    
    }else if(tipo_comando == "MOUNT"){
        int no_hijos = raiz->hijos.count();
        
        QString mensaje = "Antes de empezar-> path=" + path + " name=" + name;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
        for(int a=0; a<no_hijos; a++){
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        
        mensaje = "Despues de empezar-> path=" + path + " name=" + name;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
    
    }else if(tipo_comando == "UNMOUNT"){
        int no_hijos = raiz->hijos.count();
        
        QString mensaje = "Antes de empezar-> id=" + ID;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
        ID = raiz->hijos[0].value;
        //acciones empiezan aqui
        
        mensaje = "Despues de empezar-> id=" + ID;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
    
    }else if(tipo_comando == "REPORTES"){
        int no_hijos = raiz->hijos.count();
        
        QString mensaje = "Antes de empezar-> name:" + name + " path:" + path + " id=" + ID;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
       for(int a=0; a<no_hijos; a++){
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        
        mensaje = "Despues de empezar-> name:" + name + " path:" + path + " id=" + ID;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
    }else if(tipo_comando == "REPORTES"){
        int no_hijos = raiz->hijos.count();
        
        QString mensaje = "Antes de empezar-> name:" + name + " path:" + path + " id=" + ID;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
       for(int a=0; a<no_hijos; a++){
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        
        mensaje = "Despues de de empezar-> name:" + name + " path:" + path + " id=" + ID;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
    }else if(tipo_comando == "SCRIPT"){
        int no_hijos = raiz->hijos.count();
        
        QString mensaje = "Antes de empezar-> path:" + path;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
        
       for(int a=0; a<no_hijos; a++){
            Opciones_Parametro(&raiz->hijos[a]);
        }

        //acciones empiezan aqui
        
        mensaje = "Despues de empezar-> path:" + path;
        std::cout<<mensaje.toUtf8().constData()<<std::endl;
    }

}

void Interprete::Opciones_Parametro(Nodo_AST *raiz){
    QString tipo_param = raiz->value;

    if(tipo_param == "SIZE"){
        bool convertir;
        int aux_size = raiz->hijos[0].value.toInt(&convertir,10);

        if(convertir = true && aux_size >0){
            size = aux_size;
        }else{
            ERROR = true;
            cout<<"ERROR-> El tamaño del disco es incorrecto"<<endl;
        }

    }else if(tipo_param == "FIT"){
        QString aux_fit = raiz->hijos[0].value.toLower();
        if(aux_fit == "bf" || aux_fit == "ff" || aux_fit == "wf" ){
            fit = raiz->hijos[0].value.toLower();
        }else{
            ERROR = true;
            cout<<"ERROR-> El fit es incorrecto"<<endl;
        }
        

    }else if(tipo_param == "UNIT"){
        QChar aux_unit = raiz->hijos[0].value.at(0).toLower();
        if(aux_unit == 'm' || aux_unit == 'k' || aux_unit == 'b'){
            unidad = aux_unit;
        }else{
            ERROR = true;
            cout<<"ERROR-> las unidades a utilzar son incorrectas"<<endl;
        }
    
    }else if(tipo_param == "PATH"){
        QString ruta = raiz->hijos[0].value;

        if(ruta.at(0) == QChar('"')){
            QStringList rut = ruta.split("\"", QString::SkipEmptyParts);
            QString rut2 = rut[0];

            if(rut2.at(0) == '/'){
                path = rut[0];
            }else{
                ERROR = true;
                cout<<"ERROR-> Ruta invalida!"<<endl;
            }
        }else{
            path = ruta;
        }
        
    }else if(tipo_param == "TYPE"){
        type = raiz->hijos[0].value.at(0).toLower();
    
    }else if(tipo_param == "DELETE"){
        eliminar = raiz->hijos[0].value;
        if(opcion_fdisk == 0){
            opcion_fdisk = 1;
        }
    
    }else if(tipo_param == "NAME"){
        name = raiz->hijos[0].value;
    
    }else if(tipo_param == "ADD"){
        bool convertir;
        agregar = raiz->hijos[0].hijos[0].value.toInt(&convertir,10);

        if(opcion_fdisk == 0){
            opcion_fdisk = 2;
        }
    
    }else if(tipo_param == "ID"){
        ID = raiz->hijos[0].value;
    }
    
}

char Interprete::getFitChar(QString fit){
    if(fit == "bf"){
        return 'b';
    }else if(fit == "ff"){
        return 'f';
    }else if(fit == "wf"){
        return 'w';
    }else{
        ERROR = true;
        return '0';
    }
}
