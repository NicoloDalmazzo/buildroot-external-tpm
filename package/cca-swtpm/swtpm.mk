CCA_SWTPM_VERSION = v0.10.1
CCA_SWTPM_SITE = https://github.com/stefanberger/swtpm.git

CCA_SWTPM_SITE_METHOD = git
CCA_SWTPM_LICENSE = BSD-4-Clause
CCA_SWTPM_LICENSE_FILES = LICENSE

CCA_SWTPM_DEPENDENCIES += cca-libtpms

CCA_SWTPM_AUTORECONF = YES

CCA_SWTPM_CONF_OPTS = \
    --with-openssl \
    --with-tpm2 \
    --without-selinux \
    --without-cuse

$(eval $(autotools-package))
