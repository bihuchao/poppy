// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdlib.h>
#include "FrameBuffer.h"

namespace poppy
{

class FrameBufferOfMem: public FrameBuffer
{
  public:
    FrameBufferOfMem(): buf_(NULL), colorPalette_(NULL) { };
    FrameBufferOfMem(int32_t p, int32_t w, int32_t h, 
        int32_t pixfmt, char *colorPalette);
    int storeToBmpFile();
    virtual ~FrameBufferOfMem();
  private:
    char *buf_;
    char *colorPalette_;
};

}

