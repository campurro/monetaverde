add_definitions(-DSTATICLIB)
add_definitions(-D__STDC_FORMAT_MACROS)

include_directories(${CMAKE_SOURCE_DIR}/external/rocksdb/include)

option(WITH_AEON            "CryptoNight-Lite support" ON)
option(WITH_SUMO            "CryptoNight-Heavy support" ON)
option(WITH_CN_PICO         "CryptoNight-Pico support" ON)
option(WITH_CN_GPU          "CryptoNight-GPU support" ON)

include_directories(${CMAKE_SOURCE_DIR}/src/MultiHashing/xmrig)
include_directories(${CMAKE_SOURCE_DIR}/src/MultiHashing/xmrig/3rdparty)
#file(GLOB_RECURSE MultiHashing MultiHashing/*)
set(MultiHashing
    MultiHashing/multihashing.cpp
#    MultiHashing/xmrig/extra.cpp
    MultiHashing/xmrig/Mem.cpp
    MultiHashing/xmrig/crypto/c_blake256.c
    MultiHashing/xmrig/crypto/c_groestl.c
    MultiHashing/xmrig/crypto/c_jh.c
    MultiHashing/xmrig/crypto/c_skein.c
    MultiHashing/xmrig/common/crypto/keccak.cpp


#    MultiHashing/xmrig/crypto/CryptoNight.h
#    MultiHashing/xmrig/crypto/CryptoNight_constants.h
#    MultiHashing/xmrig/crypto/CryptoNight_monero.h
#    MultiHashing/xmrig/crypto/groestl_tables.h
#    MultiHashing/xmrig/crypto/hash.h
#    MultiHashing/xmrig/crypto/skein_port.h
#    MultiHashing/xmrig/crypto/soft_aes.h
#    MultiHashing/xmrig/crypto/asm/CryptonightR_template.h
  )

if (WIN32)
  set(MultiHashing_OS
      MultiHashing/xmrig/Mem_win.cpp
  )
else ()
  set(MultiHashing_OS
      MultiHashing/xmrig/Mem_unix.cpp
  )
endif ()

if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")
    set(MultiHashing "${MultiHashing}" 
        MultiHashing/xmrig/crypto/cn_gpu_ssse3.cpp
#        MultiHashing/xmrig/crypto/cn_gpu_arm.cpp
        MultiHashing/xmrig/common/cpu/Cpu.cpp
        MultiHashing/xmrig/common/cpu/BasicCpuInfo.cpp
#        MultiHashing/xmrig/common/cpu/BasicCpuInfo_arm.cpp
    )
endif ()

if (XMRIG_ARM)
    set(MultiHashing_OS "${MultiHashing_OS}" MultiHashing/xmrig/crypto/CryptoNight_arm.h)
    message(WARNING "METIENDO EL CryptoNight_arm.h")
else()
    set(MultiHashing_OS "${MultiHashing_OS}" MultiHashing/xmrig/crypto/CryptoNight_x86.h)
endif()

#################### CPU ###############################
if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")
    add_definitions(/DRAPIDJSON_SSE2)
endif()

if (NOT ARM_TARGET)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64|armv8-a)$")
        set(ARM_TARGET 8)
    elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(armv7|armv7f|armv7s|armv7k|armv7-a|armv7l)$")
        set(ARM_TARGET 7)
    endif()
endif()

if (ARM_TARGET AND ARM_TARGET GREATER 6)
    set(XMRIG_ARM     ON)
    set(WITH_LIBCPUID OFF)
    add_definitions(/DXMRIG_ARM)

    message(STATUS "Use ARM_TARGET=${ARM_TARGET} (${CMAKE_SYSTEM_PROCESSOR})")

    include(CheckCXXCompilerFlag)

    if (ARM_TARGET EQUAL 8)
        set(XMRIG_ARMv8 ON)
        add_definitions(/DXMRIG_ARMv8)

        CHECK_CXX_COMPILER_FLAG(-march=armv8-a+crypto XMRIG_ARM_CRYPTO)

        if (XMRIG_ARM_CRYPTO)
            add_definitions(/DXMRIG_ARM_CRYPTO)
            set(ARM8_CXX_FLAGS "-march=armv8-a+crypto")
        else()
            set(ARM8_CXX_FLAGS "-march=armv8-a")
        endif()
    elseif (ARM_TARGET EQUAL 7)
        set(XMRIG_ARMv7 ON)
        add_definitions(/DXMRIG_ARMv7)
    endif()
endif()
########################################################
################# FLAGS ################################
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(/DNDEBUG)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-strict-aliasing")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    #-Wno-class-memaccess => Throws an error in Linux
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -s")

    if (XMRIG_ARMv8)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARM8_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARM8_CXX_FLAGS} -flax-vector-conversions")
    elseif (XMRIG_ARMv7)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=neon")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon -flax-vector-conversions")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes")
    endif()

    if (WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()

    add_definitions(/D_GNU_SOURCE)

    if (${CMAKE_VERSION} VERSION_LESS "3.1.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()

    #set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -gdwarf-2")

elseif (CMAKE_CXX_COMPILER_ID MATCHES MSVC)

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Ox /Ot /Oi /MT /GL")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /Ot /Oi /MT /GL")
    add_definitions(/D_CRT_SECURE_NO_WARNINGS)
    add_definitions(/D_CRT_NONSTDC_NO_WARNINGS)
    add_definitions(/DNOMINMAX)

elseif (CMAKE_CXX_COMPILER_ID MATCHES Clang)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast -funroll-loops -fmerge-all-constants")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-missing-braces")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -funroll-loops -fmerge-all-constants")

    if (XMRIG_ARMv8)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARM8_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARM8_CXX_FLAGS}")
    elseif (XMRIG_ARMv7)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=neon -march=${CMAKE_SYSTEM_PROCESSOR}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon -march=${CMAKE_SYSTEM_PROCESSOR}")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes")
    endif()

endif()
########################################################
################### ASM ####################################
if (WITH_ASM AND NOT XMRIG_ARM AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(XMRIG_ASM_LIBRARY "xmrig-asm")

    if (CMAKE_C_COMPILER_ID MATCHES MSVC)
        enable_language(ASM_MASM)

        if (MSVC_TOOLSET_VERSION GREATER_EQUAL 141)
            set(XMRIG_ASM_FILES
                "src/crypto/asm/cn_main_loop.asm"
                "src/crypto/asm/CryptonightR_template.asm"
            )
        else()
            set(XMRIG_ASM_FILES
                "src/crypto/asm/win64/cn_main_loop.asm"
                "src/crypto/asm/win64/CryptonightR_template.asm"
            )
        endif()

        set_property(SOURCE ${XMRIG_ASM_FILES} PROPERTY ASM_MASM)
    else()
        enable_language(ASM)

        if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES GNU)
            set(XMRIG_ASM_FILES
                "src/crypto/asm/win64/cn_main_loop.S"
                "src/crypto/asm/CryptonightR_template.S"
            )
        else()
            set(XMRIG_ASM_FILES
                "src/crypto/asm/cn_main_loop.S"
                "src/crypto/asm/CryptonightR_template.S"
            )
        endif()

        set_property(SOURCE ${XMRIG_ASM_FILES} PROPERTY C)
    endif()

    add_library(${XMRIG_ASM_LIBRARY} STATIC ${XMRIG_ASM_FILES})
    set(XMRIG_ASM_SOURCES MultiHashing/xmrig/crypto/Asm.h MultiHashing/xmrig/crypto/Asm.cpp MultiHashing/xmrig/crypto/CryptonightR_gen.cpp)
    set_property(TARGET ${XMRIG_ASM_LIBRARY} PROPERTY LINKER_LANGUAGE C)
else()
    set(XMRIG_ASM_SOURCES "")
    set(XMRIG_ASM_LIBRARY "")
    add_definitions(/DXMRIG_NO_ASM)
endif()
###################################################################
############################### CN GPU ############################
if (WITH_CN_GPU AND CMAKE_SIZEOF_VOID_P EQUAL 8)

    if (XMRIG_ARM)
        set(CN_GPU_SOURCES MultiHashing/xmrig/crypto/cn_gpu_arm.cpp)

        if (CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
            set_source_files_properties(MultiHashing/xmrig/crypto/cn_gpu_arm.cpp PROPERTIES COMPILE_FLAGS "-O3")
        endif()
    else()
        set(CN_GPU_SOURCES MultiHashing/xmrig/crypto/cn_gpu_avx.cpp MultiHashing/xmrig/crypto/cn_gpu_ssse3.cpp)

        if (CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
            set_source_files_properties(MultiHashing/xmrig/crypto/cn_gpu_avx.cpp PROPERTIES COMPILE_FLAGS "-O3 -mavx2")
            set_source_files_properties(MultiHashing/xmrig/crypto/cn_gpu_ssse3.cpp PROPERTIES COMPILE_FLAGS "-O3")
        elseif (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
            set_source_files_properties(MultiHashing/xmrig/crypto/cn_gpu_avx.cpp PROPERTIES COMPILE_FLAGS "/arch:AVX")
        endif()
    endif()
else()
    set(CN_GPU_SOURCES "")

    add_definitions(/DXMRIG_NO_CN_GPU)
endif()
#####################################################################

file(GLOB_RECURSE BlockchainExplorer BlockchainExplorer/*)
file(GLOB_RECURSE Common Common/*)
file(GLOB_RECURSE ConnectivityTool ConnectivityTool/*)
file(GLOB_RECURSE Crypto crypto/*)
file(GLOB_RECURSE CryptoNoteCore CryptoNoteCore/* CryptoNoteConfig.h)
file(GLOB_RECURSE CryptoNoteProtocol CryptoNoteProtocol/*)
file(GLOB_RECURSE Daemon Daemon/*)
file(GLOB_RECURSE Http HTTP/*)
file(GLOB_RECURSE InProcessNode InProcessNode/*)
file(GLOB_RECURSE Logging Logging/*)
file(GLOB_RECURSE NodeRpcProxy NodeRpcProxy/*)
file(GLOB_RECURSE P2p P2p/*)
file(GLOB_RECURSE Rpc Rpc/*)
file(GLOB_RECURSE Serialization Serialization/*)
file(GLOB_RECURSE SimpleWallet SimpleWallet/*)
if(MSVC)
file(GLOB_RECURSE System System/* Platform/Windows/System/*)
elseif(APPLE)
file(GLOB_RECURSE System System/* Platform/OSX/System/* Platform/Posix/System/*)
else()
file(GLOB_RECURSE System System/* Platform/Linux/System/* Platform/Posix/System/*)
endif()
file(GLOB_RECURSE Transfers Transfers/*)
file(GLOB_RECURSE Wallet Wallet/*)
file(GLOB_RECURSE WalletLegacy WalletLegacy/*)

file(GLOB_RECURSE JsonRpcServer JsonRpcServer/*)

file(GLOB_RECURSE PaymentGate PaymentGate/*)
file(GLOB_RECURSE PaymentGateService PaymentGateService/*)
file(GLOB_RECURSE Miner Miner/*)

source_group("" FILES $${Common} ${ConnectivityTool} ${Crypto} ${CryptoNoteCore} ${CryptoNoteProtocol} ${Daemon} ${JsonRpcServer} ${Http} ${Logging} ${NodeRpcProxy} ${P2p} ${Rpc} ${Serialization} ${SimpleWallet} ${System} ${Transfers} ${Wallet} ${WalletLegacy})

add_library(BlockchainExplorer ${BlockchainExplorer})
add_library(Common ${Common})
add_library(Crypto ${Crypto})
#add_library(MultiHashing ${MultiHashing} ${MultiHashing_OS})
add_library(CryptoNoteCore ${CryptoNoteCore} ${MultiHashing} ${MultiHashing_OS} ${XMRIG_ASM_SOURCES} ${CN_GPU_SOURCES})
add_library(Http ${Http})
add_library(InProcessNode ${InProcessNode})
add_library(Logging ${Logging})
add_library(NodeRpcProxy ${NodeRpcProxy})
add_library(Rpc ${Rpc})
add_library(P2P ${CryptoNoteProtocol} ${P2p})
add_library(Serialization ${Serialization})
add_library(System ${System})
add_library(Transfers ${Transfers})
add_library(Wallet ${Wallet} ${WalletLegacy})
add_library(PaymentGate ${PaymentGate})
add_library(JsonRpcServer ${JsonRpcServer})

add_executable(ConnectivityTool ${ConnectivityTool})
add_executable(Daemon ${Daemon})
add_executable(SimpleWallet ${SimpleWallet})
add_executable(PaymentGateService ${PaymentGateService})
add_executable(Miner ${Miner})

if (MSVC)
  target_link_libraries(System ws2_32)
  target_link_libraries(Daemon Rpcrt4)
  target_link_libraries(PaymentGateService Rpcrt4)
endif ()

target_link_libraries(CryptoNoteCore Common Crypto Logging Serialization)
target_link_libraries(P2P CryptoNoteCore Logging ${Boost_LIBRARIES} upnpc-static)
target_link_libraries(Rpc CryptoNoteCore Logging P2P)

target_link_libraries(ConnectivityTool CryptoNoteCore Common Logging Crypto P2P Rpc Http Serialization System ${Boost_LIBRARIES})
target_link_libraries(Daemon P2P Rpc Serialization System Http Logging CryptoNoteCore Crypto Common upnpc-static rocksdb ${Boost_LIBRARIES} ${XMRIG_ASM_LIBRARY} )
target_link_libraries(SimpleWallet Wallet NodeRpcProxy Transfers Rpc P2P upnpc-static Http Serialization CryptoNoteCore System Logging Common Crypto ${Boost_LIBRARIES})
target_link_libraries(PaymentGateService PaymentGate JsonRpcServer Wallet NodeRpcProxy Transfers P2P CryptoNoteCore Crypto Rpc Http Serialization System Logging Common InProcessNode upnpc-static BlockchainExplorer rocksdb ${Boost_LIBRARIES})
target_link_libraries(Miner CryptoNoteCore Rpc Serialization System Http Logging Common Crypto ${Boost_LIBRARIES})

add_dependencies(Rpc version)

add_dependencies(ConnectivityTool version)
add_dependencies(Daemon version)
add_dependencies(SimpleWallet version)
add_dependencies(PaymentGateService version)
add_dependencies(P2P version)

set_property(TARGET ConnectivityTool PROPERTY OUTPUT_NAME "connectivity_tool")
set_property(TARGET Daemon PROPERTY OUTPUT_NAME "monetaverded")
set_property(TARGET SimpleWallet PROPERTY OUTPUT_NAME "simplewallet")
set_property(TARGET PaymentGateService PROPERTY OUTPUT_NAME "walletd")
set_property(TARGET Miner PROPERTY OUTPUT_NAME "miner")
