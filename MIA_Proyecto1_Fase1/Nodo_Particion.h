#ifndef NODO_PARTICION_H
#define NODO_PARTICION_H
//#include <String>
#include <stdlib.h>
#include <stdio.h>


struct Nodo_Particion
{
    Nodo_Particion(){
        part_status = '0';
        part_type = 'p';
        part_fit = 'w';
        part_start = -1;
        part_size = 1;
        part_name[0] = 'n';
        //String coso = "VACIO";
        //strcpy(part_name, "vacio");
    }

    char part_status; //Indica si esta particionado o no
    char part_type;  //Indica el tipo de particion
    char part_fit; //Indica el tipo de ajuste de la particion
    int part_start; //indica donde inicia la particion
    int part_size; //el tamanio total de la particion en bytes
    char part_name [16]; //Nombre de la particion

};


#endif // NODO_PARTICION_H
