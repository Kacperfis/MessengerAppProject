set(TARGET_NAME MessengerApp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(MESSENGER_APP_SOURCES
    MessengerAgent.cpp
    LoginHub/AdminLoginHub.cpp
    LoginHub/UserLoginHub.cpp
    LoginHub/AdminLoginHubCreator.cpp
    LoginHub/UserLoginHubCreator.cpp
)
set(MESSENGER_APP_HEADERS
    MessengerAgent.hpp
    LoginHub/AdminLoginHub.hpp
    LoginHub/UserLoginHub.hpp
    LoginHub/AdminLoginHubCreator.hpp
    LoginHub/UserLoginHubCreator.hpp
)
add_library(${TARGET_NAME} STATIC ${MESSENGER_APP_SOURCES} ${MESSENGER_APP_HEADERS})
target_link_libraries(${TARGET_NAME} MessengerInterfaces)


enable_testing()
set(TEST_SOURCES
    Tests/MessengerAgentTests.cpp
)

# set(MOCK_LIST

# )

set(UT_DRIVER ${TARGET_NAME}_UT)
add_executable(${UT_DRIVER} ${TEST_SOURCES}) #${MOCK_LIST})
target_link_libraries(${UT_DRIVER} ${TARGET_NAME} gmock_main gtest gmock)

if (BUILD_COVERAGE_UNIT_TESTS)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    set_target_properties(${UT_DRIVER} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    target_link_libraries(${UT_DRIVER} ${CMAKE_CXX_COVERAGE_LIBRARY})
    setup_target_for_coverage(${UT_DRIVER}_COV ${UT_DRIVER} ${COVERAGE_REPORT_LOCATION})
endif()

add_test(tests ${UT_DRIVER})
