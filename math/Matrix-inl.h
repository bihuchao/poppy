// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Logger.h"
#include "Matrix.h"

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
