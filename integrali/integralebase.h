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

#include "esbase.h"


class IntegraleBase : public EsBase
{

public:
    IntegraleBase(double a, double b);

protected:

    // smart add the partial results (basing on the magnitude)
    void add(double value);
    double getIntegral() const;
    void resetIntegral();

    /**
     * Ritorna il valore di x dell'intervallo i-esimo, dove
     * x_i(0) = a
     * x_i(intervalli) = b
     */
    double x_i(int i) const;

    /**
     * Imposta il numero di intervalli in cui suddividere la funzione
     * prima di integrarla.
     */
    void setIntervalli(int intervalli);
    double intervalli() const;

    /**
     * Larghezza dell'intervallo in cui abbiamo spezzato la funzione
     */
    double h() const;

    const double m_a, m_b;

private:
    // we're using double --> 11 bit for the exponent
    // this implies we can get 2046 different values
    // as exponent, let's create an array of this size.
#define DOUBLEEXP 2045
    double m_partialIntegral[DOUBLEEXP];

    int m_n;

    double m_l;
    int m_intervalli;
};

#endif // INGTEGRALEBASE_H
