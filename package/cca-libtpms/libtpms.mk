################################################################################
#
# libtpms
#
################################################################################
CCA_LIBTPMS_VERSION = 0.10.0
CCA_LIBTPMS_SITE = https://github.com/stefanberger/libtpms/archive/refs/tags/v$(CCA_LIBTPMS_VERSION).tar.gz
CCA_LIBTPMS_SOURCE = libtpms-$(CCA_LIBTPMS_VERSION).tar.gz

CCA_LIBTPMS_LICENSE = BSD-3-Clause
CCA_LIBTPMS_LICENSE_FILES = LICENSE

CCA_LIBTPMS_INSTALL_STAGING = YES

CCA_LIBTPMS_DEPENDENCIES = openssl

CCA_LIBTPMS_CONF_OPTS = \
    --with-openssl \
    --with-tpm2 \
    --without-tpm1

$(eval $(autotools-package))
