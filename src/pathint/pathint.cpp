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


#include "pathint.h"

#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

PathInt::PathInt()
{
    setExecType(EsBase::Linear);
    setMaxIterations(1000); // 1000 sweeps
    setMinIterations(1);

    m_A = 1;
    m_M = 1;
    m_W = 1;
    m_Del = 3;

    reset();

    // "Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random
    // number generator", Makoto Matsumoto and Takuji Nishimura, ACM Transactions
    // on Modeling and Computer Simulation: Special Issue on Uniform Random Number
    // Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
    m_gen = new boost::random::mt19937(time(0) + getpid());
}

void PathInt::reset()
{
    for (int i = 0; i < N; i++) {
        m_x[i] = 0;
        m_xN[i] = 0;
    }
}

void PathInt::exec(int sweepN)
{
    // sweep
    for (int i = 0; i < N; i++) { // for every element in x...
        changeState(i);
    }
    for (int i = 0; i < N; i++) {
        m_x[i] = m_xN[i];
//         print(sweepN, m_x[i]);
    }

}

void PathInt::changeState(int i)
{
    boost::random::uniform_real_distribution<real> dist(0, 1);

    real xin = m_x[i] + m_Del*dist(*m_gen);

    bool accept;

    if (i == 0) {
        accept = acceptState(m_x[N-1], m_x[i], m_x[i+1], xin);
    } else if (i == N-1) {
        accept = acceptState(m_x[i-1], m_x[i], m_x[0], xin);
    } else {
        accept = acceptState(m_x[i-1], m_x[i], m_x[i+1], xin);
//         debug( deltaS(m_x[i-1], m_x[i], m_x[i+1], xin));
    }

    if (accept) {
        m_xN[i] = xin;
    } else {
//         m_xN[i] = m_x[i]; // this should be unneeded.
    }
}



