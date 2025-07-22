cmake_minimum_required(VERSION 3.10)
project(Snitch)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    stats/cpu
    stats/gpu
    stats/os
    stats/host
    stats/uptime
    stats/user
    stats/kernel
    stats/packages
    stats/memory
    stats/terminal
    stats/shell
    stats/battery
    stats/disk
    stats/desktop
    config/
    utils
)

add_executable(fetch
    main.cpp
    stats/cpu/cpu.cpp
    stats/gpu/gpu.cpp
    stats/os/os.cpp
    stats/host/host.cpp
    stats/uptime/uptime.cpp
    stats/user/user.cpp
    stats/kernel/kernel.cpp
    stats/packages/packages.cpp
    stats/memory/memory.cpp
    stats/terminal/terminal.cpp
    stats/shell/shell.cpp
    stats/battery/battery.cpp
    stats/disk/disk.cpp
    stats/desktop/desktop.cpp
    config/config.cpp
    utils/utils.h
)

