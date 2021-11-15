add_executable(drone_visualizer 
src/main.cpp
src/drone_visualizer.cpp
)

target_include_directories(drone_visualizer PUBLIC include)
target_link_libraries(drone_visualizer OgreBites OgreRTShaderSystem)