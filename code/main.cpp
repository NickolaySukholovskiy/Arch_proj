#include "Camera.hpp"
#include "robotCommands.hpp"

int main()
{
    Camera cam(0);

    while (true)
    {
        cam.updateImage();
        cam.showImage();
        finite_state_machine(cam);
        // std::cout << cam.getAngle() << ' ' << cam.getDistanceTarget() << '\n';
        waitKey(25);
        if (waitKey(25) == 27)
            break;
    }
    return 0;
}