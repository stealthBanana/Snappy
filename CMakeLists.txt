cmake_minimum_required(VERSION 3.12)
project(Snappy C)

set(CMAKE_C_STANDARD 99)

add_executable(Snappy source/main.c source/compression.c source/decompression.c header/compression.h header/decompression.h source/hashTable.c header/hashTable.h source/match.c header/match.h source/literal.c header/literal.h source/utilities.c header/utilities.h source/stringBuffer.c header/stringBuffer.h)
add_executable(Snappy source/main.c source/compression.c source/decompression.c header/compression.h header/decompression.h)