################################################################################
#
# kvmtool for CCA
#
################################################################################

KVMTOOL_CCA_VERSION = cca/2025-09-12
KVMTOOL_CCA_SITE = https://gitlab.com/Linaro/cca-public/kvmtool.git
KVMTOOL_CCA_SITE_METHOD = git
KVMTOOL_CCA_DEPENDENCIES = \
	$(if $(BR2_PACKAGE_BINUTILS),binutils) \
	$(if $(BR2_PACKAGE_DTC),dtc) \
	$(if $(BR2_PACKAGE_LIBAIO),libaio) \
	$(if $(BR2_PACKAGE_LIBGTK3),libgtk3) \
	$(if $(BR2_PACKAGE_LIBVNCSERVER),libvncserver) \
	$(if $(BR2_PACKAGE_OPENSSL),openssl) \
	$(if $(BR2_PACKAGE_SDL),sdl) \
	$(if $(BR2_PACKAGE_ZLIB),zlib)
KVMTOOL_CCA_LICENSE = GPL-2.0
KVMTOOL_CCA_LICENSE_FILES = COPYING
KVMTOOL_CCA_CPE_ID_VALID = YES

# Disable -Werror, otherwise musl is not happy
KVMTOOL_CCA_MAKE_OPTS = \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	LDFLAGS="$(TARGET_LDFLAGS) $(KVMTOOL_CCA_EXTRA_LDFLAGS)" \
	WERROR=0

define KVMTOOL_CCA_BUILD_CMDS
	$(TARGET_MAKE_ENV) ARCH=$(NORMALIZED_ARCH) $(MAKE) -C $(@D) $(KVMTOOL_CCA_MAKE_OPTS)
endef

define KVMTOOL_CCA_INSTALL_TARGET_CMDS
	$(TARGET_MAKE_ENV) ARCH=$(NORMALIZED_ARCH) $(MAKE) -C $(@D) \
		$(KVMTOOL_CCA_MAKE_OPTS) install DESTDIR=$(TARGET_DIR) prefix=/usr
endef

$(eval $(generic-package))
