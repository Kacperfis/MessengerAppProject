set(TARGET_NAME MessengerApp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(MESSENGER_APP_SOURCES
    #main.cpp # uncomment to create the binary
    Common/Logger.cpp
    Connection/Client/Client.cpp
    Connection/Server/Server.cpp
    Connection/Server/Session.cpp
    MessengerAgent.cpp
    LoginHub/AdminLoginHub.cpp
    LoginHub/UserLoginHub.cpp
    LoginHub/AdminLoginHubCreator.cpp
    LoginHub/UserLoginHubCreator.cpp
    Registration/RegistrationHandler.cpp
    Encryption/EncryptionManager.cpp
    Helpers/LoginHubHelper.cpp
    Helpers/UIHelper.cpp
    Database/DatabaseController.cpp
)
set(MESSENGER_APP_HEADERS
    Common/Logger.hpp
    Common/Config/pathConfig.hpp
    Connection/Client/Client.hpp
    Connection/Server/Server.hpp
    Connection/Server/Session.hpp
    MessengerAgent.hpp
    LoginHub/AdminLoginHub.hpp
    LoginHub/UserLoginHub.hpp
    LoginHub/AdminLoginHubCreator.hpp
    LoginHub/UserLoginHubCreator.hpp
    LoginHub/LoginData.hpp
    Registration/RegistrationHandler.hpp
    Encryption/EncryptionManager.hpp
    Helpers/LoginHubHelper.hpp
    Helpers/UIHelper.hpp
    Database/DatabaseController.hpp
)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

link_directories(${OPENSSL_LIBRARY_DIR})

add_library(${TARGET_NAME} STATIC ${MESSENGER_APP_SOURCES} ${MESSENGER_APP_HEADERS})
target_link_libraries(${TARGET_NAME}
    MessengerInterfaces
    ${OPENSSL_CRYPTO_LIBRARY}
    Boost::boost
)

enable_testing()
set(TEST_SOURCES
    Tests/common/commonFixture.cpp
    Tests/UserLoginHubTests.cpp
    Tests/AdminLoginHubTests.cpp
    Tests/EncryptionManagerTests.cpp
    Tests/DatabaseControllerTests.cpp
    Tests/RegistrationHandlerTests.cpp
)

set(UT_DRIVER ut)
add_executable(${UT_DRIVER} ${TEST_SOURCES})
target_link_libraries(${UT_DRIVER} ${TARGET_NAME} gmock_main gtest gmock)

# uncomment to create the binary
# add_executable(${TARGET_NAME}_exec main.cpp)
# target_link_libraries(${TARGET_NAME}_exec ${TARGET_NAME})

if (BUILD_COVERAGE_UNIT_TESTS)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    set_target_properties(${UT_DRIVER} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    target_link_libraries(${UT_DRIVER} ${CMAKE_CXX_COVERAGE_LIBRARY})
    setup_target_for_coverage(${UT_DRIVER}_COV ${UT_DRIVER} ${COVERAGE_REPORT_LOCATION})
endif()

add_test(tests ${UT_DRIVER})

