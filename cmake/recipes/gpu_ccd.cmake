if(TARGET gpu_ccd::gpu_ccd)
    return()
endif()

message(STATUS "Third-party: creating target 'gpu_ccd::gpu_ccd'")

option(STQ_WITH_CPU  "Enable CPU Implementation"  ON)
set(STQ_WITH_CUDA ON CACHE BOOL "Enable CUDA Implementation" FORCE)

include(FetchContent)
FetchContent_Declare(
    gpu_ccd
    GIT_REPOSITORY https://github.com/dbelgrod/CCD-GPU.git
    GIT_TAG feb54c029a5fb7b8dd195b5485c3f9e85324199b
    GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(gpu_ccd)

add_library(gpu_ccd::gpu_ccd ALIAS CCDGPU)

set_target_properties(STQ_CPU PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(CCDGPU PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(STQ_CUDA PUBLIC KEEP_CPU_OVERLAPS)