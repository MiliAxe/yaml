cmake_minimum_required(VERSION 3.20)

project(stb_image LANGUAGES C)

add_library(stb_image STATIC)
target_sources(stb_image PUBLIC src/stb_image.c)
target_include_directories(stb_image PUBLIC include)

# set_target_properties(stb_image PROPERTIES LINKER_LANGUAGE C)
# target_compile_definitions(stb_image PUBLIC STB_IMAGE_IMPLEMENTATION)
