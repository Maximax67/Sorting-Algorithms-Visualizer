# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Sorter" CXX)

add_subdirectory ("Sorter")

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_definitions(ImDrawIdx=unsigned)
add_compile_definitions(IMGUI_DISABLE_OBSOLETE_FUNCTIONS)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/WX /W3 /permissive-)
    add_compile_options(/MP)
endif()

find_package(Threads REQUIRED)

add_subdirectory(extern)

find_library(COMDLG32_LIB comdlg32)

target_include_directories("Sorter" PRIVATE include)
target_link_libraries("Sorter" PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML ImPlot::ImPlot Threads::Threads ${COMDLG32_LIB})
