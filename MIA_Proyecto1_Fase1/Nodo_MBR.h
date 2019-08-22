#ifndef NODO_MBR_H
#define NODO_MBR_H
#include "Nodo_Particion.h"
#include "ctime"

struct Nodo_MRB
{
    Nodo_MRB(){
        mbr_tamanio = 1024;
        mbr_fecha_creacion = time(nullptr);
        mbr_disk_signature = -1;
        disk_fit = 'b';
        mrb_particion_1 = nullptr;
        mrb_particion_2 = nullptr;
        mrb_particion_3 = nullptr;
        mrb_particion_4 = nullptr;
        cant_particiones = 0;
        logica = false;
    }

    int mbr_tamanio;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    char disk_fit;
    int cant_particiones;
    bool logica;
    Nodo_Particion *mrb_particion_1;
    Nodo_Particion *mrb_particion_2;
    Nodo_Particion *mrb_particion_3;
    Nodo_Particion *mrb_particion_4;


};


#endif // NODO_MBR_H