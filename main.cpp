#include <QCoreApplication>
#include <chrono>
#include <thread>
#include <modules/actuator/actuator.h>
#include <modules/vision/vision.h>
#include <actions/actions.h>
#include <behaviors/behaviors.h>
#include <roles/roles.h>
#include <math.h>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Vision *vision = new Vision("224.0.0.1", 10002);
    Actuator *actuator = new Actuator("127.0.0.1", 20011);

    // Desired frequency
    int desiredFrequency = 60;

    while(true) {
        // TimePoint
        std::chrono::high_resolution_clock::time_point beforeProcess = std::chrono::high_resolution_clock::now();

        // Process vision and actuator commands
        vision->processNetworkDatagrams();
        fira_message::Robot robot = vision->getLastRobotDetection(true, 0);
        fira_message::Robot kicker = vision->getLastRobotDetection(false, 0);
        fira_message::Ball ball = vision->getLastBallDetection();

        goalKeeper(actuator, true, 0, robot, ball);
        actuator->sendCommand(false, 0, -80, 80);
        //debug


        // TimePoint
        std::chrono::high_resolution_clock::time_point afterProcess = std::chrono::high_resolution_clock::now();

        // Sleep thread
        long remainingTime = (1000 / desiredFrequency) - (std::chrono::duration_cast<std::chrono::milliseconds>(afterProcess - beforeProcess)).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
    }

    return 0;
}
