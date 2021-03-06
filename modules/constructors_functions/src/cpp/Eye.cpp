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
#include "Eye.hpp"
#include "SparseDynamicFunctions.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    ArrayOf Eye(indexType n, indexType m, Class classDest, bool bIsSparse)
    {
        Dimensions dimMat(n, m);
        void *vmat = nullptr;
        if (m * n)
        {
            switch (classDest)
            {
                case NLS_DCOMPLEX:
                {
                    if (bIsSparse)
                    {
                        vmat = EyeSparseMatrixConstructorDynamicFunction(NLS_DCOMPLEX, n, m);
                    }
                    else
                    {
                        double *mat = (double*)ArrayOf::allocateArrayOf(NLS_DCOMPLEX, m * n);
                        doublecomplex *pzMat = reinterpret_cast<doublecomplex*>((double*)mat);
                        Eigen::Map<Eigen::Matrix<doublecomplex, Eigen::Dynamic, Eigen::Dynamic>> matEye(pzMat, n, m);
                        matEye.setIdentity();
                        vmat = (void*)pzMat;
                    }
                }
                break;
                case NLS_DOUBLE:
                {
                    if (bIsSparse)
                    {
                        vmat = EyeSparseMatrixConstructorDynamicFunction(NLS_DOUBLE, n, m);
                    }
                    else
                    {
                        double *mat = (double*)ArrayOf::allocateArrayOf(NLS_DOUBLE, m * n);
                        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                        matEye.setIdentity();
                        vmat = (void*)mat;
                    }
                }
                break;
                case NLS_SCOMPLEX:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    single *mat = (single*)ArrayOf::allocateArrayOf(NLS_SCOMPLEX, m * n);
                    singlecomplex *pzMat = reinterpret_cast<singlecomplex*>((single*)mat);
                    Eigen::Map<Eigen::Matrix<singlecomplex, Eigen::Dynamic, Eigen::Dynamic>> matEye(pzMat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_SINGLE:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    single *mat = (single*)ArrayOf::allocateArrayOf(NLS_SINGLE, m * n);
                    Eigen::Map<Eigen::Matrix<single, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_LOGICAL:
                {
                    if (bIsSparse)
                    {
                        vmat = EyeSparseMatrixConstructorDynamicFunction(NLS_LOGICAL, n, m);
                    }
                    else
                    {
                        logical *mat = (logical*)ArrayOf::allocateArrayOf(NLS_LOGICAL, m * n);
                        Eigen::Map<Eigen::Matrix<logical, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                        matEye.setIdentity();
                        vmat = (void*)mat;
                    }
                }
                break;
                case NLS_INT8:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    int8 *mat = (int8*)ArrayOf::allocateArrayOf(NLS_INT8, m * n);
                    Eigen::Map<Eigen::Matrix<int8, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_INT16:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    int16 *mat = (int16*)ArrayOf::allocateArrayOf(NLS_INT16, m * n);
                    Eigen::Map<Eigen::Matrix<int16, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_INT32:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    int32 *mat = (int32*)ArrayOf::allocateArrayOf(NLS_INT32, m * n);
                    Eigen::Map<Eigen::Matrix<int32, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_INT64:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    int64 *mat = (int64*)ArrayOf::allocateArrayOf(NLS_INT64, m * n);
                    Eigen::Map<Eigen::Matrix<int64, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_UINT8:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    uint8 *mat = (uint8*)ArrayOf::allocateArrayOf(NLS_UINT8, m * n);
                    Eigen::Map<Eigen::Matrix<uint8, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_UINT16:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    uint16 *mat = (uint16*)ArrayOf::allocateArrayOf(NLS_UINT16, m * n);
                    Eigen::Map<Eigen::Matrix<uint16, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_UINT32:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    uint32 *mat = (uint32*)ArrayOf::allocateArrayOf(NLS_UINT32, m * n);
                    Eigen::Map<Eigen::Matrix<uint32, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                case NLS_UINT64:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    uint64 *mat = (uint64*)ArrayOf::allocateArrayOf(NLS_UINT64, m * n);
                    Eigen::Map<Eigen::Matrix<uint64, Eigen::Dynamic, Eigen::Dynamic>> matEye(mat, n, m);
                    matEye.setIdentity();
                    vmat = (void*)mat;
                }
                break;
                default:
                {
                    throw Exception(_W("Input following \'like'' is not a numeric array."));
                }
                break;
            }
        }
        else
        {
            switch (classDest)
            {
                case NLS_DOUBLE:
                case NLS_LOGICAL:
                {
                    vmat = nullptr;
                }
                break;
                case NLS_SCOMPLEX:
                case NLS_DCOMPLEX:
                case NLS_SINGLE:
                case NLS_INT8:
                case NLS_INT16:
                case NLS_INT32:
                case NLS_INT64:
                case NLS_UINT8:
                case NLS_UINT16:
                case NLS_UINT32:
                case NLS_UINT64:
                {
                    if (bIsSparse)
                    {
                        throw Exception(_W("sparse not supported."));
                    }
                    vmat = nullptr;
                }
                break;
                default:
                {
                    throw Exception(_W("Input following \'like\' is not a numeric array."));
                }
                break;
            }
        }
        return ArrayOf(classDest, dimMat, vmat, bIsSparse);
    }
};
//=============================================================================
