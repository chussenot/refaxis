# Include the Redis-related commands from redis.Makefile
include services/redis.Makefile

# Set the default target
.DEFAULT_GOAL := help

# Specify the build directory
BUILDDIR = build
PACKAGESDIR = packages

# Specify the Meson and Ninja commands, etc.
MESON = meson
NINJA = ninja
CONAN = conan
POETRY = poetry
DPKG-DEB = dpkg-deb
DPKG = dpkg

# Help message
help:
	@echo "Usage:"
	@echo "  make setup     - Setup the build directory"
	@echo "  make deps      - Install dependencies using Conan"
	@echo "  make build     - Build the project"
	@echo "  make install   - Install the executable"
	@echo "  make clean     - Clean the build directory"
	@echo "  make run       - Run the program"
	@echo "  make package   - Create packages"
	@echo "  make all       - Setup, build, install,..."

# Install the needed packages

# Install the uuid-dev package (Linux-specific)
install_uuid_dev:
	sudo apt-get install uuid-dev  # Use the appropriate package manager for your distribution

install:
	@$(POETRY) install

# Install dependencies using Conan
deps:
	@$(POETRY) run $(CONAN) install . -if=$(BUILDDIR) --build=missing 

# Setup the build directory
setup:
	@$(POETRY) run $(MESON) setup --reconfigure --native-file $(BUILDDIR)/conan_meson_native.ini . $(BUILDDIR)

# Build the project
.PHONY: build
build:
	@$(POETRY) run $(MESON) compile -C ${BUILDDIR}

# Clean the build directory & some artefacts
clean:
	@rm -Rf $(BUILDDIR)/* && touch $(BUILDDIR)/.gitkeep
	@rm -f $(PACKAGESDIR)/*.deb

package:
	@echo 'Ready to package'

# Setup, build, install
all: install deps setup build

.PHONY: validate
validate:
	$(POETRY) run python -m tests.test_validator
