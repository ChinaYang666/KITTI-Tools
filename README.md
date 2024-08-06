# kitti tools

## A tool for parsing the KITTI dataset

This is a tool for parsing the KITTI dataset, supporting both C++ and Python. You just need to follow the instructions to parse the dataset and publish messages.

## How to use it ?

### Read lidar data

If you need to read a single lidar data bin file, you only need to use the `lidarReader.launch` file like:

```xml
 <param name="lidarPath" type="string" value="/home/yang/数据集/KITI数据集/2024-8-4_FULL-KITI-DataSet/kitti/dataset/sequences/00/velodyne/000001.bin" />
    <param name="mode"      type="int"    value="0" />
```

If you need to read bin files for lidar data from an entire folder, you only need to use the `lidarReader.launch`  file，like:

```xml
<param name="lidarPath" type="string" value="/home/yang/数据集/KITI数据集/2024-8-4_FULL-KITI-DataSet/kitti/dataset/sequences/00/velodyne" />
    <param name="mode"      type="int"    value="1" />
```

When reading bin files from an entire folder, the program will automatically read all the bin files without exceeding the boundaries.

### Running

```bash
roslaunch kitti_tools laserReader.launch
```
