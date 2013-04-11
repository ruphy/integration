/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  Riccardo Iaconelli <riccardo@kde.org>

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


#ifndef PATHINT_H
#define PATHINT_H

#include "../esbase.h"

#define N 64

class PathInt : public EsBase
{
public:
    PathInt();

protected:
    virtual void exec(int iterations);
private:
    inline real deltaS(real xmin, real xi, real xplus, real p);

    void reset();

    real m_x[N];
    real m_xN[N];

    real m_M, m_W, m_A, m_Del;
};

real PathInt::deltaS(real xmin, real xi, real xplus, real b)
{
    real U = m_M*pow(m_W, 2)*(pow(b,2) - pow(xi, 2))/2;
    real Tb = pow((b-xmin)/a, 2) + pow((b-xplus)/a, 2);
    real Ta = pow((xplus-xi)/a, 2) + pow((xmin-xi)/a, 2);
    return -m_A*(U)-a*m*(Tb-Ta)/2;
}

#endif // PATHINT_H
