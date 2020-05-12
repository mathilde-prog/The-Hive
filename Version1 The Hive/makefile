# project name (generate executable with this name)
GAME  = game interface test_backup test_combat test_creation_items test_eat_or_drink test_inventory test_item test_item_in_inventory test_load test_quete_bandits test_quete_bunker test_quete_frontiere test_quete_montagne test_quete_recherche test_quete_soin

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm -g 

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES_SDL=-I${SDLINC_DIR}

# change these to proper directories where each file should be
SRCDIR   = ./src
OBJDIR   = obj
BINDIR   = bin
LIBDIR = lib
TRGS	 := $(GAME:%=$(BINDIR)/%)
TEST_TRGS := $(TEST:%=$(BINDIR)/%)
DIRS	 = $(OBJDIR) $(BINDIR)

.PHONY: DIRS
all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(GAME:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))

#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	@$(LINKER) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) -o $@  $(LIBS) $(INCLUDES_SDL)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(INCLUDES_SDL)
	@echo "Compiled "$<" successfully!"

rm       = rm -f

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@rm -rf $(OBJDIR)
	@rm -rf doc/html
	@rm -rf doc/latex
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) -rf $(BINDIR)
	@echo "Executables removed!"

.PHONY: docs
docs:
	@doxygen doc/Doxyfile
	@xdg-open doc/html/index.html
	@echo "Documentation generated!"
