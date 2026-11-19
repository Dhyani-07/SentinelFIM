# SentinelFIM

A file integrity and ransomware-behavior monitor written in C++17.

## Status
 Under development (Phase 0: project setup)

## Planned features
- SHA-256 baseline of monitored folders
- Detection of modified / new / deleted files
- Real-time monitoring
- Ransomware heuristics (mass changes, extension changes, entropy spikes)
- JSON alerts and logging

## Build (Windows)
Requires Visual Studio Build Tools 2022, CMake, vcpkg.

    cmake --preset default
    cmake --build build --config Release
    .\build\Release\sentinel.exe

## Disclaimer
For educational use. Only run it on systems you own.
