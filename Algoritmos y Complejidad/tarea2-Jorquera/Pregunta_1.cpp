//Librerías:
#include <iostream>
#include <vector>
using namespace std;

/*Dada un cantidad de páginas r, un vector de libros, la cantidad de jóvenes n y la cantidad de libros k
la siguiente función asignar retorna true cuando la distribución de libros es correcta*/
bool asignar(vector<int> libros, long long int n, long long int k, int r){

  long long int suma = 0;
  int j, personas = 1;

  //Itera por cada libro
  for(j = 0; j < k; j++){
    if(suma + libros[j]>r){   //Cuando la suma de paǵinas actuales supera el valor del pivote r
      personas ++;            //Se suma un nuevo joven
      suma = libros[j];       //La variable suma se reinicia en el último valor de libros[j]
      if(personas>n)         //Mientras aún existan jovenes para asignar libros no retornará false.
        return false;
    }
    else suma += libros[j]; //Si no se alcanza el valor del pivote la suma de páginas que puede aceptar el joven aumenta.
  }
  return true; //Al recorrer todos los libros retorna true
}

//Driver
int main(){

  long long int N, K;

  //Para cada caso lee la primera entrada del Input, donde N = cantidad de jóvenes y K = cantidad de libros:
  while(cin >> N >> K){
    int i, paginas, maximo = 0;
    long long int suma_paginas = 0, x = 0;
    vector<int> v;

    /*Lee las demás entradas del Input y asigna la cantidad de páginas de cada libro a un vector,
     además guarda el máximo de páginas de los libros y la suma total de páginas*/
    for(i = 0; i < K ; ++i){
      cin >> paginas;
      if (paginas > maximo) maximo = paginas;
      suma_paginas += paginas;
      v.push_back(paginas);
    }

    /* Si el número de libros coincide con la cantidad de jóvenes retorna el máximo de páginas*/
    if(N == K) cout << maximo << "\n";
    else{

      /*Realizamos Busqueda binaria sobre el vector*/
      int minimo = 0;

      //La idea es que por cada while nos acercamos al valor óptimo de distribución de páginas asignadas a cada joven
      while(x<=suma_paginas){
        long long int pivote = (x+suma_paginas)/2; //Declaramos un pivote como cota superior

        //Si retorna True pude que la respuesta se encuentre en el pivote actual
        if(asignar(v, N, K, pivote)){
          suma_paginas = pivote-1; //Se reinicia la variable suma_paginas
          minimo = pivote;
        }

        //Si retorna False se reinicia el valor de x a partir del pivote
        else x = pivote + 1;
      }

    cout << minimo << "\n"; //Output
    }
  }
  return 0;
}
