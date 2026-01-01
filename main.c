/*
 * main.c
 *
 *  Created on: Jan 1, 2026
 *  Author: mark2v
 */
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILE_SIZE 1024

void delete_tmp_files(char *path);

int main() {

	char* root_dir =
			"/media/mark2v/SanDisk/PhototsLib1";
//			"/media/mark2v/SanDisk/PhotosLibrary2";
//			"/media/mark2v/SanDisk/iphotoLibrary-to-2012";
//			"/media/mark2v/SanDisk/iPhotoLarge";
//			"/media/mark2v/SanDisk/iPhotoCurrentAndSmall";
//			"/media/mark2v/SanDisk/iphotoLibrary-to-2012/Alamogordo, June 13, 2012";
//			"/media/mark2v/SanDisk/iphotoLibrary-to-2012";
//			"/home/mark2v/Downloads/pic_test";

	delete_tmp_files(root_dir);

	return 0;
}

void delete_tmp_files(char *path) {

	struct dirent *de;
	DIR *dr = opendir(path);
	if (dr == NULL) {
		fprintf(stderr, "Unable to open root dir %s\n", path);
		return;
	}

	while ((de = readdir(dr))) {

		// Make sure this is supported on this OS.
		if (de->d_type == DT_UNKNOWN) {
			fprintf(stderr, "dirent.d_type is not supported!");
			return;
		}

		// Don't count . and ..
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
			continue;
		}

		// Construct the full file/dir name.
		char full_path[MAX_FILE_SIZE];
		snprintf(full_path, 1024, "%s/%s", path, de->d_name);

		if (!strncmp(de->d_name, "._", 2)) {
			fprintf(stderr, "Delete file: %s\n", full_path);

			if (remove(full_path) != 0) {
				fprintf(stderr, "Unable top delete file %s\n", full_path);
			}
		}
		else {
			printf("DONT delete %s\n", full_path);
		}

		// Check if a directory and traverse that.
		if (de->d_type == DT_DIR) {
			delete_tmp_files(full_path);
		}
	}
}

