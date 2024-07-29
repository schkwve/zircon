#include <utils/kvpairs.h>
#include <utils/zerr.h>

int read_key_value_file(const char *filename, KeyValueArray *kvArray,const struct zircon_config *config) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        /* If file doesnt exist create and populate it */
        file = fopen(filename, "w");
        if (file == NULL) {
            zerr("Error creating file: \n");
            return -1;
        }

        /* Populate the file */
        if (config->nickname) fprintf(file, "nickname=%s\n", config->nickname);
        if (config->username) fprintf(file, "username=%s\n", config->username);
        if (config->fullname) fprintf(file, "name=%s\n", config->fullname);

        fclose(file);

        /* Reopen to read */
        file = fopen(filename, "r");
        if (file == NULL) {
            zerr("Error reopening file: ");
            return -1;
        }
    }

    char line[513];
    kvArray->count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *equal_sign = strchr(line, '=');
        if (equal_sign) {
            *equal_sign = '\0';
            char *key = line;
            char *value = equal_sign + 1;

            /* Remove newline */
            char *newline = strchr(value, '\n');
            if (newline) {
                *newline = '\0';
            }

            /* Check if it fits */
            if (strlen(key) >= MAX_KEY_LEN) {
                key[MAX_KEY_LEN - 1] = '\0';
            }
            if (strlen(value) >= MAX_VALUE_LEN) {
                value[MAX_VALUE_LEN - 1] = '\0';
            }

            /* Copy everything */
            strncpy(kvArray->pairs[kvArray->count].key, key, MAX_KEY_LEN);
            strncpy(kvArray->pairs[kvArray->count].value, value, MAX_VALUE_LEN);
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

char* get_value(KeyValueArray *kvArray, const char *key) {
   int i;  /* ANSI C for loops */
    for (i = 0; i < kvArray->count; i++) {
        if (strcmp(kvArray->pairs[i].key, key) == 0) {
            return kvArray->pairs[i].value;
        }
    }
    return NULL; /* Key not found */
}