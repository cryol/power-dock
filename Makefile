
# main compiler
CC := gcc
# CC := clang --analyze # and comment out the linker last line for sanity

# define the directories
SRCDIR := src
INCDIR := include
BUILDDIR := build
BINDIR := bin
LIBDIR := lib



# define common variables
SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -maxdepth 1 -type f \( -iname "*.$(SRCEXT)" ! -iname "*main-*.$(SRCEXT)" \) )
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
INC := $(shell find $(INCDIR) -maxdepth 1 -type d -exec echo -I {}  \;)


# define specific binaries to create
# C libraries
LIBD := libonionpowerdock
SOURCE_LIBD := src/powerdock-exp.$(SRCEXT)
OBJECT_LIBD := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCE_LIBD:.$(SRCEXT)=.o))
TARGET_LIBD := $(LIBDIR)/$(LIBD).so



# C applications
APP0 := powerdock-exp
SOURCE_APP0 := $(SRCDIR)/main-$(APP0).$(SRCEXT)
OBJECT_APP0 := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCE_APP0:.$(SRCEXT)=.o))
LIB_APP0 := -L$(LIBDIR) -lonionpowerdock -lugpio -loniondebug
TARGET_APP0 := $(BINDIR)/$(APP0)




all: resp $(TARGET_LIBD)  $(TARGET_APP0) 


# libraries
$(TARGET_LIBD): $(OBJECT_LIBD)
	@echo " Compiling $@"
	@mkdir -p $(LIBDIR)
	$(CC) -shared -o $@  $^ $(LIB_LIBD)


# generic: build any object file required
$(TARGET_APP0): $(OBJECT_APP0)
	@echo " Compiling $(APP0)"
	@mkdir -p $(BINDIR)
	@echo " Linking..."
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $(TARGET_APP0) $(LIB) $(LIB_APP0)
	
# generic: build any object file required
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(BINDIR) $(LIBDIR)

bla:
	@echo "$(BLA)"
	@echo "TARGET_APP0: $(APP0) $(SOURCE_APP0) $(OBJECT_APP0) $(TARGET_APP0)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"

resp:
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "LIB: $(LIB)"

# Tests
#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#  $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean