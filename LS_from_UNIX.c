#include <getopt.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define false 0
#define true 1

void write_dir(DIR * dir, char recursive, char detailed) {
    struct dirent *entry;
    struct stat *s;
    char cur_path[1024];
    while((entry = readdir(dir)) != 0) {
        stat(entry->d_name, s);
        if (detailed) {
            if (S_ISDIR(s->st_mode))
                printf("d");
            else
                if (S_ISREG(s->st_mode))
                    printf("-");
                else
                    printf("l");
            if (s->st_mode | S_IRUSR)
                printf("r");
            else
                printf("-");
            if (s->st_mode | S_IWUSR)
                printf("w");
            else
                printf("-");
            if (s->st_mode | S_IXUSR)
                printf("x");
            else
                printf("-");
            //printf(" %s ", ctime(s->st_mtime));
            printf(" ");
        }
        printf("%s\n", entry->d_name);
    }
    if (!recursive)
        return;
    seekdir(dir, 0);
    while((entry = readdir(dir)) != 0)
        if (entry->d_name[0] != '.') {
            stat(entry->d_name, s);
            if (S_ISDIR(s->st_mode)) {
                printf("%s:\n\n", entry->d_name);
                DIR * new_dir = opendir(entry->d_name);
                chdir(entry->d_name);
                write_dir(new_dir, recursive, detailed);
                chdir("..");
                closedir(new_dir);
            }
        }
}

int main(int argc, char** argv)
{
    char recursive = false;
    char detailed = false;
    char res;
    DIR *dir = 0;
    while( ( res = getopt(argc, argv, "lr")) != -1 )
        switch(res) {
            case 'r':
                recursive = true;
                break;
            case 'l':
                detailed = true;
                break;
            case '?':
                printf("%s", optarg);

        }
    for (int i = 1; i < argc; i++)
        if (argv[i][0] != '-') {
            dir = opendir(argv[i]);
            chdir(argv[i]);
            break;
        }
    if (!dir) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        dir = opendir(cwd);
        chdir(cwd);
    }
    write_dir(dir, recursive, detailed);
    closedir(dir);
    return 0;
}
