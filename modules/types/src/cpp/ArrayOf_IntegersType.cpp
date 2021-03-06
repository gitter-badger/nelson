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
#include "ArrayOf.hpp"
#include "Data.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    ArrayOf ArrayOf::uint8Constructor(uint8 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        uint8 *data = (uint8 *)allocateArrayOf(NLS_UINT8, 1);
        *data = aval;
        return ArrayOf(NLS_UINT8, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::int8Constructor(int8 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        int8 *data = (int8 *)allocateArrayOf(NLS_INT8, 1);
        *data = aval;
        return ArrayOf(NLS_INT8, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::uint16Constructor(uint16 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        uint16 *data = (uint16 *)allocateArrayOf(NLS_UINT16, 1);
        *data = aval;
        return ArrayOf(NLS_UINT16, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::int16Constructor(int16 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        int16 *data = (int16 *)allocateArrayOf(NLS_INT16, 1);
        *data = aval;
        return ArrayOf(NLS_INT16, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::uint32Constructor(uint32 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        uint32 *data = (uint32 *)allocateArrayOf(NLS_UINT32, 1);
        *data = aval;
        return ArrayOf(NLS_UINT32, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::int32Constructor(int32 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        int32 *data = (int32 *)allocateArrayOf(NLS_INT32, 1);
        *data = aval;
        return ArrayOf(NLS_INT32, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::uint64Constructor(uint64 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        uint64 *data = (uint64 *)allocateArrayOf(NLS_UINT64, 1);
        *data = aval;
        return ArrayOf(NLS_UINT64, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::int64Constructor(int64 aval)
    {
        Dimensions dim;
        dim.makeScalar();
        int64 *data = (int64 *)allocateArrayOf(NLS_INT64, 1);
        *data = aval;
        return ArrayOf(NLS_INT64, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::int64VectorConstructor(int len)
    {
        Dimensions dim;
        dim.makeScalar();
        dim[1] = len;
        int64 *data = (int64*)allocateArrayOf(NLS_INT64, len);
        return ArrayOf(NLS_INT64, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::int32VectorConstructor(int len)
    {
        Dimensions dim;
        dim.makeScalar();
        dim[1] = len;
        int32 *data = (int32*)allocateArrayOf(NLS_INT32, len);
        return ArrayOf(NLS_INT32, dim, data);
    }
    //=============================================================================
    ArrayOf ArrayOf::integerRangeConstructor(indexType minval, indexType stepsize, indexType maxval, bool vert)
    {
        Dimensions Cdim;
        if (stepsize == 0)
        {
            Cdim[0] = 1;
            Cdim[1] = 0;
#ifdef NLS_INDEX_TYPE_64
            return ArrayOf(NLS_INT32, Cdim, NULL, false);
#else
            return ArrayOf(NLS_INT64, Cdim, NULL, false);
#endif
        }
        if (minval < maxval)
        {
            if (stepsize < 0)
            {
                Cdim[0] = 1;
                Cdim[1] = 0;
#ifdef NLS_INDEX_TYPE_64
                return ArrayOf(NLS_INT64, Cdim, NULL, false);
#else
                return ArrayOf(NLS_INT32, Cdim, NULL, false);
#endif
            }
        }
        if (minval > maxval)
        {
            if (stepsize > 0)
            {
                Cdim[0] = 1;
                Cdim[1] = 0;
#ifdef NLS_INDEX_TYPE_64
                return ArrayOf(NLS_INT64, Cdim, NULL, false);
#else
                return ArrayOf(NLS_INT32, Cdim, NULL, false);
#endif
            }
        }
        double dn = (double)((((maxval - minval) / stepsize) + 1));
#ifdef NLS_INDEX_TYPE_64
        int64 n = (int64)floor((double)(dn));
#else
        int32 n = (int32)floor((double)(dn));
#endif
        if (vert)
        {
            Cdim[0] = n;
            Cdim[1] = 1;
        }
        else
        {
            Cdim[0] = 1;
            Cdim[1] = n;
        }
#ifdef NLS_INDEX_TYPE_64
        int64 *rp = (int64 *)allocateArrayOf(NLS_INT64, n);
#else
        int32 *rp = (int32 *)allocateArrayOf(NLS_INT32, n);
#endif
        if (dn == (double(n)))
        {
#ifdef NLS_INDEX_TYPE_64
            Eigen::Map<Eigen::Matrix<int64, Eigen::Dynamic, 1>> Range(rp, n);
            Range = Eigen::Matrix<int64, Eigen::Dynamic, 1>::LinSpaced(n, minval, maxval);
#else
            Eigen::Map<Eigen::VectorXi> Range(rp, n);
            Range = Eigen::VectorXi::LinSpaced(n, minval, maxval);
#endif
        }
        else
        {
            // We must use another algo. in this case
            // 1:2:10
            indexType i = 0;
            indexType v = minval;
            while ((minval < maxval && v <= maxval) || (minval > maxval && v >= maxval))
            {
                rp[i] = v;
                v = v + stepsize;
                i++;
            }
        }
#ifdef NLS_INDEX_TYPE_64
        return ArrayOf(NLS_INT64, Cdim, rp);
#else
        return ArrayOf(NLS_INT32, Cdim, rp);
#endif
    }
    //=============================================================================
    int32 ArrayOf::getContentsAsInteger32Scalar()
    {
        int32 *qp;
        if (getLength() != 1)
        {
            throw Exception(ERROR_SCALAR_EXPECTED);
        }
        promoteType(NLS_INT32);
        qp = (int32*)dp->getData();
        return (*qp);
    }
    //=============================================================================
    int64 ArrayOf::getContentsAsInteger64Scalar()
    {
        int64 *qp;
        if (getLength() != 1)
        {
            throw Exception(ERROR_SCALAR_EXPECTED);
        }
        promoteType(NLS_INT64);
        qp = (int64*)dp->getData();
        return (*qp);
    }
    //=============================================================================
    uint64 ArrayOf::getContentsAsUnsignedInt64Scalar()
    {
        uint64 *qp;
        if (getLength() != 1)
        {
            throw Exception(ERROR_SCALAR_EXPECTED);
        }
        promoteType(NLS_UINT64);
        qp = (uint64*)dp->getData();
        return (*qp);
    }
    //=============================================================================
    const bool ArrayOf::isIntegerType() const
    {
        return ((dp->dataClass == NLS_UINT8) ||
                (dp->dataClass == NLS_UINT16) ||
                (dp->dataClass == NLS_UINT32) ||
                (dp->dataClass == NLS_UINT64) ||
                (dp->dataClass == NLS_INT8) ||
                (dp->dataClass == NLS_INT16) ||
                (dp->dataClass == NLS_INT32) ||
                (dp->dataClass == NLS_INT64));
    }
    //=============================================================================
    const bool ArrayOf::isNdArrayIntegerType() const
    {
        return (isIntegerType() && !isSparse() && !is2D());
    }
    //=============================================================================
}
//=============================================================================
