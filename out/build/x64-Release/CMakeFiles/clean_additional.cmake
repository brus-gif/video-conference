# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\MeetingGrid_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MeetingGrid_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\gridtest_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\gridtest_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\signalingtest_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\signalingtest_autogen.dir\\ParseCache.txt"
  "MeetingGrid_autogen"
  "gridtest_autogen"
  "server\\CMakeFiles\\MeetingGridServer_autogen.dir\\AutogenUsed.txt"
  "server\\CMakeFiles\\MeetingGridServer_autogen.dir\\ParseCache.txt"
  "server\\MeetingGridServer_autogen"
  "signalingtest_autogen"
  )
endif()
