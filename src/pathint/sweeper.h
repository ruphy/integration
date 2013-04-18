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


#ifndef SWEEPER_H
#define SWEEPER_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/math/constants/constants.hpp>

#include "../esbase.h"

#define N 64

class Sweeper
{
public:
    Sweeper();

    void doSweep();
    float S();

    float* meanCorrelator();

    int nElements();

private:
    void reset();
    /**
     * Change (maybe?) the state of the i-th element
     */
    void changeState(int i);

    inline float deltaS(float xmin, float xi, float xplus, float b);
    inline bool acceptState(float xmin, float xi, float xplus, float b);

    float m_x[N];
    float m_xN[N];
    float m_correlator[N];
    float m_meanCorrelator[N];

    float m_M, m_W, m_A, m_Del;
    boost::random::mt19937* m_gen;

    int m_sweepsDone;
};

bool Sweeper::acceptState(float xmin, float xi, float xplus, float b)
{
    float DS = pow(boost::math::constants::e<float>(), deltaS(xmin, xi, xplus, b));
    if (DS >= 1) {
        return true;
    } else {
        boost::random::uniform_real_distribution<float> dist(0, 1);
        return DS > dist(*m_gen);
    }
}

float Sweeper::deltaS(float xmin, float xi, float xplus, float b)
{
    float U = m_M*pow(m_W, 2)*(pow(b,2) - pow(xi, 2))/2;
    float Tb = pow((b-xmin)/m_A, 2) + pow((b-xplus)/m_A, 2);
    float Ta = pow((xplus-xi)/m_A, 2) + pow((xmin-xi)/m_A, 2);
    return -m_A*(U)-m_A*m_M*(Tb-Ta)/2;
}

#endif // SWEEPER_H
