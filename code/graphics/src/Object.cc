// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <stdint.h>
#include <math.h>

#include "Object.h"
#include "Logger.h"
#include "Camera.h"

namespace
{

inline bool isSpaceLine(const std::string& str)
{
  bool ret = true;
  for (size_t i = 0; i < str.size(); i++)
  {
    if (!isspace(str[i]))
    {
      ret = false;
      break;
    }
  }

  return ret;
}

inline bool isNoteLine(const std::string& str)
{
  bool ret = false;
  if (str.find("#") != std::string::npos)
  {
    ret = true;
  }

  return ret;
}

const uint16_t kPlxRgbMask        = 0x8000;
const uint16_t kPlxShadeMask      = 0x6000;
const uint16_t kPlx2SidedMask     = 0x8000;
const uint16_t kPlxColorMask      = 0x0fff;

const uint16_t kPlxColorModeRgb       = 0x8000;
const uint16_t kPlxColorModeIndexed   = 0x0000;

const uint16_t kPlx2SidedFlag     = 0x1000;
const uint16_t kPlx1SidedFlag     = 0x0000;

const uint16_t kPlxShadeModePure      = 0x0000;
const uint16_t kPlxShadeModeFlat      = 0x2000;
const uint16_t kPlxShadeModeGouraud   = 0x4000;
const uint16_t kPlxShadeModePhong     = 0x6000;

}

namespace poppy
{

Polygon::operator PolygonFull() const
{
  return PolygonFull(attr_, color_, (*pvlist_)[vert_[0]],
                     (*pvlist_)[vert_[1]], (*pvlist_)[vert_[2]]);
}

Object::Object(const char* plgfile, uint32_t attr)
  :attr_(attr), state_(0u), avgRadius_(0.0f),
   maxRadius_(0.0f), ux_(1.0f, 0.0f, 0.0f),
   vy_(0.0f, 1.0f, 0.0f), nz_(0.0f, 0.0f, 1.0f),
   pos_(0.0f, 0.0f, 0.0f), id_(0u)
{
  std::ifstream infile(plgfile);
  if (!infile)
  {
    LOG_ERROR("Open plg file %s error!\n", plgfile);
    return;
  }

  std::string line;
  //去除前面的注释和空白
  while(std::getline(infile, line))
  {
    if (isSpaceLine(line) || isNoteLine(line))
    {
      continue;
    }
    else
    {
      break;
    }
  }

  std::istringstream lineStream(line);
  if (!(lineStream >> name_))
  {
    LOG_ERROR("Input object name error!\n");
    return;
  }

  int pointNum = 0;
  if (!(lineStream >> pointNum))
  {
    LOG_ERROR("Input object num of point error!\n");
    return;
  }

  int polyNum = 0;
  if (!(lineStream >> polyNum))
  {
    LOG_ERROR("Input object num of polygon error!\n");
    return;
  }

  int idx = 0;
  while (idx < pointNum && std::getline(infile, line))
  {
    if (isSpaceLine(line) || isNoteLine(line))
    {
      continue;
    }
    Vector3 tmpVec;
    lineStream.clear();
    lineStream.str(line);
    if (!(lineStream >> tmpVec.x)
        || !(lineStream >> tmpVec.y)
        || !(lineStream >> tmpVec.z))
    {
      LOG_ERROR("Input points of object error!\n");
      return;
    }
    vlistLocal_.push_back(tmpVec);
    vlistTrans_.push_back(tmpVec);
    ++idx;
  }

  if (idx < pointNum)
  {
    LOG_ERROR("Input points of object error!\n");
    return;
  }

  idx = 0;
  while (idx < polyNum && std::getline(infile, line))
  {
    if (isSpaceLine(line) || isNoteLine(line))
    {
      continue;
    }

    uint32_t des;
    int num;
    int p1, p2, p3;
    int ret = 0;
    if (line[0] == '0' && (line[1] == 'x' || line[1] == 'X'))
    {
      ret = sscanf(line.c_str(), "%x %d %d %d %d",
                     &des, &num, &p1, &p2, &p3);
    }
    else
    {
      ret = sscanf(line.c_str(), "%d %d %d %d %d",
                     &des, &num, &p1, &p2, &p3);
    }

    if (ret == -1 || num != 3)
    {
      LOG_ERROR("Input poly of object error!\n");
      return;
    }

    uint32_t attr = 0u;
    uint32_t color = 0u;
    uint32_t shadeMode = 0u;

    if (des & kPlx2SidedFlag)
    {
      attr |= PolygonFull::kPolyAttr2Side;
    }

    if (des & kPlxColorModeRgb)
    {
      attr |= PolygonFull::kPolyAttrRgb24;

      int reg = ((des & 0x0f00) >> 8) * 16;
      int green = ((des & 0x00f0) >> 4) * 16;
      int blue = (des & 0x000f) * 16;

      color = (reg << 16) | (green << 8) | blue;
    }
    else
    {
      LOG_ERROR("Only support rgb!!!!\n");
    }

    shadeMode = des & kPlxShadeMask;
    switch (shadeMode)
    {
      case kPlxShadeModePure:
        attr |= PolygonFull::kPolyAttrShadeModePure;
        break;
      case kPlxShadeModeFlat:
        attr |= PolygonFull::kPolyAttrShadeModeFlat;
        break;
      case kPlxShadeModeGouraud:
        attr |= PolygonFull::kPolyAttrShadeModeGouraud;
        break;
      case kPlxShadeModePhong:
        attr |= PolygonFull::kPolyAttrShadeModePhong;
        break;
      default:
        LOG_ERROR("not support shade mode - %x\n", shadeMode);
        break;
    }

    Polygon poly(attr, color, &vlistTrans_, p1, p2, p3);
    polyList_.push_back(poly);
    ++idx;
  }

  if (idx < polyNum)
  {
    LOG_ERROR("Input poly of object error!\n");
  }

  state_ |= kObjectStateActive;
  state_ |= kObjectStateVisible;

  computeMaxRadius();
}

Object::Object(const Object& rhs)
  :attr_(rhs.attr_), state_(rhs.state_),
   avgRadius_(rhs.avgRadius_), maxRadius_(rhs.maxRadius_),
   ux_(rhs.ux_), vy_(rhs.vy_), nz_(rhs.nz_), pos_(rhs.pos_),
   name_(rhs.name_), id_(rhs.id_), vlistLocal_(rhs.vlistLocal_),
   vlistTrans_(rhs.vlistTrans_)
{
  int num = rhs.polyList_.size();
  for (int i = 0; i < num; i++)
  {
    Polygon poly(0u, rhs.polyList_[i].color_, &vlistTrans_, rhs.polyList_[i].vert_[0],
                 rhs.polyList_[i].vert_[1], rhs.polyList_[i].vert_[2]);
    polyList_.push_back(poly);
  }
}

int Object::insertToRenderList(RenderList *renderList)
{
  if (!(state_ & kObjectStateActive)
      || !(state_ & kObjectStateVisible)
      || (state_ & kObjectStateCulled))
  {
    return 0;
  }
  for (std::vector<Polygon>::iterator iter = polyList_.begin();
      iter != polyList_.end(); ++iter)
  {
    if (!(iter->state_ & PolygonFull::kPolyStateActive)
        || (iter->state_ & PolygonFull::kPolyStateBackface)
        || (iter->state_ & PolygonFull::kPolyStateClipped))
    {
      continue;
    }

    renderList->insert(PolygonFull(*iter));
  }

  return 0;
}

int Object::transformByMatrix(const Matrix<4, 4>& mt,
                      PolygonFull::TransMode mode)
{
  switch (mode)
  {
    case PolygonFull::kLocalOnly:
      for (std::vector<Vector3>::iterator iter = vlistLocal_.begin();
          iter != vlistLocal_.end(); ++iter)
      {
        *iter = *iter * mt;
      }
      break;
    case PolygonFull::kTransOnly:
      for (std::vector<Vector3>::iterator iter = vlistTrans_.begin();
          iter != vlistTrans_.end(); ++iter)
      {
        *iter = *iter * mt;
      }
      break;
    case PolygonFull::kLocalToTrans:
      if (vlistTrans_.size() != vlistLocal_.size())
      {
        LOG_ERROR("num of local is not equal to num of trans - %d , %d!!\n",
                  vlistLocal_.size(), vlistTrans_.size());
        return -1;
      }
      for (size_t i = 0; i < vlistTrans_.size(); i++)
      {
        vlistTrans_[i] = vlistLocal_[i] * mt;
      }
      break;
    default:
      LOG_ERROR("trans mode error - %d\n", mode);
      return -1;
  }

  if (mode == PolygonFull::kLocalOnly)
  {
    ux_ = ux_ * mt;
    vy_ = vy_ * mt;
    nz_ = nz_ * mt;
  }

  return 0;
}

int Object::transformToWorld(const Vector3& pos, const EulerAngles* angles,
                             PolygonFull::TransMode mode)
{
  if (angles == NULL)
  {
    //只平移不旋转
    moveNotByMatrix(pos, mode);
  }
  else
  {
    Matrix<4, 4> mt = angles->getObjectToWorldMatrix();
    //添加平移部分
    Vector3 move = pos - pos_;
    mt.setItem(4, 1, move.x);
    mt.setItem(4, 2, move.y);
    mt.setItem(4, 3, move.z);

    transformByMatrix(mt, mode);

    pos_ = pos;
  }

  return 0;
}

void Object::moveNotByMatrix(const Vector3& pos, PolygonFull::TransMode mode)
{
  Vector3 move = pos - pos_;
  if (mode == PolygonFull::kLocalToTrans)
  {
    for (size_t i = 0; i < vlistLocal_.size(); i++)
    {
      vlistTrans_[i].x = vlistLocal_[i].x + move.x;
      vlistTrans_[i].y = vlistLocal_[i].y + move.y;
      vlistTrans_[i].z = vlistLocal_[i].z + move.z;
    }
  }
  else //local only
  {
    for (std::vector<Vector3>::iterator iter = vlistLocal_.begin();
        iter != vlistLocal_.end(); ++iter)
    {
      iter->x += move.x;
      iter->y += move.y;
      iter->z += move.z;
    }
  }

  pos_ = pos;
}

void Object::removeBackFaces(const Camera& camera)
{
  for (std::vector<Polygon>::iterator iter = polyList_.begin();
      iter != polyList_.end(); ++iter)
  {
    if (!(iter->state_ & PolygonFull::kPolyStateActive)
        || (iter->state_ & PolygonFull::kPolyStateBackface)
        || (iter->state_ & PolygonFull::kPolyStateClipped)
        || (iter->attr_ & PolygonFull::kPolyAttr2Side))
    {
      continue;
    }

    Vector3 p0 = (*(iter->pvlist_))[iter->vert_[0]];
    Vector3 p1 = (*(iter->pvlist_))[iter->vert_[1]];
    Vector3 p2 = (*(iter->pvlist_))[iter->vert_[2]];

    Vector3 u = p1 - p0;
    Vector3 v = p2 - p0;
    Vector3 n = crossProduct(u, v);
    Vector3 view = camera.getPos() - p0;

    if (n * view <= 0.0f)
    {
      iter->state_ |= PolygonFull::kPolyStateBackface;
    }

    float nearClipZ = camera.getNearClipZ();
    if (p0.z <= nearClipZ || p1.z <= nearClipZ || p2.z <= nearClipZ)
    {
      iter->state_ |= PolygonFull::kPolyStateBackface;
    }
  }
}

int Object::cull(const Camera& camera, uint32_t cullFlag)
{
  Vector3 tmpPos = camera.transformWorldToCamera(pos_);
  Vector3 cameraPos = camera.getPos();

  if (cullFlag & kCullObjectZPlane)
  {
    if (tmpPos.z - maxRadius_ > camera.getFarClipZ()
        || tmpPos.z + maxRadius_ < camera.getNearClipZ())
    {
      state_ |= kObjectStateCulled;
      LOG_INFO("Object %s is culled by Z!!\n", name_.c_str());
      return 1;
    }
  }

  if (cullFlag & kCullObjectXPlane)
  {
    float testZ = 0.5 * camera.viewPlaneWidth() * tmpPos.z / camera.getViewDist();
    if (tmpPos.x + maxRadius_ < -testZ
        || tmpPos.x - maxRadius_ > testZ)
    {
      state_ |= kObjectStateCulled;
      LOG_INFO("Object %s is culled by X!!\n", name_.c_str());
      return 1;
    }
  }

  if (cullFlag & kCullObjectYPlane)
  {
    float testZ = 0.5 * camera.viewPlaneHeight() * tmpPos.z / camera.getViewDist();
    if (tmpPos.y + maxRadius_ < -testZ
        || tmpPos.y - maxRadius_ > testZ)
    {
      state_ |= kObjectStateCulled;
      LOG_INFO("Object %s is culled by Y!!\n", name_.c_str());
      return 1;
    }
  }

  return 0;
}

void Object::computeMaxRadius()
{
  float maxRadius = 0.0f;
  float curRadius = 0.0f;

  for (std::vector<Vector3>::iterator iter = vlistLocal_.begin();
       iter != vlistLocal_.end(); ++iter)
  {
    curRadius = iter->x * iter->x + iter->y * iter->y
        + iter->z * iter->z;
    if (curRadius > maxRadius)
    {
      maxRadius = curRadius;
    }
  }

  maxRadius_ = sqrt(curRadius);
}

int Object::scale(Vector3 vscale, PolygonFull::TransMode mode)
{
  int ret = 0;
  switch (mode)
  {
    case PolygonFull::kLocalOnly:
      for (std::vector<Vector3>::iterator iter = vlistLocal_.begin();
          iter != vlistLocal_.end(); ++iter)
      {
        iter->x *= vscale.x;
        iter->y *= vscale.y;
        iter->z *= vscale.z;
      }
      break;
    case PolygonFull::kTransOnly:
      for (std::vector<Vector3>::iterator iter = vlistTrans_.begin();
          iter != vlistTrans_.end(); ++iter)
      {
        iter->x *= vscale.x;
        iter->y *= vscale.y;
        iter->z *= vscale.z;
      }
      break;
    case PolygonFull::kLocalToTrans:
      if (vlistTrans_.size() != vlistLocal_.size())
      {
        LOG_ERROR("sizeo of trans is not equal to local: %d %d\n",
                  vlistTrans_.size(), vlistLocal_.size());
        ret = -1;
        break;
      }

      for (size_t i = 0; i < vlistTrans_.size(); i++)
      {
        vlistTrans_[i].x = vlistLocal_[i].x * vscale.x;
        vlistTrans_[i].y = vlistLocal_[i].y * vscale.y;
        vlistTrans_[i].z = vlistLocal_[i].z * vscale.z;
      }
      break;
    default:
      ret = -1;
      LOG_ERROR("trans mode error: %d\n", mode);
      break;
  }

  return ret;
}

void Object::swap(Object& other)
{
  std::swap(attr_, other.attr_);
  std::swap(state_, other.state_);
  std::swap(avgRadius_, other.avgRadius_);
  std::swap(maxRadius_, other.maxRadius_);
  std::swap(ux_, other.ux_);
  std::swap(vy_, other.vy_);
  std::swap(nz_, other.nz_);
  std::swap(pos_, other.pos_);
  name_.swap(other.name_);
  std::swap(id_, other.id_);
  vlistLocal_.swap(other.vlistLocal_);
  vlistTrans_.swap(other.vlistTrans_);
  polyList_.swap(other.polyList_);

  for (std::vector<Polygon>::iterator iter = polyList_.begin();
      iter != polyList_.end(); ++iter)
  {
    iter->pvlist_ = &vlistTrans_;
  }

  for (std::vector<Polygon>::iterator iter = other.polyList_.begin();
      iter != other.polyList_.end(); ++iter)
  {
    iter->pvlist_ = &(other.vlistTrans_);
  }
}

Object& Object::operator=(const Object& rhs)
{
  Object tmp(rhs);
  swap(tmp);
  return *this;
}

void swap(Object& lhs, Object& rhs)
{
  lhs.swap(rhs);
}

}

namespace std
{

template<>
void swap<poppy::Object>(poppy::Object& lhs, poppy::Object& rhs)
{
  lhs.swap(rhs);
}

}
