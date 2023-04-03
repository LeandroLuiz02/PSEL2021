#ifndef ROLES_H
#define ROLES_H

#include <modules/actuator/actuator.h>

class roles
{
public:
    roles();
};

void goalKeeper(Actuator* actuator, bool isYellow, int id, fira_message::Robot robot, fira_message::Ball ball);

#endif // ROLES_H
