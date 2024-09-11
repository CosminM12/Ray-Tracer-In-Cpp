#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

class Interval {
public:
    double min, max;

    Interval() : min(+infinity), max(-infinity) {}
    Interval(double min, double max) : min(min), max(max) {}


    double size() const {
        return max - min;
    }

    bool contains(double x) const { //between 2 margins (inclusive)
        return min <= x && x <= max;
    }

    bool surrounds(double x) const { //between 2 margins (exclusive) --is negated to verify if the value is outside the parameters
        return min < x && x < max;
    }

    double clamp(double x) const {  //returns x value clampped between min and max;
        if(x < min) return min;
        if(x > max) return max;
        return x;
    }


    static const Interval empty, universe; 
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif