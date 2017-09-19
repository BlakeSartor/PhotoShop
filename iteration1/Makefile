UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
	LIBS += -framework GLUT -framework openGL
else
	LIBS += -lglut -lGL -lGLU
endif

SRC_CXX += src/base_gfx_app.cc
SRC_CXX += src/brushwork_app.cc
SRC_CXX += src/color_data.cc
SRC_CXX += src/main.cc
SRC_CXX += src/pixel_buffer.cc
SRC_CXX += src/tool.cc
SRC_CXX += src/pen.cc
SRC_CXX += src/mask.cc

OBJ_CXX += obj/base_gfx_app.o
OBJ_CXX += obj/brushwork_app.o
OBJ_CXX += obj/color_data.o
OBJ_CXX += obj/main.o
OBJ_CXX += obj/pixel_buffer.o
OBJ_CXX += obj/tool.o
OBJ_CXX += obj/pen.o
OBJ_CXX += obj/calligraphy.o
OBJ_CXX += obj/eraser.o
OBJ_CXX += obj/spray_can.o
OBJ_CXX += obj/highlighter.o
OBJ_CXX += obj/mask.o
OBJ_CXX += obj/special.o

.PHONY: all glui

all: bin/BrushWork

bin/BrushWork: ext/glui/lib/libglui.a $(OBJ_CXX) | bin
	g++  -o bin/BrushWork  $(OBJ_CXX) -Lext/glui/lib/ $(LIBS) -lglui

obj/%.o: src/%.cc | obj
	g++ -Isrc -std=c++11 -Iext/glui/include -o $@ -c $<

ext/glui/lib/libglui.a:
	$(MAKE) -Cext/glui all

obj bin:
	mkdir $@

clean:
	rm -rf obj bin

clean_all: clean
	$(MAKE) -Cext/glui clean
