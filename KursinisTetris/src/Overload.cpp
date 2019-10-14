#include "Overload.h"

Overload::Overload(int r, int i)
{
real = r; imag = i;
}

Overload Overload::operator+ (const Overload& c) const{
 Overload result;
      result.real = (this->real + c.real);
      result.imag = (this->imag + c.imag);
      return result;
}
