################################################################################
#
# cca-tpm-test
#
################################################################################

CCA_TPM_TEST_VERSION = 1.0
CCA_TPM_TEST_SITE = $(CCA_TPM_TEST_PKGDIR)
CCA_TPM_TEST_SITE_METHOD = local

CCA_TPM_TEST_DEPENDENCIES = cca-libtpms

define CCA_TPM_TEST_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) \
        CC="$(TARGET_CC)" \
        CFLAGS="$(TARGET_CFLAGS)" \
        LDFLAGS="$(TARGET_LDFLAGS) -ltpms"
endef

define CCA_TPM_TEST_INSTALL_TARGET_CMDS
    $(INSTALL) -m 0755 $(@D)/tpm_test \
        $(TARGET_DIR)/usr/bin/tpm_test
endef

$(eval $(generic-package))
