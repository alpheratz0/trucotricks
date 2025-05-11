.PHONY: all run clean bump-version-patch bump-version-minor bump-version-major distribute installer

include config.mk

SRC_DIRS := scenes scenes/overlays widgets .
BUILD_DIR := build
DIST_DIR := trucotricks-windows-$(shell cat VERSION)

SRC_FILES := $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

OBJ_FILES := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

all: $(OUTNAME)

$(OUTNAME): $(OBJ_FILES)
ifeq ($(TARGET),windows)
	x86_64-w64-mingw32-windres resource.rc -o $(BUILD_DIR)/resource.o
	$(CC) $(OBJ_FILES) $(BUILD_DIR)/resource.o -o $@ $(TRUCOTRICKS_LDFLAGS) >/dev/null
else ifeq ($(TARGET),linux)
	$(CC) $(OBJ_FILES) -o $@ $(TRUCOTRICKS_LDFLAGS) >/dev/null
endif

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(TRUCOTRICKS_CFLAGS) -c $< -o $@ >/dev/null

run: all
	./$(OUTNAME)

bump-version-patch:
	./scripts/bump_version -patch

bump-version-minor:
	./scripts/bump_version -minor

bump-version-major:
	./scripts/bump_version -major

distribute: $(OUTNAME)
	rm -rf $(DIST_DIR)
	mkdir $(DIST_DIR)
	cp -r ./resources $(DIST_DIR)
	mv -f $(OUTNAME) $(DIST_DIR)
ifeq ($(TARGET),windows)
	cp ./third_party/bin/* $(DIST_DIR)
endif

installer: distribute
ifeq ($(TARGET),windows)
	sh -c 'sed -i "s/@VERSION@/$(shell cat VERSION)/g" installer.iss'
	wine "C:\\Program Files (x86)\\Inno Setup 6\\ISCC.exe" installer.iss
	sh -c 'sed -i "s/$(shell cat VERSION)/@VERSION@/g" installer.iss'
else
	@echo Only supported for windows executables
endif

clean:
	rm -rf $(BUILD_DIR) trucotricks.exe trucotricks $(DIST_DIR) trucotricks-windows-*-setup.exe
