#ifndef OVERLOAD_H
#define OVERLOAD_H

class Overload
{
     double real,
             imag;
public:
      Overload( int real = 0., int imag = 0.); // constructor
      Overload operator+(const Overload&) const;       // operator+()
};

#endif // OVERLOAD_H
