armino_build_get_property(armino_soc ARMINO_SOC)

set(incs include)
armino_component_register(INCLUDE_DIRS "${incs}")


file(GLOB common_libs ${CMAKE_CURRENT_SOURCE_DIR}/common/*.a)
foreach(lib ${common_libs})
	get_filename_component(lib_name ${lib} NAME)
	add_prebuilt_library(${lib_name} "${CMAKE_CURRENT_SOURCE_DIR}/common/${lib_name}")
	target_link_libraries(${COMPONENT_LIB} INTERFACE ${lib_name})
endforeach()

file(GLOB libs ${CMAKE_CURRENT_SOURCE_DIR}/${armino_soc}/libs/*.a)

set (blacklist_elem
    libtjpg[^.]*\.a
    libscale[^.]*\.a
)

list (JOIN blacklist_elem | blacklist_elem_regax)

list(FILTER libs EXCLUDE REGEX "^.*(${blacklist_elem_regax})$")

foreach(lib ${libs})
 	get_filename_component(lib_name ${lib} NAME)
 	add_prebuilt_library(${lib_name} "${CMAKE_CURRENT_SOURCE_DIR}/${armino_soc}/libs/${lib_name}")
 	target_link_libraries(${COMPONENT_LIB} INTERFACE ${lib_name})
endforeach()

