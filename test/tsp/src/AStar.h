/***************************
 *    A��Ѱ·�㷨
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

//���Ժ�
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
 *    Point��
 *    ��ʾһ����ά����
 ****************************/
class Point
{
SYNTHESIZE(int, _x, X)
  ;SYNTHESIZE(int, _y, Y)
  ;
 public:
  Point();
  Point(int x, int y);
  //��������پ���
  int getManhattanDistance(const Point& t) const;
  //���ŷ����þ���
  double getEuclidDistance(const Point& t) const;
  bool operator==(const Point& t) const;
  bool operator<(const Point& t) const;

  virtual ~Point() { }
};

/***************************
 *    Local��
 *    ��A��Ѱ·�㷨�еĵ�λ����
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
 *    SuperCloseList�� ������
 *    Close�б�Ļ���
 *    ��Ϊʵ��Close�б��ڲ�ͬ�����в�ͬ��ʵ��
 *    ��Ҫ�̳д���
 ****************************/
class SuperCloseList
{
 public:
  //����close�б�
  virtual void insert(const Local& p) = 0;
  //��ѯclose�б����Ƿ��Ѵ��ڴ�����
  virtual bool find(const Local& p) const = 0;

  virtual ~SuperCloseList() { }
};

/***************************
 *    CloseList��
 *    Close�б�Ĺ�ϣʵ��
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
  //���������ڴ�
  void newClose(int x, int y);
};

/***************************
 *    A���㷨��
 *    ʵ��A���㷨���߼�
 ****************************/
class AStar
{
 public:
  AStar(std::vector<std::vector<bool> >& legal, Point& start, Point& end);
  //��þ���
  int getDistance() const;
  //���·��
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
  //·���滮���㷨�ĺ���
  void pathPlanning();
  //�������
  void checkLocal(Local& local_tar, Local& local_cur);
  //����·��
  void initPath();
};

#endif
