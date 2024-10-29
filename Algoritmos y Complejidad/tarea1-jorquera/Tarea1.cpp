#include <bits/stdc++.h> //Librerias
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool solucion(string s){ //Funcion que verifica parentesis
  int cont = 0; //Contador de parentesis
  for (unsigned int i = 0; i<s.size(); ++i){
    if(s[i] == '(') ++cont;
    if(s[i] == ')' && cont-- == 0) return false;
  }
  return cont == 0; //Retorna verdadero en el caso de que el string sea válido, comparando los caracteres del string con los parentesis
}

vector<string> removerParentesis(string l){ //Funcion que remueve parentesis
  vector<string> r; //Vector de strings que almacena los strings válidos
  unordered_map<string, int> visitado;; //Diccionario
  queue<string> q; //Cola de strings
  q.push(l); //Deja el string en cola
  ++visitado[l];
  bool encontrado = false; //Este estado cambia si se encuentra una expresion valida
  while (!q.empty()){ // Backtracking sobre la cola
    l = q.front(); //Guarda el primer elemento de la cola
    q.pop(); //Saca el primer elemento
    if (solucion(l)){
      r.push_back(l); //Si es solucion se guarda en el conjunto de soluciones
      encontrado = true;
    }
    if (encontrado) continue; //Salida
    for(unsigned int i = 0;i < l.size(); ++i){ //Recorre el string
      if(l[i] != '(' && l[i] != ')') continue; //No procesa los caracteres que no sean parentesis, saliendo del for
      string u = l.substr(0, i) + l.substr(i+1); //Guarda las combinaciones de parentesis
      if(visitado.find(u) == visitado.end()){ // Arma el conjunto de soluciones
        q.push(u);
        ++visitado[u];
      }
    }
  }
  return r; //Retorna el conjunto
}

int main(){
  std::ifstream file("bigin.txt");
  std::string str;
  while (std::getline(file, str)){ //Lee el archivo
    vector<string> j = removerParentesis(str); //Guarda la solucion de cada linea en un vector string
    for(unsigned int i=0; i<j.size(); ++i)
      std::cout << j[i] << endl; //Imprime las soluciones
  }
}
