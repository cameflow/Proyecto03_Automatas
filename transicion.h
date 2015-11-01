class transicion
{
public:
  int origen;
  int destino;
  int valor;

  transicion();
  transicion(int o, int d, int v);
  int getOrigen();
  int getDestino();
  int getValor();
};

transicion::transicion(int o, int d, int v)
{
  origen = o;
  destino = d;
  valor = v;
}

int transicion::getOrigen()
{
  return origen;
}

int transicion::getDestino()
{
  return destino;
}

int transicion::getValor()
{
  return valor;
}
