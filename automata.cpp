#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <stack>
#include <string>
#include <utility>
#include "transicion.h"

//-------------DECLARACIÓN DE VARIABLES--------//
std::vector<int> x;
std::vector<std::vector<int> > defVec(11, x);
std::string expresionRegular;
std::map<int, std::vector<std::vector<int> > > tabla;
std::stack<transicion> automatas;
int next_state = 0;

//-------------DECLARACIÓN DE FUNCIONES--------//
void polaca();
int presedencia(char op);
void con();
void uni();
void kleenstar();
void mas();
void addTransicion(char a);
void printTabla();
void analiza();
void toNFA();

//-------------MAIN--------//
int main()
{
    expresionRegular = "01*|1";
    analiza();
    std::cout << "Regular Expression: " << expresionRegular << std::endl;
    polaca();
    std::cout << "Polaca inversa: " << expresionRegular << std::endl;
    toNFA();
    printTabla();
    return 0;
}

//-------------IMPLEMENTACIÓN DE FUNCIONES--------//

void polaca()
{
    std::string input = expresionRegular;
    std::string output;
    std::stack<char> operS;
    char current;
    while (!input.empty())
    {
        current = input[0];
        input.erase(0, 1);
        switch (current)
        {
            case '*': case '+': case '|': case '&':
                while (!operS.empty() && (presedencia(operS.top()) >= presedencia(current)))
                {
                    char holder = operS.top();
                    operS.pop();
                    output += holder;
                }
                operS.push(current);
                break;

            case '(':
                operS.push(current);
                break;

            case ')':
                do
                {
                    output += operS.top();
                    operS.pop();
                } while (operS.top() != '(');
                operS.pop();

                break;

            default:
                output += current;
                break;
        }
    }
    if (!operS.empty())
    {
        while (!operS.empty())
        {
            if (!(operS.top() == '(' || operS.top() == ')'))
            {
                output += operS.top();
                operS.pop();
            }
        }
    }

    expresionRegular = output;
}

int presedencia(char op)
{
    switch (op)
    {
        case '*':
            return 4;
        case '&':
            return 3;
        case '+':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}

void con()
{
    transicion aux2 = automatas.top();
    automatas.pop();
    transicion aux1 = automatas.top();
    automatas.pop();
    tabla.find(aux1.final)->second[10].push_back(aux2.origen);
    transicion b;
    b.origen = aux1.origen;
    b.final = aux2.final;
    automatas.push(b);
}

void uni()
{
    transicion aux2 = automatas.top();
    automatas.pop();
    transicion aux1 = automatas.top();
    automatas.pop();
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.find(next_state-2)->second[10].push_back(aux1.origen);
    tabla.find(next_state-2)->second[10].push_back(aux2.origen);
    tabla.find(aux1.final)->second[10].push_back(next_state-1);
    tabla.find(aux2.final)->second[10].push_back(next_state-1);
    transicion auxX;
    auxX.origen = next_state-2;
    auxX.final = next_state -1;
    automatas.push(auxX);
}

void kleenstar()
{
    transicion aux = automatas.top();
    automatas.pop();
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.find(aux.final)->second[10].push_back(aux.origen);
    tabla.find(next_state-2)->second[10].push_back(aux.origen);
    tabla.find(next_state-2)->second[10].push_back(next_state-1);
    tabla.find(aux.final)->second[10].push_back(next_state-1);
    transicion auxX;
    auxX.origen = next_state-2;
    auxX.final = next_state -1;
    automatas.push(auxX);
}

void mas()
{
    transicion aux = automatas.top();
    automatas.pop();
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.find(aux.final)->second[10].push_back(aux.origen);
    tabla.find(next_state-2)->second[10].push_back(aux.origen);
    tabla.find(aux.final)->second[10].push_back(next_state-1);
    transicion auxX;
    auxX.origen = next_state-2;
    auxX.final = next_state -1;
    automatas.push(auxX);
}

void addTransicion(char a)
{
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.insert(std::pair<int, std::vector<std::vector<int> > >(next_state++ , defVec));
    tabla.find(next_state-2)->second[a-'0'].push_back(next_state-1);
    transicion aux;
    aux.origen = next_state-2;
    aux.final = next_state -1;
    automatas.push(aux);
}

void printTabla()
{
    std::map<int, std::vector<std::vector<int> > >::iterator it;
    for (it=tabla.begin(); it != tabla.end(); ++it)
    {
        std::cout << "q" << it->first << " => ";
        int k = 0;
        for (auto i : it->second)
        {

          std::cout << "-";
          std::cout << "|";
          for (auto j : i)
          {
              std::cout << j << ",";
          }
          std::cout << "|";

        }
        std::cout << std::endl;
    }
}

void analiza()
{
    unsigned long int tam = expresionRegular.size();
    for (int i = 0; i < tam; i++)
    {
        if (expresionRegular[i] >= '0' && expresionRegular[i] <= '9')
        {
            if (expresionRegular[i+1] >= '0' && expresionRegular[i+1] <= '9')
            {
                expresionRegular.insert(i+1, "&");
                tam++;
                i++;
            }
            else if (expresionRegular[i+1] == '(')
            {
                expresionRegular.insert(i+1, "&");
                tam++;
                i++;
            }
        }
        else if (expresionRegular[i] == '*' || expresionRegular[i] == '+')
        {
            if (expresionRegular[i+1] >= '0' && expresionRegular[i+1] <= '9')
            {
                expresionRegular.insert(i+1, "&");
                tam++;
                i++;
            }
            else if (expresionRegular[i+1] == '(')
            {
                expresionRegular.insert(i+1, "&");
                tam++;
                i++;
            }
        }
        else if (expresionRegular[i] == ')' && expresionRegular[i+1] == '(')
        {
            expresionRegular.insert(i+1, "&");
            tam++;
            i++;
        }
    }
}

void toNFA()
{
    for (int i = 0; i < expresionRegular.size(); i++)
    {
        switch (expresionRegular[i])
        {
            case '&':
                con();
                break;
            case '|':
                uni();
                break;
            case '*':
                kleenstar();
                break;
            case '+':
                mas();
                break;
            default:
                addTransicion(expresionRegular[i]);
                break;
        }
    }
}
