cmake_minimum_required(VERSION 2.6)
if(${CMAKE_VERSION} VERSION_LESS 2.8.8)
  set(LIBTYPE STATIC)
else()
  set(LIBTYPE OBJECT)
  #cmake_policy(SET CMP0015 NEW)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

project(SusyFit)

# default boolean flags
option(NOMCMC "No MCMC" OFF)
option(MPIBAT "Use MPI BAT" OFF)
option(BAT_INSTALL "Install BAT" OFF)
option(LOOPTOOLS "Use LoopTools library" OFF)
option(INTEL_FORTRAN "Use ifort libraries" OFF)

# default paths
if(NOT SUSYFIT_INSTALL_DIR)
  set(SUSYFIT_INSTALL_DIR /usr/local)
endif()
if(NOT BAT_INSTALL_DIR)
  set(BAT_INSTALL_DIR /usr/local)
endif()

# absolute paths
if(NOT IS_ABSOLUTE ${SUSYFIT_INSTALL_DIR})
   set(SUSYFIT_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/${SUSYFIT_INSTALL_DIR})
endif()
if(NOT IS_ABSOLUTE ${BAT_INSTALL_DIR})
   set(BAT_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/${BAT_INSTALL_DIR})
endif()

# the path to the home directory
STRING(REGEX REPLACE "^~" "$ENV{HOME}" SUSYFIT_INSTALL_DIR ${SUSYFIT_INSTALL_DIR})
STRING(REGEX REPLACE "^~" "$ENV{HOME}" BAT_INSTALL_DIR ${BAT_INSTALL_DIR})

# Fortran libraries 
if(INTEL_FORTRAN)
  set(LFORTRAN "ifport;ifcore;imf;svml;irc")
  #set(LFORTRAN "ifport;ifcore;imf;svml;irc;ipgo;irc_s")
else()
  set(LFORTRAN "gfortran")
endif()

##########  Colored output  ##########

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColReset "${Esc}[m")
  set(Red         "${Esc}[31m")
  set(RedBold     "${Esc}[1;31m")
  set(Magenta     "${Esc}[35m")
  set(MagentaBold "${Esc}[1;35m")
endif()

##########  BAT  ##########

if(NOT NOMCMC)

if(MPIBAT)
  add_definitions(-D_MPI)
  include_directories(${MPI_INCLUDE_DIR})
  find_package(MPI REQUIRED)
  if(MPI_CXX_FOUND)
    #set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER}) # This doesn't work!
    #set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_CXX_COMPILE_FLAGS}) # unnecessary
    #set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_CXX_LINK_FLAGS}) # unnecessary
    include_directories(${MPI_CXX_INCLUDE_PATH})
  else(MPI_CXX_FOUND)
    message(FATAL_ERROR "MPI requested but implementation could not be found. Please specify the location of the mpic++ compiler with -DCMAKE_CXX_COMPILER=<path to mpi>/mpic++ and the MPI include directory with -DMPI_INCLUDE_DIR=<mpi include dir>")
  endif(MPI_CXX_FOUND)
endif(MPIBAT)

message(STATUS "looking for BAT in ${BAT_INSTALL_DIR}")
find_path(IBAT "BCModel.h" ${BAT_INSTALL_DIR}/include/BAT NO_DEFAULT_PATH)
find_library(LBAT NAMES libBAT.a BAT PATHS ${BAT_INSTALL_DIR}/lib NO_DEFAULT_PATH)
if(IBAT AND LBAT)
  set(BAT_INC ${IBAT})
  string(REGEX REPLACE "/BAT$" "" BAT_INC ${BAT_INC})
  string(REGEX REPLACE "/libBAT.*$" "" BAT_LIB ${LBAT})
  message(STATUS "Found BAT include in ${BAT_INC}")
  message("   and libs in ${BAT_LIB}")
  if(MPIBAT)
    message(STATUS "${MagentaBold}Please make sure that the installed BAT library has been compiled with our patch for MPI support.${ColReset}")
  endif()
else(IBAT AND LBAT)
  if(NOT BAT_INSTALL)
    message(FATAL_ERROR "BAT could not be found. Please supply the correct path to BAT with -DBAT_INSTALL_DIR=<BAT install path> or install BAT with the option -DBAT_INSTALL=on, where I'll download and install BAT at the default location /usr/local/. If you want me to install BAT at a custom location, you can specify it with -DBAT_INSTALL_DIR=<BAT custom install path>.")  
  endif()
endif(IBAT AND LBAT)

if(BAT_INSTALL)
  if(NOT IBAT OR NOT LBAT)
    message(STATUS "${MagentaBold}I'll download and install BAT into ${BAT_INSTALL_DIR}.${ColReset}")
    set(BAT_INC ${BAT_INSTALL_DIR}/include)
    set(BAT_LIB ${BAT_INSTALL_DIR}/lib)
    set(BAT_URL http://www.mppmu.mpg.de/bat/source/BAT-0.9.3.tar.gz)
    include(ExternalProject)
    if(MPIBAT)
      set(PATCH patch -p1 -N < ${CMAKE_CURRENT_SOURCE_DIR}/BAT_mpi_patch.txt)
      if(BAT_INSTALL_DIR)
        set(CONFIGURE_BAT CXX=mpic++ ./configure --prefix=${BAT_INSTALL_DIR})
      else()
        set(CONFIGURE_BAT CXX=mpic++ ./configure)
      endif()
      ExternalProject_Add(
        BATBUILD
        PREFIX BATBUILD
        SOURCE_DIR BATBUILD/src
        STAMP_DIR BATBUILD/src
        BINARY_DIR BATBUILD/src
        INSTALL_DIR BATBUILD/src
        URL ${BAT_URL}
        PATCH_COMMAND ${PATCH}
        CONFIGURE_COMMAND ${CONFIGURE_BAT}
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        )
     else(MPIBAT)
       if(BAT_INSTALL_DIR)
         set(CONFIGURE_BAT ./configure --prefix=${BAT_INSTALL_DIR})
       else()
         set(CONFIGURE_BAT ./configure)
       endif()
       ExternalProject_Add(
         BATBUILD
         PREFIX BATBUILD
         SOURCE_DIR BATBUILD/src
         STAMP_DIR BATBUILD/src
         BINARY_DIR BATBUILD/src
         INSTALL_DIR BATBUILD/src
         URL ${BAT_URL}
         CONFIGURE_COMMAND ${CONFIGURE_BAT}
         BUILD_COMMAND make
         INSTALL_COMMAND make install
         )
    endif(MPIBAT)
  endif(NOT IBAT OR NOT LBAT)
endif(BAT_INSTALL)

find_library(LBATM NAMES libBATmodels.a BATmodels PATHS ${BAT_LIB} NO_DEFAULT_PATH)

endif(NOT NOMCMC)

##########  BOOST  ##########

if(NOT BOOST_INC)
  find_file(IBOOST "boost/program_options.hpp")
else()
  find_file(IBOOST "program_options.hpp" PATHS ${BOOST_INC} NO_DEFAULT_PATH)
endif()
if(NOT IBOOST)
  message(FATAL_ERROR "Boost include files could not be found. Please specify the Boost include path with -DBOOST_INC=<include path>/boost/.")
else()
  get_filename_component(BOOST_INC ${IBOOST} PATH)
  string(REGEX REPLACE "/boost$" "" BOOST_INC ${BOOST_INC})
  message(STATUS "Found Boost include files in ${BOOST_INC}")
endif()

#if(NOT BOOST_LIB)
#  find_library(LBOOST NAMES libboost_program_options.a boost_program_options)
#else()
#  find_library(LBOOST NAMES libboost_program_options.a boost_program_options PATHS ${BOOST_LIB} NO_DEFAULT_PATH)
#endif()
#if(NOT LBOOST)
#  message(FATAL_ERROR "Boost library could not be found. Please specify the Boost library path with -DBOOST_LIB=<library path>.")
#else()
#  get_filename_component(BOOST_LIB ${LBOOST} PATH)
#  message(STATUS "Found Boost library in ${BOOST_LIB}")
#endif()

##########  ROOT  ##########

if(NOT ROOT_CONFIG_PATH)
  find_program(ROOT_CONFIG root-config)
else()
  find_program(ROOT_CONFIG root-config PATHS ${ROOT_CONFIG_PATH} NO_DEFAULT_PATH)
endif()
if(NOT ROOT_CONFIG)
  message(FATAL_ERROR "root-config could not be found. Please specify the directory of root-config command with -DROOT_CONFIG_PATH=<path>.")
else()
  execute_process(COMMAND ${ROOT_CONFIG} --version
                  OUTPUT_VARIABLE ROOT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "ROOT version: ${ROOT_VERSION}")
  execute_process(COMMAND ${ROOT_CONFIG} --cflags
                  OUTPUT_VARIABLE ROOT_CFLAGS
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "ROOT cflags: ${ROOT_CFLAGS}")
  execute_process(COMMAND ${ROOT_CONFIG} --libs
                  OUTPUT_VARIABLE ROOT_LIBS
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "ROOT libs: ${ROOT_LIBS}")
  execute_process(COMMAND ${ROOT_CONFIG} --ldflags
                  OUTPUT_VARIABLE ROOT_LDFLAGS
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "ROOT ldflags: ${ROOT_LDFLAGS}")
endif()

##########  GSL  ##########

if(NOT GSL_CONFIG_PATH)
  find_program(GSL_CONFIG gsl-config PATHS ${GSL_CONFIG_PATH})
else()
  find_program(GSL_CONFIG gsl-config PATHS ${GSL_CONFIG_PATH} NO_DEFAULT_PATH)
endif()
if(NOT GSL_CONFIG)
  message(FATAL_ERROR "gsl-confg could not be found. Please specify the directory of gsl-config command with -DGSL_CONFIG_PATH=<path>.")
else()
  execute_process(COMMAND ${GSL_CONFIG} --version
                  OUTPUT_VARIABLE GSL_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "GSL version: ${GSL_VERSION}")
  execute_process(COMMAND ${GSL_CONFIG} --cflags
                  OUTPUT_VARIABLE GSL_CFLAGS
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "GSL cflags: ${GSL_CFLAGS}")
  execute_process(COMMAND ${GSL_CONFIG} --libs
                  OUTPUT_VARIABLE GSL_LIBS
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "GSL libs: ${GSL_LIBS}")
endif()

##########  LoopTools  ##########

if(LOOPTOOLS)
  add_definitions(-DUSE_LOOPTOOLS)
  set(LIBOOPTOOLS ooptools)
  if(NOT LT_DIR)
    find_file(ILT "clooptools.h")
    find_library(LLT NAMES libooptools.a ooptools)
  else()
    find_file(ILT "clooptools.h" PATHS ${LT_DIR}/include NO_DEFAULT_PATH)
    find_library(LLT NAMES libooptools.a ooptools PATHS ${LT_DIR}/lib NO_DEFAULT_PATH PATH_SUFFIXES lib lib32 lib64)
  endif()
  if(ILT AND LLT)
    set(LT_INC ${ILT})
    string(REGEX REPLACE "/libooptools.*$" "" LT_LIB ${LLT})
    message(STATUS "Found LoopTools include in ${LT_INC} and libs in ${LT_LIB}")
  else()
    message(FATAL_ERROR "LoopTools include files and libs could not be found. Please specify the LoopTools path with -DLT_DIR=<LoopTools installation path>.")
  endif()
endif(LOOPTOOLS)

##########  DEBUG  ##########

#message("LFORTRAN: ${LFORTRAN}")

#message("BAT_INC: ${BAT_INC}")
#message("BAT_LIB: ${BAT_LIB}")
#message("LBAT: ${LBAT}")
#message("LBATM: ${LBATM}")

#message("BOOST_INC: ${BOOST_INC}")
#message("BOOST_LIB: ${BOOST_LIB}")
#message("LBOOST: ${LBOOST}")

#message("ROOT_CFLAGS: ${ROOT_CFLAGS}")
#message("ROOT_LIBS: ${ROOT_LIBS}")
#message("ROOT_LDFLAGS: ${ROOT_LDFLAGS}")

#message("GSL_CFLAGS: ${GSL_CFLAGS}")
#message("GSL_LIBS: ${GSL_LIBS}")

#message("LT_INC: ${LT_INC}")
#message("LT_LIB: ${LT_LIB}")
#message("LLT: ${LLT}")
#message("LIBOOPTOOLS: ${LIBOOPTOOLS}")

##############################

set(PROJECTLIST ComputeObservables InputParser EW NewPhysics Observables StandardModel LoopFunctions gslpp)
if(NOT NOMCMC)
  set(PROJECTLIST MonteCarlo ${PROJECTLIST})
endif(NOT NOMCMC)

# sub-directories
foreach(_project ${PROJECTLIST})
  add_subdirectory(${_project})
endforeach(_project)

# SusyFit library libSusyFit.a
if(${LIBTYPE} STREQUAL "OBJECT") 
  # for CMake v2.8.8 or later
  foreach(_project ${PROJECTLIST})
    set(OBJECTLIST ${OBJECTLIST} $<TARGET_OBJECTS:${_project}>)
  endforeach(_project)
  add_library(SusyFit STATIC ${OBJECTLIST})
else()
  # for older CMake
  set(CMAKE_CXX_FLAGS "-Wall ${ROOT_CFLAGS} ${GSL_CFLAGS}")
  if(NOT NOMCMC)
    include_directories(${BAT_INC})
  endif(NOT NOMCMC)
  if(LOOPTOOLS)
    include_directories(${LT_INC})
  endif(LOOPTOOLS)
  include_directories(${BOOST_INC})
  foreach(_project ${PROJECTLIST})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${_project}/src)
    file(GLOB SOURCES ${_project}/src/*.cpp)
    set(SRCLIST ${SRCLIST} ${SOURCES})
  endforeach(_project)
  add_library(SusyFit STATIC ${SRCLIST})
endif()
add_dependencies(SusyFit BATBUILD)
INSTALL(TARGETS SusyFit DESTINATION ${SUSYFIT_INSTALL_DIR}/lib COMPONENT library)

# a single commnon header file SusyFit.h
#list(REVERSE PROJECTLIST)
foreach(_project ${PROJECTLIST})
  file(GLOB HEADERS ${_project}/src/*.h)
  foreach(_header ${HEADERS})
    get_filename_component(_tmp ${_header} NAME)
    set(INCLUDE_LIST "${INCLUDE_LIST}\#include\ \"${_tmp}\"\n")
  endforeach(_header)
endforeach(_project)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/SusyFit.h.in"
               "${CMAKE_CURRENT_BINARY_DIR}/SusyFit.h" @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/SusyFit.h 
        DESTINATION ${SUSYFIT_INSTALL_DIR}/include/SusyFit COMPONENT headers)

# pkg-config
#find_package(PkgConfig)
#if(PKG_CONFIG_FOUND)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/SusyFit.pc.in" 
                 "${CMAKE_CURRENT_BINARY_DIR}/SusyFit.pc" @ONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/susyfit-config.in" 
                 "${CMAKE_CURRENT_BINARY_DIR}/susyfit-config" @ONLY)
  INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/susyfit-config ${CMAKE_CURRENT_BINARY_DIR}/SusyFit.pc 
          DESTINATION ${SUSYFIT_INSTALL_DIR}/bin COMPONENT susyfit-config)
#endif()

# example programs
set(EXAMPLE_CXXFLAGS "-I${BOOST_INC} ${ROOT_CFLAGS} ${GSL_CFLAGS}")
set(EXAMPLE_LIBS "${ROOT_LIBS} ${ROOT_LDFLAGS} ${GSL_LIBS}")
if(LOOPTOOLS)
  set(EXAMPLE_CXXFLAGS "-I${LT_INC} ${EXAMPLE_CXXFLAGS}")
  set(EXAMPLE_LIBS "-L${LT_LIB} ${LIBOOPTOOLS} -l${LFORTRAN} ${EXAMPLE_LIBS}")
endif(LOOPTOOLS)
if(NOT NOMCMC)
  set(EXAMPLE_CXXFLAGS "-I${BAT_INC} ${EXAMPLE_CXXFLAGS}")
  set(EXAMPLE_LIBS "-L${BAT_LIB} -lBATmodels -lBAT ${EXAMPLE_LIBS}")
  if(MPIBAT)
    set(EXAMPLE_CXXFLAGS "${MPI_COMPILE_FLAGS} ${EXAMPLE_CXXFLAGS}")
    set(EXAMPLE_LIBS "${MPI_LINK_FLAGS} ${MPI_LIBRARIES} ${EXAMPLE_LIBS}")
  endif(MPIBAT)
endif(NOT NOMCMC)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/LibMode_config/Makefile.in"
               "${CMAKE_CURRENT_BINARY_DIR}/examples/LibMode_config/Makefile" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/LibMode_config/libmode_config.cpp"
               "${CMAKE_CURRENT_BINARY_DIR}/examples/LibMode_config/libmode_config.cpp" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/LibMode_header/Makefile.in"
               "${CMAKE_CURRENT_BINARY_DIR}/examples/LibMode_header/Makefile" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/LibMode_header/libmode_header.cpp"
               "${CMAKE_CURRENT_BINARY_DIR}/examples/LibMode_header/libmode_header.cpp" @ONLY)
file(GLOB CONF_FILES ${CMAKE_CURRENT_SOURCE_DIR}/examples-src/configs/*.conf)
foreach(_confFile ${CONF_FILES})
  get_filename_component(_confFileName ${_confFile} NAME)
  configure_file("${_confFile}" 
                 "${CMAKE_CURRENT_BINARY_DIR}/examples/configs/${_confFileName}" COPYONLY)
endforeach(_confFile)
if(NOT NOMCMC)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/MonteCarloMode/Makefile.in"
                 "${CMAKE_CURRENT_BINARY_DIR}/examples/MonteCarloMode/Makefile" @ONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/MonteCarloMode/MCMC.cpp"
                 "${CMAKE_CURRENT_BINARY_DIR}/examples/MonteCarloMode/MCMC.cpp" @ONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/examples-src/MonteCarloMode/MonteCarlo.conf"
                 "${CMAKE_CURRENT_BINARY_DIR}/examples/MonteCarloMode/MonteCarlo.conf" COPYONLY)
endif(NOT NOMCMC)

# make uninstall
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" @ONLY)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} 
                  -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

