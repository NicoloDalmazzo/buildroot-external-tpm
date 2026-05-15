#include <stdio.h>
#include <libtpms/tpm_library.h>

int main(void)
{
    TPM_RESULT rc;

    printf("Step 1: ChooseTPMVersion\n"); fflush(stdout);
    rc = TPMLIB_ChooseTPMVersion(TPMLIB_TPM_VERSION_2);
    printf("Step 1 done: rc=0x%08x\n", rc); fflush(stdout);

    printf("Step 2: GetVersion\n"); fflush(stdout);
    const char *v = TPMLIB_GetVersion();
    printf("Step 2 done: version=%s\n", v ? v : "NULL"); fflush(stdout);

    printf("Step 3: MainInit\n"); fflush(stdout);
    rc = TPMLIB_MainInit();
    printf("Step 3 done: rc=0x%08x\n", rc); fflush(stdout);

    TPMLIB_Terminate();
    return 0;
}
