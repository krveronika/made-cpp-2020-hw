#pragma once
#include <cmath>
#include <vector>

const double tolerance = 1e-6;

struct Point
{
    double x;
    double y;
    
    Point(const double x = 0., const double y = 0.) : x(x), y(y) {}
    
    bool operator==(const Point &point) const
    {
        if (fabs(x - point.x) > tolerance)
            return false;
        else
            return (fabs(y - point.y) <= tolerance);
    }
    
    bool operator!=(const Point &point) const
    {
        return !(*this == point);
    }

    const Point& operator=(const Point &point)
    {
        x = point.x;
        y = point.y;
        return *this;
    }
    ~ Point () {}
};


double distance(const Point& a, const Point& b)
{
    return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y-b.y));
}

class Line
{
public:
    Point p1;
    Point p2;
    
    
    Line(const Point p1, const Point p2 ) : p1(p1), p2(p2) {}
    
    Line(Point q1, double alpha)
    {
        p1 = q1;
        // проходит через x = 0
        p2 = Point(0, q1.y - alpha * q1.x);
    }
    
    bool operator==(const Line &point) const
    {
        double x1 = p1.x, y1 = p1.y;
        double x2 = p2.x, y2 = p2.y;
        
        double x3 = point.p1.x, y3 = point.p1.y;
        double x4 = point.p2.x, y4 = point.p2.y;
        
        // вертикальная первая
        if (fabs(x1 - x2) <= tolerance)
        {
            return (fabs(x3 - x4) <= tolerance && fabs(x1 - x3) <= tolerance);
        }
        // вертикальная вторая, а первая наклонная
        else if (fabs(x3 - x4) <= tolerance)
        {
            return false;
        }
        // обе наклонные
        else
        {
            double m1 = (y1-y2)/(x1-x2);
            double m2 = (y3-y4)/(x3-x4);
            if (fabs(m1 - m2) > tolerance)
                return false;
            else
            {
                // либо параллельны, либо совпали
                double b2 = y3 - m2*x3;
                return (fabs(m2*x1 + b2 - y1) <= tolerance);
            }
        }
    }
    
    bool operator!=(const Line &point) const
    {
        return !(*this == point);
    }
    ~ Line () {}
};


class Shape
{
public:

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const Shape& another) const = 0;
    //virtual bool operator!=(const Shape& another) const = 0;
    virtual bool operator!=(const Shape& another) const
    {
        return !(*this == another);
    }
    // поворот на угол (в градусах, против часовой стрелки) относительно точки
    virtual void rotate(Point center, double angle) = 0;
    // симметрия относительно точки;
    virtual void reflex(Point center) = 0;
    // симметрия относительно прямой;
    virtual void reflex(Line axis) = 0;
    // гомотетия с коэффициентом coefficient и центром center
    virtual void scale(Point center, double coefficient) = 0;
    
    virtual ~Shape() = 0 ;
};

Shape::~Shape() {};

class Polygon : public Shape
{
protected:
    std::vector<Point> vertex;
    
public:
    Polygon() {}
    
    Polygon(std::vector<Point> vertices)
    {
        vertex = vertices;
    }
    
    size_t verticesCount() const
    {
        return vertex.size();
    }
    
    std::vector<Point> getVertices() const
    {
        return vertex;
    }
    
    virtual double perimeter()  const override
    {
        double p = 0;
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i)
        {
            size_t j = (i + 1)%size;
            p += distance(vertex[i], vertex[j]);
        }
        return p;
    }
    
    virtual double area()  const override
    {
        double a = 0.0;
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i)
        {
            size_t j = (i + 1)%size;
            a += 0.5 * (vertex[i].x * vertex[j].y -  vertex[j].x * vertex[i].y);
        }
        if (a < 0)
        {
            a = -a;
        }
        
        return a;
    }
    
    virtual bool operator==(const Shape& another)  const override
    {
        const Polygon* poly = dynamic_cast<const Polygon*>(&another);
        size_t size = verticesCount();
        if (poly->verticesCount() != size)
            return false;
        else
        {
            bool isStart = false;
            size_t j = 0;
            for (size_t i = 0; i < size; ++i)
            {
                if (vertex[i] == poly->vertex[0])
                {
                    isStart = true;
                    j = i;
                    if (size == 1)
                        return true;
                    break;
                }
            }
            
            if (isStart)
            {
                // прямой ход
                if (poly->vertex[1] == vertex[(j+1)%size])
                {
                    for (size_t i = 2; i < size; ++i)
                    {
                        if(poly->vertex[i] != vertex[(j+i)%size])
                            return false;
                    }
                    return true;
                }
                // обратный ход
                else if (poly->vertex.back() == vertex[(j+1)%size])
                {
                    for (size_t i = size - 2; i != 0 ; --i)
                    {
                        if(poly->vertex[i] != vertex[(size - i + j)%size])
                            return false;
                    }
                    return true;
                }
            }
        }
        return true;
    }
    
    
    virtual void rotate(Point center, double angle) override
    {
        double cos = std::cos(angle * M_PI / 180);
        double sin = std::sin(angle * M_PI / 180);
        double temp;
        size_t size = verticesCount();
        for (size_t i = 0; i < size;  ++i)
        {
            temp = ((vertex[i].x-center.x)*cos - (vertex[i].y-center.y)*sin) + center.x;
            vertex[i].y = ((vertex[i].x-center.x)*sin + (vertex[i].y-center.y)*cos) + center.y;
            vertex[i].x = temp;
        }
        return;
    }

    virtual void reflex(Point center) override
    {
        size_t size = verticesCount();
        for (size_t i = 0; i < size;  ++i)
        {
            vertex[i].y = 2*center.y - vertex[i].y;
            vertex[i].x = 2*center.x - vertex[i].x;
        }
        return;
        
    }

    // формула из https://zenodo.org/record/3972078#.X6m9AC1eOqQ
    virtual void reflex(Line axis) override
    {
        double ak,bk,ck;
        size_t size = verticesCount();
        for (size_t i = 0; i < size;  ++i)
        {
            ak = axis.p1.y - axis.p2.y;
            bk = axis.p2.x - axis.p1.x;
            ck = - (ak*axis.p1.x +bk*axis.p1.y);
            vertex[i].x = -(ak*ak + bk*bk) *vertex[i].x -2 *ck * ak;
            vertex[i].y = -(ak*ak + bk*bk) *vertex[i].y -2 *ck * bk;
        }
        return;
    }

    virtual void scale(Point center, double coefficient) override
    {
        size_t size = verticesCount();
        for (size_t i = 0; i < size;  ++i)
        {
            vertex[i].x = center.x + coefficient * (vertex[i].x - center.x);
            vertex[i].y = center.y + coefficient * (vertex[i].y - center.y);
        }
        return;
    }
    
    virtual ~ Polygon() {}
};

class Ellipse : public Shape
{
public:
    Ellipse(){};
    Ellipse(const Point &q1, const Point &q2);
    Ellipse(const double focus1, const double focus2, const double sum);
    
    // фокусы
    std::pair<Point,Point> focuses(){
        std::pair<Point,Point> res;
        return res;
    }
    
    //эксцентриситет
    double eccentricity()
    {
        return 0;
    }
    
    //центр
    Point center()
    {
        return Point();
    }
    
    
    virtual ~ Ellipse() {}
};

class Circle : public Ellipse
{
    Point c;
    double r;
public:
    Circle(const Point &center, double radius) : c(center), r(radius) {}
    
    // радиус
    const double& radius()
    {
        return r;
    }
    double perimeter() const override
    {
        return 2*M_PI*r;
    }
    double area() const override
    {
        return M_PI * r* r;
    }
    bool operator==(const Shape& another) const override
    {
        const Circle* circle = dynamic_cast<const Circle*>(&another);
        return ( (circle->c == c) and fabs(circle->r - r) <= tolerance );
    }
    
    void rotate(Point center, double angle) override
    {
        double cos = std::cos(angle * M_PI / 180);
        double sin = std::sin(angle * M_PI / 180);
        double temp = ((c.x - center.x)*cos - (c.y-center.y)*sin) + center.x;
        c.y = ((c.x-center.x)*sin + (c.y-center.y)*cos) + center.y;
        c.x = temp;
        return;
    }
    
    void reflex(Point center) override
    {
        c.y = 2*center.y - c.y;
        c.x = 2*center.x - c.x;
    }
    
    void reflex(Line axis) override
    {
        double ak,bk,ck;
        ak = axis.p1.y - axis.p2.y;
        bk = axis.p2.x - axis.p1.x;
        ck = - (ak*axis.p1.x +bk*axis.p1.y);
        c.x = -(ak*ak + bk*bk) *c.x -2 *ck * ak;
        c.y = -(ak*ak + bk*bk) *c.y -2 *ck * bk;
        return;
    }
    
    void scale(Point center, double coefficient) override
    {
        c.x = center.x + coefficient * (c.x - center.x);
        c.y = center.y + coefficient * (c.y - center.y);
        return;
    }
    
    ~ Circle() {}
};

class Rectangle : public Polygon
{
public:
    Rectangle(){}
    Rectangle(const Point &q1, const Point &q2, const double s)
    {
        vertex[0] = Point();
        vertex[1] = Point();
        vertex[2] = Point();
        vertex[3] = Point();
    }
    
    // центр
    Point center()
    {
        return Point(0.5*(vertex[0].x + vertex[0].x),0.5*(vertex[0].y + vertex[0].y));
    }
    
    // диагонали
    std::pair<Line, Line> diagonals()
    {
        Line d1(vertex[0], vertex[2]);
        Line d2(vertex[1], vertex[3]);
        return std::make_pair(d1, d2);
    }
    
    ~ Rectangle() {}
};

class Square : public Rectangle
{
public:
    Square(const Point &q1, const Point &q2)
    {
        vertex[0] = q1;
        vertex[1] = Point(q1.x, q2.y);
        vertex[2] = q2;
        vertex[3] = Point(q2.x, q1.y);
    }
    
    Circle circumscribedCircle()
    {
        double a = distance(vertex[0], vertex[1]);
        return Circle(center(), 2*a);
    }
    
    Circle inscribedCircle();
    ~ Square() {}
};

class Triangle : public Polygon
{
public:
    Circle circumscribedCircle();
    Circle inscribedCircle();
    //центр масс
    Point centroid();
    //ортоцентр
    Point orthocenter();
    //прямая Эйлера
    Line EulerLine();
    //окружность Эйлера
    Circle ninePointsCircle();
    
    ~Triangle(){}
};
