#include <dirent.h>
#include <stdio.h>
#include <glib.h>

gboolean extension_matches(char *filename, gchar **extensions) {
    char *extension = strrchr(filename, '.') + 1;

    for (int i = 0; extensions[i]; i++) {
        if (strcmp(extension, extensions[i]) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

void count_lines(gchar *dir, gchar **extensions) {
    
}

int main(int argc, char **argv) {
    static gboolean display_version = FALSE;
    static gchar *count_dir = NULL;
    static gchar **count_extensions = NULL;
    GError *error = NULL;
    GOptionContext *option_context;
    static GOptionEntry entries[] = {
        { "version", 'V', 0, G_OPTION_ARG_NONE, &display_version,
          "Display version information", NULL },
        { "directory", 'd', 0, G_OPTION_ARG_FILENAME, &count_dir,
          "Directory for counting", "<directory>" },
        { "extension", 'e', 0, G_OPTION_ARG_STRING_ARRAY, &count_extensions,
          "Extension of files to count", "<string>" },

        { NULL, 0, 0, 0, NULL, NULL, NULL }
    };
    
    option_context = g_option_context_new("- Code counter");
    g_option_context_add_main_entries(option_context, entries, NULL);

    if (!g_option_context_parse(option_context, &argc, &argv, &error)) {
        g_print("%s\n\n", error->message);
        return EXIT_SUCCESS;
    }
    g_option_context_free(option_context);

    if (display_version) {
        printf("Code Counter %s\n", VERSION);
        return EXIT_SUCCESS;
    }

    if (count_dir) {
        count_lines(count_dir, count_extensions);
    }

    g_strfreev(count_extensions);

    if (count_extensions) {
        for (int i = 0; count_extensions[i]; i++) {
            printf("%s\n", count_extensions[i]);
        }
    }

    DIR *d;
    struct dirent *dir;

    d = opendir(".");

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            //printf("%s\n", dir->d_name);

        }
        closedir(d);
    }

    return 0;
}
