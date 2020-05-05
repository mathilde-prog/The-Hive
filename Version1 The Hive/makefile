# project name (generate executable with this name)
GAME_WITH_TESTS  = game test_random_move test_quete_bandits test_quete_bunker test_quete_montagne test_quete_frontiere test_combat test_backup test_category_hexagon test_creation_items test_eat_or_drink test_inventory test_item test_item_in_inventory test_load test_loot test_map

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
LIBDIR = lib
TRGS	 := $(GAME_WITH_TESTS:%=$(BINDIR)/%)
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

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@rm -rf $(OBJDIR)
	@rm -rf doc/html
	@rm -rf doc/latex
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(GAME_WITH_TESTS)
	@echo "Executable removed!"

.PHONY: docs
docs:
	@doxygen doc/Doxyfile
	@xdg-open doc/html/index.html
	@echo "Documentation generated!"
