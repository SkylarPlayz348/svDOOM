## SDL3 Config ##
set(SDL_BUILD_TEST_LIB OFF)
set(SDL_INSTALL ON)
add_subdirectory(SDL)

## FluidSynth Config ##
add_subdirectory(fluidsynth)

## SDL3_mixer Config ##
set(FluidSynth_DIR "${CMAKE_CURRENT_BINARY_DIR}/fluidsynth")
add_subdirectory(SDL_mixer)

## cglm Config
add_subdirectory(cglm)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3-shared libfluidsynth SDL3_mixer::SDL3_mixer cglm)