################################################################################
# Name            : Makefile
# Project         : FlashPhoto Suite
# Description     : Library Makefile Template
# Creation Date   : Fri May 16 14:59:49 2014
# Original Author : jharwell
#
# Note: This file is -j (parallel build) safe, provided you don't mess with it
# too much.
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  all             build/lib/lib<dirname>   The main library
#  clean           N/A                      Removes library, all .o
#  veryclean       N/A                      Everything clean removes, +
#                                           the external libraries
#  documentation   Various                  Generates documentation for
#                                           project from the doxygen
#                                           comments/markup in the code
################################################################################

###############################################################################
# Directory Definitions
###############################################################################
# src/      - Root of the source tree for the project
# build/    - Root directory for project build process
# doc/      - Directory where all documentation lives
# config/   - Directory for all autoconf/configure/automake inputs/output
BUILDDIR        = $(BUILDROOT)/$(notdir $(shell pwd))
SRCDIR          = /src/lib/libimgtools
OBJDIR          = $(BUILDDIR)/obj
LIBDIR          = $(BUILDDIR)/lib
DOCDIR          = ./doc

###############################################################################
# Functions
###############################################################################
# Recursive wildcard: search a list of directories for all files that match a pattern
# usage: $(call rwildcard, $(DIRS1) $(DIRS2) ..., pattern)
#
# All directory lists passed as first arg must be separated by spaces, and they
# themselves must be space separated as well. There must NOT be a space between
# the last dir list the , and the start of the pattern.
#
# You should never need to modify this.
# usage: $(call rwildcard, $(DIRS1) $(DIRS2) ..., pattern)
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)  $(filter $(subst *,%,$2),$d))

# make-depend: generate dependencies for C++ source files dynamically. Very useful
# for including .h files as target dependencies.
# usage: $(call make-depend,source-file,object-file,depend-file)
#
# You should never need to modify this.
# usage: $(call make-depend,source-file,object-file,depend-file)
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

###############################################################################
# Target Definitions
###############################################################################
# Define what directories to search for source code. For us, this will just
# be a single source directory, src/.
SOURCES = $(SRCDIR)

# Define the list of files to compile for this project, which is built by
# recursively finding all .cc files in src/.
SRC_CXX = $(call rwildcard,$(SOURCES),*.cc)

# For each of the .cc files found under src/, determine the name of the
# corresponding .o file to create in obj/ via pattern substitution (patsust).
OBJECTS_CXX = $(notdir $(patsubst %.cc,%.o,$(SRC_CXX)))

# The target library (what you are building)
TARGET = $(LIBDIR)/$(notdir $(shell pwd)).a

OBJ_PATH = build/libimgtools/obj/
SRC_PATH = src/lib/libimgtools/
 
SRC_CXX += src/lib/libimgtools/filter.cc
SRC_CXX += src/lib/libimgtools/convolution_filter.cc
SRC_CXX += src/lib/libimgtools/motion_blur.cc
SRC_CXX += src/lib/libimgtools/blur.cc
SRC_CXX += src/lib/libimgtools/sharpen.cc
SRC_CXX += src/lib/libimgtools/rgb_levels.cc
SRC_CXX += src/lib/libimgtools/threshold.cc
SRC_CXX += src/lib/libimgtools/saturation.cc
SRC_CXX += src/lib/libimgtools/quantize.cc
SRC_CXX += src/lib/libimgtools/edge_detection.cc
SRC_CXX += src/lib/libimgtools/special_filter.cc
SRC_CXX += src/lib/libimgtools/stamp.cc

SRC_CXX += src/lib/libimgtools/base_gfx_app.cc
SRC_CXX += src/lib/libimgtools/blur_tool.cc
SRC_CXX += src/lib/libimgtools/calligraphy.cc
SRC_CXX += src/lib/libimgtools/color_data.cc
SRC_CXX += src/lib/libimgtools/eraser.cc
SRC_CXX += src/lib/libimgtools/highlighter.cc
SRC_CXX += src/lib/libimgtools/spray_can.cc
SRC_CXX += src/lib/libimgtools/pixel_buffer.cc
SRC_CXX += src/lib/libimgtools/tool.cc
SRC_CXX += src/lib/libimgtools/pen.cc
SRC_CXX += src/lib/libimgtools/mask.cc
SRC_CXX += src/lib/libimgtools/special.cc


OBJ_CXX += build/libimgtools/obj/filter.o
OBJ_CXX += build/libimgtools/obj/convolution_filter.o
OBJ_CXX += build/libimgtools/obj/motion_blur.o
OBJ_CXX += build/libimgtools/obj/blur.o
OBJ_CXX += build/libimgtools/obj/sharpen.o
OBJ_CXX += build/libimgtools/obj/rgb_levels.o
OBJ_CXX += build/libimgtools/obj/threshold.o
OBJ_CXX += build/libimgtools/obj/saturation.o
OBJ_CXX += build/libimgtools/obj/quantize.o
OBJ_CXX += build/libimgtools/obj/edge_detection.o
OBJ_CXX += build/libimgtools/obj/special_filter.o
OBJ_CXX += build/libimgtools/obj/stamp.o

OBJ_CXX += build/libimgtools/obj/base_gfx_app.o
OBJ_CXX += build/libimgtools/obj/blur_tool.o
OBJ_CXX += build/libimgtools/obj/calligraphy.o
OBJ_CXX += build/libimgtools/obj/color_data.o
OBJ_CXX += build/libimgtools/obj/eraser.o
OBJ_CXX += build/libimgtools/obj/highlighter.o
OBJ_CXX += build/libimgtools/obj/spray_can.o
OBJ_CXX += build/libimgtools/obj/pixel_buffer.o
OBJ_CXX += build/libimgtools/obj/tool.o
OBJ_CXX += build/libimgtools/obj/pen.o
OBJ_CXX += build/libimgtools/obj/mask.o
OBJ_CXX += build/libimgtools/obj/special.o


###############################################################################
# All targets
###############################################################################

# Phony targets: targets of this type will be run everytime by make (i.e. make
# does not assume that the target recipe will build the target name)
.PHONY: clean veryclean all documentation

# The default target which will be run if the user just types "make" without a
# target name
all: $(TARGET)

# Unless invoked with make clean, include generated dependencies. This makes
# it so that anytime you make an edit in a .h file, make will know that all
# .cc files that include are out of date and will need to be recompiled.
#
# $(MAKECMDGOALS) is a special make variable that contains a space separated
# list of variables that make was told to build.
ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(OBJECTS_CXX:.o=.d))
endif


# The Objectifier. This rule says that each .o file in obj/, depends on the
# presence of the obj/ directory. This is necessary so that parallel make
# (make -j) works. Also, some .o files depend on .cc files that in turn depend
# on header files generated by building external libraries, so add them as
# dependencies as well.
$(addprefix $(OBJDIR)/, $(OBJECTS_CXX)): | $(OBJDIR)

# The Target Library.
$(TARGET): $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) | $(LIBDIR)
	echo "FIXME: Creating libimgtools..."
	ar rcs $(LIBDIR)/libimgtools.a $(addprefix $(OBJDIR)/, $(OBJECTS_CXX))


install: $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) $(OBJ_CXX) $(TARGET)
	@rm -rf $(BUILDROOT)/lib/$(notdir $(shell pwd)).a
	@cd $(BUILDROOT)/lib && ln -s ../$(notdir $(shell pwd))/lib/$(notdir $(shell pwd)).a


# Bootstrap Bill. This creates all of the order-only prerequisites; that is,
# files/directories that have to be present in order for a given target build
# to succeed, but that make knows do not need to be remade each time their
# modification time is updated and they are newer than the target being built.
$(BINDIR) $(OBJDIR) $(LIBDIR):
	@mkdir -p $@

# The Cleaner. Clean up the project, by removing ALL files generated during
# the build process to build the main target.
clean:
	@rm -rf $(BUILDDIR)

# The Super Cleaner. Clean the project, but also clean all external libraries.
veryclean: clean
	@rm -rf $(BUILDDIR)

# The Documenter. Generate documentation for the project.
documentation:
	cd $(DOCDIR) && doxygen Doxyfile
	cd ..

###############################################################################
# Pattern Rules
###############################################################################
# For compiling the C++ source. Specify that any .o file in obj/ can be built
# from any .cc file in src/. Before doing compilation, emit (possibly) make
# rules for the includes for the .cc file, as they may have changed since the
# last invocation of make.
build/libimgtools/obj/filter.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath filter.cc) -o $(OBJDIR)/filter.o
build/libimgtools/obj/convolution_filter.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath convolution_filter.cc) -o $(OBJDIR)/convolution_filter.o
build/libimgtools/obj/motion_blur.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath motion_blur.cc) -o $(OBJDIR)/motion_blur.o
build/libimgtools/obj/blur.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath blur.cc) -o $(OBJDIR)/blur.o
build/libimgtools/obj/sharpen.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath sharpen.cc) -o $(OBJDIR)/sharpen.o
build/libimgtools/obj/rgb_levels.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath rgb_levels.cc) -o $(OBJDIR)/rgb_levels.o
build/libimgtools/obj/threshold.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath threshold.cc) -o $(OBJDIR)/threshold.o
build/libimgtools/obj/saturation.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath saturation.cc) -o $(OBJDIR)/saturation.o
build/libimgtools/obj/quantize.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath quantize.cc) -o $(OBJDIR)/quantize.o
build/libimgtools/obj/edge_detection.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath edge_detection.cc) -o $(OBJDIR)/edge_detection.o
build/libimgtools/obj/special_filter.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath special_filter.cc) -o $(OBJDIR)/special_filter.o
build/libimgtools/obj/stamp.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath stamp.cc) -o $(OBJDIR)/stamp.o
build/libimgtools/obj/base_gfx_app.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath base_gfx_app.cc) -o $(OBJDIR)/base_gfx_app.o
build/libimgtools/obj/blur_tool.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath blur_tool.cc) -o $(OBJDIR)/blur_tool.o
build/libimgtools/obj/calligraphy.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath calligraphy.cc) -o $(OBJDIR)/calligraphy.o
build/libimgtools/obj/color_data.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath color_data.cc) -o $(OBJDIR)/color_data.o
build/libimgtools/obj/eraser.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath eraser.cc) -o $(OBJDIR)/eraser.o
build/libimgtools/obj/highlighter.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath highlighter.cc) -o $(OBJDIR)/highlighter.o
build/libimgtools/obj/spray_can.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath spray_can.cc) -o $(OBJDIR)/spray_can.o
build/libimgtools/obj/pixel_buffer.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath pixel_buffer.cc) -o $(OBJDIR)/pixel_buffer.o
build/libimgtools/obj/tool.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath tool.cc) -o $(OBJDIR)/tool.o
build/libimgtools/obj/pen.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath pen.cc) -o $(OBJDIR)/pen.o
build/libimgtools/obj/mask.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath mask.cc) -o $(OBJDIR)/mask.o
build/libimgtools/obj/special.o:
	echo $(abspath $(SRC_PATH))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c $(abspath special.cc) -o $(OBJDIR)/special.o



