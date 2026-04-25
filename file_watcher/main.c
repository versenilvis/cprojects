#include <stdio.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <dir>\n", argv[0]);
        return -1;
    }
    int fd = inotify_init(); // file descriptor
    if (fd < 0) {
        perror("inotify_init");
        return -1;
    }

    char *watch_dir = argv[1];
    inotify_add_watch(fd, watch_dir,
                      IN_MOVED_TO | IN_CREATE | IN_DELETE | IN_DELETE_SELF |
                          IN_MOVE_SELF);
    if (fd < 0) {
        perror("inotify_add_watch");
        return -1;
    }

    if (strcmp(argv[1], ".") == 0) {
        printf("Watching current directory\n");
    } else {
        printf("Watching directory %s\n", argv[1]);
    }
    char buffer[4096];
    while (1) {
        ssize_t len = read(fd, buffer, sizeof(buffer));
        if (len < 0) {
            perror("Could not read from file");
            return -1;
        }
        for (int i = 0; i < len;) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->mask & IN_CREATE) {
                printf("File %s created\n", event->name);
            }
            if (event->mask & IN_DELETE) {
                printf("File %s deleted\n", event->name);
            }
            if (event->mask & IN_MOVED_TO) {
                printf("File %s moved to here\n", event->name);
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }

    return 0;
}
