#ifndef ISENSOR_INTERFACE_H_
#define ISENSOR_INTERFACE_H_ ISENSOR_INTERFACE_H_
#include "Definitions.h"

#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <winsock2.h>
#define M_PI 3.1415f
#define socklen_t int
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
/*
 *This interface must be implemented in order to
 *establish a connection to the vehicle sensor.
 */
class ISensorInterface {
public:
  /// Define a port and an ip address to connect to the vehicle sensoe
  virtual bool connectToSensor(const int port = SENSOR_SERVER_PORT,
                               const char *ip = SENSOR_SERVER_IP_ADDRESS) = 0;
  /// Get the current object list from the sensor
  virtual bool getNextObjectList(SensorObjectList &objectList) = 0;

   /// Send OBJECTS_RECEIVED_MSG to the server AFTER processing the
  /// object list in the fusion
  virtual bool confirmObjectsReceived() = 0;
  /// Disconnect from sensor
  virtual bool closeConnection() = 0;
};




class Sensor : public ISensorInterface{
  private:
      int client;
      static sockaddr_in server_addr;
      int objectReceived;
  public:
    Sensor();
    ~Sensor();
    bool connectToSensor(const int port = SENSOR_SERVER_PORT,
                        const char *ip = SENSOR_SERVER_IP_ADDRESS)override;
    bool getNextObjectList (SensorObjectList &objectList)override;
    bool confirmObjectsReceived()override;
    bool closeConnection()override;

};





#endif
