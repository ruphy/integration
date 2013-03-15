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


#ifndef INTEGRALEMC_H
#define INTEGRALEMC_H

#include "esbase.h"
#include <boost/random/mersenne_twister.hpp>

class IntegraleMC : public EsBase
{

public:
    IntegraleMC(double a, double b);
//     ~IntegraleMC();
private:
    double run();
    void statRun();

    // smart add the partial results (basing on the magnitude)
    void add(double value);
    double getIntegral();
    void resetIntegral();

    // we're using double --> 11 bit for the exponent
    // this implies we can get 2046 different values
    // as exponent, let's create an array of this size.
#define DOUBLEEXP 2045
    double m_partialIntegral[DOUBLEEXP];

    boost::random::mt19937* m_gen;
    const double m_a, m_b;
    int m_n;

};

#endif // INTEGRALEMC_H
