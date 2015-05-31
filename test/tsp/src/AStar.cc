#include <cstring>
#include <cmath>

#include "AStar.h"

Point::Point()
{
  _x = _y = 0;
}
Point::Point(int x, int y)
{
  _x = x;
  _y = y;
}
int Point::getManhattanDistance(const Point& t) const
{
  return std::abs(_x - t._x) + std::abs(_y - t._y);
}
double Point::getEuclidDistance(const Point& t) const
{
  return std::sqrt((_x - t._x) * (_x - t._x) + (_y - t._y) * (_y - t._y));
}
bool Point::operator==(const Point& t) const
{
  return _x == t._x && _y == t._y;
}
bool Point::operator<(const Point& t) const
{
  if (_x == t._x)
  {
    return _y < t._y;
  }
  return _x < t._x;
}

Local::Local()
    : Point()
{
  _g = _h = 0;
}
Local::Local(int x, int y, int g, int h)
    : Point(x, y)
{
  _g = g;
  _h = h;
}
Local::Local(const Point& t, int g, int h)
    : Point(t)
{
  _g = g;
  _h = h;
}
Local::Local(const Local& t)
{
  _x = t._x;
  _y = t._y;
  _g = t._g;
  _h = t._h;
}
int Local::getF() const
{
  return _g + _h;
}
bool Local::operator<(const Local& t) const
{
  return getF() < t.getF();
}

CloseList::CloseList()
{
  newClose(100, 100);
}
CloseList::CloseList(int x, int y)
{
  newClose(x, y);
}
CloseList::~CloseList()
{
  for (int i = 0; i < size_y; i++)
  {
    delete[] _close[i];
  }
  delete[] _close;
}
void CloseList::insert(const Local& p)
{
  _close[p.getX()][p.getY()] = true;
}
bool CloseList::find(const Local& p) const
{
  return _close[p.getX()][p.getY()] == true;
}
void CloseList::newClose(int x, int y)
{
  size_x = x;
  size_y = y;
  _close = new bool*[x];
  for (int i = 0; i < x; i++)
  {
    _close[i] = new bool[y];
    memset(_close[i], false, sizeof(_close[i]));
  }
}

AStar::AStar(std::vector<std::vector<bool> >& legal, Point& start, Point& end)
{
  _legal = legal;
  _start = start;
  _end = end;
  pathPlanning();
}
int AStar::getDistance() const
{
  return _distance;
}
std::list<Point> AStar::getPath() const
{
  return _path_list;
}
void AStar::pathPlanning()
{
  open.insert(Local(_start, 0, 0));
  int dir[][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
  while (!open.empty())
  {
    Local cur = *open.begin();
    open.erase(open.begin());
    close.insert(cur);
    if (cur == _end)
    {
      initPath();
      _distance = cur.getG();
      return;
    }
    for (int i = 0; i < 4; i++)
    {
      int x = cur.getX() + dir[i][0];
      int y = cur.getY() + dir[i][1];
      int g = cur.getG() + 1;
      int h = _end.getManhattanDistance(Point(x, y));
      Local point_choose(x, y, g, h);
      checkLocal(point_choose, cur);
    }
  }
  _distance = -1;
}
void AStar::checkLocal(Local& local_tar, Local& local_cur)
{
  int x = local_tar.getX();
  int y = local_tar.getY();
  int g = local_tar.getG();
  int h = local_tar.getH();
  if (x < _legal.size() && x >= 0 && y < _legal[0].size() && y >= 0
      && _legal[x][y] && !close.find(local_tar))
  {
    bool inopen = false;
    for (std::multiset<Local>::iterator it = open.begin(); it != open.end();
        it++)
    {
      if (it->getX() == x && it->getY() == y)
      {
        inopen = true;
        if (it->getG() > g)
        {
          open.erase(it);
          open.insert(local_tar);
          _path_pre[local_tar] = local_cur;
          break;
        }
      }
    }
    if (!inopen)
    {
      open.insert(local_tar);
      _path_pre[local_tar] = local_cur;
    }
  }
}
void AStar::initPath()
{
  Point path_res = _end;
  while (!(path_res == _start))
  {
    _path_list.push_front(path_res);
    path_res = _path_pre[path_res];
  }
  _path_list.push_front(_start);
}
