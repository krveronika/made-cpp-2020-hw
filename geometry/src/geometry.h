#pragma once
#include <cmath>
#include <vector>

const double tolerance = 1e-6;

bool equals(const double first, const double second) {
    return fabs(first - second) <= tolerance;
}

struct Point {
    double x;
    double y;
    
    Point(const double x = 0., const double y = 0.) : x(x), y(y) {}
    
    bool operator==(const Point &point) const {
        if (!equals(x, point.x))
            return false;
        else
            return equals(y, point.y);
    }
    
    bool operator!=(const Point &point) const { return !(*this == point); }
    
    const Point &operator=(const Point &point) {
        x = point.x;
        y = point.y;
        return *this;
    }
    
    const Point &rotate(const Point &center, const double &cos,
                        const double &sin) {
        double temp;
        temp = ((x - center.x) * cos - (y - center.y) * sin) + center.x;
        y = ((x - center.x) * sin + (y - center.y) * cos) + center.y;
        x = temp;
        return *this;
    }
    
    const Point &reflex(const Point &center) {
        y = 2 * center.y - y;
        x = 2 * center.x - x;
        return *this;
    }
    
    const Point &reflex(const Point &p1, const Point &p2) {
        double ak, bk, ck;
        ak = p1.y - p2.y;
        bk = p2.x - p1.x;
        ck = -(ak * p1.x + bk * p1.y);
        double temp = x;
        x = ((bk * bk - ak * ak) * x - 2 * ak * bk * y - 2 * ck * ak) /
        (ak * ak + bk * bk);
        y = ((ak * ak - bk * bk) * y - 2 * ak * bk * temp - 2 * ck * bk) /
        (ak * ak + bk * bk);
        return *this;
    }
    
    const Point &scale(const Point &center, const double &coefficient) {
        x = center.x + coefficient * (x - center.x);
        y = center.y + coefficient * (y - center.y);
        return *this;
    }
    
    ~Point() {}
};

double distance(const Point &a, const Point &b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

class Line {
public:
    Point p1;
    Point p2;
    
    Line(const Point p1, const Point p2) : p1(p1), p2(p2) {}
    
    Line(double k, double b) {
        p1 = Point(0, b);
        p2 = Point(10, 10 * k + b);
    }
    
    Line(Point q1, double alpha) {
        p1 = q1;
        // проходит через x = 0, y = b = y1-alpha*x1
        p2 = Point(0, q1.y - alpha * q1.x);
    }
    
    bool operator==(const Line &point) const {
        double x1 = p1.x, y1 = p1.y;
        double x2 = p2.x, y2 = p2.y;
        
        double x3 = point.p1.x, y3 = point.p1.y;
        double x4 = point.p2.x, y4 = point.p2.y;
        
        // вертикальная первая
        if (equals(x1, x2)) {
            return (equals(x3, x4) && equals(x1, x3));
        }
        // вертикальная вторая, а первая наклонная
        else if (equals(x3, x4)) {
            return false;
        }
        // обе наклонные
        else {
            double m1 = (y1 - y2) / (x1 - x2);
            double m2 = (y3 - y4) / (x3 - x4);
            if (!equals(m1, m2))
                return false;
            else {
                // либо параллельны, либо совпали b1=b2 => y1-m2*x1 = b2
                double b2 = y3 - m2 * x3;
                return equals(y1 - m2 * x1, b2);
            }
        }
    }
    
    bool operator!=(const Line &point) const { return !(*this == point); }
    ~Line() {}
};

class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const Shape &another) const = 0;
    // virtual bool operator!=(const Shape& another) const = 0;
    virtual bool operator!=(const Shape &another) const {
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
    
    virtual ~Shape() = 0;
};

Shape::~Shape(){};

class Polygon : public Shape {
protected:
    std::vector<Point> vertex;
    
public:
    Polygon() {}
    
    Polygon(std::vector<Point> vertices) : vertex(vertices) {}
    
    size_t verticesCount() const { return vertex.size(); }
    
    std::vector<Point> getVertices() const { return vertex; }
    
    virtual double perimeter() const override {
        double p = 0;
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i) {
            size_t j = (i + 1) % size;
            p += distance(vertex[i], vertex[j]);
        }
        return p;
    }
    
    virtual double area() const override {
        double a = 0.0;
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i) {
            size_t j = (i + 1) % size;
            a += 0.5 * (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
        }
        if (a < 0) {
            a = -a;
        }
        
        return a;
    }
    
    virtual bool operator==(const Shape &another) const override {
        const Polygon *poly = dynamic_cast<const Polygon *>(&another);
        size_t size = verticesCount();
        if (poly->verticesCount() != size)
            return false;
        else if (!equals(poly->perimeter(), perimeter()))
            return false;
        else if (!equals(poly->area(), area()))
            return false;
        else {
            bool isStart = false;
            size_t j = 0;
            for (size_t i = 0; i < size; ++i) {
                if (vertex[i] == poly->vertex[0]) {
                    isStart = true;
                    j = i;
                    if (size == 1)
                        return true;
                    break;
                }
            }
            
            if (isStart) {
                // прямой ход
                if (poly->vertex[1] == vertex[(j + 1) % size]) {
                    for (size_t i = 2; i < size; ++i) {
                        if (poly->vertex[i] != vertex[(j + i) % size])
                            return false;
                    }
                    return true;
                }
                // обратный ход
                else if (poly->vertex.back() == vertex[(j + 1) % size]) {
                    for (size_t i = size - 2; i != 0; --i) {
                        if (poly->vertex[i] != vertex[(size - i + j) % size])
                            return false;
                    }
                    return true;
                }
            }
        }
        return true;
    }
    
    virtual void rotate(Point center, double angle) override {
        double cos = std::cos(angle * M_PI / 180);
        double sin = std::sin(angle * M_PI / 180);
        
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i) {
            vertex[i] = vertex[i].rotate(center, cos, sin);
        }
        return;
    }
    
    virtual void reflex(Point center) override {
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i) {
            vertex[i] = vertex[i].reflex(center);
        }
        return;
    }
    
    virtual void reflex(Line axis) override {
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i) {
            vertex[i] = vertex[i].reflex(axis.p1, axis.p2);
        }
        return;
    }
    
    virtual void scale(Point center, double coefficient) override {
        size_t size = verticesCount();
        for (size_t i = 0; i < size; ++i) {
            vertex[i] = vertex[i].scale(center, coefficient);
        }
        return;
    }
    
    virtual ~Polygon() {}
};

class Ellipse : public Shape {
protected:
    Point focus1;
    Point focus2;
    double sum;
    
public:
    Ellipse(){};
    Ellipse(const Point focus1, const Point focus2, const double sum)
    : focus1(focus1), focus2(focus2), sum(sum) {}
    
    std::pair<Point, Point> focuses() const {
        return std::make_pair(focus1, focus2);
    }
    
    Point center() const {
        return Point(0.5 * (focus1.x + focus2.x), 0.5 * (focus1.y + focus2.y));
    }
    
    double eccentricity() const { return 2 * distance(center(), focus1) / sum; }
    
    virtual double perimeter() const override {
        double a = sum / 2;
        double c = distance(center(), focus2);
        double b = std::sqrt(a * a - c * c);
        return M_PI * (3 * (a + b) - std::sqrt((3 * a + b) * (a + 3 * b)));
    }
    
    virtual double area() const override {
        double a = sum / 2;
        double c = distance(center(), focus2);
        double b = std::sqrt(a * a - c * c);
        return M_PI * a * b;
    }
    
    virtual bool operator==(const Shape &another) const override {
        const Ellipse *ellipse = dynamic_cast<const Ellipse *>(&another);
        if (equals(ellipse->sum, sum)) {
            return equals(distance(ellipse->focus1, ellipse->focus2),
                          distance(focus1, focus2));
        }
        return false;
    }
    
    virtual void rotate(Point center, double angle) override {
        double cos = std::cos(angle * M_PI / 180);
        double sin = std::sin(angle * M_PI / 180);
        focus1 = focus1.rotate(center, cos, sin);
        focus2 = focus2.rotate(center, cos, sin);
        return;
    }
    
    virtual void reflex(Point center) override {
        focus1 = focus1.reflex(center);
        focus2 = focus2.reflex(center);
        return;
    }
    
    // формула из https://zenodo.org/record/3972078#.X6m9AC1eOqQ
    virtual void reflex(Line axis) override {
        focus1 = focus1.reflex(axis.p1, axis.p2);
        focus2 = focus2.reflex(axis.p1, axis.p2);
        
        return;
    }
    
    virtual void scale(Point center, double coefficient) override {
        focus1 = focus1.scale(center, coefficient);
        focus2 = focus2.scale(center, coefficient);
        sum *= coefficient;
        return;
    }
    
    virtual ~Ellipse() {}
};

class Circle : public Ellipse {
private:
    Point c;
    double r;
    
public:
    Circle(const Point &center, double radius) : c(center), r(radius) {
        focus1 = Point(radius, 0);
        focus2 = Point(-radius, 0);
        sum = 2 * radius;
    }
    
    const double &radius() const { return r; }
    
    const Point &center() const { return c; }
    
    double perimeter() const override { return 2 * M_PI * r; }
    double area() const override { return M_PI * r * r; }
    
    void rotate(Point center, double angle) override {
        Ellipse::rotate(center, angle);
        double cos = std::cos(angle * M_PI / 180);
        double sin = std::sin(angle * M_PI / 180);
        c = c.rotate(center, cos, sin);
        return;
    }
    
    void reflex(Point center) override {
        Ellipse::reflex(center);
        c = c.reflex(center);
    }
    
    void reflex(Line axis) override {
        Ellipse::reflex(axis);
        
        c = c.reflex(axis.p1, axis.p2);
        return;
    }
    
    void scale(Point center, double coefficient) override {
        Ellipse::scale(center, coefficient);
        c = c.scale(center, coefficient);
        r *= coefficient;
        return;
    }
    
    ~Circle() {}
};

class Rectangle : public Polygon {
public:
    Rectangle() { vertex.resize(4); }
    
    Rectangle(Point q1, Point q2, double s) {
        if (s > 1)
            s = 1 / s;
        if (q1.x > q2.x)
            std::swap(q1, q2);
        
        vertex.resize(4);
        vertex[0] = q1;
        vertex[2] = q2;
        
        double sin = std::sqrt(1 / (1 + s * s));
        double cos = std::sqrt(1 - sin * sin);
        vertex[1] = q2.rotate(q1, cos, sin);
        q2 = vertex[2];
        vertex[3] = q2.rotate(q1, cos, -sin);
    }
    
    // центр
    Point center() {
        return Point(0.5 * (vertex[0].x + vertex[0].x),
                     0.5 * (vertex[0].y + vertex[0].y));
    }
    
    // диагонали
    std::pair<Line, Line> diagonals() {
        Line d1(vertex[0], vertex[2]);
        Line d2(vertex[1], vertex[3]);
        return std::make_pair(d1, d2);
    }
    
    ~Rectangle() {}
};

class Square : public Rectangle {
public:
    Square(const Point &q1, const Point &q2) { Rectangle::Rectangle(q1, q2, 1); }
    
    // описанная
    Circle circumscribedCircle() {
        double a = distance(vertex[0], vertex[1]);
        return Circle(center(), a * std::sqrt(2));
    }
    
    Circle inscribedCircle() {
        double a = distance(vertex[0], vertex[1]);
        return Circle(center(), 0.5 * a);
    }
    
    bool operator==(const Shape &another) const override {
        const Square *sq = dynamic_cast<const Square *>(&another);
        return equals(distance(sq->vertex[0], sq->vertex[1]),
                      distance(vertex[0], vertex[1]));
    }
    ~Square() {}
};

class Triangle : public Polygon {
public:
    Triangle(const Point &a, const Point &b, const Point &c) {
        vertex.resize(3);
        vertex[0] = a;
        vertex[1] = b;
        vertex[2] = c;
    }
    
    const double circumscribedRadius() const {
        double a = distance(vertex[0], vertex[1]);
        double b = distance(vertex[1], vertex[2]);
        double c = distance(vertex[0], vertex[2]);
        double p = 0.5 * (a + b + c);
        if (a + b >= c && b + c >= a && a + c >= b) {
            double R =
            0.25 * a * b * c / (std::sqrt(p * (p - a) * (p - b) * (p - c)));
            return R;
        } else {
            std::cerr << "Такой треугольник не существует\n";
        }
        return -1;
    }
    
    // Формулы https://www.wikiwand.com/ru/Описанная_окружность
    Circle circumscribedCircle() {
        double ax = vertex[0].x, ay = vertex[0].y;
        double bx = vertex[1].x, by = vertex[1].y;
        double cx = vertex[2].x, cy = vertex[2].y;
        double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
        double ux =
        ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) +
         (cx * cx + cy * cy) * (ay - by)) /
        d;
        double uy =
        ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) +
         (cx * cx + cy * cy) * (bx - ax)) /
        d;
        double r = circumscribedRadius();
        return Circle(Point(ux, uy), r);
    }
    
    const double inscribedRadius() const {
        double s = area();
        double a = distance(vertex[0], vertex[1]);
        double b = distance(vertex[1], vertex[2]);
        double c = distance(vertex[0], vertex[2]);
        double p = a + b + c;
        if (a + b >= c && b + c >= a && a + c >= b) {
            double r = 2 * s / p;
            return r;
        } else {
            std::cerr << "Такой треугольник не существует\n";
        }
        return -1;
    }
    
    Circle inscribedCircle() const {
        double a = distance(vertex[0], vertex[1]);
        double b = distance(vertex[1], vertex[2]);
        double c = distance(vertex[0], vertex[2]);
        double p = a + b + c;
        double ax = vertex[0].x, ay = vertex[0].y;
        double bx = vertex[1].x, by = vertex[1].y;
        double cx = vertex[2].x, cy = vertex[2].y;
        double ux = (a * cx + b * ax + c * bx) / p;
        double uy = (a * cy + b * ay + c * by) / p;
        double R = inscribedRadius();
        return Circle(Point(ux, uy), R);
    }
    
    Point centroid() const {
        double ox = (vertex[0].x + vertex[1].x + vertex[2].x) / 3;
        double oy = (vertex[0].y + vertex[1].y + vertex[2].y) / 3;
        return Point(ox, oy);
    }
    
    //ортоцентр c
    //https://www.quora.com/What-is-the-orthocentre-of-a-triangle-when-the-vertices-are-x1-y1-x2-y2-x3-y3
    Point orthocenter() const {
        double x1 = vertex[0].x, y1 = vertex[0].y;
        double x2 = vertex[1].x, y2 = vertex[1].y;
        double x3 = vertex[2].x, y3 = vertex[2].y;
        double x = ((x2 * (x1 - x3) + y2 * (y1 - y3)) * (y3 - y2) -
                    (x1 * (x2 - x3) + y1 * (y2 - y3)) * (y3 - y1)) /
        ((x3 - x2) * (y3 - y1) - (y3 - y2) * (x3 - x1));
        double y = ((x2 * (x1 - x3) + y2 * (y1 - y3)) * (x3 - x2) -
                    (x1 * (x2 - x3) + y1 * (y2 - y3)) * (x3 - x1)) /
        ((y3 - y2) * (x3 - x1) - (x3 - x2) * (y3 - y1));
        return Point(x, y);
    }
    
    //прямая Эйлера
    Line EulerLine() const {
        return Line(Triangle::centroid(), Triangle::orthocenter());
    }
    
    //окружность Эйлера
    Circle ninePointsCircle() {
        Circle c = circumscribedCircle();
        Point o = orthocenter();
        Point point = c.center();
        double r = c.radius();
        return Circle(Point(0.5 * (o.x + point.x), 0.5 * (o.y + point.y)), r * 0.5);
    }
    
    ~Triangle() {}
};
