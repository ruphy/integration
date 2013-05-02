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
    m_totalSweeps = 1;

    reset();

    // "Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random
    // number generator", Makoto Matsumoto and Takuji Nishimura, ACM Transactions
    // on Modeling and Computer Simulation: Special Issue on Uniform Random Number
    // Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
    m_gen = new boost::random::mt19937(time(0) + getpid());

    m_sweepsDone = 0;
}

Sweeper::~Sweeper()
{
    delete m_gen;
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
//     for (int i = 0; i < N; i++) {
//         m_x[i] = m_xN[i];
//     }

    // update the correlator
    for (int j = 0; j < N; j++) {

        double tempSum = 0;
        for (int i = 0; i < N; i++) {
            tempSum += m_x[i]*m_x[(i+j) % N]/N;
        }
        m_correlator[j] = tempSum;

        if (j == 3) {
            // save the correlator for each markovian time
            // for j = 3
            m_corr_0.push_back(tempSum);
        }

        // update mean correlator
//         if (m_sweepsDone != 1) {
//             m_meanCorrelator[j] *= (m_sweepsDone-1)/(m_sweepsDone);
//         }
        m_meanCorrelator[j] += tempSum/m_totalSweeps;
    }
}

/////////////////////////////

double* Sweeper::meanCorrelator()
{
    return m_meanCorrelator;
}

std::vector<double> Sweeper::corr_0()
{
    return m_corr_0;
}

int Sweeper::nElements()
{
    return N;
}

void Sweeper::setTotalSweeps(int totalSweeps)
{
    m_totalSweeps = totalSweeps;
}

double Sweeper::S()
{
    double tempS = 0;
    for (int i = 0; i < N-1; i++) {
        tempS += m_M*pow((m_x[i+1]-m_x[i]), 2)/2 + m_A*(m_M*pow(m_W, 2)*pow(m_x[i], 2)/2);
    }
    tempS += m_M*pow((m_x[0]-m_x[N-1]), 2)/2 + m_A*(m_M*pow(m_W, 2)*pow(m_x[N-1], 2))/2;
    return tempS;
}

void Sweeper::changeState(int i)
{
    boost::random::uniform_real_distribution<double> dist(-1, 1);

    double xin = m_x[i] + m_Del*dist(*m_gen);

    // we have the new state, should we accept it?
    if (acceptState(m_x[(i-1+N) % N], m_x[i % N], m_x[(i+1) %N], xin)) {
        m_x[i] = xin;
//         m_xN[i] = xin;
    }
}

