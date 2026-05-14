################################################################################
#
# libtpms
#
################################################################################
CCA_LIBTPMS_VERSION = v0.10.0
CCA_LIBTPMS_SITE = https://github.com/stefanberger/libtpms.git

CCA_LIBTPMS_SITE_METHOD = git
CCA_LIBTPMS_LICENSE = BSD-4-Clause
CCA_LIBTPMS_LICENSE_FILES = LICENSE

CCA_LIBTPMS_AUTORECONF = YES

CCA_LIBTPMS_DEPENDENCIES += host-pkgconf openssl

CCA_LIBTPMS_CONF_OPTS = \
    --with-openssl \
	--with-tpm2 \
    --without-tpm1

$(eval $(autotools-package))
