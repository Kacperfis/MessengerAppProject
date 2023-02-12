set(TARGET_NAME MessengerApp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(MESSENGER_APP_SOURCES
    MessengerAgent.cpp
    LoginHub/AdminLoginHub.cpp
    LoginHub/UserLoginHub.cpp
    LoginHub/AdminLoginHubCreator.cpp
    LoginHub/UserLoginHubCreator.cpp
    Registration/RegistrationHandler.cpp
    Helpers/LoginHubHelper.cpp
    Helpers/UIHelper.cpp
)
set(MESSENGER_APP_HEADERS
    MessengerAgent.hpp
    LoginHub/AdminLoginHub.hpp
    LoginHub/UserLoginHub.hpp
    LoginHub/AdminLoginHubCreator.hpp
    LoginHub/UserLoginHubCreator.hpp
    LoginHub/LoginData.hpp
    Registration/RegistrationHandler.hpp
    Helpers/LoginHubHelper.hpp
    Helpers/UIHelper.hpp
)
<<<<<<< HEAD
add_library(${TARGET_NAME} STATIC ${MESSENGER_APP_SOURCES} ${MESSENGER_APP_HEADERS})
target_link_libraries(${TARGET_NAME}
    MessengerInterfaces
    OpenSSL::Crypto
    OpenSSL::SSL
=======

#sudo apt-get install libssl-dev
#cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib

set(OPENSSL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openssl)
find_package(OpenSSL REQUIRED)

add_library(${TARGET_NAME} STATIC ${MESSENGER_APP_SOURCES} ${MESSENGER_APP_HEADERS})
target_link_libraries(${TARGET_NAME}
    MessengerInterfaces
    OpenSSL::SSL OpenSSL::Crypto
>>>>>>> 9dfee03b ([NF] added openSSL library to cmake)
)

enable_testing()
set(TEST_SOURCES
    Tests/MessengerAgentTests.cpp
    Tests/UserLoginHubTests.cpp
    Tests/AdminLoginHubTests.cpp
)

set(UT_DRIVER ut)
<<<<<<< HEAD
add_executable(${UT_DRIVER} ${TEST_SOURCES}) #${MOCK_LIST})
target_link_libraries(${UT_DRIVER} ${TARGET_NAME} gmock_main gtest gmock OpenSSL::Crypto OpenSSL::SSL)
=======
add_executable(${UT_DRIVER} ${TEST_SOURCES})
target_link_libraries(${UT_DRIVER} ${TARGET_NAME} gmock_main gtest gmock OpenSSL::SSL OpenSSL::Crypto)
>>>>>>> 9dfee03b ([NF] added openSSL library to cmake)

if (BUILD_COVERAGE_UNIT_TESTS)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    set_target_properties(${UT_DRIVER} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    target_link_libraries(${UT_DRIVER} ${CMAKE_CXX_COVERAGE_LIBRARY})
    setup_target_for_coverage(${UT_DRIVER}_COV ${UT_DRIVER} ${COVERAGE_REPORT_LOCATION})
endif()

add_test(tests ${UT_DRIVER})

