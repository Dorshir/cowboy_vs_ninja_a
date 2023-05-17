
#ifndef COWBOY_VS_NINJA_A_POINT_HPP
#define COWBOY_VS_NINJA_A_POINT_HPP


class Point {

    double x;
    double y;

public:

    Point(double newX, double newY) : x(newX), y(newY) {}

    double distance(Point &point);

    void print() const;

    static Point moveTowards(Point &source, Point &dest, double dist);

    ~Point() = default;

    [[nodiscard]] double getX() const;

    [[nodiscard]] double getY() const;

    // Copy constructor
    Point(const Point& other) = default;

    // Copy assignment operator
    Point& operator=(const Point& other) = default;

    // Move constructor
    Point(Point&& other) = default;

    // Move assignment operator
    Point& operator=(Point&& other) = default;
    
};


#endif //COWBOY_VS_NINJA_A_POINT_HPP
