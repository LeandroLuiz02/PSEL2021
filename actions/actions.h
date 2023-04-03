#ifndef ACTIONS_H
#define ACTIONS_H

#include "modules/actuator/actuator.h"
#include "modules/vision/vision.h"
#include "qvector.h"

class actions
{
public:
    actions();
};

float distanceTo(fira_message::Robot robot, float x, float y);
float angleTo(fira_message::Robot robot, float x, float y);
bool angleBetweenOtherTwoAngles(float dynamicAngle, float angle1, float angle2);
bool shouldRotateLeft(fira_message::Robot robot, float x, float y);

QVector<float> rotate(bool angularDirection, float radious, float vel); //returns proper left and right wheel speeds
//QVector<float> orientationToBall(fira_message::Ball ball, fira_message::Robot robot);
//float vectorModule(QVector vector);

#endif // ACTIONS_H
