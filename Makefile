################################################################################
# OBD-II/GPS Application
# Josh Lubawy <jlubawy@asu.edu>
################################################################################

ifeq ($(OS),Windows_NT)
RM = DEL /Q
MKDIR = if not exist $(dir $@) MKDIR $(dir $@)
else
RM = rm -rf
MKDIR = mkdir -p $@
endif

MMCU ?= atmega328p
COM_PORT ?= COM10

HAS_LCD = FALSE

DEFINES  = -DF_CPU=16000000L
DEFINES += -DARDUINO=10603
DEFINES += -DARDUINO_AVR_UNO
DEFINES += -DARDUINO_ARCH_AVR

ARDUINO_DIR = C:/PROGRA~2/Arduino
ARDUINO_LIBRARIES_DIR = $(ARDUINO_DIR)/hardware/arduino/avr/libraries
AVR_BIN_DIR = $(ARDUINO_DIR)/hardware/tools/avr/bin
AVR_ETC_DIR = $(ARDUINO_DIR)/hardware/tools/avr/etc
BIN_DIR = bin
LIB_DIR = lib
OBJ_DIR = obj
VENDOR_DIR = vendor

AVR_DUDE = $(AVR_BIN_DIR)/avrdude
AVR_OBJCOPY = $(AVR_BIN_DIR)/avr-objcopy
AVR_OBJDUMP = $(AVR_BIN_DIR)/avr-objdump
AVR_SIZE = $(AVR_BIN_DIR)/avr-size

AR = $(AVR_BIN_DIR)/avr-ar
CC = $(AVR_BIN_DIR)/avr-gcc
CXX = $(AVR_BIN_DIR)/avr-g++

INCLUDES = $(addprefix -I,$(ARDUINO_DIR)/hardware/arduino/avr/variants/standard $(LIBS_DIRS))

COMMON_FLAGS = -g -Os -Wl,-Map,$@.map -Wl,--gc-sections -Wl,-u,vfprintf -lprintf_flt -lm -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=$(MMCU) $(DEFINES) $(INCLUDES)
CFLAGS = $(COMMON_FLAGS)
CXXFLAGS = $(COMMON_FLAGS)

C_RECIPE = $(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<
CPP_RECIPE = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -fno-threadsafe-statics -o $@ -c $<

LIB_RECIPE = $(AR) rcs $@ $^

################################################################################
# TinyGPSPlus Library Recipes
################################################################################
TGP_DIR = $(VENDOR_DIR)/TinyGPSPlus
TGP_TARGET = $(LIB_DIR)/libTinyGPSPlus.a
TGP_CPP_PREREQS = $(wildcard $(TGP_DIR)/*.cpp)
TGP_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(TGP_CPP_PREREQS:.cpp=.cpp.o)))

################################################################################
# SD Library Recipes
################################################################################
# SD_DIR = $(VENDOR_DIR)/SD
# SD_UTILITY_DIR = $(SD_DIR)/utility
# SD_TARGET = $(LIB_DIR)/libSD.a
# SD_CPP_PREREQS = $(wildcard $(SD_DIR)/*.cpp) $(wildcard $(SD_UTILITY_DIR)/*.cpp)
# SD_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SD_CPP_PREREQS:.cpp=.cpp.o)))

################################################################################
# SPI Library Recipes
################################################################################
# SPI_DIR = $(ARDUINO_LIBRARIES_DIR)/SPI
# SPI_TARGET = $(LIB_DIR)/libSPI.a
# SPI_CPP_PREREQS = $(wildcard $(SPI_DIR)/*.cpp)
# SPI_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SPI_CPP_PREREQS:.cpp=.cpp.o)))

################################################################################
# SoftwareSerial Library Recipes
################################################################################
SS_DIR = $(ARDUINO_LIBRARIES_DIR)/SoftwareSerial
SS_TARGET = $(LIB_DIR)/libSoftwareSerial.a
SS_CPP_PREREQS = $(wildcard $(SS_DIR)/*.cpp)
SS_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SS_CPP_PREREQS:.cpp=.cpp.o)))

################################################################################
# Arduino Core Recipes
################################################################################
CORE_DIR = $(ARDUINO_DIR)/hardware/arduino/avr/cores/arduino
CORE_TARGET = $(LIB_DIR)/libArduinoCore.a
CORE_C_PREREQS = $(wildcard $(CORE_DIR)/*.c)
CORE_CPP_PREREQS = $(wildcard $(CORE_DIR)/*.cpp)
CORE_C_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(CORE_C_PREREQS:.c=.c.o)))
CORE_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(CORE_CPP_PREREQS:.cpp=.cpp.o)))

################################################################################
# Application Recipes
################################################################################
APP_DIR = src
APP_TARGET = ObdApp
APP_TARGET_ELF = $(addprefix $(BIN_DIR)/,$(addsuffix .elf,$(APP_TARGET)))
APP_TARGET_EEP = $(addprefix $(BIN_DIR)/,$(addsuffix .eep,$(APP_TARGET)))
APP_TARGET_HEX = $(addprefix $(BIN_DIR)/,$(addsuffix .hex,$(APP_TARGET)))
APP_TARGETS = $(APP_TARGET_EEP) $(APP_TARGET_ELF) $(APP_TARGET_HEX)
APP_C_PREREQS = $(wildcard $(APP_DIR)/*.c)
APP_CPP_PREREQS = $(wildcard $(APP_DIR)/*.cpp)
APP_C_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(APP_C_PREREQS:.c=.c.o)))
APP_CPP_OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(APP_CPP_PREREQS:.cpp=.cpp.o)))

LIB_TARGETS = $(TGP_TARGET) $(SD_TARGET) $(SPI_TARGET) $(SS_TARGET) $(CORE_TARGET)
LIBS = $(addprefix -l,$(notdir $(basename $(subst lib,,$(LIB_TARGETS)))))
LIBS_DIRS = $(TGP_DIR) $(SD_DIR) $(SD_UTILITY_DIR) $(SPI_DIR) $(SS_DIR) $(CORE_DIR)

################################################################################
# Targets
################################################################################
all: $(APP_TARGETS)

clean:
	$(RM) bin lib obj

install: $(APP_TARGET_HEX)
	$(AVR_DUDE) -C$(AVR_ETC_DIR)/avrdude.conf -v -p$(MMCU) -carduino -P$(COM_PORT) -b115200 -D -Uflash:w:$<:i

.PHONY: all clean install

# Libraries
$(TGP_TARGET): $(TGP_CPP_OBJS)
	$(info $@)
	@$(MKDIR)
	$(LIB_RECIPE)

$(SS_TARGET): $(SS_CPP_OBJS)
	$(info $@)
	@$(MKDIR)
	$(LIB_RECIPE)

$(CORE_TARGET): $(CORE_C_OBJS) $(CORE_CPP_OBJS)
	$(info $@)
	@$(MKDIR)
	$(LIB_RECIPE)

# Object Files
$(OBJ_DIR)/%.cpp.o: $(TGP_DIR)/%.cpp
	$(info $@)
	@$(MKDIR)
	$(CPP_RECIPE)

$(OBJ_DIR)/%.cpp.o: $(SS_DIR)/%.cpp
	$(info $@)
	@$(MKDIR)
	$(CPP_RECIPE) -w

$(OBJ_DIR)/%.c.o: $(CORE_DIR)/%.c
	$(info $@)
	@$(MKDIR)
	$(C_RECIPE)

$(OBJ_DIR)/%.cpp.o: $(CORE_DIR)/%.cpp
	$(info $@)
	@$(MKDIR)
	$(CPP_RECIPE)

$(OBJ_DIR)/%.c.o: $(APP_DIR)/%.c
	$(info $@)
	@$(MKDIR)
	$(C_RECIPE)

$(OBJ_DIR)/%.cpp.o: $(APP_DIR)/%.cpp
	$(info $@)
	@$(MKDIR)
	$(CPP_RECIPE)

# Output Files
$(APP_TARGET_ELF): $(LIB_TARGETS)
$(APP_TARGET_ELF): $(APP_C_OBJS) $(APP_CPP_OBJS)
	$(info $@)
	@$(MKDIR)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $@ $^
	@$(AVR_SIZE) --mcu=$(MMCU) -C $@
	@$(AVR_SIZE) --mcu=$(MMCU) -C $@ > $(BIN_DIR)/memory_usage.txt
	@$(AVR_OBJDUMP) --disassemble --syms $@ > $@.lst
$(APP_TARGET_EEP) $(APP_TARGET_HEX): $(APP_TARGET_ELF)
	$(info $@)
	@$(MKDIR)
	@$(AVR_OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@
	@$(AVR_OBJCOPY) -O ihex -R .eeprom $< $@
