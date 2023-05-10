
#ifndef COWBOY_VS_NINJA_A_POINT_HPP
#define COWBOY_VS_NINJA_A_POINT_HPP


class Point {

    double x;
    double y;

public:

    Point(double x, double y) : x(x), y(y) {}

    double distance(Point &point);

    void print() const;

    static Point moveTowards(Point &source, Point &dest, double dist);

    ~Point();

    [[nodiscard]] double getX() const;

    [[nodiscard]] double getY() const;
};


#endif //COWBOY_VS_NINJA_A_POINT_HPP
