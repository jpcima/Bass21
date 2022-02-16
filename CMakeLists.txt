cmake_minimum_required(VERSION 3.14)
project(Bass21 VERSION "0.0.1" LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(FaustWrap)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
find_package(PkgConfig)

#------------------------------------------------------------------------------#
# DSP core                                                                     #
#------------------------------------------------------------------------------#

# TODO: change to OFF when implemented
option(BASS21_USE_FAUST_DSP "Prefer using Faust DSP instead of C++" ON)

add_library(Bass21DSP STATIC EXCLUDE_FROM_ALL
  "sources/dsp/Core.h"
  "sources/dsp/Core.cpp"
  "sources/dsp/Bass21Definitions.h")

target_include_directories(Bass21DSP
  PUBLIC
  "sources")

if(BASS21_USE_FAUST_DSP)
  add_faust_command(
    "sources/dsp/Bass21Faust.dsp"
    "sources/dsp/Bass21Faust.hxx"
    IN_PLACE
    DOUBLE
    MATH_APPROXIMATION
    CLASS_NAME "Bass21FaustDSP"
    IMPORT_DIRS "sources/dsp")

  target_sources(Bass21DSP PRIVATE
    "sources/dsp/Bass21Faust.hxx")

  target_compile_definitions(Bass21DSP
    PRIVATE
    "USE_FAUST_DSP")
else()
  target_sources(Bass21DSP PRIVATE
    "sources/dsp/Bass21Cpp.cpp"
    "sources/dsp/Bass21Cpp.h"
    "sources/dsp/cpp/Bass21Filters.cpp"
    "sources/dsp/cpp/Bass21Filters.h"
    "sources/dsp/cpp/FilterTransfer.cpp"
    "sources/dsp/cpp/FilterTransfer.h"
    "sources/dsp/cpp/Filter.h")
endif()

target_include_directories(Bass21DSP
  PRIVATE
  "thirdparty/iPlug2"
  "thirdparty/hiir-1.33"
  "thirdparty/blink"
  "thirdparty/DISTRHO/sources")

if(MSVC)
  target_compile_options(Bass21DSP PRIVATE "/fp:fast")
else()
  target_compile_options(Bass21DSP PRIVATE "-ffast-math")
endif()

#------------------------------------------------------------------------------#
# JUCE plugin                                                                  #
#------------------------------------------------------------------------------#

option(BASS21_JUCE "Build a JUCE plugin" ON)
option(BASS21_COPY_AFTER_BUILD "Copy the JUCE plugin after build" OFF)

if(BASS21_JUCE)
  FetchContent_Declare(juce
    URL "https://github.com/juce-framework/JUCE/archive/refs/tags/6.1.4.tar.gz"
    URL_HASH "SHA512=d956bbb1c8226b03f529332cb285799c732d0d4d564df4a253284219908391ba4b4ce3ea987dbcfbb42bb592336cf7edc14f24a9b2f898bf996afb1416bba062")

  FetchContent_GetProperties(juce)
  if(NOT juce_POPULATED)
    FetchContent_Populate(juce)
    add_subdirectory("${juce_SOURCE_DIR}" "${juce_BINARY_DIR}" EXCLUDE_FROM_ALL)
  endif()

  juce_add_plugin(Bass21
    PLUGIN_CODE Bs21
    PLUGIN_MANUFACTURER_CODE Juju
    PRODUCT_NAME "Bass21"
    COMPANY_NAME "JPC electronics"
    FORMATS AU VST3
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    VST3_CATEGORIES "Fx Distortion EQ Filter"
    AU_MAIN_TYPE "kAudioUnitType_MusicEffect"
    COPY_PLUGIN_AFTER_BUILD "${BASS21_COPY_AFTER_BUILD}"
    NEEDS_CURL FALSE
    NEEDS_WEB_BROWSER FALSE)

  target_compile_definitions(Bass21
    PUBLIC
    "JUCE_WEB_BROWSER=0"
    "JUCE_USE_CURL=0"
    "JUCE_VST3_CAN_REPLACE_VST2=0"
    "JUCE_DISPLAY_SPLASH_SCREEN=0")

  target_sources(Bass21
    PRIVATE
    "sources/plugin/Processor.h"
    "sources/plugin/Processor.cpp"
    "sources/plugin/Editor.h"
    "sources/plugin/Editor.cpp")

  target_link_libraries(Bass21
    PRIVATE
    Bass21DSP
    juce::juce_audio_processors
    juce::juce_opengl
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)
endif()

#------------------------------------------------------------------------------#
# LV2 plugin                                                                   #
#------------------------------------------------------------------------------#

option(BASS21_LV2 "Build a LV2 plugin" ON)

if(BASS21_LV2)
  pkg_check_modules(LV2 "lv2" REQUIRED)

  add_library(Bass21_LV2 MODULE
    "sources/lv2/LV2Plugin.cpp")

  target_link_libraries(Bass21_LV2
    PRIVATE
    Bass21DSP)
  target_include_directories(Bass21_LV2
    PRIVATE
    ${LV2_INCLUDE_DIRS})
  set_target_properties(Bass21_LV2 PROPERTIES
    OUTPUT_NAME "Bass21"
    LIBRARY_OUTPUT_DIRECTORY "LV2/Bass21.lv2"
    PREFIX ""
    SUFFIX ".so")

  set(Bass21_LV2_BUNDLE_FILES
    "manifest.ttl"
    "modgui.ttl"
    "modgui/icon-bass21.html"
    "modgui/knobs/boxy/gold.png"
    "modgui/pedals/boxy75/black.png"
    "modgui/pedals/footswitch.png"
    "modgui/stylesheet-bass21.css"
    "modgui/utils/dropdown-arrow-black.png"
    "modgui/utils/dropdown-arrow-white.png")

  set(_filecounter 0)
  foreach(_file ${Bass21_LV2_BUNDLE_FILES})
    get_filename_component(_dir "${_file}" DIRECTORY)
    add_custom_command(
      OUTPUT "LV2/Bass21.lv2/${_file}"
      COMMAND "${CMAKE_COMMAND}" -E make_directory
          "${CMAKE_CURRENT_BINARY_DIR}/LV2/Bass21.lv2/${_dir}"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/sources/lv2/${_file}"
          "${CMAKE_CURRENT_BINARY_DIR}/LV2/Bass21.lv2/${_file}"
      DEPENDS "sources/lv2/${_file}")
    add_custom_target("Bass21_LV2_FileCopy_${_filecounter}" DEPENDS
      "LV2/Bass21.lv2/${_file}")
    add_dependencies(Bass21_LV2 "Bass21_LV2_FileCopy_${_filecounter}")
    math(EXPR _filecounter "${_filecounter}+1")
  endforeach()
endif()

#------------------------------------------------------------------------------#
# Test programs                                                                #
#------------------------------------------------------------------------------#

option(BASS21_TESTS "Build test programs" OFF)

if(NOT BASS21_USE_FAUST_DSP)
  add_executable(Bass21FilterCache
    "sources/tests/FilterCache.cpp")
  target_link_libraries(Bass21FilterCache
    PRIVATE
    Bass21DSP)
endif()
