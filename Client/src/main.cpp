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

    bool a = sensor.connectToSensor();
    SensorObjectList objectList;
    bool vc = sensor.getNextObjectList(objectList);
// for (size_t i = 0; i < 5; i++)
// {
//       bool b  = sensor.confirmObjectsReceived();

//   if (i = 4){
//     sensor.closeConnection();
//   }
// }

  //create a socket
  // int client;
  // sockaddr_in server_addr;
  // client = socket(AF_INET,SOCK_STREAM,0);
  
  // if(client < 0){
  //   std::cout << "error creating socket" << std::endl;
  // }
  // std::cout << "client socket created"<< std::endl;
  // // create a hint structure for the server we are connecting with
  // server_addr.sin_family =AF_INET;
  // server_addr.sin_port = htons(5555); 
  // // connect to the server on the internet
  // if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
  //       std::cout << "=> Connection to the server port number: " << "5555" << std::endl;
  
  
  //   //	While loop:
  //   char buf[4096];
  //   std::string userInput;

  // do {
  //       //		Enter lines of text
  //       std::cout << "> ";
  //       std::getline(std::cin, userInput);

  //       //		Send to server
  //       int sendRes = send(client, userInput.c_str(), userInput.size() + 1, 0);
  //       if (sendRes == -1)
    //     {
    //         std::cout << "Could not send to server! Whoops!\r\n";
    //         continue;
    //     }
        
    //     //		Wait for response
    //     //memset(buf, 0, 4096);
    //     int bytesReceived = recv(client, buf, 4096, 0);
    //     if (bytesReceived == -1)
    //     {
    //         std::cout << "There was an error getting response from server\r\n";
    //     }
    //     else
    //     {
    //         //		Display response
    //         std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
    //     }
    // } while(true);

    // //	Close the socket
    // close(client);
  return 0;
}
