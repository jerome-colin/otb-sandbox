

cmake_minimum_required(VERSION 2.6)

FIND_PACKAGE(OTB)
IF(OTB_FOUND)
  INCLUDE(${OTB_USE_FILE})
ELSE(OTB_FOUND)
  MESSAGE(FATAL_ERROR
    "Cannot built OTB project without OTB. Please set OTB_DIR.")
ENDIF(OTB_FOUND)

ADD_EXECUTABLE(Pipeline Pipeline.cxx)
TARGET_LINK_LIBRARIES(Pipeline ${OTB_LIBRARIES})

ADD_EXECUTABLE(FilteringPipeline FilteringPipeline.cxx)
TARGET_LINK_LIBRARIES(FilteringPipeline ${OTB_LIBRARIES})

ADD_EXECUTABLE(ScalingPipeline ScalingPipeline.cxx)
TARGET_LINK_LIBRARIES(ScalingPipeline ${OTB_LIBRARIES})

ADD_EXECUTABLE(Multispectral Multispectral.cxx)
TARGET_LINK_LIBRARIES(Multispectral ${OTB_LIBRARIES})

ADD_EXECUTABLE(SmartFilteringPipeline SmartFilteringPipeline.cxx)
TARGET_LINK_LIBRARIES(SmartFilteringPipeline ${OTB_LIBRARIES})

ADD_EXECUTABLE(ExtractPlot ExtractPlot.cxx)
TARGET_LINK_LIBRARIES(ExtractPlot ${OTB_LIBRARIES})
