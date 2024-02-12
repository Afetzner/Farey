add_executable(FareyTestExe test.cpp)

# Link tests exe to core tests library
add_subdirectory(core)
target_link_libraries(FareyTestExe PUBLIC FareyCoreTestLib)

# Add Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(FareyTestExe PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(FareyTestExe)
