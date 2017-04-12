#RPG Makefile
OBJS = jump.o resource_manager.o game.o shader.o texture.o sprite_renderer.o character_object.o game_object.o text_renderer.o
#OBJS = text_rendering.o texture.o shader.o resource_manager.o sprite_renderer.o
CXX = clang++
CFLAGS = -Wall -clang
LIBRARIES = -Wall -std=c++11 -stdlib=libc++\
			-L/usr/local/Cellar/glew/1.13.0/lib \
			-I/usr/local/Cellar/glew/1.13.0/include -lglew \
			-L/usr/local/Cellar/glfw3/3.2.1/lib \
			-I/usr/local/Cellar/glfw3/3.2.1/include -lglfw3\
			-L/opt/local/lib -lSOIL\
			-I/opt/local/include/SOIL\
			-L/usr/local/include/freetype2 -lfreetype\
			-I/usr/local/include/freetype2 -lfreetype\
			-I/Users/jacobkohuth/Desktop/FirstGame/include\
			-I/Users/jacobkohuth/Desktop/FirstGame\
			-framework Cocoa -framework OpenGL -framework IOKit\
			-framework CoreFoundation -framework CoreVideo\

.PHONY : start clean

all : start

start : $(OBJS)
	$(CXX) -o start $(LIBRARIES) $(OBJS)

jump.o : jump.cpp resource_manager.h game.h
	$(CXX) $(LIBRARIES) -c jump.cpp

#RPG.o : RPG.cpp resource_manager.h game.h
#	$(CXX) $(LIBRARIES) -c RPG.cpp

game.o : game.cpp game.h resource_manager.h sprite_renderer.h
	$(CXX) $(LIBRARIES) -c game.cpp

character_object.o : character_object.cpp character_object.h sprite_renderer.h game_object.h texture.o
	$(CXX) $(LIBRARIES) -c character_object.cpp

game_object.o : game_object.cpp game_object.h texture.h sprite_renderer.h
	$(CXX) $(LIBRARIES) -c game_object.cpp 

resource_manager.o : resource_manager.cpp resource_manager.h texture.h shader.h
	$(CXX) $(LIBRARIES) -c resource_manager.cpp

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