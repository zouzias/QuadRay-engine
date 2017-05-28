
INC_PATH =                                  \
        -I../core/config/                   \
        -I../core/engine/                   \
        -I../core/system/                   \
        -I../core/tracer/                   \
        -I../data/materials/                \
        -I../data/objects/                  \
        -I../data/textures/                 \
        -Iscenes/

SRC_LIST =                                  \
        ../core/engine/engine.cpp           \
        ../core/engine/object.cpp           \
        ../core/engine/rtgeom.cpp           \
        ../core/engine/rtimag.cpp           \
        ../core/system/system.cpp           \
        ../core/tracer/tracer.cpp           \
        ../core/tracer/tracer_128v1.cpp     \
        ../core/tracer/tracer_128v2.cpp     \
        ../core/tracer/tracer_128v4.cpp     \
        ../core/tracer/tracer_256v1_r8.cpp  \
        ../core/tracer/tracer_256v1.cpp     \
        ../core/tracer/tracer_256v2.cpp     \
        ../core/tracer/tracer_256v4.cpp     \
        ../core/tracer/tracer_256v8.cpp     \
        ../core/tracer/tracer_512v1.cpp     \
        ../core/tracer/tracer_512v2.cpp     \
        core_test.cpp

LIB_PATH =

LIB_LIST =                                  \
        -lm                                 \
        -lstdc++


build: core_test_p32Bg4 core_test_p32Bp7 core_test_p32Bp8

strip:
	powerpc-linux-gnu-strip core_test.p32*

clean:
	rm core_test.p32*


core_test_p32Bg4:
	powerpc-linux-gnu-g++ -O3 -g -static \
        -DRT_LINUX -DRT_P32 -DRT_128=1 -DRT_256_R8=1 \
        -DRT_POINTER=32 -DRT_ADDRESS=32 -DRT_ELEMENT=32 -DRT_ENDIAN=1 \
        -DRT_DEBUG=0 -DRT_PATH="../" \
        -DRT_EMBED_STDOUT=0 -DRT_EMBED_FILEIO=0 -DRT_EMBED_TEX=1 \
        ${INC_PATH} ${SRC_LIST} ${LIB_PATH} ${LIB_LIST} -o core_test.p32Bg4

core_test_p32Bp7:
	powerpc-linux-gnu-g++ -O3 -g -static \
        -DRT_LINUX -DRT_P32 -DRT_128=1+2 -DRT_256_R8=1 -DRT_256=1 -DRT_512=1 \
        -DRT_POINTER=32 -DRT_ADDRESS=32 -DRT_ELEMENT=32 -DRT_ENDIAN=1 \
        -DRT_DEBUG=0 -DRT_PATH="../" \
        -DRT_EMBED_STDOUT=0 -DRT_EMBED_FILEIO=0 -DRT_EMBED_TEX=1 \
        ${INC_PATH} ${SRC_LIST} ${LIB_PATH} ${LIB_LIST} -o core_test.p32Bp7

core_test_p32Bp8:
	powerpc-linux-gnu-g++ -O3 -g -static \
        -DRT_LINUX -DRT_P32 -DRT_128=1+2+4 -DRT_256_R8=1 \
        -DRT_256=1+2 -DRT_512=1+2 \
        -DRT_POINTER=32 -DRT_ADDRESS=32 -DRT_ELEMENT=32 -DRT_ENDIAN=1 \
        -DRT_DEBUG=0 -DRT_PATH="../" \
        -DRT_EMBED_STDOUT=0 -DRT_EMBED_FILEIO=0 -DRT_EMBED_TEX=1 \
        ${INC_PATH} ${SRC_LIST} ${LIB_PATH} ${LIB_LIST} -o core_test.p32Bp8


# On Ubuntu 16.04 Live CD add "universe multiverse" to "main restricted"
# in /etc/apt/sources.list (sudo gedit /etc/apt/sources.list) then run:
# sudo apt-get update (ignoring the old database errors in the end)
#
# Prerequisites for the build:
# (cross-)compiler for PowerPC is installed and in the PATH variable.
# sudo apt-get install g++-powerpc-linux-gnu
#
# Prerequisites for emulation:
# recent QEMU(-2.5) is installed or built from source and in the PATH variable.
# sudo apt-get install qemu
#
# Building/running CORE test:
# make -f core_make_p32.mk
# qemu-ppc -cpu G4 core_test.p32Bg4 -i -a
# (should produce antialiased (-a) images (-i) in the ../dump subfolder)
# qemu-ppc64abi32 -cpu POWER7 core_test.p32Bp7 -i -a
# (should produce antialiased (-a) images (-i) in the ../dump subfolder)
# qemu-ppc64abi32 -cpu POWER8 core_test.p32Bp8 -i -a
# (should produce antialiased (-a) images (-i) in the ../dump subfolder)

# core_test uses runtime SIMD target selection, multiple can be specified above
# on RISC targets top value above is chosen by default, use -n/-k/-s to override
# 256-bit SIMD is achieved by combining pairs of 128-bit registers/instructions
# 512-bit SIMD is achieved by combining quads of 128-bit registers/instructions

# For interpretation of SIMD build flags check compatibility layer in rtzero.h

# For 30 256-bit VSX1/2 registers on POWER7/8 targets use (replace): RT_256=4+8
