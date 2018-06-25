target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/windraw.hpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/window/window.hpp"		
		"${CMAKE_CURRENT_LIST_DIR}/window/spec.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/style.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/event.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/window/window.cpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/util/color.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/util/color.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/util/math.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/util/math.cpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/graphics/canvas.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/graphics/canvas.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/graphics/shapes.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/graphics/bitmap.hpp"
)

target_sources(windraw
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/assets/cache.hpp"
)