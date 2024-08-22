set(SOURCES
    "src/pch.cpp"
    "src/module.cpp"
)

add_library(HashingModule SHARED ${SOURCES})
target_include_directories(HashingModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(HashingModule PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp)
target_link_libraries(HashingModule cryptopp)
set_target_properties(HashingModule PROPERTIES PREFIX "")

install(TARGETS HashingModule RUNTIME DESTINATION "Server/modules" COMPONENT LCMPServer)
