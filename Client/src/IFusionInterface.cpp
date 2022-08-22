#include "IFusionInterface.h"



  Fusion::~Fusion(){
    _logger.close();
  };
  
  void Fusion::doUpdate(const SensorObjectList &sensorObjectList){

    _logger.openNewFusionCycleArray(); // start logger cycle
    _logger.addSensorObjectList(sensorObjectList); // add new coming sensor objects
    uint8_t associatedObjectIndex = 0;

    if(_objectList.numOfValidObjects ==0){

      for (size_t i = 0; i < sensorObjectList.numOfValidObjects; i++){
          associate(sensorObjectList.objectList[i],associatedObjectIndex);  
          createNewObject(sensorObjectList.objectList[i]);
          _currentObjectId++;
          associatedObjectIndex++;
      }
     _objectList.numOfValidObjects = sensorObjectList.numOfValidObjects;
      predict(sensorObjectList.timestamp);
      _logger.addObjectList(_objectList,"PredictedObjectList");
      _logger.addAssociationIndices(associatedObjects);

    }else{

      predict(sensorObjectList.timestamp);
      _logger.addObjectList(_objectList,"PredictedObjectList");

      for (size_t i = 0; i < sensorObjectList.numOfValidObjects; i++){
        associate(sensorObjectList.objectList[i],associatedObjectIndex);  
        update(sensorObjectList.objectList[i],associatedObjectIndex);
        createNewObject(sensorObjectList.objectList[i]);
        associatedObjectIndex++;
        _currentObjectId++;

      }
       _objectList.numOfValidObjects = sensorObjectList.numOfValidObjects;

      _logger.addAssociationIndices(associatedObjects);
      _logger.addObjectList(_objectList,"UpdatedObjectList");    
      std::cout << " updated " << std::endl;

    }
    _currentObjectId = 0;
    associatedObjects.erase (associatedObjects.begin(),associatedObjects.end());
}

  void Fusion::createNewObject(const SensorObject &sensorObject){
        
        _objectList.objects[_currentObjectId].objectId = _currentObjectId;
        _objectList.objects[_currentObjectId].x = sensorObject.x; // position x
        _objectList.objects[_currentObjectId].y = sensorObject.y; // positoin y
        _objectList.objects[_currentObjectId].vx = sensorObject.vx; // velocity x
        _objectList.objects[_currentObjectId].vy = sensorObject.vy;
      
}

  void Fusion::predict(const uint64_t timestamp){
      // Predict state estimate
      _objectList.timestamp = timestamp;
       Eigen::Matrix<float,4,4> P_hat;

      for (size_t i = 0; i < _objectList.numOfValidObjects; i++){
        Eigen::Matrix<float,4,1> x_hat;

        Eigen::Matrix<float,4,1> x{
                            {_objectList.objects[i].x},
                            {_objectList.objects[i].y},
                            {_objectList.objects[i].vx},
                            {_objectList.objects[i].vy}};
        x_hat = F * x;
        P_hat = F * P * F.transpose() + Q;

        _objectList.objects[i].x = x_hat.coeff(0,0); 
        _objectList.objects[i].y = x_hat.coeff(1,0); 
        _objectList.objects[i].vx = x_hat.coeff(2,0); 
        _objectList.objects[i].vy = x_hat.coeff(3,0); 
        _objectList.objects[i].Pxx = P_hat.coeff(0,0); // variance of x position
        _objectList.objects[i].Pyy = P_hat.coeff(1,1); // variance of y position
        _objectList.objects[i].Pvxvx = P_hat.coeff(2,2) ;// variance of x velocity
        _objectList.objects[i].Pvyvy = P_hat.coeff(3,3); //  variance of y velocity
        _objectList.objects[i].Pxvx = P_hat.coeff(0,2); // covariance of x postion and velocity
        _objectList.objects[i].Pyvy = P_hat.coeff(1,3); // covariance of x postion and velocity
        
      }
      std::cout << " Predicted " << std::endl;

      P = P_hat;
      
    
         
}

  bool Fusion::associate(const SensorObject &sensorObject,
                         uint8_t &associatedObjectIndex){
      if(_objectList.numOfValidObjects == 2){
       associatedObjects.emplace_back(std::make_pair(_objectList.objects[associatedObjectIndex].objectId,associatedObjectIndex));
      }else{
        associatedObjects.emplace_back(std::make_pair(-1,associatedObjectIndex));
      }
      return true;
}

  void Fusion::update(const SensorObject &sensorObject,
                      const uint8_t associatedObjectIndex){
        Eigen::Matrix<float,4,1> x_k; // estimated state
        Eigen::Matrix<float,4,4> P_k; // covariance state
        Eigen::Matrix<float,4,1> y; // Measurement residuals 
        Eigen::Matrix<float,4,4>  P_hat; //Estimate error covariance
Eigen::Matrix<float,4,1> z {
                            {sensorObject.x},
                            {sensorObject.y},
                            {sensorObject.vx},
                            {sensorObject.vy}};  

      // estimated state vector
      Eigen::Matrix<float,4,1> x_hat{
                            {_objectList.objects[associatedObjectIndex].x},
                            {_objectList.objects[associatedObjectIndex].y},
                            {_objectList.objects[associatedObjectIndex].vx},
                            {_objectList.objects[associatedObjectIndex].vy}};
      // Estimated error covariance
      P_hat << _objectList.objects[associatedObjectIndex].Pxx,0.0f,_objectList.objects[associatedObjectIndex].Pxvx,0.0f,
           0.0f,_objectList.objects[associatedObjectIndex].Pyy,0.0f,_objectList.objects[associatedObjectIndex].Pyvy,
           0.0f,0.0f,_objectList.objects[associatedObjectIndex].Pvxvx,0.0f,
           0.0f,0.0f,0.0f, _objectList.objects[associatedObjectIndex].Pvyvy;

        y = z - H * x_hat;

        //  // Kalman Gain                   
        K = (P*H.transpose()) * ((R + H*P*H.transpose() + R)).inverse();
        // Updated state estimate
        x_k = x_hat + K * y;
        // Updated error covariance
        P_k = (I - K*H)*P;   


        _objectList.objects[associatedObjectIndex].x = x_k.coeff(0,0); 
        _objectList.objects[associatedObjectIndex].y = x_k.coeff(1,0); 
        _objectList.objects[associatedObjectIndex].vx = x_k.coeff(2,0); 
        _objectList.objects[associatedObjectIndex].vy = x_k.coeff(3,0); 
        _objectList.objects[associatedObjectIndex].Pxx = P_k.coeff(0,0); // variance of x position
        _objectList.objects[associatedObjectIndex].Pyy = P_k.coeff(1,1); // variance of y position
        _objectList.objects[associatedObjectIndex].Pvxvx = P_k.coeff(2,2) ;// variance of x velocity
        _objectList.objects[associatedObjectIndex].Pvyvy = P_k.coeff(3,3); //  variance of y velocity
        _objectList.objects[associatedObjectIndex].Pxvx = P_k.coeff(0,2); // covariance of x postion and velocity
        _objectList.objects[associatedObjectIndex].Pyvy = P_k.coeff(1,3); // covariance 

       
}