#include "actions.h"
#include "math.h"

actions::actions()
{

}

QVector<float> rotate(bool right, float radious, float vel) {
    const float halfDistanceWheels = 0.75;
    float leftWheelVel = 0;
    float rightWheelVel = 0;

    float greaterVel = (vel / radious) * (radious + halfDistanceWheels);
    float lesserVel = (vel / radious) * (radious - halfDistanceWheels);

    if (right) {
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

float distanceTo(float x, float y, fira_message::Robot robot) {

    // returned value = sqrt( (x - r.x)² + (y - r.y)² ), that is the module of a vector
    return sqrt(pow(x - robot.x(), 2) + pow(y - robot.y(), 2));

}

float angleTo(float x, float y, fira_message::Robot robot) {

    //in case the ball has a lower y than the robot, the angle returned should have a negative value
    int signal = 1;
    if (y < robot.y()) signal = -1;

    // uses the formula that returns the angle between two vectors
    if (distanceTo(x, y, robot) != .0f)
    return signal * acos((x - robot.x()) / (distanceTo(x, y, robot)));

    else return .0f;
}

bool angleBetweenOtherTwoAngles(float dynamicAngle, float angle1, float angle2) {
    //verify if a given angle is between other two angles
    if ((dynamicAngle < angle1 && dynamicAngle > angle2) || (dynamicAngle > angle1 && dynamicAngle < angle2))
        return true;
    else return false;
}

// not working properly yet
bool shouldRotateLeft(float x, float y, fira_message::Robot robot) {
    float toBallOrientation = angleTo(x, y, robot);

    // in case both robot orientation and ball orientation has same signal
    if (toBallOrientation * robot.orientation() > 0) {

        if (toBallOrientation > robot.orientation()) return true;
        else return false;
    }

    else {
        if (toBallOrientation > 0) { // using sqrt(pow()) to get absolute value
            if (toBallOrientation + sqrt(pow(robot.orientation(), 2)) < M_PI)
                return true;
            else return false;
        }
        else if (robot.orientation() + sqrt(pow(toBallOrientation, 2)) > M_PI)
            return false;
        else return true;
    }
}
