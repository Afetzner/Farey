add_library(FareyCoreTestLib STATIC)

# Add Catch2
find_package(Catch2 3 REQUIRED)
target_link_libraries(FareyCoreTestLib PRIVATE Catch2::Catch2)

# Link tests to core library
target_link_libraries(FareyCoreTestLib PUBLIC FareyCoreLib)

include(sources.cmake)
target_sources(FareyCoreTestLib PUBLIC ${SOURCES})
