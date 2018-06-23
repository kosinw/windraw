target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/windraw.hpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/window/window.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/window.cpp"		
		"${CMAKE_CURRENT_LIST_DIR}/window/spec.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/style.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/math.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/math.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/event.hpp"
)