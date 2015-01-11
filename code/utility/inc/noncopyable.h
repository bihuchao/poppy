// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_UTILITY_NONCOPYABLE_H
#define POPPY_UTILITY_NONCOPYABLE_H

namespace poppy
{

class noncopyable
{
 protected:
  noncopyable() {}
  ~noncopyable() {}
 private:
  noncopyable(const noncopyable&);
  noncopyable& operator=(const noncopyable&);
};

}

#endif
