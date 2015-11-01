#include <vector>

class estado
{
public:
  int id;

  int getID();
  void setID(int i);

};

int estado::getID()
{
  return id;
}

void estado::setID(int i)
{
  id = i;
}
