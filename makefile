# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -I./libs
LDFLAGS = -L./libs -lSDL2 -lSDL2_gfx -lSDL2_ttf -lm

# ssh
USER = pi
IP = 192.168.207.49

# Chemins
SRC_DIR = src
FRONT_DIR = $(SRC_DIR)/frontend
BACK_DIR = $(SRC_DIR)/backend
LIB_WIDGETS_DIR = libs/sdl_widgets
LIB_SHAPES_DIR = libs/sdl_shapes
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

# Fichiers sources
WIDGETS_SOURCES = $(wildcard $(LIB_WIDGETS_DIR)/*.c)
SHAPES_SOURCES = $(wildcard $(LIB_SHAPES_DIR)/*.c)
MAIN_SOURCE = $(SRC_DIR)/main.c
FRONT_SOURCES = $(wildcard $(FRONT_DIR)/*.c)

# Fichiers objets
WIDGETS_OBJECTS = $(WIDGETS_SOURCES:$(LIB_WIDGETS_DIR)/%.c=$(OBJ_DIR)/%.o)
SHAPES_OBJECTS = $(SHAPES_SOURCES:$(LIB_SHAPES_DIR)/%.c=$(OBJ_DIR)/%.o)
MAIN_OBJECT = $(MAIN_SOURCE:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
FRONT_OBJECTS = $(FRONT_SOURCES:$(FRONT_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nom de la bibliothèque
LIB_WIDGETS_NAME = libsdl_widgets.a
LIB_WIDGETS_PATH = $(LIB_WIDGETS_DIR)/$(LIB_WIDGETS_NAME)
LIB_SHAPES_NAME = libsdl_shapes.a
LIB_SHAPES_PATH = $(LIB_SHAPES_DIR)/$(LIB_SHAPES_NAME)

# Nom de l'exécutable
EXECUTABLE = $(BIN_DIR)/main

# Règle par défaut
all: directories $(LIB_WIDGETS_PATH) $(LIB_SHAPES_PATH) $(EXECUTABLE)

# Création des répertoires nécessaires
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Compilation de la bibliothèque WIDGETS
$(LIB_WIDGETS_PATH): $(WIDGETS_OBJECTS)
	@echo "--- Compilation de la bibliothèque WIDGETS ---"
	ar rcs $@ $^

# Compilation de la bibliothèque SHAPES
$(LIB_SHAPES_PATH): $(SHAPES_OBJECTS)
	@echo "--- Compilation de la bibliothèque SHAPES ---"
	ar rcs $@ $^

# Compilation du programme principal
$(EXECUTABLE): $(MAIN_OBJECT) $(FRONT_OBJECTS) $(LIB_WIDGETS_PATH) $(LIB_SHAPES_PATH)
	@echo "--- Compilation du programme principal ---"
	$(CC) $(MAIN_OBJECT) $(FRONT_OBJECTS) -o $@ -L$(LIB_WIDGETS_DIR) -lsdl_widgets -L$(LIB_SHAPES_DIR) -lsdl_shapes $(LDFLAGS)

# Règle pour les fichiers objets de la bibliothèque WIDGETS
$(OBJ_DIR)/%.o: $(LIB_WIDGETS_DIR)/%.c $(LIB_WIDGETS_DIR)/sdl_widgets.h
	@echo "[$(OBJ_DIR)/%.o] $(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle pour les fichiers objets de la bibliothèque SHAPES
$(OBJ_DIR)/%.o: $(LIB_SHAPES_DIR)/%.c $(LIB_SHAPES_DIR)/sdl_shapes.h
	@echo "[$(OBJ_DIR)/%.o] $(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle pour le fichier objet du main
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[$(OBJ_DIR)/%.o] $(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle pour les fichiers frontend
$(OBJ_DIR)/%.o : $(FRONT_DIR)/%.c $(FRONT_DIR)/%.h
	@echo "[$(OBJ_DIR)/%.o] $(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(BIN_DIR)
	rm -f $(LIB_WIDGETS_PATH)
	rm -f $(LIB_SHAPES_PATH)
	rm -rf IHM_SDL.tar.gz

# Pour éviter les conflits avec des fichiers du même nom
.PHONY: all clean directories

# Pour archiver
archive: clean
	tar -czf IHM_SDL.tar.gz *

televerse: archive
	scp IHM_SDL.tar.gz $(USER)@$(IP):/home/$(USER)/IHM_SDL