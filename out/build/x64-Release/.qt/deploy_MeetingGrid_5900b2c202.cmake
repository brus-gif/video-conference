include("D:/deepseekworkspace/联网会议/out/build/x64-Release/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MeetingGrid-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtmultimedia;qtwebsockets")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "D:/deepseekworkspace/联网会议/out/build/x64-Release/bin/Release/MeetingGrid.exe"
    GENERATE_QT_CONF
)
