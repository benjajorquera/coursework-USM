#ifndef LISTA_H
#define LISTA_H

typedef struct NodoLista{
    void *contenido;
    struct NodoLista *anterior;
    struct NodoLista *siguiente;
}nodo;

typedef struct ListaIdentificacion{
    nodo *inicio;
    nodo *fin;
    nodo *actual;
    int tamanno;
}List;


List* inicializar(List *lista);


nodo* inicializarNodo(nodo *nod, void *info);


void insertar(List *lista, nodo *nuevo);



void irInicio(List *lista);


void eliminar(List *lista);


#endif // LISTA_H