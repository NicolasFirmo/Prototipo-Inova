#include <Lista.h>
#include <iostream>

namespace nic
{

/* ------------------------------| No |------------------------------ */

template <typename T>
No<T>::No() : m_Prox(this), m_Ante(this), m_Obj(nullptr) {}
template <typename T>
No<T>::No(const T &obj) : m_Prox(this), m_Ante(this), m_Obj((T *)&obj) {}
template <typename T>
No<T>::~No() {}

template <typename T>
T &No<T>::pegaObj(long ind) const
{
  if (ind > 0)
    return m_Prox->pegaObj(--ind);
  else if (ind < 0)
    return m_Ante->pegaObj(++ind);
  else
    return *m_Obj;
}

template <typename T>
void No<T>::botaObj(const T &obj, long ind)
{
  if (ind > 0)
    m_Prox->botaObj(obj, --ind);
  else if (ind < 0)
    m_Ante->botaObj(obj, ++ind);
  else
    m_Obj = (T *)&obj;
}

template <typename T>
T &No<T>::tiraObj(long ind)
{
  if (ind > 0)
    return m_Prox->tiraObj(--ind);
  else if (ind < -1)
    return m_Ante->tiraObj(++ind);
  else
  {
    m_Ante->m_Prox = m_Prox;
    m_Prox->m_Ante = m_Ante;
    T *Obj = m_Obj;
    delete this;
    return *Obj;
  }
}

template <typename T>
void No<T>::adicObjAnt(No *novo, long ind)
{
  if (ind > 0)
    m_Prox->adicObjAnt(novo, --ind);
  else if (ind <= -1)
    m_Ante->adicObjAnt(novo, ++ind);
  else
  {
    novo->m_Prox = this;
    novo->m_Ante = m_Ante;
    m_Ante->m_Prox = novo;
    m_Ante = novo;
  }
}

template <typename T>
void No<T>::adicObjDep(No *novo, long ind)
{
  if (ind > 0)
    m_Prox->adicObjDep(novo, --ind);
  else if (ind <= -1)
    m_Ante->adicObjDep(novo, ++ind);
  else
  {
    novo->m_Ante = this;
    novo->m_Prox = m_Prox;
    m_Prox->m_Ante = novo;
    m_Prox = novo;
  }
}

/* ------------------------------| Lista |------------------------------ */

template <typename T>
Lista<T>::Lista() : m_Cabeca(nullptr), m_Fase(0), m_Tam(0) {}
template <typename T>
Lista<T>::~Lista()
{
  while (m_Tam > 0)
    tira(1);
}

template <typename T>
T &Lista<T>::operator[](long ind)
{
  long indR = fazIndR(ind);

  if (m_Tam)
  {
    for (long i = 0; i < indR; i++)
      m_Cabeca = m_Cabeca->m_Prox;

    return m_Cabeca->pegaObj(0);
  }
}

template <typename T>
void Lista<T>::bota(const T &obj, long ind)
{
  long indR = fazIndR(ind);

  if (m_Tam)
  {
    for (long i = 0; i < indR; i++)
      m_Cabeca = m_Cabeca->m_Prox;

    m_Cabeca->botaObj(obj, 0);
  }
}

template <typename T>
T &Lista<T>::tira(long ind)
{
  long indR = fazIndR(ind);

  if (m_Tam)
  {
    if (m_Tam-- == 1)
    {
      No<T> *tirado = m_Cabeca;
      m_Cabeca = nullptr;
      return tirado->tiraObj(0);
    }
    else
    {
      for (long i = 0; i <= indR; i++)
        m_Cabeca = m_Cabeca->m_Prox;

      return m_Cabeca->m_Ante->tiraObj(0);
    }
  }
}

template <typename T>
void Lista<T>::adic(const T &obj, long ind)
{
  long indR = fazIndR(ind);

  No<T> *novo = new No<T>(obj);
  if (!m_Tam)
  {
    m_Cabeca = novo;
  }
  else
  {
    if (ind < 0)
      m_Cabeca->adicObjDep(novo, indR);
    else
      m_Cabeca->adicObjAnt(novo, indR);

    m_Cabeca = novo;
  }
  m_Tam++;
}

template <typename T>
long Lista<T>::fazIndR(const long &ind)
{
  long indR;
  indR = ind - m_Fase;

  while (indR < 0)
  {
    indR += m_Tam;
  }
  if (m_Tam)
    indR %= m_Tam;
  m_Fase = ind;
  return indR;
}

template <typename T>
void Lista<T>::paracada (void (*func)(T &obj))
{
  for (long i = 0; i < m_Tam; i++)
    func((*this)[i]);
}

} // namespace nic
