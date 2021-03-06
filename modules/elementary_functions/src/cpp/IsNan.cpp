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
#include "IsNaN.hpp"
#include "ClassName.hpp"
//=============================================================================
namespace Nelson {
	//=============================================================================
	template <class T>
	void boolean_isnan(indexType N, logical* C, const T *A)
    {
        for (indexType i = 0; i<N; i++)
        {
            C[i] = std::isnan(A[i]);
        }
    }
	//=============================================================================
	template <class T>
	void boolean_isnan_cplx(indexType N, logical* C, const T *A)
	{
		for (indexType i = 0; i<N; i++)
		{
			C[i] = std::isnan(A[i].real()) || std::isnan(A[i].imag());
		}
	}
	//=============================================================================

	ArrayOf IsNaN(ArrayOf A)
    {
        ArrayOf C;
		switch (A.getDataClass())
		{
		case NLS_DOUBLE:
		{
			C = ArrayOf(NLS_LOGICAL, A.getDimensions(), NULL);
			void *Cp = C.allocateArrayOf(NLS_LOGICAL, A.getLength());
			boolean_isnan<double>(A.getLength(), (logical*)Cp, (const double*)A.getDataPointer());
			C.setDataPointer(Cp);
		}
		break;
		case NLS_SINGLE:
		{
			C = ArrayOf(NLS_LOGICAL, A.getDimensions(), NULL);
			void *Cp = C.allocateArrayOf(NLS_LOGICAL, A.getLength());
			boolean_isnan<single>(A.getLength(), (logical*)Cp, (const single*)A.getDataPointer());
			C.setDataPointer(Cp);
		}
		break;
		case NLS_SCOMPLEX:
		{
			C = ArrayOf(NLS_LOGICAL, A.getDimensions(), NULL);
			void *Cp = C.allocateArrayOf(NLS_LOGICAL, A.getLength());
			single *pValueA = (single*)A.getDataPointer();
			singlecomplex *cplx = reinterpret_cast<singlecomplex*>(pValueA);
			boolean_isnan_cplx<singlecomplex>(A.getLength(), (logical*)Cp, cplx);
			C.setDataPointer(Cp);
		}
		break;
		case NLS_DCOMPLEX:
		{
			C = ArrayOf(NLS_LOGICAL, A.getDimensions(), NULL);
			void *Cp = C.allocateArrayOf(NLS_LOGICAL, A.getLength());
			double *pValueA = (double*)A.getDataPointer();
			doublecomplex *cplx = reinterpret_cast<doublecomplex*>(pValueA);
			boolean_isnan_cplx<doublecomplex>(A.getLength(), (logical*)Cp, cplx);
			C.setDataPointer(Cp);
		}
		break;
		case NLS_CHAR:
		case NLS_LOGICAL:
		case NLS_INT8:
		case NLS_UINT8:
		case NLS_INT16:
		case NLS_UINT16:
		case NLS_INT32:
		case NLS_UINT32:
		case NLS_INT64:
		case NLS_UINT64:
		{
			C = ArrayOf(NLS_LOGICAL, A.getDimensions(), NULL);
			void *Cp = C.allocateArrayOf(NLS_LOGICAL, A.getLength());
			logical *CpLogical = (logical*)Cp;
			for (indexType i = 0; i < A.getLength(); i++)
			{
				CpLogical[i] = (logical)0;
			}
			C.setDataPointer(Cp);
		}
			break;
		default:
		{
			throw Exception(_("Undefined function 'isnan' for input arguments of type") + " '" + ClassName(A) + "'.");
		}
			break;
		}
        return C;
    }
	//=============================================================================
}
//=============================================================================
