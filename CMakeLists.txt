cmake_minimum_required(VERSION 3.7)
project(Bass21 VERSION "0.0.1" LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(FaustWrap)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PkgConfig)

add_subdirectory("thirdparty/JUCE" EXCLUDE_FROM_ALL)

#------------------------------------------------------------------------------#
# JUCE plugin                                                                  #
#------------------------------------------------------------------------------#

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
  COPY_PLUGIN_AFTER_BUILD FALSE
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
  "sources/plugin/Editor.cpp"
  "sources/dsp/Core.h"
  "sources/dsp/Core.cpp"
  "sources/dsp/Bass21.hxx")

add_faust_command(
  "sources/dsp/Bass21.dsp"
  "sources/dsp/Bass21.hxx"
  IN_PLACE
  DOUBLE
  MATH_APPROXIMATION
  CLASS_NAME "Bass21DSP"
  IMPORT_DIRS "sources/dsp")

target_include_directories(Bass21
  PRIVATE
  "sources")

target_link_libraries(Bass21
  PRIVATE
  juce::juce_audio_processors
  juce::juce_opengl
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags)

if(MSVC)
  target_compile_options(Bass21 PRIVATE "/fp:fast")
else()
  target_compile_options(Bass21 PRIVATE "-ffast-math")
endif()

###
target_include_directories(Bass21 PRIVATE
  "thirdparty/iPlug2"
  "thirdparty/hiir-1.33")

#------------------------------------------------------------------------------#
# LV2 plugin                                                                   #
#------------------------------------------------------------------------------#

option(BASS21_LV2 "Build a LV2 plugin" OFF)

if(BASS21_LV2)
  pkg_check_modules(LV2 "lv2" REQUIRED)

  add_library(Bass21_LV2 MODULE
    "sources/lv2/LV2Plugin.cpp"
    "sources/dsp/Core.h"
    "sources/dsp/Core.cpp")

  target_include_directories(Bass21_LV2
    PRIVATE
    "sources")
  target_link_libraries(Bass21_LV2
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

  target_include_directories(Bass21_LV2 PRIVATE
    "thirdparty/iPlug2"
    "thirdparty/hiir-1.33")
endif()
