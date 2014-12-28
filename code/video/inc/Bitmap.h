// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_VIDEO_BITMAP_H
#define POPPY_VIDEO_BITMAP_H

#include <stdint.h>

#include <vector>

namespace poppy
{

#pragma pack(1)
typedef struct BitmapFileHeader_
{
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offBits;
} BitmapFileHeader;

typedef struct BitmapInfoHeader_
{
  uint32_t size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bitCounts;
  uint32_t compress;
  uint32_t sizeImage;
  uint32_t xPelsPerMeter;
  uint32_t yPelsPerMeter;
  uint32_t clrUsed;
  uint32_t clrImportant;
} BitmapInfoHeader;

typedef struct PaletteEntry_
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t flags;
} PaletteEntry;

#pragma pack()

class Bitmap
{
 public:
  static const uint16_t kBmpFileMagic = 0x4d42;

  int loadFromBmpFile(const char *name);
  int storeToBmpFile(const char *name);
  void dumpInfoHeader();
  void dumpFileHeader();
 private:
  BitmapFileHeader fileHeader;
  BitmapInfoHeader infoHeader;
  std::vector<uint8_t> imageBuffer;
  std::vector<PaletteEntry> palette;
};

}

#endif

