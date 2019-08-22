#include "FDISK.h"

FDISK::FDISK(int size, char unit, QString path, char type, char fit, QString eliminar, QString name, int add, int opcion)
{
    this->size = size;
    this->unit = unit;
    this->path = path;
    this->type = type;
    this->fit = fit;
    this->eliminar = eliminar;
    this->name = name;
    this->add = add;
    this->opcion_exe = opcion;

}

void FDISK::Ejecutar(){
    Nodo_MRB Disco_Actual;

    if(opcion_exe == 0){
        //CREAR PARTICION
        Nodo_Particion *Particion_nueva = new Nodo_Particion();
        bool ERROR = false;

        FILE *disco = fopen(path.toUtf8(), "rb+");

        if(disco != nullptr){
            
            fread(&Disco_Actual,sizeof(Nodo_MRB),1,disco);
            //cout<<"El tama;o del disco es "<<Disco_Actual.mbr_tamanio<<endl;
            
            Particion_nueva->part_size = asignar_size(unit);
            Particion_nueva->part_status = '1';
            Particion_nueva->part_type = type;
            Particion_nueva->part_fit = fit;
            strcpy(Particion_nueva->part_name, name.toUtf8().constData());

            if(type == 'p'){
                //Crear particion primaria si aun se puede
                int tamanio_mbr = sizeof(Nodo_MRB);
                if(Disco_Actual.mrb_particion_1 == nullptr){
                    Particion_nueva->part_start = sizeof(Nodo_MRB);
                    Disco_Actual.mrb_particion_1 = Particion_nueva;

                }else if(Disco_Actual.mrb_particion_2 == nullptr){

                    Particion_nueva->part_start = tamanio_mbr + Disco_Actual.mrb_particion_1->part_size;
                    Disco_Actual.mrb_particion_2 = Particion_nueva;

                }else if(Disco_Actual.mrb_particion_3 == nullptr){
                    Particion_nueva->part_start = tamanio_mbr + Disco_Actual.mrb_particion_1->part_size + Disco_Actual.mrb_particion_2->part_size;
                    Disco_Actual.mrb_particion_3 = Particion_nueva;

                }else if(Disco_Actual.mrb_particion_4 == nullptr){
                    Particion_nueva->part_start = tamanio_mbr + Disco_Actual.mrb_particion_1->part_size + Disco_Actual.mrb_particion_2->part_size + Disco_Actual.mrb_particion_3->part_size;
                    Disco_Actual.mrb_particion_4 = Particion_nueva;

                }else{
                    ERROR = true;
                    cout<<"ERROR-> Ya existen 4 particiones en el disco"<<endl;
                }

                if(ERROR != true){
                    fseek(disco,0,SEEK_SET);
                    fwrite(&Disco_Actual,sizeof(Nodo_MRB),1,disco);
                }

            }else if(type == 'e'){
                Nodo_EBR *EBR = new Nodo_EBR();
                Nodo_Particion *part1 = Disco_Actual.mrb_particion_1;
                Nodo_Particion *part2 = Disco_Actual.mrb_particion_2;
                Nodo_Particion *part3 = Disco_Actual.mrb_particion_3;
                Nodo_Particion *part4 = Disco_Actual.mrb_particion_4;
                int tamanio_mbr = sizeof(Nodo_MRB);

                if(Disco_Actual.logica == false){
                    if(part1 == nullptr){
                        Particion_nueva->part_start = sizeof(Nodo_MRB);
                        Disco_Actual.mrb_particion_1 = Particion_nueva;
                        EBR->part_start = Particion_nueva->part_start;
                        cout<<"el EBR comienza en......"<<EBR->part_start<<endl;
                        Disco_Actual.logica = true;

                    }else if(part2 == nullptr){
                        Particion_nueva->part_start = tamanio_mbr + part1->part_size;
                        Disco_Actual.mrb_particion_2 = Particion_nueva;
                        EBR->part_start = Particion_nueva->part_start;
                        cout<<"el EBR comienza en......"<<EBR->part_start<<endl;
                        Disco_Actual.logica = true;

                    }else if(part3 == nullptr){
                        Particion_nueva->part_start = tamanio_mbr + part1->part_size + part2->part_size;
                        Disco_Actual.mrb_particion_3 = Particion_nueva;
                        EBR->part_start = Particion_nueva->part_start;
                        cout<<"el EBR comienza en......"<<EBR->part_start<<endl;
                        Disco_Actual.logica = true;

                    }else if(part4 == nullptr){
                        Particion_nueva->part_start = tamanio_mbr + part1->part_size + part2->part_size + part3->part_size;
                        Disco_Actual.mrb_particion_4 = Particion_nueva;
                        EBR->part_start = Particion_nueva->part_start;
                        cout<<"el EBR comienza en......"<<EBR->part_start<<endl;
                        Disco_Actual.logica = true;

                    }else{
                        ERROR = true;
                        cout<<"ERROR-> Ya existen 4 particiones en el disco"<<endl;
                    }

                    if(ERROR != true){
                        fseek(disco,0,SEEK_SET);
                        fwrite(&Disco_Actual,sizeof(Nodo_MRB),1,disco);
                        fseek(disco,Particion_nueva->part_start,SEEK_SET);
                        fwrite(EBR,sizeof(Nodo_EBR),1,disco);
                    }

                }else{
                    ERROR = true;
                    cout<<"ERROR-> Ya exite una particion extendida, ya no puede crear otra"<<endl;
                }

            }else if(type == 'l'){
                if(Disco_Actual.logica == true){
                    Nodo_EBR *Nueva_logica = new Nodo_EBR();
                    Nodo_EBR EBR_Inicial;
                    int ubicacion_EBR_inicial = buscar_primer_EBR(Disco_Actual);
                    fseek(disco,ubicacion_EBR_inicial,SEEK_SET);
                    fread(&EBR_Inicial,sizeof(Nodo_EBR),1,disco);

                    Nueva_logica->part_status = '1';
                    Nueva_logica->part_fit = fit;
                    //Nueva_logica->part_start = ubicacion_EBR_inicial;
                    Nueva_logica->part_size = asignar_size(unit);
                    //Nueva_logica->next
                    strcpy(Nueva_logica->part_name, name.toUtf8().constData());

                    //Nodo_EBR anterior = new Nodo_EBR;
                    while(true){
                        Nodo_EBR *temp = &EBR_Inicial;
                        if(temp->part_next > 0){
                            ubicacion_EBR_inicial += temp->part_size;
                            fseek(disco,ubicacion_EBR_inicial,SEEK_SET);
                            fread(&EBR_Inicial,sizeof(Nodo_EBR),1,disco);
                            //cout<<"El EBR empieza en...."<<EBR_Inicial.part_name<<endl;

                        }else{
                            if(temp->part_size <1){
                                Nueva_logica->part_start = ubicacion_EBR_inicial;
                                break;
                            }else{
                                temp->part_next = 1;
                                fseek(disco,ubicacion_EBR_inicial,SEEK_SET);
                                fwrite(temp,sizeof(Nodo_EBR),1,disco);
                            }
                        }
                    }

                    if(ERROR != true){
                        fseek(disco,ubicacion_EBR_inicial,SEEK_SET);
                        fwrite(Nueva_logica,sizeof(Nodo_EBR),1,disco);


                        Nodo_EBR prueba;
                        fseek(disco,ubicacion_EBR_inicial,SEEK_SET);
                        fread(&prueba,sizeof(Nodo_EBR),1,disco);

                        cout<<"El EBR empieza en...."<<prueba.part_name<<endl;
                    }

                }else{
                    ERROR = true;
                    cout<<"ERROR-> No existe una particion extendida para agregar la logica"<<endl;
                }
            }

            //FILE *Nuevo_Disco_Actual = fopen(path.toUtf8(), "wb");
            fclose(disco);

        }

        if(type == 'p'){
            disco = fopen(path.toUtf8(), "rb+");
            fread(&Disco_Actual,sizeof(Nodo_MRB),1,disco);
            cout<<"El nombre de la particion 1 de este disco es...."<<Disco_Actual.mrb_particion_1->part_name<<endl;
            if(Disco_Actual.mrb_particion_2 != nullptr){
                cout<<"El nombre de la particion 2 de este disco es...."<<Disco_Actual.mrb_particion_2->part_name<<endl;
            }
            if(Disco_Actual.mrb_particion_3 != nullptr){
                cout<<"El nombre de la particion 3 de este disco es...."<<Disco_Actual.mrb_particion_3->part_name<<endl;
            }
            if(Disco_Actual.mrb_particion_4 != nullptr){
                cout<<"El nombre de la particion 4 de este disco es...."<<Disco_Actual.mrb_particion_4->part_name<<endl;
            }
            fclose(disco);

        }else if(type == 'e'){
            Nodo_EBR prueba;
            disco = fopen(path.toUtf8(), "rb+");
            fread(&Disco_Actual,sizeof(Nodo_MRB),1,disco);
            int mover =buscar_primer_EBR(Disco_Actual);
            fseek(disco,mover,SEEK_SET);
            fread(&prueba,sizeof(Nodo_EBR),1,disco);

            cout<<"El EBR empieza en...."<<prueba.part_name<<endl;
            fclose(disco);
        }
        

    }

}

int FDISK::asignar_size(char type){
    if(type == 'k'){
        return size*1024;
            
    }else if(type == 'm'){
        return size*1024*1024;
    }else{
        return size;
    }
}

int FDISK::buscar_primer_EBR(Nodo_MRB disco_actual){
    int tam_mbr = sizeof(Nodo_MRB);
    if(disco_actual.mrb_particion_1->part_type == 'e'){
        return tam_mbr;
    }else if(disco_actual.mrb_particion_2->part_type == 'e'){
        return tam_mbr + disco_actual.mrb_particion_1->part_size;
    }else if(disco_actual.mrb_particion_3->part_type == 'e'){
        return tam_mbr + disco_actual.mrb_particion_1->part_size + disco_actual.mrb_particion_2->part_size;
    }else if(disco_actual.mrb_particion_4->part_type == 'e'){
        return tam_mbr + disco_actual.mrb_particion_1->part_size + disco_actual.mrb_particion_2->part_size + disco_actual.mrb_particion_3->part_size;
    }else{
        return 0;
    }
}

int FDISK::Espacio_disponible(Nodo_MRB MBR_Actual){
    int espacio = MBR_Actual.mbr_tamanio;
    espacio -=  sizeof(Nodo_MRB);

    if(MBR_Actual.mrb_particion_1 != nullptr || MBR_Actual.mrb_particion_1->part_status != '0'){
        espacio -= MBR_Actual.mrb_particion_1->part_size;
    }

    if(MBR_Actual.mrb_particion_2 != nullptr || MBR_Actual.mrb_particion_2->part_status != '0'){
        espacio -= MBR_Actual.mrb_particion_2->part_size;
    }

    if(MBR_Actual.mrb_particion_3 != nullptr || MBR_Actual.mrb_particion_3->part_status != '0'){
        espacio -= MBR_Actual.mrb_particion_3->part_size;
    }

    if(MBR_Actual.mrb_particion_4 != nullptr || MBR_Actual.mrb_particion_4->part_status != '0'){
        espacio -= MBR_Actual.mrb_particion_4->part_size;
    }

    return espacio;

}
