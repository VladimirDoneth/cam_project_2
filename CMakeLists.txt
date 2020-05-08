cmake_minimum_required(VERSION 3.13)
project(cam_project_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(cam_project_2
        main.cpp
        lib_gphoto2_bash_adapter/gphoto2_bash.cpp lib_gphoto2_bash_adapter/gphoto2_bash.h
        web_sockets/lib_my_event_handler/delegate_ws.cpp web_sockets/lib_my_event_handler/delegate_ws.h
        web_sockets/lib_my_event_handler/event_ws.cpp web_sockets/lib_my_event_handler/event_ws.h
        web_sockets/lib_my_event_handler/handler_ws.h
        web_sockets/WebServer.cpp web_sockets/WebServer.h web_sockets/client_events.h
        my_web_server_worker.cpp my_web_server_worker.h
        #my_cam_adapter/cam_adapter.h my_cam_adapter/cam_adapter.cpp
        my_cam_adapter_2/cam_adapter.cpp my_cam_adapter_2/cam_adapter.h my_cam_adapter_2/cam_functions.h my_cam_adapter_2/context.cpp)

target_link_libraries(cam_project_2 seasocks "${ZLIB_LIBRARIES}")
target_link_libraries(cam_project_2 pthread z)
target_link_libraries(cam_project_2 gphoto2)
target_link_libraries(cam_project_2 gphoto2_port)

add_custom_command(TARGET cam_project_2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/server_files $<TARGET_FILE_DIR:cam_project_2>/src/server_files)