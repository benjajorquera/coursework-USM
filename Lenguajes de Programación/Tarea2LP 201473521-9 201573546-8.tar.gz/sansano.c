#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h" 
#include "CartaCurso.h"
#include "sansano.h"

/******** Funcion: inicializar_sansano ********************
Descripcion: inicializa la estructura sansano, dándole un espacio de memoria, nombre, prioridad y mazo.
Parametros:
*sans Sansano
*n char
*m void
Retorno: una estructura de tipo sansano inicializada.
************************************************/

sansano* inicializar_sansano(sansano *sans, char * n, void * m){
    sans = (sansano *)malloc(sizeof(sansano));
    sans->prioridad = 3000;
    sans->nombre = n;
    sans->mazo = m;
    return sans;
}