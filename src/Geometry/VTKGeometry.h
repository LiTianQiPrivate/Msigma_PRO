#ifndef VTKGEOMETRY_H
#define VTKGEOMETRY_H
#include "Point3D.h"
#include "vtkPolyData.h"
#include "vtkOBBTree.h"
#include "Common.h"
#include "vtkCleanPolyData.h"
#include "kdtree.h"
#include <vtkCell.h>
#include <vtkCellData.h>
#include <QString>
#include <QColor>

#define PI 3.1415926
class VTKGeometry
{
public:
    VTKGeometry();
    static void pointMappingPlane(Point3D p, Normal mapNormal, Point3D origin, Normal normal, Point3D& outP);
    static float vec3dot(Normal a, Normal b);
    static double getAngleDegOf2Vec(Normal v1, Normal v2);
    static void cross_Product(double a[3], double b[3], double out[3]);
    static void cross_Product(const Normal& a, const Normal& b, Normal& out);
    static std::vector<Point3D> calIntersectPolydata(Point3D p1 , Point3D p2, vtkPolyData* polydata, VSP<vtkOBBTree> tree = NULL); // 求交点
    static Point3D calIntersectPolydataSingle(Point3D p, Normal n, vtkPolyData* polydata, VSP<vtkOBBTree> tree = NULL);
    static void transformationObjectData(double m[], vtkPolyData *object); // 将模型变化到当前矩阵
    static void transformationCurveData(double m[], std::vector<Point3D>& fittingPoints); // 将点集变换到当前矩阵
    static void transformationNormal(double m[], Normal &n); // 变换种植位的法相
    static void transformationObjectData(vtkMatrix4x4* m, vtkPolyData *object);
    static void transformationCurveData(vtkMatrix4x4* m, std::vector<Point3D>& fittingPoints);
    static void transformationNormal(vtkMatrix4x4* m, Normal &n); // 变换种植位的法相
    static void moveObject(vtkPolyData* polydata, Normal n);
    static void movePoints(std::vector<Point3D>& points, Normal n);
    static void calBounds(vtkPolyData *object, double* box); // 计算包围盒，vtk函数有时不好使
    static void findAllBorder(vtkPolyData *object, vtkCleanPolyData* cleanPolyData); // 查找所有边，返回的是存储边的数据结构
    static std::vector<Point3D> findNearestBorder(vtkCleanPolyData* cleanPolyData, Point3D p); // 查找模型最近的边
    static void rotatePoint(Normal axis, double angle, Point3D center, std::vector<Point3D> &inputPoints);
    static void getRotateMatrix(Normal axis, double angle, Point3D center, vtkMatrix4x4* outputM);
    static void GetRoteTransMatrix(float A[], float dir[], float roteangle, custom::matrix &result);
    static int getLoopMinDist(Point3D p, std::vector<Point3D> &loop, kdtree* kdTree = NULL);
    static std::vector<Point3D> calPolyData2DHull_Z(vtkPolyData *object);
    static std::vector<Point3D> calPolyData2DHull_Y(vtkPolyData *object);
    static std::vector<Point3D> calPolyData2DHull_X(vtkPolyData *object);
    static void fittedCurve(std::vector<Point3D> curve, std::vector<Point3D> &newCurve, double dist, bool v = true);
    static void sparsePoints(std::vector<Point3D> points, std::vector<Point3D> &newPoints, double dist);
    static void offsetLoop(std::vector<Point3D> currentLoop, double d, std::vector<std::vector<Point3D> > &outLoops);
    static void genDelaunay(std::vector<Point3D> allpoints, vtkPolyData* polydata);
    static void outputPtList(const std::vector<Point3D> &pts, std::string fileName);
    static Normal unitOrthoVec(Normal srcVec);
    static void constructCoordinateByZAxle(const Normal &zDir, Normal &xDir, Normal &yDir);
    static Point3D findPointsMinDist(std::vector<Point3D> points, Point3D inputP);
    static void makeTriangles(std::vector<std::vector<Point3D>> points, vtkPolyData *polyData, bool isClose = false); // 多排点构建网格
    static QColor getRandomColor();
};

#endif // VTKGEOMETRY_H
