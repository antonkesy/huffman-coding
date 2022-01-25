enable_testing()

set(test_essentials
        ../test_utility.c)

file(GLOB files "*.c")
foreach(file ${files})
    string(REGEX REPLACE ".*/" "" file_path ${file})
    string(REGEX REPLACE ".c$" "" file_name ${file_path})
    add_executable(${file_name} ${file_path} ${test_essentials})
    target_link_libraries(${file_name} PRIVATE huffman_coding)
    add_test(test_${file_name} ${file_name})
    set_tests_properties(test_${file_name} PROPERTIES WILL_FAIL FALSE)
endforeach()