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
		"${CMAKE_CURRENT_LIST_DIR}/window/event.hpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/util/color.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/util/math.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/util/math.cpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/graphics/canvas.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/graphics/canvas_impl.hpp"
)

if (D2D_ENABLED)
	include("${CMAKE_CURRENT_LIST_DIR}/graphics/direct2d")
endif()