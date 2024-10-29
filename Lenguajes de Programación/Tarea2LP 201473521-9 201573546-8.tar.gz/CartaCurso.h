#ifndef CARTACURSO_H
#define CARTACURSO_H

typedef struct SCartaCurso{
    char * nombre, * descripcion;
    int ataque, defensa;
    void (*reprobar)(void *, void *); //Los parametros son la carta y el enemigo
    void (*aprobar)(void *, void *); //Los parametros son la carta y el jugador
}CartaC;


CartaC* inicializar_CartaCurso(CartaC *carta, char * n);


void reprobar(void *carta, void *sans);


void aprobar(void *carta, void *sans);


void generarmazo(List* mazo);

#endif
