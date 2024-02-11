add_library(FareyCoreLib STATIC)

include(sources.cmake)
target_sources(FareyCoreLib PUBLIC ${SOURCES})
target_include_directories(FareyCoreLib PUBLIC include)

add_subdirectory(runner)
