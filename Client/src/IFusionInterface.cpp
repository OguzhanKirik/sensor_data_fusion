#include "IFusionInterface.h"



  Fusion::~Fusion(){};
  
  void Fusion::doUpdate(const SensorObjectList &sensorObjectList){
    _logger.openNewFusionCycleArray();
    _logger.addSensorObjectList(sensorObjectList);
    uint8_t associatedObjectIndex;
    if(_objectList.numOfValidObjects ==0){
      associatedObjectIndex = -1;

      for (size_t i = 0; i < sensorObjectList.numOfValidObjects; i++){
          createNewObject(sensorObjectList.objectList[i]);
      }
      predict(sensorObjectList.timestamp);


    }else{
      associatedObjectIndex =0;
      for (size_t i = 0; i < sensorObjectList.numOfValidObjects; i++){
          associate(sensorObjectList.objectList[i],associatedObjectIndex);
          update(sensorObjectList.objectList[i],associatedObjectIndex);
          createNewObject(sensorObjectList.objectList[i]);

          associatedObjectIndex++;
      }
      predict(sensorObjectList.timestamp);
    }
    _currentObjectId = 0;
}

  void Fusion::createNewObject(const SensorObject &sensorObject){
        
        _objectList.objects[_currentObjectId].objectId = _currentObjectId;
        _objectList.objects[_currentObjectId].x = sensorObject.x; // position x
        _objectList.objects[_currentObjectId].y = sensorObject.y; // positoin y
        _objectList.objects[_currentObjectId].vx = sensorObject.vx; // velocity x
        _objectList.objects[_currentObjectId].vy = sensorObject.vy;
        _objectList.numOfValidObjects = _currentObjectId+1;
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
        Eigen::Matrix<double,4,1> x{
                            {_objectList.objects->x},
                            {_objectList.objects->y},
                            {_objectList.objects->vx},
                            {_objectList.objects->vy}};
        x_hat = F * x;
        P = F * P * F.transpose() + Q;

         _logger.addObjectList(_objectList,"PredictedObjectList");

         
}

  bool Fusion::associate(const SensorObject &sensorObject,
                         uint8_t &associatedObjectIndex){
      //_logger.addAssociationIndices;
      return true;
}

  void Fusion::update(const SensorObject &sensorObject,
                      const uint8_t associatedObjectIndex){
        Eigen::Matrix<double,4,1> x_k; // estimated
        Eigen::Matrix<double,4,4> P_k; // covariance
        Eigen::Matrix<double,4,1> z; //measurement   


        // Measurement residuals
        Eigen::Matrix<double,4,1> y; 
        y = z - H * x_hat;

        //  // Kalman Gain                   
        K = (P*H.transpose()) * ((R + H*P*H.transpose() + R)).inverse();
        // Updated state estimate
        x_k = x_hat + K * y;
        // Updated error covariance
        P_k = (I - K*H)*P;   

         _logger.addObjectList(_objectList,"UpdatedObjectList");    
       

}