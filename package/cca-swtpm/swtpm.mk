CCA_SWTPM_VERSION = 0.9.0
CCA_SWTPM_SITE = https://github.com/stefanberger/swtpm/archive/refs/tags/v$(CCA_SWTPM_VERSION).tar.gz
CCA_SWTPM_SOURCE = swtpm-$(CCA_SWTPM_VERSION).tar.gz

CCA_SWTPM_LICENSE = BSD-3-Clause
CCA_SWTPM_LICENSE_FILES = LICENSE

CCA_SWTPM_INSTALL_STAGING = YES

CCA_SWTPM_DEPENDENCIES = cca-libtpms openssl libseccomp libtasn1 gnutls

CCA_SWTPM_CONF_OPTS = \
    --with-openssl \
    --with-tpm2 \
    --without-selinux \
    --without-cuse

define CCA_SWTPM_INSTALL_INIT_SYSV
    $(INSTALL) -m 0755 $(CCA_SWTPM_PKGDIR)/S10swtpm \
        $(TARGET_DIR)/etc/init.d/S10swtpm
endef

$(eval $(autotools-package))
