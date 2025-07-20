cmake_minimum_required(VERSION 3.10)
project(Snitch)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    stats/CPU
    stats/GPU
    stats/OS
    stats/HOST
    stats/UPTIME
    stats/USER
    stats/KERNEL
)

add_executable(fetch
    main.cpp
    stats/CPU/CPU.cpp
    stats/GPU/GPU.cpp
    stats/OS/OS.cpp
    stats/HOST/HOST.cpp
    stats/UPTIME/UPTIME.cpp
    stats/USER/USER.cpp
    stats/KERNEL/KERNEL.cpp
)

