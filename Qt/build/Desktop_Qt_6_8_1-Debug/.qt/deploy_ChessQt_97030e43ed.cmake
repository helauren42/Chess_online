include(/home/helauren/ChessQt/build/Desktop_Qt_6_8_1-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/ChessQt-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/helauren/ChessQt/build/Desktop_Qt_6_8_1-Debug/ChessQt
    GENERATE_QT_CONF
)
