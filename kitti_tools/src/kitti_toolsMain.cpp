#include "kitti_tools/kitti_tools.hpp"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "kitti_toolsNode");
    ros::NodeHandle nh;
 

    std::string lidarPath;
    
    if(nh.getParam("lidarPath",lidarPath)){
        std::cout << "lidarPath : " << lidarPath << std::endl;
        
    }else{
        ROS_ERROR("Failed to get param 'lidarPath'");
    }

    int mode;
    if(nh.getParam("mode",mode)){
        std::cout << "mode : " << mode << std::endl;

        
    }else{
        ROS_ERROR("Failed to get param 'mode'");
    }
    
    ros::Rate loop_rate(10); 
    ros::Publisher lidarPub = nh.advertise<sensor_msgs::PointCloud2>("velodyne_points", 1);
 
    lidarDataReader lidarData;
    lidarData.mode = mode;
    

    
    while (ros::ok())
    {
        lidarData.readData(lidarPath);
       
        lidarPub.publish(lidarData.cloudMsg);

        



        loop_rate.sleep();
    }

    return 0;
}
