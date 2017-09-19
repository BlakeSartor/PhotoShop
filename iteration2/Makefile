CC = g++

CFLAGS = -std=c++11

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
	LINK_LIBS += -framework GLUT -framework openGL
else
	LINK_LIBS += -lglut -lGL -lGLU
endif

GLUI = glui
GLUI_PATH = ext/glui
GLUI_LIB = $(GLUI_PATH)/lib/lib$(GLUI).a

PNG = png
PNG_PATH = ext/libpng-1.6.16
PNG_LIB = $(PNG_PATH)/lib/lib$(PNG).a

JPEG = jpeg
JPEG_PATH = ext/jpeg-9a
JPEG_LIB = $(JPEG_PATH)/lib/lib$(JPEG).a

INCLUDE += -Isrc
INCLUDE += -I$(GLUI_PATH)/include
INCLUDE += -I$(PNG_PATH)/include
INCLUDE += -I$(JPEG_PATH)/include

LINK_LIBS += -L$(GLUI_PATH)/lib/ -lglui
LINK_LIBS += -L$(PNG_PATH)/lib/ -lpng
LINK_LIBS += -L$(JPEG_PATH)/lib/ -ljpeg
LINK_LIBS += -lz

OBJECT_PATH = obj
SOURCE_PATH = src

OBJECTS = $(addprefix $(OBJECT_PATH)/,  $(FILENAMES:.cc=.o))
CPPFILES = $(wildcard $(SOURCE_DIR)/*.cc)
FILENAMES =  $(notdir $(CPPFILES))

SRC_CXX += src/filter.cc
SRC_CXX += src/convolution_filter.cc
SRC_CXX += src/motion_blur.cc
SRC_CXX += src/blur.cc
SRC_CXX += src/sharpen.cc
SRC_CXX += src/rgb_levels.cc
SRC_CXX += src/threshold.cc
SRC_CXX += src/saturation.cc
SRC_CXX += src/quantize.cc
SRC_CXX += src/edge_detection.cc
SRC_CXX += src/special_filter.cc
SRC_CXX += src/stamp.cc

SRC_CXX += src/base_gfx_app.cc
SRC_CXX += src/blur_tool.cc
SRC_CXX += src/calligraphy.cc
SRC_CXX += src/color_data.cc
SRC_CXX += src/eraser.cc
SRC_CXX += src/filter_manager.cc
SRC_CXX += src/highlighter.cc
SRC_CXX += src/flashphoto_app.cc
SRC_CXX += src/io_manager.cc
SRC_CXX += src/spray_can.cc
SRC_CXX += src/state_manager.cc
SRC_CXX += src/main.cc
SRC_CXX += src/pixel_buffer.cc
SRC_CXX += src/tool.cc
SRC_CXX += src/pen.cc
SRC_CXX += src/mask.cc
SRC_CXX += src/special.cc
SRC_CXX += src/image_manager.cc

OBJ_CXX += obj/filter.o
OBJ_CXX += obj/convolution_filter.o
OBJ_CXX += obj/motion_blur.o
OBJ_CXX += obj/blur.o
OBJ_CXX += obj/sharpen.o
OBJ_CXX += obj/rgb_levels.o
OBJ_CXX += obj/threshold.o
OBJ_CXX += obj/saturation.o
OBJ_CXX += obj/quantize.o
OBJ_CXX += obj/edge_detection.o
OBJ_CXX += obj/special_filter.o
OBJ_CXX += obj/stamp.o

OBJ_CXX += obj/base_gfx_app.o
OBJ_CXX += obj/blur_tool.o
OBJ_CXX += obj/calligraphy.o
OBJ_CXX += obj/color_data.o
OBJ_CXX += obj/eraser.o
OBJ_CXX += obj/filter_manager.o
OBJ_CXX += obj/highlighter.o
OBJ_CXX += obj/flashphoto_app.o
OBJ_CXX += obj/io_manager.o
OBJ_CXX += obj/spray_can.o
OBJ_CXX += obj/state_manager.o
OBJ_CXX += obj/main.o
OBJ_CXX += obj/pixel_buffer.o
OBJ_CXX += obj/tool.o
OBJ_CXX += obj/pen.o
OBJ_CXX += obj/mask.o
OBJ_CXX += obj/special.o
OBJ_CXX += obj/image_manager.o


.PHONY: all glui 

all: bin/FlashPhoto

bin/FlashPhoto: $(GLUI_LIB) $(PNG_LIB) $(JPEG_LIB) $(OBJ_CXX) | bin
	g++ -o bin/FlashPhoto $(OBJ_CXX) $(LINK_LIBS)

obj/%.o: src/%.cc | obj
	g++ $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(GLUI_LIB):
	$(MAKE) -C$(GLUI_PATH) all

$(PNG_LIB):
	cd $(PNG_PATH); \
	./configure --prefix=$(abspath $(PNG_PATH)) --enable-shared=no 
	$(MAKE) -C$(PNG_PATH)
	#$(MAKE) -C$(PNG_PATH) check
	$(MAKE) -C$(PNG_PATH) install

$(JPEG_LIB):
	cd $(JPEG_PATH); \
	./configure --prefix=$(abspath $(JPEG_PATH)) --enable-shared=no
	$(MAKE) -C$(JPEG_PATH)
	$(MAKE) -C$(JPEG_PATH) check
	$(MAKE) -C$(JPEG_PATH) install

obj bin:
	mkdir $@

clean:
	rm -rf obj bin

clean_all: clean
	$(MAKE) -C$(GLUI_PATH) clean
	$(MAKE) -C$(PNG_PATH) clean
	$(MAKE) -C$(JPEG_PATH) clean
