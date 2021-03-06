//=============================================================================
// Copyright (c) 2016-2017 Allan CORNET (Nelson)
//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "HorzCatSparseLogical.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    ArrayOf HorzCatSparseLogical(ArrayOf A, ArrayOf B)
    {
        ArrayOf C;
        if (A.isEmpty(true))
        {
            ArrayOf C(B);
            return C;
        }
        if (B.isEmpty(true))
        {
            ArrayOf C(A);
            return C;
        }
        Eigen::SparseMatrix<logical, 0, signedIndexType> *spMatA = (Eigen::SparseMatrix<logical, 0, signedIndexType> *)A.getSparseDataPointer();
        Eigen::SparseMatrix<logical, 0, signedIndexType> *spMatB = (Eigen::SparseMatrix<logical, 0, signedIndexType> *)B.getSparseDataPointer();
        Eigen::SparseMatrix<logical, 0, signedIndexType> *spMatC;
        Dimensions dimsA = A.getDimensions();
        Dimensions dimsB = B.getDimensions();
        indexType newColumnsSize = dimsA.getColumns() + dimsB.getColumns();
        indexType newRowsSize = dimsA.getRows();
        indexType newSize = newColumnsSize * newRowsSize;
        Dimensions dimsC = Dimensions(newRowsSize, newColumnsSize);
        try
        {
            spMatC = new Eigen::SparseMatrix<logical, 0, signedIndexType>(newRowsSize, newColumnsSize);
        }
        catch (std::bad_alloc &e)
        {
            e.what();
            spMatC = nullptr;
            throw Exception(ERROR_MEMORY_ALLOCATION);
        }
        spMatC->middleCols(0, spMatA->cols()) = *spMatA;
        spMatC->middleCols(spMatA->cols(), spMatB->cols()) = *spMatB;
        C = ArrayOf(NLS_LOGICAL, dimsC, (void*)spMatC, true);
        return C;
    }
    //=============================================================================
}
//=============================================================================
