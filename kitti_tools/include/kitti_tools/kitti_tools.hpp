#ifndef __KITTITOOLS_HPP__
#define __KITTITOOLS_HPP__

#include <ros/ros.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

#include <sensor_msgs/PointCloud2.h>

namespace fs = boost::filesystem;


class dataReader{

  protected:
    int countFilesInDirectory(const fs::path& directory) ;

  public:
    virtual ~dataReader() = default;
    virtual void readData(const std::string& filePath) = 0;

    
};


class lidarDataReader : public dataReader{
  private:
    pcl::PointXYZI point;
    pcl::PointCloud<pcl::PointXYZI> cloud;
    int fileNum = 0;
    int maxFileNum = 0;

  public:

    sensor_msgs::PointCloud2 cloudMsg;
    int mode = 0;//0-singel bin; 1-the whole folder bin; 
    
    void readData(const std::string& filePath) override;


};



#endif
