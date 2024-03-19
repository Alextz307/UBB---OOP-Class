#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>

const int ALPHABET_SIZE = 26;

void read_distribution(float distribution[]) {
    FILE *file = fopen("distribution.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening distribution file.\n");
        return;
    }

    for (int ch = 0; ch < ALPHABET_SIZE; ++ch) {
        fscanf(file, "%f", &distribution[ch]);
    }

    fclose(file);
}

void compute_normalized_frequency(const char *text, float normalized_frequency[]) {
    int frequency[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (const char *ptr = text; *ptr != '\0'; ++ptr) {
        if (isalpha(*ptr)) {
            char ch = tolower(*ptr);
            frequency[ch - 'a'] += 1;
            total_letters += 1;
        }
    }

    for (int ch = 0; ch < ALPHABET_SIZE; ++ch) {
        normalized_frequency[ch] = (float)frequency[ch] / total_letters;
    }
}

float compute_CHI_square_distance(const float hist1[], const float hist2[]) {
    float chi_square = 0;

    for (int ch = 0; ch < ALPHABET_SIZE; ++ch) {
        if (hist2[ch] != 0) {
            float diff = hist1[ch] - hist2[ch];
            chi_square += (diff * diff) / hist2[ch];
        }
    }

    return chi_square;
}

char shift_ch(char ch, int shift) {
    int shifted_index = (tolower(ch) - 'a' + shift + ALPHABET_SIZE) % ALPHABET_SIZE;
    char shifted_ch = (isupper(ch) ? 'A' : 'a') + shifted_index;

    return shifted_ch;
}

char* encrypt_text(const char *text, const int shift) {
    char *encrypted_text = (char *)malloc((strlen(text) + 1) * sizeof(char));

    for (const char *ptr = text; *ptr != '\0'; ++ptr) {
        if (isalpha(*ptr)) {
            char encrypted_ch = shift_ch(*ptr, shift);
            strncat(encrypted_text, &encrypted_ch, 1);
        } else {
            strncat(encrypted_text, ptr, 1);
        }
    }

    return encrypted_text;
}

char* decrypt_text(const char *encrypted_text, const float normal_distribution[]) {
    float encrypted_hist[ALPHABET_SIZE];
    compute_normalized_frequency(encrypted_text, encrypted_hist);

    float min_chi_square = FLT_MAX;
    char *decrypted_text = (char *)malloc((strlen(encrypted_text) + 1) * sizeof(char));

    for (int shift = 0; shift < ALPHABET_SIZE; ++shift) {
        char *decrypted_candidate = (char *)malloc((strlen(encrypted_text) + 1) * sizeof(char));

        for (const char *ptr = encrypted_text; *ptr != '\0'; ++ptr) {
            if (isalpha(*ptr)) {
                char decrypted_ch = shift_ch(*ptr, -shift);
                strncat(decrypted_candidate, &decrypted_ch, 1);
            } else {
                strncat(decrypted_candidate, ptr, 1);
            }
        }

        float decrypted_hist[ALPHABET_SIZE];
        compute_normalized_frequency(decrypted_candidate, decrypted_hist);

        const float chi_square = compute_CHI_square_distance(decrypted_hist, normal_distribution);

        if (chi_square < min_chi_square) {
            min_chi_square = chi_square;
            strcpy(decrypted_text, decrypted_candidate);
        }

        free(decrypted_candidate);
    }

    return decrypted_text;
}

void print_menu() {
    printf("1. Encrypt an English text using Caesar Cipher\n");
    printf("2. Decrypt a text (which was encrypted using Caesar Cipher)\n");
    printf("3. Stop\n");
    printf("\n");
}

char* read_text() {
    char *text = NULL;
    char curr_ch;
    int length = 0;

    printf("Enter the text (press 'Enter' when done):\n");

    while ((curr_ch = getchar()) != '\n') {
        text = (char *)realloc(text, (length + 1) * sizeof(char));
        text[length++] = curr_ch;
    }

    text = (char *)realloc(text, (length + 1) * sizeof(char));
    text[length] = '\0';

    return text;
}

int main() {
    float normal_distribution[ALPHABET_SIZE];
    read_distribution(normal_distribution);

    printf("Welcome to the Caesar Cipher tool!\n\n");

    while (1) {
        print_menu();

        int option;
        scanf("%d", &option);
        getchar();

        if (option == 1) {
            char *text = read_text();
            int shift;

            printf("Enter the shift: ");
            scanf("%d", &shift);

            char *encrypted_text = encrypt_text(text, shift);

            printf("\nEncrypted text:\n");
            printf("%s\n\n", encrypted_text);

            free(encrypted_text);
        } else if (option == 2) {
            char *encrypted_text = read_text();
            char *decrypted_text = decrypt_text(encrypted_text, normal_distribution);

            printf("\nDecrypted text:\n");
            printf("%s\n\n", decrypted_text);

            free(encrypted_text);
            free(decrypted_text);
        } else if (option == 3) {
            break;
        } else {
            fprintf(stderr, "\nYour choice is not valid!\n\n");
        }
    }

    return 0;
}
