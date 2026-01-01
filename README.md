# Remove iPhoto Tmp Files

Simple utility to remove iPhoto tmp files that get added when exporting a library.  These files typically start with a "._" with the file name appended to that.

> IMPORTANT: This tool uses ``` de->d_type ``` to determine if a directory or a file.  If this does not work on your system, modify the code to use ``` sys/stat.h ``:

```

#include <sys/stat.h>

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}


int isRegularFile(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISREG(statbuf.st_mode);
}

```

Feel free to create a Pull Request and I'll merge it in.

* Also, this tool allocates a total of 1K of memory for a complete file path (on the stack).  If more is needed, simply change ``` #define MAX_FILE_SIZE ```