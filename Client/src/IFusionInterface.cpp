#include "IFusionInterface.h"



  Fusion::~Fusion(){};
  
  void Fusion::doUpdate(const SensorObjectList &sensorObjectList){
    //std::cout <<"valid objects"  << sensorObjectList.numOfValidObjects <<  std::endl;
    //std::cout <<"time stamp objects"  << sensorObjectList.timestamp <<  std::endl;

    for (size_t i = 0; i < sensorObjectList.numOfValidObjects; i++){
        createNewObject(sensorObjectList.objectList[i]);
    }
    predict(sensorObjectList.timestamp);
}

  void Fusion::createNewObject(const SensorObject &sensorObject){

        _objectList.objects[_currentObjectId].objectId = _currentObjectId;
        _objectList.objects[_currentObjectId].x = sensorObject.x; // position x
        _objectList.objects[_currentObjectId].y = sensorObject.y; // positoin y
        _objectList.objects[_currentObjectId].vx = sensorObject.vx; // velocity x
        _objectList.objects[_currentObjectId].vy = sensorObject.vy; // velocity y
        // _objectList.objects[_currentObjectId].Pxx = Qxx; // variance of x position
        // _objectList.objects[_currentObjectId].Pyy = Qyy; // variance of y position
        // _objectList.objects[_currentObjectId].Pvxvx = Rvxvx ;// variance of x velocity
        // _objectList.objects[_currentObjectId].Pvyvy = Rvyvy; //  variance of y velocity
        // _objectList.objects[_currentObjectId].Pxvx = Qvxvx; // covariance of x postion and velocity
        // _objectList.objects[_currentObjectId].Pyvy= Qvyvy; // covariance of y position and velocity
        _currentObjectId++;
        std::cout << "object is created" << std::endl;
}

  void Fusion::predict(const uint64_t timestamp){
      //     x_k_pred = F*x_{k-1} + B*u_{k-1} --> no control input
      // Predict state estimate
        Eigen::Matrix<double,4,1> x_hat; // predicted 
        Eigen::Matrix<double,4,1> x{
                            {_objectList.objects->x},
                            {_objectList.objects->y},
                            {_objectList.objects->vx},
                            {_objectList.objects->vy}};
        std::cout <<"show " << x.matrix() << std::endl;
        x_hat = F * x;
        std::cout <<"show " << x_hat.matrix() << std::endl;
        // Predict error covariance (error in the estimate, state convariance matrix)
        // P --> state convariance matrix
        // Q --> process noise convariance matrix (keeps the state convariance matrix from becoming too small)
        // R --> Measurement convariance matrix (error in the measurement)
        // K --> Kalman gain (weight factor based on the comparing the error in the estimate
        // to the error in the measurement)

        //Eigen::Matrix<double,4,4> P_hat;

        P = F * P * F.transpose() + Q;

        std::cout <<"phat " << P.matrix() << std::endl;



}

  bool Fusion::associate(const SensorObject &sensorObject,
                         uint8_t &associatedObjectIndex){
              
                                    return true;
}

  void Fusion::update(const SensorObject &sensorObject,
                      const uint8_t associatedObjectIndex){

}