add_executable(FareyTestExe test.cpp)


# Add Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(FareyTestExe PRIVATE Catch2::Catch2WithMain)

# Link tests to core library
target_link_libraries(FareyTestExe PRIVATE FareyCoreLib)

# Link tests exe to core tests library
add_subdirectory(core)

include(CTest)
include(Catch)
catch_discover_tests(FareyTestExe)
