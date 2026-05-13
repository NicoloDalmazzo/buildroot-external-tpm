################################################################################
#
# CCA Workload Attestation PoC
#
################################################################################

CCA_WORKLOAD_ATTESTATION_VERSION = clo/main
CCA_WORKLOAD_ATTESTATION_SITE = https://gitlab.com/Linaro/cca-public/cca-demos/cca-workload-attestation-poc.git
CCA_WORKLOAD_ATTESTATION_SITE_METHOD = git
CCA_WORKLOAD_ATTESTATION_LICENSE = BSD 3-Clause
CCA_WORKLOAD_ATTESTATION_LICENSE_FILES = LICENSE

CCA_WORKLOAD_ATTESTATION_GOMOD = gitlab.com/Linaro/cca-public/cca-demos/cca-workload-attestation-poc

# Uncomment the next two lines for a statically linked application
#CCA_WORKLOAD_ATTESTATION_GO_ENV = CGO_ENABLED=0 GOARCH=arm64 GOOS=linux
#CCA_WORKLOAD_ATTESTATION_LDFLAGS = -s -w
#CCA_WORKLOAD_ATTESTATION_GO_ENV = GOFLAGS=-mod=mod

$(eval $(golang-package))
