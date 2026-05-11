################################################################################
#
# libtpms
#
################################################################################
CCA_LIBTPMS_VERSION = 0.10.2
CCA_LIBTPMS_SITE = $(call github,stefanberger,libtpms,v$(CCA_LIBTPMS_VERSION))

CCA_LIBTPMS_LICENSE = BSD-4-Clause
CCA_LIBTPMS_LICENSE_FILES = LICENSE
CCA_LIBTPMS_INSTALL_STAGING = YES

CCA_LIBTPMS_DEPENDENCIES = openssl
CCA_LIBTPMS_AUTORECONF = YES
CCA_LIBTPMS_CONF_OPTS = \
    --with-openssl \
    --with-tpm2 \
    --without-tpm1

$(eval $(autotools-package))
