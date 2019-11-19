#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

char * readable_form(long size){
    int x = 0;
    char * end[] = { "B", "KB", "MB", "GB" };
    while (size / 1024 != 0){
        size = size / 1024;
        x++;
    }
    return end[x];
}

char * readable_permissions(mode_t mode, char * output){
    char ans[10] = "000000000";
    if (mode & S_IRUSR) ans[0] = 'r';
    else ans[0] = '-';
    if (mode & S_IWUSR) ans[1] = 'w';
    else ans[1] = '-';
    if (mode & S_IXUSR) ans[2] = 'x';
    else ans[2] = '-';
    if (mode & S_IRGRP) ans[3] = 'r';
    else ans[3] = '-';
    if (mode & S_IWGRP) ans[4] = 'w';
    else ans[4] = '-';
    if (mode & S_IXGRP) ans[5] = 'x';
    else ans[5] = '-';
    if (mode & S_IROTH) ans[6] = 'r';
    else ans[6] = '-';
    if (mode & S_IWOTH) ans[7] = 'w';
    else ans[7] = '-';
    if (mode & S_IXOTH) ans[8] = 'x';
    else ans[8] = '-';
    strcpy(output, ans);
    return output;
}

int main(int argc, char *argv[]){

    DIR *dir;
    struct dirent *rd;
    long total_size = 0.0;
    
    printf("\n\nOpening the Directory\n =======================");
    if (argc > 1){
        dir = opendir(argv[1]);
    }
    dir = opendir(".");
    if (dir == NULL){
        printf("\nCannot Open Directory");
    }
    
    printf("\n\nSearching for Files in Directory\n =======================");
    rd = readdir (dir);
    if (rd == NULL)
        printf("\nNo Files Found in this Directory");
    while(rd != NULL){
        char * filename = rd->d_name;
        struct stat buffer;
        if (rd->d_type == DT_DIR){
            printf("\nThis is the directory: %s", rd->d_name);
        }
        printf("\nFile Type: %d", rd->d_type);
        printf("\nFound File: %s", rd->d_name);
        stat(filename, &buffer);
        total_size += buffer.st_size;
        char * file_size = readable_form(buffer.st_size);
        char size[100];
        while (buffer.st_size > 1024){
            buffer.st_size = buffer.st_size/1024;
        }
        sprintf(size, "%lld %s", buffer.st_size, file_size);
        printf("\nSize of %s: %s\n", rd->d_name, size);
        rd = readdir(dir);
    }
    if (total_size == 0.0)
        printf("\nThis Directory is Empty");
    char * readable_size = readable_form(total_size);
    char std_form[100];
    while (total_size > 1024){
        total_size = total_size/1024;
    }
    sprintf(std_form, "%ld %s", total_size, readable_size);
    printf("\n\nTotal Size of Directory: %s\n", std_form);
    
}
