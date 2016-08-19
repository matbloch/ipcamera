INCLUDE_DIRECTORIES(
  .
)


# Set common link libraries
SET(COMMON_LIBS ${OpenCV_LIBS})

# Add eigen (header file only)
# INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}" )

IF(ARTOOLKIT5_FOUND)
	# ARToolkit
	# Optional - but essential for tracking via ARToolkit
	INCLUDE_DIRECTORIES(
	  ${ARTOOLKIT5_INCLUDE_DIR}
	)
	SET(COMMON_LIBS ${COMMON_LIBS} ${ARTOOLKIT5_LIBRARY})
ENDIF(ARTOOLKIT5_FOUND)

ADD_EXECUTABLE(camera camera.cpp)
TARGET_LINK_LIBRARIES(camera
  ${COMMON_LIBS}
)

ADD_EXECUTABLE(video_to_image video_to_image.cpp)
TARGET_LINK_LIBRARIES(video_to_image
  ${COMMON_LIBS}
)

MESSAGE(${COMMON_LIBS})
