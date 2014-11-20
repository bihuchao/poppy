// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdlib.h>
#include "FrameBufferOfMem.h"

namespace poppy
{

FrameBufferOfMem::FrameBufferOfMem(int32_t p, int32_t w, int32_t h, 
    int32_t pixfmt, char *colorPalette)
  : FrameBuffer(p, w, h, pixfmt), buf_(NULL), colorPalette_(colorPalette)
{
  buf_ = (char *)malloc(p * h);
}

FrameBufferOfMem::~FrameBufferOfMem()
{
  if (buf_)
  {
    free(buf_);
  }
}

}
