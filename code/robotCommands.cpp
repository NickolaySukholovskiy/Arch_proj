#include "robotCommands.hpp"

void finite_state_machine(Camera cam) {

    int angle = cam.getAngle();
    int distance = cam.getDistanceTarget();
    int action = 1;

    if (distance > 3) {
        if (angle <= 5 && angle >= -5) {
            std::cout << "Robot goes straight\n";
        }
        else if (angle < -5) {
            //turn left
            std::cout << "Robot turns left\n";
        }
        else if (angle > 5) {
            //turn right
            std::cout << "Robot turns right\n";
        }
    }
    else {
        std::cout << "Robot is on target\n";
    }

    
}