#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include <actions/actions.h>
#include <modules/actuator/actuator.h>
#include <modules/vision/vision.h>
#include <math.h>

class behaviors
{
public:
    behaviors();
};

QVector<float> goTo(fira_message::Robot robot, float x, float y);
QVector<float> goToGK(fira_message::Robot robot, float x, float y);
QVector<float> spin(bool left);

#endif // BEHAVIORS_H
