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
  public:

       bool connected = false; 

  public:
    Sensor(){
    }

    ~Sensor(){
      //std::cout << "object destriyed " << std::endl;
      
    }

    bool connectToSensor(const int port = SENSOR_SERVER_PORT,
                        const char *ip = SENSOR_SERVER_IP_ADDRESS)override{
       static int client;
       static struct sockaddr_in server_addr;
      client = socket(AF_INET,SOCK_STREAM,0);             
       if(client < 0){
         std::cout << "error creating socket" << std::endl;
       }
       std::cout << "client socket created"<< std::endl;
       server_addr.sin_family =AF_INET;
       server_addr.sin_port = htons(SENSOR_SERVER_PORT); 



       if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0){
          std::cout << "=> Connection to the server port number: " << SENSOR_SERVER_PORT << std::endl;
          return true;
      }else
        return false;
    }
      /// Get the current object list from the sensor
    bool getNextObjectList (SensorObjectList &objectList)override{
          return false;
    }
    bool confirmObjectsReceived()override{
          return false;
    }
    /// Disconnect from sensor
    bool closeConnection()override{
          return false;
    }
};




#endif
