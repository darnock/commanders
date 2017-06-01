BUILD_DIR=build/
SRC_DIR=src/
CPP=g++ 
CPP_FLAGS= -Wall --pedantic -std=c++11

#os check
UNAME := $(shell uname)

#linux
ifeq ($(UNAME), Linux) 
CPP_FLAGS_SDL= -lSDL2 -lSDL2_ttf
CPP_FLAGS_NCURSES = -lncurses
endif

#cygwin
ifeq ($(UNAME), CYGWIN_NT-6.1)
CPP_FLAGS_SDL = -L/usr/local/lib -lcygwin -lSDL2_ttf -lSDL2main -lSDL2 -mwindows
CPP_FLAGS_NCURSES = -L/usr/local/lib -lcygwin -lncurses
endif

OUTPUT= -o $(BUILD_DIR)
SRC_SETTINGS=$(SRC_DIR)mod_settings/

all: mkdir settings.out main.out mklink;
	
mkdir:
	if [ -d "$(BUILD_DIR)" ]; then echo "$(BUILD_DIR) exists"; \
	else mkdir $(BUILD_DIR); fi

$(BUILD_DIR)units.o: $(SRC_DIR)units.cpp $(SRC_DIR)include/units.h $(SRC_DIR)include/main.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)$(*F).cpp $(OUTPUT)$(@F)
	
$(BUILD_DIR)main.o: $(SRC_DIR)main.cpp $(SRC_DIR)include/units.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)$(*F).cpp $(OUTPUT)$(@F)
	
$(BUILD_DIR)text_mode.o: $(SRC_DIR)text_mode.cpp $(SRC_DIR)include/text_mode.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)$(*F).cpp $(OUTPUT)$(@F)

$(BUILD_DIR)class_attribute.o: $(SRC_SETTINGS)class_attribute.cpp $(SRC_SETTINGS)class_attribute.h $(SRC_DIR)mod_debug/debug.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_SETTINGS)$(*F).cpp $(OUTPUT)$(@F)

$(BUILD_DIR)class_save_file.o: $(SRC_SETTINGS)class_save_file.cpp $(SRC_SETTINGS)class_save_file.h $(SRC_SETTINGS)class_attribute.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_SETTINGS)class_save_file.cpp $(OUTPUT)class_save_file.o
	
$(BUILD_DIR)settings.o: $(SRC_SETTINGS)settings.cpp $(SRC_SETTINGS)settings.h $(SRC_SETTINGS)settings.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_SETTINGS)$(*F).cpp $(OUTPUT)$(@F)
	
$(BUILD_DIR)debug.o: $(SRC_DIR)/mod_debug/debug.cpp $(SRC_DIR)/mod_debug/debug.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)mod_debug/$(*F).cpp $(OUTPUT)$(@F)

$(BUILD_DIR)game.o: $(SRC_DIR)game.cpp $(SRC_DIR)include/game.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)$(*F).cpp $(OUTPUT)$(@F)
	
$(BUILD_DIR)text.o: $(SRC_DIR)text.cpp $(SRC_DIR)include/text.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)$(*F).cpp $(OUTPUT)$(@F)
	
$(BUILD_DIR)sign.o: $(SRC_DIR)sign.cpp $(SRC_DIR)include/sign.h
	$(CPP) $(CPP_FLAGS) -c $(SRC_DIR)$(*F).cpp $(OUTPUT)$(@F)

#main.out: $(BUILD_DIR)sign.o $(BUILD_DIR)text.o $(BUILD_DIR)units.o $(BUILD_DIR)main.o $(BUILD_DIR)text_mode.o $(BUILD_DIR)class_save_file.o $(BUILD_DIR)game.o
main.out: $(BUILD_DIR)sign.o $(BUILD_DIR)text.o $(BUILD_DIR)units.o $(BUILD_DIR)main.o $(BUILD_DIR)class_save_file.o $(BUILD_DIR)game.o
#	$(CPP) $(OUTPUT)main.out $(BUILD_DIR)sign.o $(BUILD_DIR)units.o $(BUILD_DIR)main.o $(BUILD_DIR)text_mode.o $(BUILD_DIR)text.o $(BUILD_DIR)game.o $(CPP_FLAGS_SDL) $(CPP_FLAGS_NCURSES)
	$(CPP) $(OUTPUT)main.out $(BUILD_DIR)sign.o $(BUILD_DIR)units.o $(BUILD_DIR)main.o $(BUILD_DIR)text.o $(BUILD_DIR)game.o $(CPP_FLAGS_SDL) $(CPP_FLAGS_NCURSES)
	cp -rfv $(BUILD_DIR)main.out main.exe

settings.out: $(BUILD_DIR)debug.o $(BUILD_DIR)class_attribute.o $(BUILD_DIR)class_save_file.o $(BUILD_DIR)settings.o
	$(CPP) $(OUTPUT)settings.out $(BUILD_DIR)/debug.o $(BUILD_DIR)/class_attribute.o $(BUILD_DIR)/class_save_file.o $(BUILD_DIR)/settings.o  $(CPP_FLAGS) $(CPP_FLAGS_SDL) $(CPP_FLAGS_NCURSES)
	cp -rfv $(BUILD_DIR)settings.out settings.exe
	
mklink:
	if [ -e $(BUILD_DIR)main.out ]; then echo "link exists"; \
	else ln -s $(BUILD_DIR)main.out; fi
	if [ -e $(BUILD_DIR)settings.out ]; then echo "link exists"; \
	else ln -s $(BUILD_DIR)settings.out; fi
	
clean:
	rm -rfv $(BUILD_DIR)
	#usuwamy link symboliczny
	rm -rfv main.out settings.out main.exe settings.exe
