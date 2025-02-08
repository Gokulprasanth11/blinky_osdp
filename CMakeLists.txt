# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.21.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky_prosense)

# Include custom directories only if necessary
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/subsys/mgmt/osdp/src)

# Specify application sources
target_sources(app PRIVATE
    src/main.c
    subsys/mgmt/osdp1/src/osdp.c
)
