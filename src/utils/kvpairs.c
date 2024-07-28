#include <utils/kvpairs.h>

int read_key_value_file(const char *filename, KeyValueArray *kvArray) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char line[512];
    kvArray->count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *equal_sign = strchr(line, '=');
        if (equal_sign) {
            *equal_sign = '\0';
            char *key = line;
            char *value = equal_sign + 1;

            /* Remove newline character from value */
            char *newline = strchr(value, '\n');
            if (newline) {
                *newline = '\0';
            }

            strncpy(kvArray->pairs[kvArray->count].key, key, 512);
            strncpy(kvArray->pairs[kvArray->count].value, value, 512);
            kvArray->pairs[kvArray->count].key[MAX_KEY_LEN - 1] = '\0';
            kvArray->pairs[kvArray->count].value[MAX_VALUE_LEN - 1] = '\0';
            kvArray->count++;
            
            if (kvArray->count >= MAX_PAIRS) {
                break;
            }
        }
    }

    fclose(file);
    return 0;
}

void print_key_value_pairs(const KeyValueArray *kvArray) {
    int i;
    for (i = 0; i < kvArray->count; i++) {
        printf("%s=%s\n", kvArray->pairs[i].key, kvArray->pairs[i].value);
    }
}
