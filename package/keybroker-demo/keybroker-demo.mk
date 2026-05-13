################################################################################
#
# Veraison keybroker demo application
#
################################################################################

# To use your own source directory during development:
#
# - Add a local.mk file in the buildroot build directory
#
#     BUILD_DIR=~/.shrinkwrap/build/cca-3world/buildroot
#     echo "KEYBROKER_DEMO_OVERRIDE_SRCDIR = /path/to/sourcedir" > $BUILD_DIR/local.mk
#
# - Sync the source directory after modifications
#
#     make -C $BUILD_DIR keybroker-demo-rebuild

KEYBROKER_DEMO_VERSION = 01a0d49de1928814cfbd3426ba07df8617177935
KEYBROKER_DEMO_SITE = https://github.com/veraison/keybroker-demo.git
#KEYBROKER_DEMO_SITE = file:///home/z/src/cca/keybroker-demo
KEYBROKER_DEMO_SITE_METHOD = git
KEYBROKER_DEMO_LICENSE = Apache-2.0
KEYBROKER_DEMO_LICENSE_FILES = LICENSE-APACHE
KEYBROKER_DEMO_SUBDIR = rust-keybroker/keybroker-app

# Depends on OpenSSL lib, so pkg-config is used during build
KEYBROKER_DEMO_DEPENDENCIES += host-pkgconf openssl

$(eval $(cargo-package))
