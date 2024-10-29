#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "lista.h" 
#include "CartaCurso.h"
#include "sansano.h"
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"

/******** Funcion: inicializar_CartaCurso ********************
Descripcion: incializa una carta asignandole espacios de memorias, nombre, ataque, defensa y descripción 
Parametros:
*carta CartaC
*n char
Retorno: resultado de la operacion aritmetica de la suma entero
************************************************/

CartaC* inicializar_CartaCurso(CartaC *carta, char * nom){
    carta = (CartaC *)malloc(sizeof(CartaC));
    carta->nombre = (char *)malloc(sizeof(char)*50);
    carta->descripcion = (char *)malloc(sizeof(char)*100);
    strcpy(carta->nombre,nom);
    if(strcmp(carta->nombre,"Matematicas")==0){
        carta->ataque =550;
        carta->defensa=200;
        strcpy(carta->descripcion,"\x1B[31m Ataca 550 \x1B[0m / \x1B[32m Cura 200 \x1B[0m puntos de prioridad.");
    }
    else if(strcmp(carta->nombre,"Fisica")==0){
        carta->ataque =450;
        carta->defensa=150;
        strcpy(carta->descripcion,"\x1B[31m Ataca 450 \x1B[0m / \x1B[32m Cura 150 \x1B[0m puntos de prioridad.");
    }
    else if(strcmp(carta->nombre,"LP")==0){
        carta->ataque =510;
        carta->defensa=180;
        strcpy(carta->descripcion,"\x1B[31m Ataca 510 \x1B[0m / \x1B[32m Cura 180 \x1B[0m puntos de prioridad.");
    }
    else if(strcmp(carta->nombre, "Programacion")==0){
        carta->ataque =110;
        carta->defensa=300;
        strcpy(carta->descripcion,"\x1B[31m Ataca 110 \x1B[0m / \x1B[32m Cura 300 \x1B[0m puntos de prioridad");
    }
    else if(strcmp(carta->nombre, "ED")==0){
        carta->ataque =470;
        carta->defensa=160;
        strcpy(carta->descripcion,"\x1B[31m Ataca 470 \x1B[0m / \x1B[32m Cura 160 \x1B[0m puntos de prioridad.");
    }
    else if(strcmp(carta->nombre, "EDD")==0){
        carta->ataque =430;
        carta->defensa=120;
        strcpy(carta->descripcion,"\x1B[31m Ataca 430 \x1B[0m / \x1B[32m Cura 120 \x1B[0m puntos de prioridad.");
    }
    carta->reprobar = &reprobar;
    carta->aprobar = &aprobar;
    return carta;
}

/******** Funcion: generarmazo ********************
Descripcion: funcion encargada de agregar las cartas al mazo de forma aleatorea
Parametros:
mazo List
Retorno: no retorna nada
************************************************/

void generarmazo(List*mazo){
    CartaC *carta11 = NULL, *carta12 = NULL, *carta13 = NULL;
    CartaC *carta21 = NULL, *carta22 = NULL, *carta23 = NULL, *carta24 = NULL;
    CartaC *carta31 = NULL, *carta32 = NULL;
    CartaC *carta41 = NULL, *carta42 = NULL, *carta43 = NULL, *carta44 = NULL, *carta45 = NULL, *carta46 = NULL;
    CartaC *carta5 = NULL;
    CartaC *carta61 = NULL, *carta62 = NULL, *carta63 = NULL, *carta64 = NULL;

    carta11 = inicializar_CartaCurso(carta11,"ED");
    carta12 = inicializar_CartaCurso(carta12,"ED");
    carta13 = inicializar_CartaCurso(carta13,"ED");

    carta21 = inicializar_CartaCurso(carta21,"EDD");
    carta22 = inicializar_CartaCurso(carta22,"EDD");
    carta23 = inicializar_CartaCurso(carta23,"EDD");
    carta24 = inicializar_CartaCurso(carta24,"EDD");

    carta31 = inicializar_CartaCurso(carta31,"LP");
    carta32 = inicializar_CartaCurso(carta32,"LP");

    carta41 = inicializar_CartaCurso(carta41,"Programacion");
    carta42 = inicializar_CartaCurso(carta42,"Programacion");
    carta43 = inicializar_CartaCurso(carta43,"Programacion");
    carta44 = inicializar_CartaCurso(carta44,"Programacion");
    carta45 = inicializar_CartaCurso(carta45,"Programacion");
    carta46 = inicializar_CartaCurso(carta46,"Programacion");

    carta5 = inicializar_CartaCurso(carta5,"Matematicas");

    carta61 = inicializar_CartaCurso(carta61,"Fisica");
    carta62 = inicializar_CartaCurso(carta62,"Fisica");
    carta63 = inicializar_CartaCurso(carta63,"Fisica");
    carta64 = inicializar_CartaCurso(carta64,"Fisica");
 
    CartaC* a[] = {carta11,carta21,carta31,carta41,carta5,carta61};
    int var,cmat = 0,clp = 0,cedd = 0,cfis = 0,cpro = 0,ced = 0, tamanno;
    
    while (tamanno < 20) { 

        var = rand() % 6;

        
        nodo *envase = NULL;
        if(a[var]->defensa == 200 && cmat == 0){
                envase = inicializarNodo(envase,(void *)carta5);
                insertar((List *)mazo,envase);
                cmat++;
                tamanno++;
         } 
        else if (a[var]->defensa == 180){
            if(clp == 0){
                envase = inicializarNodo(envase,(void *)carta31);
                insertar((List *)mazo,envase);
                clp++;
                tamanno++;
            }
            if(clp == 1){
                envase = inicializarNodo(envase,(void *)carta32);
                insertar((List *)mazo,envase);
                clp++;
                tamanno++;
            }
        }
        else if (a[var]->defensa == 120){
            if(cedd == 0){
                envase = inicializarNodo(envase,(void *)carta21);
                insertar((List *)mazo,envase);
                cedd++;
                tamanno++;
            }
            if(cedd == 1){
                envase = inicializarNodo(envase,(void *)carta22);
                insertar((List *)mazo,envase);
                cedd++;
                tamanno++;
            }
            if(cedd == 2){
                envase = inicializarNodo(envase,(void *)carta23);
                insertar((List *)mazo,envase);
                cedd++;
                tamanno++;
            }
            if(cedd == 3){
                envase = inicializarNodo(envase,(void *)carta24);
                insertar((List *)mazo,envase);
                cedd++;
                tamanno++;
            }
        }
        else if (a[var]->defensa == 150){
            if (cfis == 0){
                envase = inicializarNodo(envase,(void *)carta61);
                insertar((List *)mazo,envase);
                cfis++;
                tamanno++;
            }
            if (cfis == 1){
                envase = inicializarNodo(envase,(void *)carta62);
                insertar((List *)mazo,envase);
                cfis++;
                tamanno++;
            }
            if (cfis == 2){
                envase = inicializarNodo(envase,(void *)carta63);
                insertar((List *)mazo,envase);
                cfis++;
                tamanno++;
            }
            if (cfis == 3){
                envase = inicializarNodo(envase,(void *)carta64);
                insertar((List *)mazo,envase);
                cfis++;
                tamanno++;
            }
        }
        else if (a[var]->defensa == 300){
            if(cpro == 0){
                envase = inicializarNodo(envase,(void *)carta41);
                insertar((List *)mazo,envase);
                cpro++;
                tamanno++;
            }
            if(cpro == 1){
                envase = inicializarNodo(envase,(void *)carta42);
                insertar((List *)mazo,envase);
                cpro++;
                tamanno++;
            }
            if(cpro == 2){
                envase = inicializarNodo(envase,(void *)carta43);
                insertar((List *)mazo,envase);
                cpro++;
                tamanno++;
            }
            if(cpro == 3){
                envase = inicializarNodo(envase,(void *)carta44);
                insertar((List *)mazo,envase);
                cpro++;
                tamanno++;
            }
            if(cpro == 4){
                envase = inicializarNodo(envase,(void *)carta45);
                insertar((List *)mazo,envase);
                cpro++;
                tamanno++;
            }
            if(cpro == 5){
                envase = inicializarNodo(envase,(void *)carta46);
                insertar((List *)mazo,envase);
                cpro++;
                tamanno++;
            }
        }
        else if (a[var]->defensa == 160){
            if (ced == 0){
                envase = inicializarNodo(envase,(void *)carta11);
                insertar((List *)mazo,envase);
                ced++;
                tamanno++;
            }
            if (ced == 1){
                envase = inicializarNodo(envase,(void *)carta12);
                insertar((List *)mazo,envase);
                ced++;
                tamanno++;
            }
            if (ced == 2){
                envase = inicializarNodo(envase,(void *)carta13);
                insertar((List *)mazo,envase);
                ced++;
                tamanno++;
            }
        }
    }   
}

/******** Funcion: aprobar ********************
Descripcion: Funcion encargada de sumar prioridad a un jugador el valor de ataque de una carta
Parametros:
*carta void
*sans void
Retorno: resultado de la operacion aritmetica de la suma entero
************************************************/

void aprobar(void *carta, void *sans){
    CartaC* card = (CartaC *)carta;
    sansano* me = (sansano *)sans;
    me->prioridad += card->defensa;
    if (me->prioridad > 3000){
        me->prioridad = 3000;
    }

}

/******** Funcion: reprobar ********************
Descripcion: Funcion encargada de restar prioridad a un jugador el valor de ataque de una carta
Parametros:
*carta void
*sans void
Retorno: no retorna nada
************************************************/

void reprobar(void *carta, void *sans){
    CartaC* card = (CartaC *)carta;
    sansano* enemy = (sansano *)sans;
    enemy->prioridad -= card->ataque;
    if (enemy->prioridad < 0){
        enemy->prioridad = 0;
    }
    

}
