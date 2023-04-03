#include "actions.h"
#include "math.h"

actions::actions()
{

}

float distanceTo(fira_message::Robot robot, float x, float y) {

    // returned value = sqrt( (x - r.x)² + (y - r.y)² ), that is the module of a vector
    return sqrt(pow(x - robot.x(), 2) + pow(y - robot.y(), 2));

}

float angleTo(fira_message::Robot robot, float x, float y) {

    //in case target has a lower y than the robot, the angle returned should have a negative value
    int signal = 1;
    if (y < robot.y()) signal = -1;

    // uses the formula that returns the angle between two vectors
    if (distanceTo(robot, x, y) != .0f)
    return signal * acos((x - robot.x()) / (distanceTo(robot, x, y)));

    else return 0.0;
}

bool angleBetweenOtherTwoAngles(float dynamicAngle, float angle1, float angle2) {
    //verify if a given angle is between other two angles
    if ((dynamicAngle < angle1 && dynamicAngle > angle2) || (dynamicAngle > angle1 && dynamicAngle < angle2))
        return true;
    else return false;
}

bool shouldRotateLeft(fira_message::Robot robot, float x, float y) {

    if (robot.orientation() * angleTo(robot, x, y) >= 0) { // both have same signal

        if (robot.orientation() > angleTo(robot, x, y)) return false;
        else return true;
    }

    else {

        float oppositeRobotAngle;


        //if robot poins to positive y
        if (robot.orientation() > 0) {
            oppositeRobotAngle = robot.orientation() - M_PI/2.0;
            if (robot.orientation() >= angleTo(robot, x, y) && angleTo(robot, x, y) >= oppositeRobotAngle) return false;
            return true;
        }

        else {
            oppositeRobotAngle = robot.orientation() + M_PI/2.0;
            if (oppositeRobotAngle >= angleTo(robot, x, y) && angleTo(robot, x, y) >= robot.orientation()) return true;
            return false;
        }
    }
}

QVector<float> rotate(bool angularDirection, float radious, float vel) {
    const float halfDistanceWheels = 0.75;
    float leftWheelVel = 0;
    float rightWheelVel = 0;

    float greaterVel = (vel / radious) * (radious + halfDistanceWheels);
    float lesserVel = (vel / radious) * (radious - halfDistanceWheels);

    if (angularDirection) {
        leftWheelVel = greaterVel;
        rightWheelVel = lesserVel;
    }
    else {
        leftWheelVel = lesserVel;
        rightWheelVel = greaterVel;
    }

    QVector<float> v = {leftWheelVel, rightWheelVel};
    return v;
}
