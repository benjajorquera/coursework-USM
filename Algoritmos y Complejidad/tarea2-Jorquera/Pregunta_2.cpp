//Librerías:
#include<bits/stdc++.h>
#include <algorithm>
using namespace std;

// Clase que representará el Grafo Unidireccional Simple:
class Grafo{

    long long int V; //Número de vertices
    list<long long int> *ady; //Puntero a un arreglo que contiene una lista de adyacencia
    vector<long int> tiempos; //Vector tiempos de cada actividad

public:
    Grafo(long long int V);   // Constructor

    void addDependencia(long int u,long int v); //Agregar una dependencia al Grafo

    void addTiempos(long int t); //Agregar los tiempos al vector

    int comparar(vector<long int> tp); //Compara dos elementos de un vector y retorna el máximo de ellos

    void topoSort(vector<long long int> &); //Imprime el orden de las actividades

};

Grafo::Grafo(long long int V){
    this->V = V;
    ady = new list<long long int>[V];
}

void Grafo::addDependencia(long int u,long int v){
    ady[u].push_back(v);
}

void Grafo::addTiempos(long int t){
  tiempos.push_back(t);
}

int Grafo::comparar(vector<long int> tp){
  return *max_element(tp.begin(), tp.end());
}

void Grafo::topoSort(vector<long long int> &b){

    /*Inicializamos en 0 un vector de tamaño V que contendrá los grados de cada nodo, es decir,
    la cantidad de arcos que se deben visitar antes de visit a un nodo.*/
    vector<int> grados(V, 0);

    //Llena el vector de grados
    for (long long int i=0; i<V; i++){
        list<long long int>::iterator itr;
        for (itr = ady[i].begin(); itr != ady[i].end(); itr++)
             grados[*itr]++;
    }

    //Vector que contendra los nodos candidatos a ser visitados
    vector<long int> candidatos;

    //Vector booleano de nodos visitados, inicializado en false
    vector <bool> visitados(V, false);

    //Vector para agregar el orden correcto de los nodos
    vector <int> resultado;

    //Itera por cada nodo
    for(long long int j = 0; j < V; j++){

      //Agrega el tiempo de los nodos que pueden ser visitados al vector de candidatos
      for (long long int i = 0; i < V; i++)
        if (grados[i] == 0 && visitados[i] == false) candidatos.push_back(tiempos[i]);

      //Se elige el mejor candidato (la actividad que tarda más), se visita el nodo y se limpia el vector de candidatos
      auto match = find(tiempos.begin(), tiempos.end(), comparar(candidatos));
      long int u = match - tiempos.begin();
      visitados[u] = true;
      candidatos.clear();

      //Se agrega el nodo al resultado
      resultado.push_back(u);

      //Decrece el grado de los vecinos adyacentes al nodo visitado
      list<long long int>::iterator itr;
      for (itr = ady[u].begin(); itr != ady[u].end(); itr++)
        grados[*itr]--;

    }

    //Imprime el orden topológico de las actividades con prioridad de mayor duración
    for (unsigned long int i=0; i<resultado.size(); i++)
        cout << b[resultado[i]] << " ";
    cout << endl;
}

//Driver
int main(){

  long long int n, d, k = 1;

  //Entrada de datos, con n = cantidad de vertices y d = cantidad de dependencias
  while(cin >> n >> d){
    if(k != 1) cout << "\n";
    Grafo g(n); //Se inicializa el grafo

    long int i, j, t;
    vector<long long int> a;

    for(j = 0; j < n; j++){
      cin >> i >> t;
      a.push_back(i); //Se agregan los nodos a un vector
      g.addTiempos(t); //Se agregan los tiempos al grafo
    }

    long int u, v;

    for(j = 0; j < d; j++){
      cin >> u >> v;
      auto match = find(a.begin(), a.end(), u);
      u = match - a.begin();
      auto match2 = find(a.begin(), a.end(), v);
      v = match2 - a.begin();
      g.addDependencia(u,v); //Genera las dependencias de cada nodo
    }

    g.topoSort(a);
    k++;
  }
  return 0;
}
