#include "behaviors.h"

behaviors::behaviors()
{

}

QVector<float> goTo(fira_message::Robot robot, float x, float y) {
    float angSpeed = 9;
    float linSpeed = 30;
    QVector<float> wheelsRotation;
    float angleToTarget = angleTo(robot, x, y) - robot.orientation();

    if (angleToTarget < M_PI/8.0 && angleToTarget > -M_PI/8.0) angSpeed = 0.9;

    //adding angular speed
    if (shouldRotateLeft(robot, x, y)) wheelsRotation = {-angSpeed, angSpeed};
    else wheelsRotation = {angSpeed, -angSpeed};

    //adding linear speed
    if (angleToTarget < M_PI/2.0 && angleToTarget > -M_PI/2.0) {
        wheelsRotation[0] += linSpeed;
        wheelsRotation[1] += linSpeed;
    }

    return wheelsRotation;
}

QVector<float> goToGK(fira_message::Robot robot, float x, float y) {
    float angSpeed = 9;
    float linSpeed = 30;
    QVector<float> wheelsRotation;
    float angleToTarget = angleTo(robot, x, y) - robot.orientation();

    if (angleToTarget < M_PI/8.0 && angleToTarget > -M_PI/8.0) angSpeed = 0.9;
    if (angleToTarget > 7 * M_PI/8.0 || angleToTarget < -7 * M_PI/8.0) angSpeed = 0.9;

    //adding angular speed
    if (angleToTarget < M_PI/4.0 && angleToTarget > -M_PI/4.0) {
        if (shouldRotateLeft(robot, x, y)) wheelsRotation = {-angSpeed, angSpeed};
        else wheelsRotation = {angSpeed, -angSpeed};
    }
    else {
        if (shouldRotateLeft(robot, x, y)) wheelsRotation = {angSpeed, -angSpeed};
        else wheelsRotation = {-angSpeed, angSpeed};
    }

    //adding linear speed
    if (angleToTarget < M_PI/2.0 && angleToTarget > -M_PI/2.0) {
        wheelsRotation[0] += linSpeed;
        wheelsRotation[1] += linSpeed;
    }
    else {
        wheelsRotation[0] -= linSpeed;
        wheelsRotation[1] -= linSpeed;
    }


    return wheelsRotation;
}

QVector<float> spin( bool left) {
    float rotationSpeed = 40;
    if (left) return {-rotationSpeed, rotationSpeed};
    else return {rotationSpeed, -rotationSpeed};
}
