/***************************
 *    A星寻路算法
 *
 *    Anti-Magic
 *    2014/5/26
 ****************************/

#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <map>
#include <set>
#include <vector>
#include <list>

//属性宏
#define SYNTHESIZE(varType, varName, funName) \
protected: \
    varType varName; \
public: \
virtual varType get##funName(void) const { \
    return varName; \
} \
virtual void set##funName(varType var) { \
    varName = var; \
}

/***************************
 *    Point类
 *    表示一个二维坐标
 ****************************/
class Point
{
SYNTHESIZE(int, _x, X)
  ;SYNTHESIZE(int, _y, Y)
  ;
 public:
  Point();
  Point(int x, int y);
  //获得曼哈顿距离
  int getManhattanDistance(const Point& t) const;
  //获得欧几里得距离
  double getEuclidDistance(const Point& t) const;
  bool operator==(const Point& t) const;
  bool operator<(const Point& t) const;

  virtual ~Point() { }
};

/***************************
 *    Local类
 *    在A星寻路算法中的单位区域
 ****************************/
class Local : public Point
{
SYNTHESIZE(int, _g, G)
  ;SYNTHESIZE(int, _h, H)
  ;
 public:
  Local();
  Local(int x, int y, int g, int h);
  Local(const Point& t, int g, int h);
  Local(const Local& t);
  int getF() const;
  bool operator<(const Local& t) const;
};

/***************************
 *    SuperCloseList类 抽象类
 *    Close列表的基类
 *    因为实现Close列表在不同场合有不同的实现
 *    需要继承此类
 ****************************/
class SuperCloseList
{
 public:
  //插入close列表
  virtual void insert(const Local& p) = 0;
  //查询close列表中是否已存在此区域
  virtual bool find(const Local& p) const = 0;

  virtual ~SuperCloseList() { }
};

/***************************
 *    CloseList类
 *    Close列表的哈希实现
 ****************************/
class CloseList : public SuperCloseList
{
 public:
  CloseList();
  CloseList(int x, int y);
  ~CloseList();
  void insert(const Local& p) override;
  bool find(const Local& p) const override;
 private:
  bool** _close;
  int size_x, size_y;
  //申请数组内存
  void newClose(int x, int y);
};

/***************************
 *    A星算法类
 *    实现A星算法的逻辑
 ****************************/
class AStar
{
 public:
  AStar(std::vector<std::vector<bool> >& legal, Point& start, Point& end);
  //获得距离
  int getDistance() const;
  //获得路径
  std::list<Point> getPath() const;
 private:
  std::vector<std::vector<bool> > _legal;
  std::multiset<Local> open;
  CloseList close;
  Point _start;
  Point _end;
  std::map<Point, Point> _path_pre;
  std::list<Point> _path_list;
  int _distance;
  //路径规划，算法的核心
  void pathPlanning();
  //检查区域
  void checkLocal(Local& local_tar, Local& local_cur);
  //生成路径
  void initPath();
};

#endif
