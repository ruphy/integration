/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  Riccardo Iaconelli <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef ESBASE_H
#define ESBASE_H

#include <boost/multiprecision/gmp.hpp>
#include <iostream>

// typedef double real;
typedef boost::multiprecision::mpf_float_50 real;

class EsBase
{
public:
    EsBase();
    void statRun();

protected:
    void debug(real number);

    void print(real number);
    void print(real number, real number2);
    void print(real number, real number2, real number3);
    void print(real number, real number2, real number3, real number4);

    void setMinIterations(int min);
    void setMaxIterations(int max);
    void setIterations(int min, int max);

    virtual void exec(int iterations) = 0;
    void setExecType(ExecType);

    enum ExecType {
        Linear,
        Quadratic
    };
private:
    int m_minIterations;
    int m_maxIterations;
    ExecType m_execType;
};


inline void EsBase::debug(real number)
{
    std::cout << "DEBUG: " << number << std::endl;
}

inline void EsBase::print(real number)
{
    std::cout << number << std::endl;
}

inline void EsBase::print(real number, real number2)
{
    std::cout << number << ',' << number2 << std::endl;
}

inline void EsBase::print(real number, real number2, real number3)
{
    std::cout << number << ',' << number2 << ',' << number3 << std::endl;
}

inline void EsBase::print(real number, real number2, real number3, real number4)
{
    std::cout << number << ',' << number2 << ',' << number3 << ',' << number4 << std::endl;
}

#endif // ESBASE_H
