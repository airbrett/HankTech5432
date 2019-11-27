cmake_minimum_required (VERSION 3.8)

project(Async)

add_definitions(-DGLEW_STATIC)

add_subdirectory(${SDL2_LISTS_DIR} SDL2)
add_subdirectory(${GLEW_LISTS_DIR} glew)

find_package(OpenGL REQUIRED)

add_executable(Async
	Draw.h
	Draw.cpp
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
	User.h
	User.cpp
)

target_compile_definitions(Async
	PRIVATE WIN32_LEAN_AND_MEAN
	PRIVATE NOMINMAX
	PRIVATE _CRT_SECURE_NO_WARNINGS
	PRIVATE _SCL_SECURE_NO_WARNINGS
	PRIVATE SDL_MAIN_HANDLED
)

target_include_directories(Async PUBLIC
	${GLM_DIR}
)

target_link_libraries(Async
	SDL2
	glew
	${OPENGL_LIBRARIES}
)