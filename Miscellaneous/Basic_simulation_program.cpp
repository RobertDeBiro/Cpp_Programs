/*

The program simulates the motion of a projectile (e.g. a ball or a rock) launched from a given initial position and velocity, and at a given angle. The program prompts the user to input the initial position, velocity and angle of the projectile. It then uses basic physics equations to calculate the horizontal and vertical velocities of the projectile and updates the position of the projectile in each time step. The program continues to update the position of the projectile and print the current position until the projectile reaches the ground. This simulation can teach beginners about basic physics concepts such as kinematics, and how to use these concepts to simulate the motion of an object in code.

*/

#include <iostream>
#include <cmath>

const double g = 9.81;  // acceleration due to gravity

class Projectile {
 public:
    double x, y, vx, vy;

    Projectile(double x, double y, double vx, double vy)
        : x(x), y(y), vx(vx), vy(vy) {}

    void update(double dt) {
        x += vx * dt;
        y += vy * dt;
        vy -= g * dt;
    }
};

int main() {
    double x, y, v, theta;
    std::cout << "Enter the initial position (x y): ";
    std::cin >> x >> y;
    std::cout << "Enter the initial velocity (m/s) and angle (degrees): ";
    std::cin >> v >> theta;

    theta = theta * M_PI / 180.0;  // convert degrees to radians
    double vx = v * cos(theta);
    double vy = v * sin(theta);

    Projectile projectile(x, y, vx, vy);

    double t = 0;
    double dt = 0.01;
    while (projectile.y >= 0) {
        std::cout << "t = " << t << ": x = " << projectile.x
                  << ", y = " << projectile.y << std::endl;
        projectile.update(dt);
        t += dt;
    }

    return 0;
}
