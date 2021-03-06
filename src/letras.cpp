// Autores: Pablo Baeyens Fernández y José Manuel Muñoz Fuentes

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>     // std::sort
#include "diccionario.h"

bool Correcta(vector<letra> disponibles, string palabra) {
  if (palabra.length() == 0)
    return true;

  for (vector<letra>::const_iterator v_it = disponibles.begin(); v_it != disponibles.end(); ++v_it)
    if (palabra.back() == (*v_it).l) {
      disponibles.erase(v_it);
      palabra.pop_back();
      return Correcta(disponibles, palabra);
    }

  return false;
}

bool Mal(const string& s, const vector<letra>& disponibles, const Diccionario& D) {
  if (s.length() > disponibles.size() || !Correcta(disponibles, s)) {
    cout << "Esa palabra no puede formarse con las letras disponibles.\n";
    return true;
  }
  if (!D.Esta(s)) {
    cout << "Esa palabra no está en el diccionario.\n";
    return true;
  }
  return false;
}

int main(int argc, char * argv[]){
  if (argc != 5) {
	 cerr << "Uso: " << argv[0] << " diccionario letras tamaño modo" << endl;
	 return 1;
  }

  string dict = argv[1], letras = argv[2], modo = argv[4];
  int tam = stoi(argv[3]);

  if(tam <= 0){
    cerr << "El tamaño debe ser un entero positivo" << endl;
    return 1;
  }

  if(modo != "L" && modo != "P"){
    cerr << "Los modos posibles son longitud (L) y puntuación (P)" << endl;
    return 1;
  }

  ifstream fd(dict), fl(letras);
  if (!fd) {
    cerr << "No se pudo cargar el diccionario" << endl;
    return 1;
  }

  if (!fl) {
    cerr << "No se pudo cargar el fichero con las letras" << endl;
    return 1;
  }

  Diccionario D;
  fd >> D;

  Conjunto_Letras cl;
  fl >> cl;
  char s_j;
  Bolsa_Letras bl(cl);
  srand(time(0));

  do{
    vector<letra> disponibles, disponibles_ordenadas;
    vector<string> sols;

    while (sols.empty()) {
      disponibles_ordenadas = disponibles = bl.MuestraAleatoria(tam);
      sort(disponibles_ordenadas.begin(), disponibles_ordenadas.end());
      sols = D.MejoresSoluciones(disponibles_ordenadas, (modo == "P" ? &cl : 0));
    }

    string s_usuario;
    cout << "Las letras son: ";
    for (vector<letra>::const_iterator it = disponibles.begin(); it != disponibles.end(); ++it)
      cout << (it != disponibles.begin()?'\t':' ') << (*it).l << " ";

    cout << "\n" << endl;

    do {
      cout << "Dime tu solución (escribe un punto '.' para rendirte): ";
      cin >> s_usuario;
    } while(s_usuario != "." && Mal(s_usuario, disponibles_ordenadas, D));

    if (s_usuario != ".")
      cout << s_usuario << " Puntuación: " << (modo == "P" ? cl.Puntuacion(s_usuario) : s_usuario.length()) << endl;

    cout << "Mis soluciones son: " << endl;

    for (vector<string>::iterator it = sols.begin(); it != sols.end(); ++it)
      cout << *it << " Puntuación: " << (modo == "P" ? cl.Puntuacion(*it) : (*it).length()) << endl;

    if (sols.size() != 0)
      cout << "Mejor solución: " << *sols.begin() << endl;

    cout << "¿Quieres seguir jugando? [S/N]: ";
    cin >> s_j;
  } while(s_j == 'S' || s_j == 's');
}
