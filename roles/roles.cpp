#include "roles.h"
#include <modules/actuator/actuator.h>
#include <behaviors/behaviors.h>

roles::roles()
{

}

void goalKeeper(Actuator* actuator, bool isYellow, int id, fira_message::Robot robot, fira_message::Ball ball) {
    QVector<float> wheelsV;
    //std::cout << robot.y() << " -- " << (ball.y() / 0.65) * 0.25 << std::endl;
    //std::cout << ball.y() << std::endl;

    if (ball.x() < 0) { // C
        if (ball.y() < 0.2 && ball.y() > -0.2) wheelsV = goTo(robot, 0.63, ball.y());

        else{
            if (ball.y() > 0.2) wheelsV = goTo(robot, 0.63, 0.2);
            else wheelsV = goTo(robot, 0.63, -0.2);
        }
        std::cout << "C " << ball.y() << std::endl;
    }

    else if (ball.y() > 0.26) { // B (right)
        std::cout << "B" << std::endl;

        if (robot.y() < 0.25) wheelsV = goTo(robot, 0.645, 0.26);

        else wheelsV = spin(true);
    }

    else if (ball.y() < -0.26) { // B (left)
        std::cout << "B" << std::endl;

        if (robot.y() > -0.25) wheelsV = goTo(robot, 0.645, -0.26);

        else wheelsV = spin(false);
    }

    else { // A
        std::cout << "A" << std::endl;
        if (distanceTo(robot, ball.x(), ball.y()) < 0.1) {
            if (ball.y() > robot.y()) wheelsV = spin(true);
            else wheelsV = spin(false);
        }

        else {
            wheelsV = goTo(robot, 0.63, ball.y());
        }
    }

    actuator->sendCommand(isYellow, id, wheelsV[0], wheelsV[1]);
}
