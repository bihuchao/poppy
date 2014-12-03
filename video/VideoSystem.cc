// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "VideoSystem.h" 
#include "Logger.h"
namespace poppy
{

int VideoSystem::lockFrameBufferComon(bool isPrimary)
{
  FrameBuffer *frameBuf = isPrimary ? primary_ : secondary_;
  uint8_t *buf = NULL;
  int pitch = 0;
  int ret = frameBuf->lockFrameBuffer(&buf, &pitch);
  if (ret != 0)
  {
    LOG_ERROR("lock buffer(%d) error - %d\n", isPrimary, ret); 
    return -1;
  }

  if (isPrimary)
  {
    lockedPrimaryBuf_ = buf;
    pitchPrimary_ = pitch;
  }
  else
  {
    lockedSecondaryBuf_ = buf;
    pitchSecondary_ = pitch;
  }

  return 0;
}

int VideoSystem::unlockFrameBufferComon(bool isPrimary)
{
  uint8_t *lockedBuf = isPrimary ? lockedPrimaryBuf_ : lockedSecondaryBuf_;
  FrameBuffer *frameBuf = isPrimary ? primary_ : secondary_;

  if (lockedBuf == NULL)
  {
    LOG_ERROR("buf(%d) is not locked!\n", isPrimary); 
    return -1;
  }

  int ret = frameBuf->unlockFrameBuffer(lockedBuf);
  if (ret != 0)
  {
    LOG_ERROR("unlock buf(%d) error - %d\n", isPrimary, ret); 
    return -1;
  }
  
  if (isPrimary)
  {
    lockedPrimaryBuf_ = NULL;
    pitchPrimary_ = 0;
  }
  else
  {
    lockedSecondaryBuf_ = NULL; 
    pitchSecondary_ = 0;
  }

  return 0;
}

int VideoSystem::lockPrimary()
{
  return lockFrameBufferComon(true);
}

int VideoSystem::unlockPrimary()
{
  return unlockFrameBufferComon(true);
}

int VideoSystem::lockSecondary()
{
  return lockFrameBufferComon(false);
}

int VideoSystem::unlockSecondary()
{
  return unlockFrameBufferComon(false);
}

int VideoSystem::fillSecondary(uint32_t color)
{
  return secondary_->fill(color);
}

int VideoSystem::fillPrimary(uint32_t color)
{
  return primary_->fill(color);
}

int VideoSystem::flipDisplay()
{
  return primary_->flip(secondary_);
}

void VideoSystem::drawPixel(int x, int y, uint32_t color)
{
  secondary_->putPixel(lockedSecondaryBuf_, x, y, color);
}

}

