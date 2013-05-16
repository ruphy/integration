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


#ifndef INTEGRALEBASE_H
#define INTEGRALEBASE_H

#include "../esbase.h"


class IntegraleBase : public EsBase
{

public:
    IntegraleBase(real a, real b);

protected:

    // smart add the partial results (basing on the magnitude)
    inline void add(real value);
    real getIntegral() const;
    void resetIntegral();

    /**
     * Ritorna il valore di x dell'intervallo i-esimo, dove
     * x_i(0) = a
     * x_i(intervalli) = b
     */
    inline real x_i(int i) const;

    /**
     * Imposta il numero di intervalli in cui suddividere la funzione
     * prima di integrarla.
     */
    void setIntervalli(int intervalli);
    real intervalli() const;

    /**
     * Larghezza dell'intervallo in cui abbiamo spezzato la funzione
     */
    inline real h() const;

    virtual void exec(int iterations) = 0;

    const real m_a, m_b;

private:
    // we're using real --> 11 bit for the exponent
    // this implies we can get 2046 different values
    // as exponent, let's create an array of this size.
#define DOUBLEEXP 2045
    real m_partialIntegral[DOUBLEEXP];

    int m_n;

    real m_l;
    int m_intervalli;
};


void IntegraleBase::add(real value)
{
    int i;
    //extracting the exponent
    real result = frexp(value , &i);

    // let's ensure we sum with same orders of magnitude
    m_partialIntegral[i + 1022] += value;
}

real IntegraleBase::x_i(int i) const
{
    return (m_a + m_l*i);
}

real IntegraleBase::h() const
{
    return m_l;
}

#endif // INGTEGRALEBASE_H
