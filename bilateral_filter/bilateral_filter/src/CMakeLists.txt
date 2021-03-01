

add_library(${PROJECT_NAME}_lib SHARED filter.cpp)

target_link_libraries(${PROJECT_NAME}_lib Qt5::Core)
target_link_libraries (${PROJECT_NAME}_lib Qt5::Gui)
