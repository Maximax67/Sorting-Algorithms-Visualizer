add_executable (Sorter WIN32 "main.cpp" "App.h" "Algorithms/Algorithm.h" "Algorithms/Algorithm.cpp" "Algorithms/QuickSort.cpp" "App.cpp" "Controller.h" "Controller.cpp" "Interface.h" "Interface.cpp" "Algorithms/QuickSort.h" "Algorithms/Statistic.h" "Algorithms/Statistic.cpp" "Random.h" "Random.cpp" "Constants.h" "Algorithms/Heapsort.cpp" "Algorithms/Heapsort.h" "Algorithms/SmoothSort.h" "Algorithms/SmoothSort.cpp" "WindowsConfig.h" "FileProcessor.h" "FileProcessor.cpp" "Resources/icons.h" "Resources/icons.hpp" "Resources/Ubuntu-M.hpp" "Resources/icon.hpp")

if (WIN32)
    target_link_options(Sorter PRIVATE "/SUBSYSTEM:WINDOWS")
    set_target_properties(Sorter PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Sorter PROPERTY CXX_STANDARD 20)
endif()
