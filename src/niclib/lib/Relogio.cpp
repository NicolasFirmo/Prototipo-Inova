#include <Relogio.h>

namespace nic
{

template <typename RAZ>
Sufixo<RAZ>::Sufixo() : s("s") {}
template <>
Sufixo<nanosegundos>::Sufixo() : s("ns") {}
template <>
Sufixo<microsegundos>::Sufixo() : s("us") {}
template <>
Sufixo<milisegundos>::Sufixo() : s("ms") {}
template <>
Sufixo<segundos>::Sufixo() : s("s") {}
template <>
Sufixo<minutos>::Sufixo() : s("m") {}
template <>
Sufixo<horas>::Sufixo() : s("h") {}

template <typename RAZ>
std::ostream &operator<<(std::ostream &os, const Sufixo<RAZ> &s) { os << s.s; };

template <typename RAZ, const unsigned char r, const unsigned char g, const unsigned char b>
Relogio<RAZ, r, g, b>::Relogio() : t0(std::chrono::steady_clock::now()) {}

template <typename RAZ, const unsigned char r, const unsigned char g, const unsigned char b>
Relogio<RAZ, r, g, b>::~Relogio()
{
  auto tf = std::chrono::steady_clock::now() - t0;

  std::cout << "\033[38;2;" << (const unsigned)r << ";" << (const unsigned)g << ";" << (const unsigned)b << "m";

  std::cout << "Tempo do escopo: " << std::chrono::duration_cast<RAZ>(tf).count() << this->s << '\n';

  std::cout << "\033[0m";
}

} // namespace nic