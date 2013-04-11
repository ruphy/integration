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

void PathInt::exec(int sweepN)
{

}

PathInt::PathInt()
{
    setExecType(EsBase::Linear);
    setMaxIterations(1000); // 1000 sweeps
    setMaxIterations(1);

    m_A = 1;
    m_M = 1;
    m_W = 1;
    m_Del = 3;

    reset();
}

void PathInt::reset()
{
    for (int i = 0; i < N; i++) {
        m_x[i] = 0;
        m_xN[i] = 0;
    }
}
