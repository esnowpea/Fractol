cmake_minimum_required(VERSION 3.15)
project(fractol C)

set(CMAKE_C_STANDARD 90)

add_executable(fractol src/main.c inc/fractol.h src/event_handler.c inc/error_message.h src/init.c src/draw_win.c src/mandelbrot.c inc/key_define.h src/mouse_hook.c src/julia.c)
target_include_directories(fractol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(fractol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(fractol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libft/inc)
#find_library(FT ft)
set(FT ${CMAKE_CURRENT_SOURCE_DIR}/libft/libft.a)
target_link_libraries(fractol ${FT})

target_include_directories(fractol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/minilibx_macos/inc)
find_library(MLX mlx)
target_link_libraries(fractol ${MLX})

target_link_libraries(fractol "-framework OpenGL")

target_link_libraries(fractol "-framework AppKit")