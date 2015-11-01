#include <vector>

class estado
{
public:
  int id;

  estado(){};
  estado(int i);
  int getID();
  void setID(int i);

};

estado::estado(int i)
{
  id = i;
}

int estado::getID()
{
  return id;
}

void estado::setID(int i)
{
  id = i;
}
