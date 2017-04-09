

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define MAX_SIZE 100000
#define NUM_TO_PRINT 50

typedef struct wordFrequency {
    char *word;
    int count;
} WordFrequency;

void print_data(void *data, void *user_data) {
    int count = *(int *)user_data;
    if (count > NUM_TO_PRINT) {
        return;
    }
    *(int *)user_data = count + 1;
    WordFrequency *word_freq = (WordFrequency *)data;
    printf("%s -- %d times\n", word_freq->word, word_freq->count);
}

int sort_word_freq(const void *wordFreq1, const void *wordFreq2) {
    WordFrequency *w1 = *(WordFrequency **)wordFreq1;
    WordFrequency *w2 = *(WordFrequency **)wordFreq2;
    return w2->count - w1->count;
}

void add_word_freq_to_array(void *word, void *frequency, void *array) {
    WordFrequency *wordFreq = malloc(sizeof(WordFrequency));
    wordFreq->word = (char *)word;
    wordFreq->count = *(int *)frequency;
    g_ptr_array_add((GPtrArray *)array, wordFreq);
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Please enter file to read\n");
        return -1;
    }

    char *fname = argv[1];
    gchar **contents = malloc(MAX_SIZE);
    g_file_get_contents(fname,
        contents,
        NULL,
        NULL);

    gchar *file_contents = *contents;

    // Remove punctuation
    g_strdelimit(file_contents, ".,'\":;)(][", ' ');

    // Split on whitespace
    gchar **words = g_strsplit_set(file_contents, "\n\t\r ", -1);

    GHashTable *words_to_counts = g_hash_table_new(g_str_hash, g_str_equal);
    int index = 0;
    char *current_word = words[index];

    while (current_word != NULL) {
        if (current_word[0] != '\0') {
            int *val = (int *)g_hash_table_lookup(words_to_counts, current_word);
            int *result = malloc(sizeof(int));
            if (val == NULL) {
                *result = 1;
            } else {
                *result = *val + 1;
            }
            g_hash_table_insert(words_to_counts, current_word, result);
        }

        index++;
        current_word = words[index];
    }

    GPtrArray *word_freq_arr = g_ptr_array_new();

    g_hash_table_foreach(words_to_counts,
        add_word_freq_to_array,
        word_freq_arr);

    g_ptr_array_sort(word_freq_arr, sort_word_freq);

    int *count = malloc(sizeof(int));
    *count = 0;
    g_ptr_array_foreach(word_freq_arr, print_data, count);
}
