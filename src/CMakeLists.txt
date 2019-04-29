# Build statically
add_definitions(-DSTATICLIB)

# Add external libraries as include dirs, so we can do #include "httplib" for example
include_directories(${CMAKE_SOURCE_DIR}/external/cpp-linenoise)
include_directories(${CMAKE_SOURCE_DIR}/external/cpp-httplib)
include_directories(${CMAKE_SOURCE_DIR}/external/nlohmann-json)
include_directories(${CMAKE_SOURCE_DIR}/external/rapidjson)
include_directories(${CMAKE_SOURCE_DIR}/external/cxxopts)
include_directories(${CMAKE_SOURCE_DIR}/external/cryptopp)

# Show cmake where the source files are
# Note, if you add remove a source file, you will need to re-run cmake so it
# can find the new file
file(GLOB_RECURSE Common Common/*)
file(GLOB_RECURSE Crypto crypto/*)
file(GLOB_RECURSE Errors Errors/*)
file(GLOB_RECURSE Logger Logger/*)
file(GLOB_RECURSE Mnemonics Mnemonics/*)
file(GLOB_RECURSE Nigel Nigel/*)
file(GLOB_RECURSE Serialization Serialization/*)
file(GLOB_RECURSE SubWallets SubWallets/*)
file(GLOB_RECURSE Utilities Utilities/*)
file(GLOB_RECURSE WalletBackend WalletBackend/*)
file(GLOB_RECURSE zedwallet++ zedwallet++/*)

# Group the files together in IDEs
source_group("" FILES $${Common} ${Crypto} ${Logger} ${Mnemonics} ${Nigel} ${Serialization} ${WalletBackend} ${zedwallet++} ${Errors} ${Utilities} ${SubWallets})

# Define a group of files as a library to link against
add_library(Common STATIC ${Common})
add_library(Crypto STATIC ${Crypto})
add_library(Errors STATIC ${Errors})
add_library(Logger STATIC ${Logger})
add_library(Mnemonics STATIC ${Mnemonics})
add_library(Nigel STATIC ${Nigel})
add_library(Serialization STATIC ${Serialization})
add_library(SubWallets STATIC ${SubWallets})
add_library(Utilities STATIC ${Utilities})
add_library(WalletBackend STATIC ${WalletBackend})

add_executable(zedwallet++ ${zedwallet++} ${ZED_WALLET_SOURCES_OS})

if(MSVC)
    target_link_libraries(zedwallet++ ws2_32 advapi32 crypt32 gdi32 user32)
endif ()

# A bit of hackery so we don't have to do the if/else/ for every target that
# wants to use filesystem
add_library(__filesystem INTERFACE)

# Windows works out of the box
if (APPLE)
    target_link_libraries(__filesystem INTERFACE /usr/local/opt/llvm/lib/libc++fs.a)
elseif (UNIX)
    target_link_libraries(__filesystem INTERFACE stdc++fs)
endif()

# Add the dependencies we need
target_link_libraries(Common __filesystem)
target_link_libraries(Errors Crypto SubWallets)
target_link_libraries(Nigel Errors)
target_link_libraries(SubWallets Common Logger)
target_link_libraries(WalletBackend Serialization Mnemonics Nigel cryptopp-static __filesystem Utilities SubWallets Logger)
target_link_libraries(zedwallet++ WalletBackend)

if(OPENSSL_FOUND)
  target_link_libraries(Nigel ${OPENSSL_LIBRARIES})
  target_link_libraries(zedwallet++ ${OPENSSL_LIBRARIES})
endif()

# Finally build the binaries
set_property(TARGET zedwallet++ PROPERTY OUTPUT_NAME "zedwallet-beta")
