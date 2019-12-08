#pragma once

namespace nic
{
// Essa é a classe principal a qual o usuário tem acesso
template <typename T>
class Lista;

// Essa é a classe encapsulada da qual a lista se utiliza
template <typename T>
class No
{
private:
  No *m_Prox, *m_Ante;
  T *m_Obj;

  No();
  No(const T &obj);
  ~No();

  T &pegaObj(long ind) const;
  void botaObj(const T &obj, long ind);
  T &tiraObj(long ind);
  void adicObjAnt(No *novo, long ind);
  void adicObjDep(No *novo, long ind);

  friend class Lista<T>;
};

template <typename T>
class Lista
{
private:
  No<T> *m_Cabeca;
  long m_Fase;
  unsigned long m_Tam;

  long fazIndR(const long &ind);

public:
  Lista();
  ~Lista();

  // Retorna o tamanho da lista = número de elemento
  inline unsigned long tam() const { return m_Tam; }

  // Permite acessar a lista como um array
  T &operator[](long ind);

  // Bota o elemento no indice atual
  void bota(const T &obj, long ind);

  // Tira o elemento da lista retornando o seu valor
  T &tira(long ind = 0);

  // Adiciona o novo elemento entre o elemento de indice indicado e o seu anterior
  void adic(const T &obj, long ind = 0);

  void paracada(void (*func)(T &obj));
};

} // namespace nic
