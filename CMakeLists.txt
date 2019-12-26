cmake_minimum_required (VERSION 3.8)

project(Async)

add_definitions(-DGLEW_STATIC)

add_subdirectory(${SDL2_LIST_DIR} SDL2)
add_subdirectory(${GLEW_LIST_DIR} glew)
add_subdirectory(${BOX2D_LIST_DIR} Box2D)
add_subdirectory(${LODEPNG_LIST_DIR} lodepng)
add_subdirectory(${ASSIMP_LIST_DIR} assimp)

add_executable(Async
	Context.h
	Context.cpp
	HandleHandler.h
	HandleHandler.cpp
	Instance.h
	main.cpp
	Physics.h
	Physics.cpp
	Player.h
	Player.cpp
	RAM.h
	RAM.cpp
	StaticThing.h
	StaticThing.cpp
	Thing.h
	Thing.cpp
	WindowHandler.h
	WindowHandler.cpp
)

target_compile_definitions(Async
	PRIVATE WIN32_LEAN_AND_MEAN
	PRIVATE NOMINMAX
	PRIVATE _CRT_SECURE_NO_WARNINGS
	PRIVATE _SCL_SECURE_NO_WARNINGS
	PRIVATE SDL_MAIN_HANDLED
)

target_include_directories(Async PUBLIC
	${GLM_SRC_DIR}
)

target_link_libraries(Async
	SDL2
	glew
	Box2D
	lodepng
	assimp
)