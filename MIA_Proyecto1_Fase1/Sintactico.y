%{
#include "scanner.h"//se importa el header del analisis sintactico
#include "Nodo_AST.h"
//#include "Nodo_EBR.h"
//#include "Nodo_MBR.h"
//#include "Nodo_Particion.h"
#include "qdebug.h"
#include <iostream>
#include <stdlib.h>
#include <QString>
#include <string>
#include <cstring>
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
extern Nodo_AST *raiz; // Raiz del arbol

int yyerror(const char* mens)
{

    std::cout << mens <<" "<<yytext<< std::endl;
    return 0;
}
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
%error-verbose
%locations

%union{
//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
class Nodo_AST *nodo;
//struct Nodo_MBR *NodoMbr;
}

//-------------- Terminales --------------//
%token<TEXT> tk_Size;
%token<TEXT> tk_Fit;
%token<TEXT> tk_Unit;
%token<TEXT> tk_Path;
%token<TEXT> tk_Type;
%token<TEXT> tk_Delete;
%token<TEXT> tk_Name;
%token<TEXT> tk_Add;
%token<TEXT> tk_ID;
%token<TEXT> tk_MKd;
%token<TEXT> tk_RMd;
%token<TEXT> tk_Fd;
%token<TEXT> tk_Mount;
%token<TEXT> tk_UnMount;
%token<TEXT> tk_Rep;
%token<TEXT> tk_Exec;
%token<TEXT> tk_Bf;
%token<TEXT> tk_Ff;
%token<TEXT> tk_Wf;
%token<TEXT> tk_Fast;
%token<TEXT> tk_Full;
%token<TEXT> numero;
%token<TEXT> decimal;
%token<TEXT> cadena;
%token<TEXT> id;
%token<TEXT> ruta;
%token<TEXT> mas;
%token<TEXT> menos;
%token<TEXT> por;
%token<TEXT> division;
%token<TEXT> potencia;
%token<TEXT> igual;
%token<TEXT> parentA;
%token<TEXT> parentC;
%token<TEXT> llaveA;
%token<TEXT> llaveC;
%token<TEXT> corcheA;
%token<TEXT> corcheC;
%token<TEXT> exclama;
%token<TEXT> puntoComa;
%token<TEXT> coma;
%token<TEXT> simple;

//-------------- No terimanesl --------------//
%type<nodo> INICIO;
%type<nodo> COMANDOS_T; 
%type<nodo> MKdisk;
%type<nodo> LISTA_MKD; 
%type<nodo> OPCIONES_MKD;  
%type<nodo> RMdisk; 
%type<nodo> Fdisk; 
%type<nodo> LISTA_FD;
%type<nodo> OPCIONES_FD;
%type<nodo> MOUNT;
%type<nodo> LISTA_MOUNT;
%type<nodo> OPCIONES_MOUNT;
%type<nodo> UNMOUNT;
%type<nodo> REPORTES; 
%type<nodo> LISTA_REPORTES; 
%type<nodo> OPCIONES_REPOTES;
%type<nodo> SCRIPT;
%type<nodo> VAL_NUM;
%type<nodo> OPCIONES_DELETE;
%type<nodo> OPCIONES_FIT


//-------------- Precedecia --------------//
%left mas menos
%left por division
%left potencia
%right UMINUS



//-------------- Gramatica --------------//

%start INICIO

%%
INICIO: COMANDOS_T{ raiz = $$; };

COMANDOS_T: tk_MKd MKdisk { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                            //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                            //nodo->add(*$2);
                            $$->add(*$2);
                           }
            | tk_RMd RMdisk { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                            //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                            //nodo->add(*$2);
                            $$->add(*$2);
                           }
            | tk_Fd Fdisk { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                            //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                            //nodo->add(*$2);
                            $$->add(*$2);
                           }
            | tk_Mount MOUNT { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                            //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                            //nodo->add(*$2);
                            $$->add(*$2);
                           }
            | tk_UnMount UNMOUNT { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                                   //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                                   //nodo->add(*$2);
                                   $$->add(*$2);
                                  }
            | tk_Rep REPORTES { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                                //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                                //nodo->add(*$2);
                                $$->add(*$2);
                               }
            | tk_Exec SCRIPT { $$ = new Nodo_AST(@2.first_line, @2.first_column, "INICIO");
                               //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_COMANDO");
                               //nodo->add(*$2);
                               $$->add(*$2);
                              };

MKdisk: LISTA_MKD {$$ = $1;//new Nodo_AST(@1.first_line, @1.first_column,"MKDISK");
                   //$$->add(*$1);
                  }; 

LISTA_MKD: LISTA_MKD OPCIONES_MKD{ $$=$1;
                                   //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column,"OPCIONES_MKD");
                                   //nodo->add(*$2);
                                   $$->add(*$2);
                                  }
            | OPCIONES_MKD { $$ = new Nodo_AST(@1.first_line,@1.first_column, "MKDISK");
                             //Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column, "OPCIONES_MKD");
                             //nodo->add(*$1);
                             $$->add(*$1);
                           };

OPCIONES_MKD: tk_Size igual numero { $$ = new Nodo_AST(@1.first_line, @1.first_column, "SIZE");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);
                                    }
            | tk_Fit igual OPCIONES_FIT { $$ = new Nodo_AST(@1.first_line, @1.first_column, "FIT");
                                          //Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                          $$->add(*$3);
                                        }
            | tk_Unit igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "UNIT");
                                 Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                 $$->add(*nodo);
                               }
            | tk_Path igual ruta { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                   Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                   $$->add(*nodo);
                                  }
            | tk_Path igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);
                                    };  

OPCIONES_FIT: tk_Bf {$$ = new Nodo_AST(@1.first_line, @1.first_column, $1);}
            | tk_Ff {$$ = new Nodo_AST(@1.first_line, @1.first_column, $1);}
            | tk_Wf {$$ = new Nodo_AST(@1.first_line, @1.first_column, $1);};

RMdisk: tk_Path igual ruta { $$ = new Nodo_AST(@1.first_line, @1.first_column,"RMDISK");
                             Nodo_AST *nodo1 = new Nodo_AST(@1.first_line, @1.first_column,"PATH");
                             Nodo_AST *nodo2 = new Nodo_AST(@1.first_line, @1.first_column,$3);
                             nodo1->add(*nodo2);
                             $$->add(*nodo1);
                           }
            | tk_Path igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column,"RMDISK");
                                     Nodo_AST *nodo1 = new Nodo_AST(@1.first_line, @1.first_column,"PATH");
                                     Nodo_AST *nodo2 = new Nodo_AST(@1.first_line, @1.first_column,$3);
                                     nodo1->add(*nodo2);
                                     $$->add(*nodo1);
                                   };

Fdisk: LISTA_FD { $$ = $1;/*new Nodo_AST(@1.first_line, @1.first_column,"FDISK");
                  $$->add(*$1);*/
                }; 

LISTA_FD: LISTA_FD OPCIONES_FD { $$ = $1;
                                 //Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column,"OPCIONES_FD");
                                 //nodo->add(*$2);
                                 $$->add(*$2);
                                }
            | OPCIONES_FD { $$ = new Nodo_AST(@1.first_line, @1.first_column,"FDISK"); 
                            //Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column,"OPCIONES_FD");
                            //nodo->add(*$1);
                            $$->add(*$1);
                           };

OPCIONES_FD: tk_Size igual numero { $$ = new Nodo_AST(@1.first_line, @1.first_column, "SIZE");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);
                                    }
            | tk_Unit igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "UNIT");
                                 Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                 $$->add(*nodo);
                               }
            | tk_Path igual ruta { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                   Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                   $$->add(*nodo);
                                  }
            | tk_Path igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);
                                    }
            | tk_Type igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "TYPE");
                                 Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                 $$->add(*nodo);
                                }
            | tk_Fit igual OPCIONES_FIT { $$ = new Nodo_AST(@1.first_line, @1.first_column, "FIT");
                                          //Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                          $$->add(*$3);
                                        }
            | tk_Delete igual OPCIONES_DELETE { $$ = new Nodo_AST(@1.first_line, @1.first_column, "DELETE");
                                                //Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                                $$->add(*$3);
                                               }
            | tk_Name igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column, "NAME");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);  
                                    }
            | tk_Name igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "NAME");
                                 Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                 $$->add(*nodo);  
                                }
            | tk_Add igual VAL_NUM { $$ = new Nodo_AST(@1.first_line, @1.first_column, "ADD");
                                     $$->add(*$3);
                                    };

OPCIONES_DELETE: tk_Fast { $$ = new Nodo_AST(@1.first_line, @1.first_column, $1); }
            | tk_Full { $$ = new Nodo_AST(@1.first_line, @1.first_column, $1); };

MOUNT: LISTA_MOUNT { $$ = $1;/*new Nodo_AST(@1.first_line, @1.first_column,"MOUNT");
                     $$->add(*$1);*/
                    };

LISTA_MOUNT: LISTA_MOUNT OPCIONES_MOUNT { $$=$1;
                                          //Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column, "OPCIONES_MOUNT");
                                          //nodo->add(*$2);
                                          $$->add(*$2);
                                         }
           | OPCIONES_MOUNT { $$ = new Nodo_AST(@1.first_line, @1.first_column, "MOUNT");
                              //Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column, "OPCIONES_MOUNT");
                              //nodo->add(*$1);
                              $$->add(*$1);
                             };

OPCIONES_MOUNT: tk_Path igual ruta { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);
                                    }
              | tk_Path igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                       Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                       $$->add(*nodo);
                                      }
              | tk_Name igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "NAME");
                                   Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                   $$->add(*nodo);
                                  };

UNMOUNT: tk_ID igual id { $$ = new Nodo_AST(@1.first_line,@1.first_column, "UNMOUNT");
                          Nodo_AST *nodo = new Nodo_AST(@3.first_line,@3.first_column, $3);
                          $$->add(*nodo);
                         };

REPORTES: LISTA_REPORTES { $$ = $1;/*new Nodo_AST(@1.first_line,@1.first_column, "REPORTES");
                           $$->add(*$1);*/ 
                          };

LISTA_REPORTES: REPORTES OPCIONES_REPOTES { $$ = $1; 
                                            //Nodo_AST *nodo = new Nodo_AST(@2.first_line, @2.first_column, "OPCIONES_REPOTES");
                                            //nodo->add(*$2);
                                            $$->add(*$2);
                                           }
            | OPCIONES_REPOTES { $$ = new Nodo_AST(@1.first_line, @1.first_column, "REPORTES");
                                 //Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column, "OPCIONES_REPORTES");
                                 //nodo->add(*$1);
                                 $$->add(*$1);
                                };

OPCIONES_REPOTES: tk_Name igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "NAME");
                                      Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                      $$->add(*nodo);
                                    }
            | tk_Path igual ruta { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                   Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                   $$->add(*nodo);
                                  }
            | tk_Path igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                     Nodo_AST *nodo = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     $$->add(*nodo);
                                    }
            | tk_ID igual id { $$ = new Nodo_AST(@1.first_line, @1.first_column, "ID");
                               Nodo_AST *nodo = new Nodo_AST(@1.first_line, @1.first_column, $3);
                               $$->add(*nodo);
                              };

SCRIPT: tk_Path igual ruta { $$ = new Nodo_AST(@1.first_line, @1.first_column, "SCRIPT");
                             Nodo_AST *nodo1 = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                             Nodo_AST *nodo2 = new Nodo_AST(@3.first_line, @3.first_column, $3);
                             nodo1->add(*nodo2);
                             $$->add(*nodo1);
                            }
            | tk_Path igual cadena { $$ = new Nodo_AST(@1.first_line, @1.first_column, "SCRIPT");
                                     Nodo_AST *nodo1 = new Nodo_AST(@1.first_line, @1.first_column, "PATH");
                                     Nodo_AST *nodo2 = new Nodo_AST(@3.first_line, @3.first_column, $3);
                                     nodo1->add(*nodo2);
                                     $$->add(*nodo1);
                                    };

VAL_NUM: numero { $$ = new Nodo_AST(@1.first_line,@1.first_column,"VAL_NUM");
                  Nodo_AST *nod1 = new Nodo_AST(@1.first_line,@1.first_column,$1);
                  $$-> add(*nod1);
                };
            | menos numero %prec UMINUS { $$ = new Nodo_AST(@1.first_line,@1.first_column,"VAL_NUM");
                                          //Nodo_AST *nod1 = new Nodo_AST(@1.first_line,@1.first_column,$1);
                                          QString a = $1;
                                          QString b = $2;
                                          QString c = a + b;
                                          Nodo_AST *nod2 = new Nodo_AST(@2.first_line,@2.first_column,c);
                                          //$$-> add(*nod1);
                                          $$-> add(*nod2);
                                        };


%%