// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_RGB_H
#define POPPY_GRAPHICS_RGB_H

namespace poppy
{

struct Rbg
{
  union
  {
    uint32_t rgba;
    uint8_t rgbaM[4];
    struct {uint8_t a, b, g, r; };
  };
};

}

#endif
