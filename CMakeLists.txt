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

add_subdirectory("thirdparty/JUCE" EXCLUDE_FROM_ALL)

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
  "sources/dsp/Bass21.hxx")

add_faust_command(
  "sources/dsp/Bass21.dsp"
  "sources/dsp/Bass21.hxx"
  IN_PLACE
  MATH_APPROXIMATION
  CLASS_NAME "Bass21"
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
