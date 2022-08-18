
#include "ISensorInterface.h"
#include <iostream>

    Sensor::Sensor(){
      std::cout << "constructed" << std::endl;
      client = socket(AF_INET,SOCK_STREAM,0);               
    }

    Sensor::~Sensor(){
      std::cout << "object destriyed " << std::endl;
     
    }

     sockaddr_in Sensor::server_addr;

      bool Sensor::connectToSensor(const int port,const char *ip){
        //static struct sockaddr_in server_addr;
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
    bool Sensor::getNextObjectList (SensorObjectList &objectList){
          this->objectReceived = recv(client, (char *)&objectList, sizeof(SensorObjectList), 0);        
          return true;
    }
    bool Sensor::confirmObjectsReceived(){

        if (this->objectReceived == -1){
          return false;
        }else{ 
          char objectsReceivedMsg[OBJECTS_RECEIVED_MSG_SIZE];
          send(client, objectsReceivedMsg, OBJECTS_RECEIVED_MSG_SIZE, 0);
          return true;
        }
    }
    /// Disconnect from sensor
    bool Sensor::closeConnection(){
          close(client);
          return true;
    }
