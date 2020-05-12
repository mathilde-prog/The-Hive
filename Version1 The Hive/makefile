# project name (generate executable with this name)
GAME_WITH_TESTS  = game test_quete_recherche test_quete_soin test_quete_bandits test_quete_bunker test_quete_montagne test_quete_frontiere test_combat test_backup test_creation_items test_eat_or_drink test_inventory test_item test_item_in_inventory test_load

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm -g

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

FONCTIONS= interface.c interface_combat.c scan.c
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES_SDL=-I${SDLINC_DIR}
SDL= sdl

# change these to proper directories where each file should be
SRCDIR   = ./src
OBJDIR   = obj
BINDIR   = bin
LIBDIR = lib
TRGS	 := $(GAME_WITH_TESTS:%=$(BINDIR)/%)
DIRS	 = $(OBJDIR) $(BINDIR)

.PHONY: DIRS
all: $(DIRS) $(TRGS) $(SDL:%=$(BINDIR)/%)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(GAME_WITH_TESTS:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))
rm       = rm -f

#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	@$(LINKER) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

sdl: interface.c
		${CC} -o ${INTERFACE} $(SRCDIR)/${FONCTIONS} ${LIBS} ${INCLUDES_SDL}

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
