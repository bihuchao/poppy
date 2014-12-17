// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_MATRIX_INL_H
#define POPPY_MATH_MATRIX_INL_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Logger.h"
#include "Matrix.h"

namespace poppy
{

template<size_t R, size_t C>
Matrix<R, C>::Matrix(const char *filename)
{
  std::ifstream infile(filename);
  if (!infile)
  {
    LOG_ERROR("open file error!\n");
    return;
  }

  std::string line;
  size_t row = 0;
  while (std::getline(infile, line))
  {
    std::istringstream lineStream(line);
    float item;
    size_t column = 0;
    while (lineStream >> item)
    {
      matrixData_[row][column] = item;
      ++column;
    }
    if (column != C)
    {
      LOG_ERROR("size of column is error!\n");
      break;
    }
    ++row;
  }

  if (row != R)
  {
    LOG_ERROR("size of row is error!\n");
  }
}

template<size_t R, size_t C>
Matrix<R, C>::Matrix(const Matrix<R, C>& rhs)
{
  memcpy(matrixData_, rhs.matrixData_, sizeof(matrixData_));
}

template<size_t R, size_t C>
Matrix<R, C>& Matrix<R, C>::operator=(const Matrix<R, C>& rhs)
{
  if (this != &rhs)
  {
    memcpy(matrixData_, rhs.matrixData_, sizeof(matrixData_));
  }

  return *this;
}

template<size_t R, size_t C>
void Matrix<R, C>::dump() const
{
  fprintf(stdout, "\n");
  for (int i = 0; i < R; i++)
  {
    for (int j = 0; j < C; j++)
    {
      fprintf(stdout, "%10.5f ", matrixData_[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

template<size_t R, size_t D, size_t C>
Matrix<R, C> operator*(const Matrix<R, D>& lhs, const Matrix<D, C>& rhs)
{
  Matrix<R, C> ret;
  for (int i = 1; i <= R; i++)
  {
    for (int j = 1; j <= C; j++)
    {
      float item = 0;
      for (int k = 1; k <= D; k++)
      {
        item += lhs.getItem(i, k) * rhs.getItem(k, j);
      }
      ret.setItem(i, j, item);
    }
  }

  return ret;
}

template<size_t R, size_t C>
Matrix<R - 1, C - 1> Matrix<R, C>::cofactor(size_t dr, size_t dc)
{
  Matrix<R - 1, C - 1> ret;

  size_t rrow = 0;
  for (size_t i = 0; i < R; i++)
  {
    if (i + 1 == dr)
    {
      continue;
    }

    size_t rcolumn = 0;
    for (size_t j = 0; j < C; j++)
    {
      if (j + 1 == dc)
      {
        continue;
      }
      ret.setItem(rrow, rcolumn, getItem(i, j));
      ++rcolumn;
    }
    ++rrow;
  }
}

/*
template<size_t R, size_t C>
float Matrix<R, C>::cofactorOfDeterminant(size_t r, size_t c)
{

}
*/
}

#endif
