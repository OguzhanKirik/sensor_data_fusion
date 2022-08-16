#include "IFusionInterface.h"
 #include <iostream> 

  Fusion::~Fusion(){};
  
  void Fusion::doUpdate(const SensorObjectList &sensorObjectList){
    std::cout <<"valid objects"  << sensorObjectList.numOfValidObjects <<  std::endl;
std::cout <<"time stamp objects"  << sensorObjectList.timestamp <<  std::endl;

    for (size_t i = 0; i < sensorObjectList.numOfValidObjects; i++){
        createNewObject(sensorObjectList.objectList[i]);
    }
    //predict(sensorObjectList.timestamp);
}

  void Fusion::createNewObject(const SensorObject &sensorObject){

        _objectList.objects->objectId = _currentObjectId;
        _objectList.objects->x = sensorObject.x; // position x
        _objectList.objects->y = sensorObject.x; // positoin y
        _objectList.objects->vx = sensorObject.x; // velocity x
        _objectList.objects->vy = sensorObject.x; // velocity y
        _objectList.objects->Pxx = Qxx; // variance of x position
        _objectList.objects->Pyy = Qyy; // variance of y position
        _objectList.objects->Pvxvx = Rvxvx ;// variance of x velocity
        _objectList.objects->Pvyvy = Rvyvy; //  variance of y velocity
        _objectList.objects->Pxvx = Qvxvx; // covariance of x postion and velocity
        _objectList.objects->Pyvy= Qvyvy; // covariance of y position and velocity
        _currentObjectId++;
}

  void Fusion::predict(const uint64_t timestamp){
        _objectList.timestamp = timestamp;
        _objectList.objects[0].objectId ;
}

  bool Fusion::associate(const SensorObject &sensorObject,
                         uint8_t &associatedObjectIndex){
                                    return true;
}

  void Fusion::update(const SensorObject &sensorObject,
                      const uint8_t associatedObjectIndex){

}