#include "estado.h"
#include "transicion.h"
#include <iostream>
#include <deque>
#include <string>


int main()
{

  std::string expresion;
  int cont = 0;
  std::deque<char> regEx;
  std::deque<char> aux;
  std::vector<transicion> transiciones;
  std::vector<estado> estados;

  std::cout << "Ingrese una expresión regular" << std::endl;
  std::cin >> expresion;
  std::cout << std::endl;

  //For para llenar la cola con los datos de la expresión regular
  for (int i = 0; i < expresion.size(); i++)
  {
    char caracter = expresion[i];

    //Revisa si todas las entradas fueron validas
    if (caracter == '0' || caracter == '1' || caracter == '2' || caracter == '3' ||
      caracter == '4' || caracter == '5' || caracter == '6' || caracter == '7' ||
      caracter == '8' || caracter == '9' || caracter == '*' || caracter == '+' ||
      caracter == 'u' || caracter == '(' || caracter == ')' )
    {
      regEx.push_back(caracter);
    }
    else
    {
        std::cout << "Esa expresión regular no es valida" << std::endl;
        break;
    }
  }

  while(!regEx.empty())
  {
    aux.push_back(regEx.front());
    estado a;
    estado b;
    a.setID(cont);
    cont++;
    b.setID(cont);
    cont++;
    estados.push_back(a);
    estados.push_back(b);
    transicion t = transicion(a.getID(),b.getID(),regEx.front()-48);
    transiciones.push_back(t);
    regEx.pop_front();
  }





  return 0;
}
