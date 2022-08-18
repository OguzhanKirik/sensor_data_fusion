#ifndef IFUSIONINTERFACE_H_
#define IFUSIONINTERFACE_H_ IFUSIONINTERFACE_H_
#include <Eigen/Dense>
#include<iostream>
#include "JSONFileLogger.h"
class IFusionInterface {
public:
  IFusionInterface() : _currentObjectId(0)
  ,_logger(LOG_FILE_NAME) 
   {}

  // Do the whole magic here, i.e.,
  // prediction, association, update
  //@param[in] sensorObjectList
  virtual void doUpdate(const SensorObjectList &sensorObjectList) = 0;

protected:
  // Use this function to initialize a new object within the
  // object list.
  //@param[in] sensorObject
  virtual void createNewObject(const SensorObject &sensorObject) = 0;
  // Prediction of all objects within the object list
  // to the given timestamp.
  // Both, the state and the uncertainty shall be predicted.
  //@param[in] timestamp
  virtual void predict(const uint64_t timestamp) = 0;
  // Associate the current sensor object with a suitable object stored in
  // the object list. The association result must be written to the index.
  //@param[in] sensorObject
  //@param[out] associatedObjectIndex
  virtual bool associate(const SensorObject &sensorObject,
                         uint8_t &associatedObjectIndex) = 0;
  // Given an associated object, perform the Kalman filter update here.
  //@param[in] sensorObject
  //@param[in] associatedObjectIndex
  virtual void update(const SensorObject &sensorObject,
                      const uint8_t associatedObjectIndex) = 0;

  ObjectList _objectList;    // object database
  uint16_t _currentObjectId; // use this one to create new object id's
  JSONFileLogger _logger;    // write the fusion result to file
};

class Fusion :public IFusionInterface{
public:
  Fusion() : _currentObjectId(0)
  ,_logger(LOG_FILE_NAME) 
   {
    //Initialize the logger
    _logger.init();

    //initiliaze
   F << 1.0f,0.0f,0.4f,0.0f,
        0.0f,1.0f,0.0f,0.4f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,1.0f;

    R << Rxx,0.0f,0.0f,0.0f,
          0.0f,Ryy,0.0f,0.0f,
          0.0f,0.0f,Rvxvx,0.0f,
          0.0f,0.0f,0.0f,Rvyvy;

    Q << Qxx,0.0f,0.0f,0.0f,
          0.0f,Qyy,0.0f,0.0f,
          0.0f,0.0f,Qvxvx,0.0f,
          0.0f,0.0f,0.0f,Qvyvy;

    H <<  1.0f,0.0f,0.0f,0.0f,
          0.0f,1.0f,0.0f,0.0f,
           0.0f,0.0f,1.0f,0.0f,
           1.0f,0.0f,0.0f,1.0f;  
    
    I.setIdentity();

    //initialize error covariance 
    // P << Rxx,0.0f,0.0f,0.0f,
    //       0.0f,Ryy,0.0f,0.0f,
    //       0.0f,0.0f,Rvxvx,0.0f,
    //       0.0f,0.0f,0.0f,Rvyvy;
     P << 5.0f,0.0f,5.0f,0.0f,
           0.0f,5.0f,0.0f,5.0f,
           0.0f,0.0f,5.0f,0.0f,
           0.0f,0.0f,0.0f,5.0f;
   }
  ~Fusion();
  void doUpdate(const SensorObjectList &sensorObjectList)override;

protected:
  void createNewObject(const SensorObject &sensorObject)override;

  void predict(const uint64_t timestamp)override;

  bool associate(const SensorObject &sensorObject,
                         uint8_t &associatedObjectIndex)override;
  void update(const SensorObject &sensorObject,
                      const uint8_t associatedObjectIndex)override;

  ObjectList _objectList;  
  uint16_t _currentObjectId; 
  Eigen::Matrix<float,4,4>  F; // state transition
  Eigen::Matrix<float,4,4>  P; //Estimate error covariance
  Eigen::Matrix<float,4,4>  Q; // process noise covariance
  Eigen::Matrix<float,4,4>  R; // measurement  covariance
  Eigen::Matrix<float,4,4>  K; // Kalman Gain
  Eigen::Matrix<float,4,4>  I; // Identity Matrix
  Eigen::Matrix<float,4,4>  H; // state-to-measurement matrix
  std::vector<std::pair<int,int>> associatedObjects;
  JSONFileLogger _logger;    // write the fusion result to file
};


#endif
