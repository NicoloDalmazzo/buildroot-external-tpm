CCA_SWTPM_VERSION = 0.10.1
CCA_SWTPM_SITE = $(call github,stefanberger,swtpm,v$(SWTPM_VERSION))

CCA_SWTPM_LICENSE = BSD-4-Clause
CCA_SWTPM_LICENSE_FILES = LICENSE

CCA_SWTPM_INSTALL_STAGING = YES

CCA_SWTPM_DEPENDENCIES = cca-libtpms openssl libseccomp libtasn1 gnutls json-glib

# Required because a plain Git clone is used:
CCA_SWTPM_AUTORECONF = YES

CCA_SWTPM_CONF_OPTS = \
	--disable-tests \
    --with-openssl \
    --with-tpm2 \
    --without-selinux \
    --without-cuse

define CCA_SWTPM_INSTALL_INIT_SYSV
    $(INSTALL) -m 0755 $(CCA_SWTPM_PKGDIR)/S10swtpm \
        $(TARGET_DIR)/etc/init.d/S10swtpm
endef

$(eval $(autotools-package))
