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
#include <boost/container/vector.hpp>
#include "ToChar.hpp"
#include "IEEEFP.hpp"
#include "VertCatString.hpp"
//=============================================================================
namespace Nelson {
    static ArrayOf ArrayOfDoubleToChar(ArrayOf A)
    {
        Dimensions dimsA = A.getDimensions();
        std::wstring res;
        res.reserve(A.getLength());
        double *pDouble = (double*)A.getDataPointer();
#if defined(__NLS_WITH_OPENMP)
        #pragma omp parallel for
#endif
        for (indexType k = 0; k < A.getLength(); k++)
        {
            double v = pDouble[k];
            if (IsFinite(v))
            {
                if (v < 0)
                {
                    res.push_back((charType)0);
                }
                else
                {
                    if (v > 65535)
                    {
                        res.push_back((charType)65535);
                    }
                    else
                    {
                        res.push_back((charType)(v));
                    }
                }
            }
            else
            {
                if (IsNaN(v))
                {
                    res.push_back((charType)0);
                }
                else
                {
                    if (v <= 0)
                    {
                        res.push_back((charType)0);
                    }
                    else if (IsInfinite(v))
                    {
                        if (v < 0)
                        {
                            res.push_back((charType)0);
                        }
                        else
                        {
                            res.push_back((charType)65535);
                        }
                    }
                }
            }
        }
        ArrayOf result = ArrayOf::stringConstructor(res);
        result.reshape(dimsA);
        return result;
    }
    //=============================================================================
    ArrayOf ToChar(ArrayOf A, ArrayOf B)
    {
        ArrayOf res;
        ArrayOf charA = ToChar(A);
        ArrayOf charB = ToChar(B);
        Dimensions dimsA = charA.getDimensions();
        Dimensions dimsB = charB.getDimensions();
        wstringVector vA = charA.getContentAsWideStringVector();
        if (vA.size() == 0)
        {
            vA.push_back(L"");
        }
        wstringVector vB = charB.getContentAsWideStringVector();
        if (vB.size() == 0)
        {
            vB.push_back(L"");
        }
        size_t lenMax = 0;
        for (indexType i = 0; i < vA.size(); ++i)
        {
            if (lenMax < vA[i].size())
            {
                lenMax = vA[i].size();
            }
        }
        for (indexType i = 0; i < vB.size(); ++i)
        {
            if (lenMax < vB[i].size())
            {
                lenMax = vB[i].size();
            }
        }
        for (indexType i = 0; i < vA.size(); ++i)
        {
            size_t newLen = lenMax - vA[i].size();
            if (newLen > 0)
            {
                for (size_t q = 0; q < newLen; q++)
                {
                    vA[i] = vA[i] + std::wstring(L" ");
                }
            }
        }
        for (indexType i = 0; i < vB.size(); ++i)
        {
            size_t newLen = lenMax - vB[i].size();
            if (newLen > 0)
            {
                for (size_t q = 0; q < newLen; q++)
                {
                    vB[i] = vB[i] + std::wstring(L" ");
                }
            }
        }
        res = ArrayOf::stringConstructor(vA[0]);
        for (size_t i = 1; i < vA.size(); i++)
        {
            ArrayOf B = ArrayOf::stringConstructor(vA[i]);
            res = VertCatString(res, B);
        }
        for (size_t i = 0; i < vB.size(); i++)
        {
            ArrayOf B = ArrayOf::stringConstructor(vB[i]);
            res = VertCatString(res, B);
        }
        return res;
    }
    //=============================================================================
    ArrayOf ToChar(ArrayOf A)
    {
        ArrayOf res;
        if (A.isSparse())
        {
            throw Exception(_W("Attempt to convert to unimplemented sparse type."));
        }
        switch (A.getDataClass())
        {
            case NLS_HANDLE:
            {
                throw Exception(_W("Conversion to char from handle is not possible."));
            }
            break;
            case NLS_CELL_ARRAY:
            {
                bool isCellOfString = true;
                ArrayOf *arg = (ArrayOf*)(A.getDataPointer());
                for (indexType k = 0; k < A.getDimensions().getElementCount(); k++)
                {
                    if (!arg[k].isString())
                    {
                        isCellOfString = false;
                        break;
                    }
                }
                if (isCellOfString)
                {
                    ArrayOfVector V;
                    ArrayOf *arg = (ArrayOf*)(A.getDataPointer());
                    for (indexType k = 0; k < A.getDimensions().getElementCount(); k++)
                    {
                        V.push_back(ToChar(arg[k]));
                    }
                    res = V[0];
                    for (indexType k = 1; k < V.size(); k++)
                    {
                        res = ToChar(res, V[k]);
                    }
                }
                else
                {
                    throw Exception(_W("Conversion to char from cell is possible only with cell of strings."));
                }
            }
            break;
            case NLS_STRUCT_ARRAY:
            {
                if (A.getStructType() != "struct")
                {
                    throw Exception(_("Undefined function 'char' for input arguments of type") + " '" + A.getStructType() + "'.");
                }
                else
                {
                    throw Exception(_W("Conversion to char from struct is not possible."));
                }
            }
            break;
            case NLS_LOGICAL:
            {
                throw Exception(_W("Conversion to char from logical is not possible."));
            }
            break;
            case NLS_SCOMPLEX:
            {
                throw Exception(_W("Conversion to char from complex is not possible."));
            }
            break;
            case NLS_CHAR:
            {
                if (A.isSparse())
                {
                    throw Exception(_W("Attempt to convert to unimplemented sparse type."));
                }
                else
                {
                    ArrayOf result = A;
                    return result;
                }
            }
            break;
            case NLS_DCOMPLEX:
            {
                throw Exception(_W("Conversion to char from complex is not possible."));
            }
            break;
            case NLS_UINT8:
            case NLS_INT8:
            case NLS_UINT16:
            case NLS_INT16:
            case NLS_UINT32:
            case NLS_INT32:
            case NLS_UINT64:
            case NLS_INT64:
            case NLS_SINGLE:
            case NLS_DOUBLE:
            {
                A.promoteType(NLS_DOUBLE);
                res = ArrayOfDoubleToChar(A);
            }
            break;
            default:
            {
                throw Exception(_W("Invalid conversion."));
            }
            break;
        }
        return res;
    }
    //=============================================================================



















    //=============================================================================
    static std::wstring ToChar(wstringVector V, boost::container::vector<Dimensions> dimsVector, Dimensions &dims)
    {
        std::wstring res;
        size_t lenMax = 0;
        for (size_t k = 0; k < V.size(); ++k)
        {
            if (lenMax < V[k].size())
            {
                lenMax = dimsVector[k].getColumns();
            }
        }
        if (V.size() == 1)
        {
            dims = dimsVector[0];
            return V[0];
        }
        else
        {
            /*
            for (size_t k = 0; k < V.size(); k++)
            {
            	size_t newLen = lenMax - dimsVector[k].getColumns();
            	if (newLen > 0)
            	{
            		for (size_t q = 0; q < newLen; q++)
            		{
            			V[k] = V[k] + std::wstring(L" ");
            		}
            	}
            }
            */
            ArrayOf resAsArrayOf = ArrayOf::stringConstructor(V[0]);
            resAsArrayOf.reshape(dimsVector[0]);
            for (size_t i = 1; i < V.size(); i++)
            {
                ArrayOf B = ArrayOf::stringConstructor(V[i]);
                B.reshape(dimsVector[i]),
                          resAsArrayOf = VertCatString(resAsArrayOf, B);
            }
            res = resAsArrayOf.getContentsAsArrayOfCharacters();
            dims[0] = resAsArrayOf.getDimensions().getRows();
            dims[1] = resAsArrayOf.getDimensions().getColumns();
        }
        return res;
    }
    //=============================================================================
}
//=============================================================================
