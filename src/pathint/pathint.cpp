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

#include "sweeper.h"

PathInt::PathInt()
 : m_sweeper(new Sweeper)
{
    setExecType(EsBase::Linear);
    setMaxIterations(200); // 200 sweeps
    setMinIterations(1);

//     printHeader("n,S");
}

void PathInt::exec(int sweepN)
{
    m_sweeper->doSweep();
    print(sweepN, m_sweeper->S());

    if (sweepN == maxIterations()) {
//         printHeader("j,corr");
        float *meanCorr = m_sweeper->meanCorrelator();
        for (int i = 0; i < m_sweeper->nElements(); i++) {
//             print(i, meanCorr[i]);
        }
    }
}




