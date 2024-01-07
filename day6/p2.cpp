#include <iostream>
#include <array>
#include <math.h>

using namespace std;

// Solution: finding integers that solves 0 < t_pressed + s/t_pressed < t_max
// t_pressed = velocity -> time moving = space/velocity = s/t_pressed
int main(int argc, char** argv) {
    long time {58819676};
    long distance {434104122191218};
    double sol1 = (time+sqrt(time * time - 4*distance))/2 ;
    double sol2= (time-sqrt(time * time - 4*distance))/2 ;
    // sol1 > sol2, so the solutions for the problem are in the range ceil(sol2) - round(sol1)
    cout << fixed << long(sol1) - ceill(sol2) + 1 << endl;
}