# CMake generated Testfile for 
# Source directory: E:/Code/Marco/WorkSpace/MeetingGrid
# Build directory: E:/Code/Marco/WorkSpace/MeetingGrid/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(gridtest "E:/Code/Marco/WorkSpace/MeetingGrid/build/gridtest.exe")
set_tests_properties(gridtest PROPERTIES  _BACKTRACE_TRIPLES "E:/Code/Marco/WorkSpace/MeetingGrid/CMakeLists.txt;47;add_test;E:/Code/Marco/WorkSpace/MeetingGrid/CMakeLists.txt;0;")
add_test(signalingtest "E:/Code/Marco/WorkSpace/MeetingGrid/build/signalingtest.exe")
set_tests_properties(signalingtest PROPERTIES  _BACKTRACE_TRIPLES "E:/Code/Marco/WorkSpace/MeetingGrid/CMakeLists.txt;58;add_test;E:/Code/Marco/WorkSpace/MeetingGrid/CMakeLists.txt;0;")
subdirs("server")
