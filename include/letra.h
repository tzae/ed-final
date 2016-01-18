#ifndef __Letra_h__
#define __Letra_h__

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct letra{
  char l; ///<< Caracter de la letra
  int n; ///<< Cantidad de veces que puede aparecer
  int puntos; ///<< Puntuación de la letra

  letra():l('\0'),n(0),puntos(-1){}
  letra(char let, int cant, int p):l(let),n(cant),puntos(p){}

  bool operator<(const letra& otra) const {
    return l < otra.l;
  }

  bool operator>(const letra& otra) const {
    return l > otra.l;
  }

  bool operator==(const letra& otra) const {
    return l == otra.l;
  }
  bool operator!=(const letra& otra) const {
    return l != otra.l;
  }
};

class Conjunto_Letras{
  vector<letra> letras;

public:
  typedef vector<letra>::iterator iterator;
  typedef vector<letra>::const_iterator const_iterator;

  const_iterator begin() const { return letras.begin(); }
  const_iterator end() const { return letras.end(); }
  iterator begin() { return letras.begin(); }
  iterator end() { return letras.end(); }

  /**
  * @brief Obtiene el iterador a una letra o donde debería insertarse
  */
  iterator Encuentra(char c);

  /**
  * @brief Obtiene el iterador constante a una letra o donde debería insertarse
  */
  const_iterator Encuentra(char c) const;

  /**
  * @brief Operador de lectura
  */
  friend istream & operator>>(istream & is, Conjunto_Letras & C);

  /**
  * @brief Operador de escritura
  */
  friend ostream & operator<<(ostream & os, const Conjunto_Letras & C);

  /**
  * @brief Añade una letra al conjunto
  */
  void Add(char l, int n, int puntos);

  /**
  * @brief Obtiene la puntuación de una palabra
  * @pre La palabra es correcta
  */
  unsigned Puntuacion(string palabra) const;
};

class Bolsa_Letras{
  vector<letra> letras;
public:
  typedef vector<letra>::iterator iterator;
  typedef vector<letra>::const_iterator const_iterator;

  const_iterator begin() const { return letras.begin(); }
  const_iterator end() const { return letras.end(); }
  iterator begin() { return letras.begin(); }
  iterator end() { return letras.end(); }
  /**
  * @brief Constructor por defecto
  */
  Bolsa_Letras(){}

  /**
  * @brief Construye una bolsa de tamaño tam a partir de c
  */
  Bolsa_Letras(Conjunto_Letras &c, int tam);

  /**
  * @brief Indica si una palabra puede formarse con las letras de la bolsa
  */
  bool Correcta(string palabra) const;
};

#include "letra.cpp"

#endif
