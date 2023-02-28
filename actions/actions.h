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

QVector<float> rotate(bool right, float radious, float vel); //returns proper left and right wheel speeds
QVector<float> orientationToBall(fira_message::Ball ball, fira_message::Robot robot);
float vectorModule(QVector vector);

#endif // ACTIONS_H
