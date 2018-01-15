# lustro engine Makefile
# All right reserved... or something.

all: texture_test raycaster_test

CC=g++
CFLAGS=-lncursesw
CFLAGSREAL=-O2 -g
SRCDIR=source
BLDDIR=build

SRC= $(filter-out $(wildcard source/Examples/*.cpp) $(wildcard source/*/staticaa*.cpp),  $(wildcard source/*.cpp) $(wildcard source/*/*.cpp) $(wildcard source/*/*/*.cpp) $(wildcard source/*/*/*/*.cpp))
OBJ=$(SRC:%.cpp=%.o)
INCLUDEDIRS=-Isource/ -Isource/* -Isource/*/* -Isource/*/*/* -Isource/*/*/*/*

clear: 
	rm -rf source/*/*.o source/*/*/*.o source/*/*/*/*.o

lustro: $(OBJ)
	echo --------------------------------------------------------
	echo --------------------------------------------------------
	$(CC) $(CFLAGSREAL) $(OBJ) $(SRCDIR)/Examples/lustro_game.cpp -o $(BLDDIR)/Examples/lustro $(CFLAGS)

rebuildlustro: clear lustro

texture_creator: $(OBJ)
	$(CC) $(CFLAGSREAL) $(OBJ) $(SRCDIR)/Examples/texture_creator.cpp -o $(BLDDIR)/Examples/lustro-texture-creator $(CFLAGS)

lustro_game: $(SRCDIR)/Examples/lustro_game.cpp $(SRCDIR)/Drawable/Drawable.cpp $(SRCDIR)/Engine/Engine.cpp $(SRCDIR)/Wall/LinkedWall/LinkedWall.cpp $(SRCDIR)/Map/Map.cpp $(SRCDIR)/PixelData/PixelData.cpp $(SRCDIR)/Drawable/Raycaster/Raycaster.cpp $(SRCDIR)/Renderer/Renderer.cpp $(SRCDIR)/Sprite2D/Sprite2D.cpp $(SRCDIR)/Drawable/Spritecaster/Spritecaster.cpp $(SRCDIR)/Texture/Texture.cpp $(SRCDIR)/Wall/Wall.cpp $(SRCDIR)/IniInterpreter/IniFile.cpp $(SRCDIR)/IniInterpreter/Section.cpp $(SRCDIR)/IniInterpreter/Variable.cpp
	$(CC) -O2 -o $(BLDDIR)/Examples/lustro_game $(SRCDIR)/Examples/lustro_game.cpp $(SRCDIR)/Drawable/Drawable.cpp $(SRCDIR)/Engine/Engine.cpp $(SRCDIR)/Wall/LinkedWall/LinkedWall.cpp $(SRCDIR)/Map/Map.cpp $(SRCDIR)/PixelData/PixelData.cpp $(SRCDIR)/Drawable/Raycaster/Raycaster.cpp $(SRCDIR)/Renderer/Renderer.cpp $(SRCDIR)/Sprite2D/Sprite2D.cpp $(SRCDIR)/Drawable/Spritecaster/Spritecaster.cpp $(SRCDIR)/Texture/Texture.cpp $(SRCDIR)/Wall/Wall.cpp $(SRCDIR)/IniInterpreter/IniFile.cpp $(SRCDIR)/IniInterpreter/Section.cpp $(SRCDIR)/IniInterpreter/Variable.cpp $(CFLAGS)

texture_test: $(SRCDIR)/Examples/texture_test.cpp $(SRCDIR)/Texture/Texture.cpp $(SRCDIR)/PixelData/PixelData.cpp
	$(CC) -O2 -o $(BLDDIR)/Examples/texture_test $(SRCDIR)/Examples/texture_test.cpp $(SRCDIR)/Texture/Texture.cpp $(SRCDIR)/PixelData/PixelData.cpp $(CFLAGS)

raycaster_test: $(SRCDIR)/Examples/raycaster_test.cpp $(SRCDIR)/Drawable/Drawable.cpp $(SRCDIR)/Wall/LinkedWall/LinkedWall.cpp $(SRCDIR)/Drawable/Raycaster/Raycaster.cpp $(SRCDIR)/Texture/Texture.cpp $(SRCDIR)/PixelData/PixelData.cpp $(SRCDIR)/Wall/Wall.cpp
	$(CC) -O2 -o $(BLDDIR)/Examples/raycaster_test $(SRCDIR)/Examples/raycaster_test.cpp $(SRCDIR)/Drawable/Drawable.cpp $(SRCDIR)/Wall/LinkedWall/LinkedWall.cpp $(SRCDIR)/Drawable/Raycaster/Raycaster.cpp $(SRCDIR)/Texture/Texture.cpp $(SRCDIR)/PixelData/PixelData.cpp $(SRCDIR)/Wall/Wall.cpp $(CFLAGS)
