# Installation

#### opencv 2.4.9

```bash
# dependencies
sudo apt-get -y install libopencv-dev build-essential git-core autoconf libtool cmake git libgtk2.0-dev pkg-config python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libtiff4-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils unzip

sudo apt-get -qq install checkinstall yasm 


# video I/O
sudo apt-get install libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev yasm libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev

# Parallelism and linear algebra libraries:
sudo apt-get install libtbb-dev libeigen3-dev
```


#### ARToolkit

##### Download and build from source

```bash
# Dependencies:
$ sudo apt-get install clang
# CV dependencies for calib_camera
$ sudo apt-get install libopencv-dev
# Toolkit
$ cd ~/installations
$ git clone https://github.com/artoolkit/artoolkit5.git
$ cd artoolkit5
$ ./Configure
$ make

**Configuration**
- First select "No" (do not compile with Clang)
- Select "No" to skip OSG and VRML examples



##### Installation

**Option 1**: Install in user program directory
```bash
# Copy includes (header files)
sudo cp -R ./include/AR /usr/local/include/
# Copy libraries (libAR.a, libAR2.a, libARICP.a)
sudo cp ./lib/*.a /usr/local/lib/
```

**Option 2**: Set environment variable to the ARTolkit root

```bash
# from the unpacked artoolkit5 directory run
./share/artoolkit5-setenv
```

##### Uninstall

```bash
sudo rm -rf /usr/local/include/AR
sudo rm /usr/local/lib/libAR*.a
```

## Build Project

```bash
mkdir build
cd build
cmake ..
make
```