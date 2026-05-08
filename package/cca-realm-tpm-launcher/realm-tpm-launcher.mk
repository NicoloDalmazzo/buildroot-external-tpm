################################################################################
#
# cca-realm-tpm-launcher
#
################################################################################

CCA_REALM_TPM_LAUNCHER_VERSION = 1.0
CCA_REALM_TPM_LAUNCHER_SITE =
CCA_REALM_TPM_LAUNCHER_SOURCE =

CCA_REALM_TPM_LAUNCHER_LICENSE = BSD-3-Clause

define CCA_REALM_TPM_LAUNCHER_INSTALL_TARGET_CMDS
    $(INSTALL) -d $(TARGET_DIR)/mnt/realm
    $(INSTALL) -m 0755 $(CCA_REALM_TPM_LAUNCHER_PKGDIR)/S50realm-tpm \
        $(TARGET_DIR)/etc/init.d/S50realm-tpm
    $(INSTALL) -m 0755 $(CCA_REALM_TPM_LAUNCHER_PKGDIR)/launch-realm.sh \
        $(TARGET_DIR)/usr/bin/launch-realm.sh
endef

$(eval $(generic-package))
