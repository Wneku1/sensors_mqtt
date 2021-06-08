cmake_minimum_required(VERSION 3.10)

project(RFID_MQTT LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS " ")

set(RFID_MQTT ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(SHARED_MODULES_DIR ${CMAKE_SOURCE_DIR}/shared_module)

set(SENSOR_INTERFACE_DIR ${SHARED_MODULES_DIR}/sensor_interface)
set(SENSOR_INTERFACE ${SENSOR_INTERFACE_DIR}/sensor_interface.hpp)

#dbg_trace
set(DBG_TRACE_DIR ${SHARED_MODULES_DIR}/dbg_trace)
set(DEBUG_TRACE ${DBG_TRACE_DIR}/dbg_trace.hpp ${DBG_TRACE_DIR}/dbg_trace.cpp ${DBG_TRACE_DIR}/dbg_trace_types.hpp)

#mqtt
set(MQTT_DIR ${SHARED_MODULES_DIR}/MQTT)
set(MQTT ${MQTT_DIR}/mqtt.hpp ${MQTT_DIR}/mqtt.cpp)

#mqtt library
find_library(paho-mqttpp3 NAMES libpaho-mqttpp3.a REQUIRED)
find_library(paho-mqtt3a NAMES libpaho-mqtt3a.so REQUIRED)

add_library(pahottpp STATIC IMPORTED)
set_target_properties(pahottpp PROPERTIES IMPORTED_LOCATION ${paho-mqttpp3})

add_library(pahomqtt3a SHARED IMPORTED)
set_property(TARGET pahomqtt3a PROPERTY IMPORTED_LOCATION ${paho-mqtt3a})

set(RFID_DIR ${CMAKE_SOURCE_DIR}/lib/RFID)
set(RFID ${RFID_DIR}/bcm2835.h ${RFID_DIR}/MFRC522.h ${RFID_DIR}/MFRC522.cpp)

set(RFID_CLASS_DIR ${CMAKE_SOURCE_DIR}/src/rfid_class)
set(RFID_CLASS ${RFID_CLASS_DIR}/rfid_class.hpp ${RFID_CLASS_DIR}/rfid_class.cpp)

set(BUZZER_DIR ${CMAKE_SOURCE_DIR}/src/buzzer)
set(BUZZER ${BUZZER_DIR}/buzzer.h ${BUZZER_DIR}/buzzer.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${RFID_MQTT} ${RFID} ${DEBUG_TRACE} ${SENSOR_INTERFACE} ${RFID_CLASS} ${BUZZER} ${MQTT})

target_link_libraries(${CMAKE_PROJECT_NAME} wiringPi bcm2835 pahottpp pahomqtt3a)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    "${RFID_DIR}"
    "${RFID_CLASS_DIR}"
    "${DBG_TRACE_DIR}"
    "${SENSOR_INTERFACE_DIR}"
    "${MQTT_DIR}"
    )
