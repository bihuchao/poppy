// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdio.h>

#include <tr1/memory>

#include "Bitmap.h"

namespace poppy
{

int Bitmap::loadFromBmpFile(const char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *fp = ::fopen(filename, "rb");
  if (fp == NULL)
  {
    return -1;
  }

  std::tr1::shared_ptr<FILE> filePtr(fp, ::fclose);

  size_t ret = ::fread(&fileHeader, 1, sizeof(BitmapFileHeader), fp);
  if (ret != sizeof(BitmapFileHeader) || fileHeader.type != kBmpFileMagic)
  {
    return -1;
  }

  ret = ::fread(&infoHeader, 1, sizeof(BitmapInfoHeader), fp);
  if (ret != sizeof(BitmapInfoHeader))
  {
    return -1;
  }

  if (infoHeader.bitCounts == 8)
  {
    palette.resize(256);
    ret = ::fread(&*palette.begin(), 1, palette.size()
        * sizeof(PaletteEntry), fp);
    if (ret != palette.size() * sizeof(PaletteEntry))
    {
      palette.clear();
      return -1;
    }
  }

  imageBuffer.resize(infoHeader.sizeImage);
  ret = ::fread(&*imageBuffer.begin(), 1, infoHeader.sizeImage, fp);
  if (ret != infoHeader.sizeImage)
  {
    imageBuffer.clear();
    return -1;
  }

  return 0;
}

int Bitmap::storeToBmpFile(const char *filename)
{
  if (imageBuffer.empty())
  {
    return -1;
  }

  FILE *fp = ::fopen(filename, "wb");
  if (fp == NULL)
  {
    return -1;
  }

  std::tr1::shared_ptr<FILE> filePtr(fp, ::fclose);

  size_t ret = ::fwrite(&fileHeader, 1, sizeof(BitmapFileHeader), fp);
  if (ret != sizeof(BitmapFileHeader))
  {
    return -1;
  }

  ret = ::fwrite(&infoHeader, 1, sizeof(BitmapInfoHeader), fp);
  if (ret != sizeof(BitmapInfoHeader))
  {
    return -1;
  }

  if (!palette.empty())
  {
    ret = ::fwrite(&*palette.begin(), 1, palette.size()
        * sizeof(PaletteEntry), fp);
    if (ret != palette.size() * sizeof(PaletteEntry))
    {
      return -1;
    }
  }

  ret = ::fwrite(&*imageBuffer.begin(), 1, imageBuffer.size(), fp);
  if (ret != imageBuffer.size())
  {
    return -1;
  }

  return 0;
}

void Bitmap::dumpInfoHeader()
{
  printf("\n-----bmp info header----\n");
  printf("size                %d\n", infoHeader.size);
  printf("width               %d\n", infoHeader.width);
  printf("height              %d\n", infoHeader.height);
  printf("planes              %d\n", infoHeader.planes);
  printf("bitCounts           %d\n", infoHeader.bitCounts);
  printf("compress            %d\n", infoHeader.compress);
  printf("sizeImage           %d\n", infoHeader.sizeImage);
  printf("xPelsPerMeter       %d\n", infoHeader.xPelsPerMeter);
  printf("yPelsPerMeter       %d\n", infoHeader.yPelsPerMeter);
  printf("clrUsed             %d\n", infoHeader.clrUsed);
  printf("clrImportant        %d\n", infoHeader.clrImportant);
  printf("-----------end----------\n");

  return;
}

void Bitmap::dumpFileHeader()
{
  printf("\n---bmp file header--------\n");
  printf("type                0x%x\n",  fileHeader.type);
  printf("size                %d\n",    fileHeader.size);
  printf("reserved1           %d\n",    fileHeader.reserved1);
  printf("reserved2           %d\n",    fileHeader.reserved2);
  printf("offBits             %d\n",    fileHeader.offBits);
  printf("-----------end--------------\n");

  return;
}

}

