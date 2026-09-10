# CMake generated Testfile for 
# Source directory: D:/deepseekworkspace/联网会议
# Build directory: D:/deepseekworkspace/联网会议/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(gridtest "D:/deepseekworkspace/联网会议/out/build/x64-Debug/gridtest.exe")
set_tests_properties(gridtest PROPERTIES  _BACKTRACE_TRIPLES "D:/deepseekworkspace/联网会议/CMakeLists.txt;47;add_test;D:/deepseekworkspace/联网会议/CMakeLists.txt;0;")
add_test(signalingtest "D:/deepseekworkspace/联网会议/out/build/x64-Debug/signalingtest.exe")
set_tests_properties(signalingtest PROPERTIES  _BACKTRACE_TRIPLES "D:/deepseekworkspace/联网会议/CMakeLists.txt;58;add_test;D:/deepseekworkspace/联网会议/CMakeLists.txt;0;")
subdirs("server")
