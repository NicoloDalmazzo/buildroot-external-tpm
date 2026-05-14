#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libtpms/tpm_library.h>
#include <libtpms/tpm_error.h>
#include <libtpms/tpm_types.h>
#include <libtpms/tpm_memory.h>
#include <libtpms/tpm_nvfilename.h>

static void print_hex(const char *label, unsigned char *buf, size_t len)
{
    size_t i;
    printf("%s: ", label);
    for (i = 0; i < len; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

int main(void)
{
    TPM_RESULT rc;
    unsigned char *response = NULL;
    uint32_t response_len = 0;
    uint32_t response_total = 0;
    int ret = 0;

    printf("========================================\n");
    printf("  libtpms API Test - CCA Realm\n");
    printf("========================================\n\n");

    printf("=== Test 1: TPM Initialization ===\n");

    /* Step 1 - set state storage directory BEFORE anything else */
    rc = TPMLIB_SetState(TPMLIB_STATE_SAVE_STATE, NULL, 0);

    printf("=== Test 1: TPM Initialization ===\n");
    /* Step 2 - choose TPM2 */
    rc = TPMLIB_ChooseTPMVersion(TPMLIB_TPM_VERSION_2);
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: ChooseTPMVersion 0x%08x\n", rc);
        return -1;
    }
    printf("=== Test 1: TPM Initialization ===\n");
    /* Step 3 - set the NV storage path */
    rc = TPMLIB_SetBufferSize(0, NULL, NULL);

    /* Step 4 - register default callbacks */
    struct libtpms_callbacks callbacks = {
        .sizeOfStruct            = sizeof(struct libtpms_callbacks),
        .tpm_nvram_init          = NULL,
        .tpm_nvram_loaddata      = NULL,
        .tpm_nvram_storedata     = NULL,
        .tpm_nvram_deletename    = NULL,
        .tpm_io_init             = NULL,
        .tpm_io_getlocality      = NULL,
        .tpm_io_getphysicalpresence = NULL,
    };

    rc = TPMLIB_RegisterCallbacks(&callbacks);
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: RegisterCallbacks 0x%08x\n", rc);
        return -1;
    }

    /* Step 5 - now safe to initialize */
    rc = TPMLIB_MainInit();
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: MainInit 0x%08x\n", rc);
        return -1;
    }
    printf("PASS: TPM2 initialized\n");

    /* Test 2 - GetRandom */
    printf("\n=== Test 2: TPM2_GetRandom ===\n");
    unsigned char cmd_random[] = {
        0x80, 0x01,
        0x00, 0x00, 0x00, 0x0C,
        0x00, 0x00, 0x01, 0x7C,
        0x00, 0x20
    };

    rc = TPMLIB_Process(&response, &response_len, &response_total,
                        cmd_random, sizeof(cmd_random));
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: GetRandom 0x%08x\n", rc);
        ret = -1;
        goto cleanup;
    }

    uint32_t resp_code = (response[6] << 24) | (response[7] << 16) |
                         (response[8] << 8)  |  response[9];
    if (resp_code != 0) {
        fprintf(stderr, "FAIL: GetRandom error 0x%08x\n", resp_code);
        ret = -1;
        goto cleanup;
    }

    if (response_len >= 44)
        print_hex("Random bytes", response + 12, 32);

    printf("PASS: GetRandom succeeded\n");
    TPM_Free(response);
    response = NULL;

    /* Test 3 - SelfTest */
    printf("\n=== Test 3: TPM2_SelfTest ===\n");
    unsigned char cmd_selftest[] = {
        0x80, 0x01,
        0x00, 0x00, 0x00, 0x0B,
        0x00, 0x00, 0x01, 0x43,
        0x01
    };

    rc = TPMLIB_Process(&response, &response_len, &response_total,
                        cmd_selftest, sizeof(cmd_selftest));
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: SelfTest 0x%08x\n", rc);
        ret = -1;
        goto cleanup;
    }

    resp_code = (response[6] << 24) | (response[7] << 16) |
                (response[8] << 8)  |  response[9];
    if (resp_code != 0) {
        fprintf(stderr, "FAIL: SelfTest error 0x%08x\n", resp_code);
        ret = -1;
        goto cleanup;
    }
    printf("PASS: SelfTest succeeded\n");

cleanup:
    TPM_Free(response);
    TPMLIB_Terminate();

    printf("\n========================================\n");
    printf("  Result: %s\n", ret == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    printf("========================================\n");

    return ret;
}
