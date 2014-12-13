// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_MATRIX_H
#define POPPY_MATH_MATRIX_H

#include <stddef.h>

template<size_t R, size_t C> class Matrix
{
 public:
  Matrix(const char *filename);
  Matrix() { }
  Matrix(const Matrix<R, C>& rhs);
  Matrix<R, C>& operator=(const Matrix<R, C>& rhs);

  float getItem(int r, int c) const { return matrixData_[r - 1][c - 1]; }
  void setItem(int r, int c, float item) { matrixData_[r - 1][c - 1] = item; }
  size_t row() const { return R; }
  size_t column() const {return C; }
  void dump() const;
 private:
  float matrixData_[R][C];
};

template<size_t R, size_t D, size_t C>
Matrix<R, C> operator*(const Matrix<R, D>& lhs, const Matrix<D, C>& rhs);

#include "Matrix-inl.h"

#endif
