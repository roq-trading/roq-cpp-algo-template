set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(flags)
add_subdirectory(strategy)

set(SOURCES application.cpp config.cpp factory.cpp settings.cpp main.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

add_dependencies(${TARGET_NAME} ${TARGET_NAME}-flags-autogen-headers)

target_link_libraries(
  ${TARGET_NAME}
  PRIVATE ${PROJECT_NAME}-flags
          ${PROJECT_NAME}-strategy
          roq-algo::roq-algo
          roq-api::roq-api
          roq-cache::roq-cache
          roq-client::roq-client
          roq-client::roq-client-flags
          roq-flags::roq-flags
          roq-logging::roq-logging
          roq-logging::roq-logging-flags
          roq-market::roq-market
          roq-utils::roq-utils
          fmt::fmt
          tomlplusplus::tomlplusplus
          unordered_dense::unordered_dense)

if(ROQ_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
endif()

target_compile_definitions(${TARGET_NAME} PRIVATE ROQ_PACKAGE_NAME="${CMAKE_PROJECT_NAME}" ROQ_BUILD_VERSION="${CMAKE_PROJECT_VERSION}")

install(TARGETS ${TARGET_NAME})

# ##############################################################################################################################################################
# !!! EXPERIMENTAL !!! ###
# ##############################################################################################################################################################

set(PYTHON_TARGET_NAME ${PROJECT_NAME}-python)

set(PYTHON_SOURCES module.cpp)

pybind11_add_module(${PYTHON_TARGET_NAME} ${PYTHON_SOURCES})

target_link_libraries(
  ${PYTHON_TARGET_NAME}
  PUBLIC pybind11::headers
  PRIVATE ${PROJECT_NAME}-strategy roq-algo::roq-algo roq-python-core::roq-python-core fmt::fmt)

# note! python packages are not allowed to use "-" (dash) in their name
string(REPLACE "-" "_" PYTHON_PROJECT_NAME ${PROJECT_NAME}) # note! using PROJECT_NAME
set_target_properties(${PYTHON_TARGET_NAME} PROPERTIES OUTPUT_NAME ${PYTHON_PROJECT_NAME})
target_compile_definitions(${PYTHON_TARGET_NAME} PRIVATE ROQ_PACKAGE_NAME=${PYTHON_PROJECT_NAME} ROQ_BUILD_VERSION="${CMAKE_PROJECT_VERSION}")

install(TARGETS ${PYTHON_TARGET_NAME} DESTINATION ${PYTHON_SITE}/${PYTHON_PROJECT_NAME})
