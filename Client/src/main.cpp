#include <iostream>

#include <string>

#include "IFusionInterface.h"
#include "ISensorInterface.h"
#include "JSONFileLogger.h"
#include "Definitions.h"

// #ifdef _WIN32
// #define WINDOWS_LEAN_AND_MEAN
// #include <winsock2.h>
// #define M_PI 3.1415f
// #define socklen_t int
// #else
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #endif



int main() {
  // This is the entry point for your solution.
  // Connect to the sensor and track all objects.
  // Have fun!!!
    Sensor sensor;
    Fusion fusion;

  if(sensor.connectToSensor()){
    for (size_t i = 0; i < 4; i++){
        SensorObjectList objectList;
        if(sensor.getNextObjectList(objectList)){
          if(sensor.confirmObjectsReceived()){
             fusion.doUpdate(objectList);    
          }
        }
    }
  }

    sensor.closeConnection();

  return 0;
}
