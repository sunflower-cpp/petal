include_directories(../)

add_executable(PETAL_TEST_EXE fp.cpp)
target_link_libraries(PETAL_TEST_EXE petal)
add_test(PETAL_TEST PETAL_TEST_EXE)