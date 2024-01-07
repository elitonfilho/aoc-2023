#include <iostream>
#include <array>
#include <math.h>

using namespace std;

// Solution: finding integers that solves 0 < t_pressed + s/t_pressed < t_max
// t_pressed = velocity -> time moving = space/velocity = s/t_pressed
int main(int argc, char** argv) {
    array<int,4> time {58, 81, 96, 76};
    array<int,4> distance {434, 1041, 2219, 1218};
    int solution = 1;
    // solving t^2 -t_m*t+s = 0
    for (int i = 0; i < 4; i++){
        double sol1 = (time[i]+sqrt(time[i] * time[i] - 4*distance[i]))/2 ;
        double sol2= (time[i]-sqrt(time[i] * time[i] - 4*distance[i]))/2 ;
        // sol1 > sol2, so the solutions for the problem are in the range ceil(sol2) - round(sol1)
        solution *= int(sol1) - ceill(sol2) + 1;
    }
    cout << solution ;
}