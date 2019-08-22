#ifndef NODO_EBR_H
#define NODO_EBR_H


struct Nodo_EBR
{
    Nodo_EBR(){
        part_status = '0';
        part_fit = 'w';
        part_start = -1;
        part_size = -1;
        part_next = -1;
        part_name[0] = 'n';
    }

    char part_status; //Indica si esta particionado o no
    char part_fit; //Indica el tipo de ajuste de la particion
    int part_start; //indica donde inicia la particion
    int part_size; //el tamanio total de la particion en bytes
    int part_next; //Byte en el que esta el proximo EBR
    char part_name [16]; //Nombre de la particion

    
};


#endif // NODO_EBR_H