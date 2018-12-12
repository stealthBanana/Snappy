cmake_minimum_required(VERSION 3.12)
project(Snappy C)

set(CMAKE_C_STANDARD 99)

add_executable(Snappy source/main.c source/compression.c source/decompression.c header/compression.h header/decompression.h source/hashTable.c header/hashTable.h)