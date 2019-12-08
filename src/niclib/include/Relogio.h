#pragma once
#include <chrono>
#include <iostream>

namespace nic
{

// nanosegundos
typedef std::chrono::duration<double, std::nano> nanosegundos;

// microsegundos
typedef std::chrono::duration<double, std::micro> microsegundos;

// milisegundos
typedef std::chrono::duration<double, std::milli> milisegundos;

// segundos
typedef std::chrono::duration<double> segundos;

// minutos
typedef std::chrono::duration<double, std::ratio<60>> minutos;

// horas
typedef std::chrono::duration<double, std::ratio<3600>> horas;

template <typename RAZ>
class Sufixo;

template <typename RAZ>
std::ostream &operator<<(std::ostream &os, const Sufixo<RAZ> &s);

template <typename RAZ>
class Sufixo
{
private:
  const char *s;

public:
  Sufixo();

  friend std::ostream &operator<<<RAZ>(std::ostream &os, const Sufixo<RAZ> &s);
};

template <typename RAZ = segundos, const unsigned char r = 0, const unsigned char g = 255, const unsigned char b = 0>
class Relogio
{
private:
  std::chrono::steady_clock::time_point t0;
  Sufixo<RAZ> s;

public:
  Relogio();
  ~Relogio();
};

} // namespace nic
