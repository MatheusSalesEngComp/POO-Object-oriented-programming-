#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
using namespace std;

template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

class Point {
private:
    double x;
    double y;

public:
    Point(double x=0, double y=0): x(x), y(y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }
    string toString() const {
        stringstream ss;
        ss << fixed << setprecision(2) << "(" << x << ", " << y << ")";
        return ss.str();
    }
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual string getName() const = 0;
    virtual bool inside(const Point& point) const = 0;
    virtual string toString() const = 0;
};

class Circle : public Shape {
private:
    Point center;
    double radius;

public:
    Circle(Point center = Point(0, 0), double radius = 0.0)
        : center(center), radius(radius) {}

    double getArea() const override {
        return M_PI * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }

    string getName() const override {
        return "Circ";
    }

    bool inside(const Point& point) const override {
        double dx = point.getX() - center.getX();
        double dy = point.getY() - center.getY();
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    string toString() const override {
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << "Circ: C=" << center.toString() << "," << " R=" << radius;
        return ss.str();
    }
};


class Rectangle : public Shape {
private:
    Point p1;
    Point p2;

public:
    Rectangle(const Point p1= Point(0,0), const Point p2= Point(0,0))
        : p1(p1), p2(p2) {}

    double getArea() const override {
        return abs(p2.getX() - p1.getX()) * abs(p2.getY() - p1.getY());
    }

    double getPerimeter() const override {
        return 2 * (abs(p2.getX() - p1.getX()) + abs(p2.getY() - p1.getY()));
    }

    bool inside(const Point& point) const override {
        return (point.getX() >= p1.getX() && point.getX() <= p2.getX() &&
                point.getY() >= p1.getY() && point.getY() <= p2.getY());
    }

    string getName() const override { 
        return "Rect";
    }

    string toString() const override { 
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << "Rect: P1=" << p1.toString() << " P2=" << p2.toString();
        return ss.str();
    }
};


int main() {
    vector<shared_ptr<Shape>> shapes;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")  { 
            break;                                  
        }
        else if (cmd == "show") { 
            // Imprima as formas, uma por linha
            for (const auto& shape : shapes) {
                cout << shape->toString() << endl;
            }
        }
        else if (cmd == "circle") { 
            // Crie um novo circulo e adicione ao vetor
            double x{}, y{}, radius{};
            ss >> x >> y >> radius;
            shapes.push_back(make_shared<Circle>(Point(x, y), radius));
        }
        else if (cmd == "rect") {
            // Crie um retangulo e insira no vetor
            double x1{}, y1{}, x2{}, y2{};
            ss >> x1 >> y1 >> x2 >> y2;
            shapes.push_back(make_shared<Rectangle>(Point(x1, y1), Point(x2, y2)));        }
        else if (cmd == "info") {
            // Imprima as informações de área e perímetro de todas as formas
            for (const auto& shape : shapes) {
                cout << fixed << setprecision(2);
                cout << shape->getName() << ": ";
                cout << "A=" << shape->getArea() << " ";
                cout << "P=" << shape->getPerimeter() << endl;
            }
        }
        else {
            cout << "fail: comando inválido" << '\n';
        }
    }
}
