
#include <kitti_tools/kitti_tools.hpp>
#define SIZEOFFLOAT 4


int dataReader::countFilesInDirectory(const fs::path& directory) {
    int fileCount = 0;

    try {
        for (fs::directory_iterator it(directory), end; it != end; ++it) {
            if (fs::is_regular_file(it->status())) {
                ++fileCount;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return -1;  
    }

    return fileCount-1;
}
       
void lidarDataReader::readData(const std::string& filePath) {

  if(mode == 1){
    
    maxFileNum = countFilesInDirectory(filePath);

    if( fileNum < maxFileNum){

      std::ostringstream filePathTemp;
      std::string finalFilePath;
      filePathTemp << std::setfill('0') << std::setw(6) << std::to_string(fileNum);
      finalFilePath = filePath + "/" + filePathTemp.str() + ".bin";
      std::ifstream file(finalFilePath,std::ios::binary);

      if(!file.is_open()){
        std::cout << "Uable to open file " << std::endl
                  << "filePath : " << finalFilePath << std::endl;
      }else{

        cloudMsg.data.clear();
        cloud.clear();
        while (file.peek() != EOF)
        {
          file.read(reinterpret_cast<char*>(&point.x), SIZEOFFLOAT);
          file.read(reinterpret_cast<char*>(&point.y), SIZEOFFLOAT);
          file.read(reinterpret_cast<char*>(&point.z), SIZEOFFLOAT);
          file.read(reinterpret_cast<char*>(&point.intensity), SIZEOFFLOAT);
          cloud.push_back(point);
        
        }

        file.close();
        fileNum = fileNum + 1;

        pcl::toROSMsg(cloud,cloudMsg);
        cloudMsg.header.stamp = ros::Time::now();
        cloudMsg.header.frame_id = "velodyne";
      }
    }else{
      std::cout << "read all file,file num : " << fileNum + 1 << std::endl;
      
    }
      

  }else if(mode == 0){
    std::ifstream file(filePath,std::ios::binary);
    if(!file.is_open()){
        std::cout << "Uable to open file,filePath : " << filePath << std::endl;
    }else{

      cloudMsg.data.clear();
      cloud.clear();
      while (file.peek() != EOF)
      {
        file.read(reinterpret_cast<char*>(&point.x), SIZEOFFLOAT);
        file.read(reinterpret_cast<char*>(&point.y), SIZEOFFLOAT);
        file.read(reinterpret_cast<char*>(&point.z), SIZEOFFLOAT);
        file.read(reinterpret_cast<char*>(&point.intensity), SIZEOFFLOAT);
        cloud.push_back(point);
      
      }

      file.close();
      pcl::toROSMsg(cloud,cloudMsg);
      cloudMsg.header.stamp = ros::Time::now();
      cloudMsg.header.frame_id = "velodyne";
    }
  }
}

