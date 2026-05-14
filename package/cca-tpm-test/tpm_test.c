#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libtpms/tpm_library.h>
#include <libtpms/tpm_error.h>
#include <libtpms/tpm_types.h>
#include <libtpms/tpm_memory.h>

/*
 * Simple test program for libtpms API
 * Tests basic TPM2 functionality inside a CCA Realm
 */

static void print_hex(const char *label, unsigned char *buf, size_t len)
{
    size_t i;
    printf("%s: ", label);
    for (i = 0; i < len; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

static int test_tpm_init(void)
{
    TPM_RESULT rc;

    printf("=== Test 1: TPM Initialization ===\n");

    /* Register callbacks - NULL uses defaults */
    rc = TPMLIB_RegisterCallbacks(NULL);
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: RegisterCallbacks returned 0x%08x\n", rc);
        return -1;
    }

    /* Choose TPM2 */
    rc = TPMLIB_ChooseTPMVersion(TPMLIB_TPM_VERSION_2);
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: ChooseTPMVersion returned 0x%08x\n", rc);
        return -1;
    }

    /* Initialize the TPM */
    rc = TPMLIB_MainInit();
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: MainInit returned 0x%08x\n", rc);
        return -1;
    }

    printf("PASS: TPM2 initialized successfully\n");
    return 0;
}

static int test_tpm_getcapability(void)
{
    TPM_RESULT rc;
    unsigned char *response = NULL;
    uint32_t response_len = 0;
    uint32_t response_total = 0;

    printf("\n=== Test 2: TPM2_GetCapability ===\n");

    /*
     * TPM2_GetCapability command to get TPM properties
     * Command: TPM2_CC_GetCapability = 0x0000017A
     * Capability: TPM_CAP_TPM_PROPERTIES = 0x00000006
     * Property: TPM_PT_MANUFACTURER = 0x00000105
     * PropertyCount: 1
     */
    unsigned char cmd[] = {
        0x80, 0x01,             /* TPM_ST_NO_SESSIONS */
        0x00, 0x00, 0x00, 0x16, /* commandSize = 22 */
        0x00, 0x00, 0x01, 0x7A, /* TPM2_CC_GetCapability */
        0x00, 0x00, 0x00, 0x06, /* TPM_CAP_TPM_PROPERTIES */
        0x00, 0x00, 0x01, 0x05, /* TPM_PT_MANUFACTURER */
        0x00, 0x00, 0x00, 0x01  /* propertyCount = 1 */
    };

    rc = TPMLIB_Process(&response, &response_len, &response_total,
                        cmd, sizeof(cmd));
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: Process returned 0x%08x\n", rc);
        return -1;
    }

    if (response_len < 10) {
        fprintf(stderr, "FAIL: Response too short (%u bytes)\n", response_len);
        TPM_Free(response);
        return -1;
    }

    /* Check response code at bytes 6-9 */
    uint32_t resp_code = (response[6] << 24) | (response[7] << 16) |
                         (response[8] << 8)  |  response[9];

    print_hex("Response", response, response_len);
    printf("Response code: 0x%08x\n", resp_code);

    if (resp_code != 0) {
        fprintf(stderr, "FAIL: TPM returned error 0x%08x\n", resp_code);
        TPM_Free(response);
        return -1;
    }

    /* Extract manufacturer name from response (bytes 23-26) */
    if (response_len >= 27) {
        printf("Manufacturer: %c%c%c%c\n",
               response[23], response[24],
               response[25], response[26]);
    }

    printf("PASS: GetCapability succeeded\n");
    TPM_Free(response);
    return 0;
}

static int test_tpm_getrandom(void)
{
    TPM_RESULT rc;
    unsigned char *response = NULL;
    uint32_t response_len = 0;
    uint32_t response_total = 0;

    printf("\n=== Test 3: TPM2_GetRandom ===\n");

    /*
     * TPM2_GetRandom command - request 32 bytes
     * TPM2_CC_GetRandom = 0x0000017C
     */
    unsigned char cmd[] = {
        0x80, 0x01,             /* TPM_ST_NO_SESSIONS */
        0x00, 0x00, 0x00, 0x0C, /* commandSize = 12 */
        0x00, 0x00, 0x01, 0x7C, /* TPM2_CC_GetRandom */
        0x00, 0x20              /* bytesRequested = 32 */
    };

    rc = TPMLIB_Process(&response, &response_len, &response_total,
                        cmd, sizeof(cmd));
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: Process returned 0x%08x\n", rc);
        return -1;
    }

    /* Check response code */
    uint32_t resp_code = (response[6] << 24) | (response[7] << 16) |
                         (response[8] << 8)  |  response[9];

    if (resp_code != 0) {
        fprintf(stderr, "FAIL: TPM returned error 0x%08x\n", resp_code);
        TPM_Free(response);
        return -1;
    }

    /* Random bytes start at offset 12 (after header + size field) */
    if (response_len >= 44) {
        print_hex("Random bytes", response + 12, 32);
    }

    printf("PASS: GetRandom succeeded\n");
    TPM_Free(response);
    return 0;
}

static int test_tpm_selftest(void)
{
    TPM_RESULT rc;
    unsigned char *response = NULL;
    uint32_t response_len = 0;
    uint32_t response_total = 0;

    printf("\n=== Test 4: TPM2_SelfTest ===\n");

    /*
     * TPM2_SelfTest command
     * TPM2_CC_SelfTest = 0x00000143
     * fullTest = YES (0x01)
     */
    unsigned char cmd[] = {
        0x80, 0x01,             /* TPM_ST_NO_SESSIONS */
        0x00, 0x00, 0x00, 0x0B, /* commandSize = 11 */
        0x00, 0x00, 0x01, 0x43, /* TPM2_CC_SelfTest */
        0x01                    /* fullTest = YES */
    };

    rc = TPMLIB_Process(&response, &response_len, &response_total,
                        cmd, sizeof(cmd));
    if (rc != TPM_SUCCESS) {
        fprintf(stderr, "FAIL: Process returned 0x%08x\n", rc);
        return -1;
    }

    uint32_t resp_code = (response[6] << 24) | (response[7] << 16) |
                         (response[8] << 8)  |  response[9];

    if (resp_code != 0) {
        fprintf(stderr, "FAIL: SelfTest returned error 0x%08x\n", resp_code);
        TPM_Free(response);
        return -1;
    }

    printf("PASS: SelfTest succeeded\n");
    TPM_Free(response);
    return 0;
}

int main(void)
{
    int ret = 0;

    printf("========================================\n");
    printf("  libtpms API Test - CCA Realm\n");
    printf("========================================\n\n");

    ret |= test_tpm_init();
    if (ret) {
        fprintf(stderr, "Initialization failed, aborting\n");
        goto cleanup;
    }

    ret |= test_tpm_getcapability();
    ret |= test_tpm_getrandom();
    ret |= test_tpm_selftest();

cleanup:
    TPMLIB_Terminate();

    printf("\n========================================\n");
    printf("  Result: %s\n", ret == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    printf("========================================\n");

    return ret;
}
