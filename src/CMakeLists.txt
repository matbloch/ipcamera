INCLUDE_DIRECTORIES(
  .
)

#include dlib
INCLUDE_DIRECTORIES(
 ${DLIB_INCLUDE_DIR}
)

# Set common link libraries
## Set common link libraries
SET(COMMON_LIBS 
${OpenCV_LIBS}
${DLIB_LIBRARY}
)

# Add eigen (header file only)
# INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}" )

ADD_EXECUTABLE(camera camera.cpp)
TARGET_LINK_LIBRARIES(camera
  ${COMMON_LIBS}
)

# ADD_EXECUTABLE(video_to_image video_to_image.cpp)
# TARGET_LINK_LIBRARIES(video_to_image
  # ${COMMON_LIBS}
# )

MESSAGE("libs: ${COMMON_LIBS}")
