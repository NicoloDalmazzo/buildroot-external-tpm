################################################################################
#
# cca-realm-measurements
#
################################################################################

CCA_REALM_MEASUREMENTS_VERSION = bba1cf721e64c7a067c093cef511caf2f85a258a
CCA_REALM_MEASUREMENTS_SITE = https://github.com/veraison/cca-realm-measurements.git

CCA_REALM_MEASUREMENTS_SITE_METHOD = git
CCA_REALM_MEASUREMENTS_LICENSE = Apache-2.0 or MIT
CCA_REALM_MEASUREMENTS_LICENSE_FILES = LICENSE-APACHE LICENSE-MIT

define CCA_REALM_MEASUREMENTS_INSTALL_TARGET_CMDS
	cd $($(PKG)_SRCDIR) && \
		$(TARGET_MAKE_ENV) \
		$(TARGET_CONFIGURE_OPTS) \
		$(PKG_CARGO_ENV) \
		$(CCA_REALM_MEASUREMENTS_CARGO_ENV) \
		cargo install \
			--offline \
			--root $(TARGET_DIR)/usr/ \
			--bins \
			--path ./ \
			--force \
			--locked \
			-Z target-applies-to-host \
			$(CCA_REALM_MEASUREMENTS_CARGO_INSTALL_OPTS) && \
		install -Dt $(TARGET_DIR)/usr/share/cca-realm-measurements/configs/ configs/* && \
		install -Dt $(TARGET_DIR)/usr/share/cca-realm-measurements/ $(BR2_PACKAGE_CCA_REALM_MEASUREMENTS_CFG) && \
		install -Dt $(TARGET_DIR)/usr/bin/ scripts/gen-run-vmm.sh
endef

# Depends on OpenSSL lib, so pkg-config is used during build
CCA_REALM_MEASUREMENTS_DEPENDENCIES += host-pkgconf openssl

$(eval $(cargo-package))
