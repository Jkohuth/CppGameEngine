#RPG Makefile
OBJS = jump.o resource_manager.o game.o shader.o texture.o sprite_renderer.o character_object.o \
		game_object.o text_renderer.o circle_object.o collision.o input_handler.o glad.o
#post_processor.o 
#map_renderer.o map_layer.o
#OBJS = text_rendering.o texture.o shader.o resource_manager.o sprite_renderer.o
CXX = clang++
CFLAGS = -Wall
LIBRARIES = -std=c++11 \
			-L/usr/lib/ \
			-L/usr/local/lib/ \
			-L/user/lib64 \
			-L/usr/lib/x86_64-linux-gnu/ \
			-I/usr/include/ \
			-I/usr/local/include/ \
			-I./ \
			-I./include/ \
			-lglfw -lGL -lfreetype -lSOIL -lpthread -lXrandr -lX11 -ldl
#			-lglfw -lGL -lGLEW -lfreetype 
#			-lXrandr -lXi -lX11 
#			-lXrandr -lXi -lX11 -lGLEW
BUILD_DIR = src

# Uncertain about these linkers use -lm -lpthread -lXxf86vm

.PHONY : start clean

all : start

start : $(OBJS)
	$(CXX) -o start $(LIBRARIES) $(OBJS)

jump.o : jump.cpp resource_manager.h game.h global_enumerations.h
	$(CXX) $(LIBRARIES) -c jump.cpp

game.o : game.cpp game.h resource_manager.h sprite_renderer.h global_enumerations.h collision.h input_handler.h # map_renderer.h
	$(CXX) $(LIBRARIES) -c game.cpp

glad.o : glad.c
	$(CXX) $(LIBRARIES) -c glad.c

post_processor.o : post_processor.cpp post_processor.h texture.h sprite_renderer.h shader.h
	$(CXX) $(LIBRARIES) -c post_processor.cpp

collision.o : collision.cpp collision.h game_object.h character_object.h circle_object.h global_enumerations.h
	$(CXX) $(LIBRARIES) -c collision.cpp

circle_object.o : circle_object.cpp circle_object.h game_object.h texture.h sprite_renderer.h 
	$(CXX) $(LIBRARIES) -c circle_object.cpp

character_object.o : character_object.cpp character_object.h sprite_renderer.h game_object.h texture.h global_enumerations.h
	$(CXX) $(LIBRARIES) -c character_object.cpp

game_object.o : game_object.cpp game_object.h texture.h sprite_renderer.h
	$(CXX) $(LIBRARIES) -c game_object.cpp 

input_handler.o : input_handler.cpp input_handler.h global_enumerations.h
	$(CXX) $(LIBRARIES) -c input_handler.cpp

resource_manager.o : resource_manager.cpp resource_manager.h texture.h shader.h #map_layer.h
	$(CXX) $(LIBRARIES) -c resource_manager.cpp

#map_renderer.o : map_renderer.cpp map_renderer.h shader.h texture.h map_layer.h
#	$(CXX) $(LIBRARIES) -c map_renderer.cpp

#map_layer.o : map_layer.cpp map_layer.h shader.h texture.h
#	$(CXX) $(LIBRARIES) -c map_layer.cpp

text_renderer.o : text_renderer.cpp text_renderer.h sprite_renderer.h shader.h texture.h 
	$(CXX) $(LIBRARIES) -c text_renderer.cpp

sprite_renderer.o : sprite_renderer.cpp sprite_renderer.h texture.h shader.h 
	$(CXX) $(LIBRARIES) -c sprite_renderer.cpp

text_rendering.o : text_rendering.cpp shader.h texture.h resource_manager.h sprite_renderer.h
	$(CXX) $(LIBRARIES) -c text_rendering.cpp

texture.o : texture.cpp texture.h 
	$(CXX) $(LIBRARIES) -c texture.cpp

shader.o : shader.cpp shader.h 
	$(CXX) $(LIBRARIES) -c shader.cpp


clean : 
	\rm -f *.o *~
