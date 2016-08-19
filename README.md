# Installation (Windows)

### Compiler - Visual C++

- Download and install VS community edition
- Create new project > Visual C++ and select "Install Visual C++ 2015 Tools for Windows Desktop"

### CMake
CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.

- Download latest Cmake installer tool from cmake.org
- Choose add CMake to Path variable
- Test in Console `cmake --version`


### OpenCV 2.4.13 binaries for Visual Studio 14 2015

- Download and extract source from: https://sourceforge.net/projects/opencvlibrary/files/opencv-win/
- OpenCV 2.4.13 is ++not++ precompiled for VS14 2015! We need to compile it first.
- Open CMake GUI and select source (C:/lib/OpenCV2413/sources) and build (C:/lib/OpenCV2413/build) Path
- Click on `Configure` and Select "Microsoft Visual Studio 2015 x64"
- Click on `Generate` - Microsoft Visual Studio project gets generated
- Open `OpenCV.sln` in Visual Stduio from build path

**Building OpenCV**

- Select `Debug` and `RMB > Build` on `CMakeTargets > ALL_BUILD` in Project Explorer
- Select `Release` and `RMB > Build` on `CMakeTargets > ALL_BUILD` in Project Explorer
- OpenCV ist now built for/with Visual Studio 14


**Combining includes/libraries**
- Select `Debug` and `RMB > Build` on `CMakeTargets > INSTALL` in Project Explorer
- Select `Release` and `RMB > Build` on `CMakeTargets > INSTALL` in Project Explorer

**Set Environment/PATH Variable**
For CMake to find OpenCV

```bash
setx -m OPENCV_DIR "C:\lib\OpenCV2413\install\"
```

Set PATH variable, so linker finds libraries (-m for all users on machine).
```bash
setx -m PATH "%PATH%;C:\lib\OpenCV2413\install\x64\vc14\bin"
```

- **restart**

# Build Project
Open command prompt and execute:
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 14 2015 Win64"
```

