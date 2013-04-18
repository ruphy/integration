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


#include "sweeper.h"

Sweeper::Sweeper()
{
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

    m_sweepsDone = 0;
}

void Sweeper::reset()
{
    for (int i = 0; i < N; i++) {
        m_x[i] = 0;
        m_xN[i] = 0;
        m_correlator[i] = 0;
        m_meanCorrelator[i] = 0;
    }
}

void Sweeper::doSweep()
{
    m_sweepsDone++;

    // sweep
    for (int i = 0; i < N; i++) { // for every element in x...
        changeState(i);
    }
    for (int i = 0; i < N; i++) {
        m_x[i] = m_xN[i];
    }

    // update the correlator
    for (int j = 0; j < N; j++) {

        float tempSum = 0;
        for (int i = 0; i < N; i++) {
            tempSum += m_x[i]*m_x[i+j]/64;
        }
        m_correlator[j] = tempSum;

        if (m_sweepsDone != 1) {
            m_meanCorrelator[j] *= m_sweepsDone/(m_sweepsDone-1);
        }
        m_meanCorrelator[j] += tempSum/m_sweepsDone;
    }

}

/////////////////////////////

float* Sweeper::meanCorrelator()
{
    return m_meanCorrelator;
}

int Sweeper::nElements()
{
    return N;
}

float Sweeper::S()
{
    float tempS = 0;
    for (int i = 0; i < N-1; i++) {
        tempS += m_M*pow((m_x[i+1]-m_x[i]), 2)/2 + m_A*(m_M*pow(m_W, 2)*pow(m_x[i], 2)/2);
    }
    tempS += m_M*pow((m_x[0]-m_x[N-1]), 2)/2 + m_A*(m_M*pow(m_W, 2)*pow(m_x[N-1], 2))/2;
    return tempS;
}

void Sweeper::changeState(int i)
{
    boost::random::uniform_real_distribution<float> dist(-1, 1);

    float xin = m_x[i] + m_Del*dist(*m_gen);

    bool accept;

    if (i == 0) {
        accept = acceptState(m_x[N-1], m_x[i], m_x[i+1], xin);
    } else if (i == N-1) {
        accept = acceptState(m_x[i-1], m_x[i], m_x[0], xin);
    } else {
        accept = acceptState(m_x[i-1], m_x[i], m_x[i+1], xin);
    }

    if (accept) {
        m_xN[i] = xin;
    }
}

