#include "shell.h"
#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "keyboard.h"
#include "proto.h"
#include "stdio.h"

PUBLIC void init_shell()
{
    argc = 0;
    fd = -1;
}

PUBLIC void shell(char *s)
{
    //disp_str(s);
    int i;
    char buf[256];
    int size;

    split(s);
    //deint(argc);
    // for (i = 0; i < argc; ++i) {
    //     disp_str(argv[i]);
    //     disp_str("\n");
    // }

    // if (!strcmp(argv[0], "createfile")) {
    //     CreateFile_user(argv[1]);
    // } else if (!strcmp(argv[0], "deletefile")) {
    //     DeleteFile_user(argv[1]);
    // } else if (!strcmp(argv[0], "openfile")) {
    //     int mode = 0;
    //     if (!strcmp(argv[2], "w")) {
    //         mode = 6;
    //     } else if (!strcmp(argv[2], "r")) {
    //         mode = 5;
    //     } else {
    //         debug("error!");
    //     }
    //     fd = OpenFile_user(argv[1], mode);
    // } else if (!strcmp(argv[0], "writefile")) {
    //     WriteFile_user(argv[1], strlen(argv[1]), fd);
    // } else if (!strcmp(argv[0], "closefile")) {
    //     CloseFile_user(fd);
    //     fd = -1;
    // } else if (!strcmp(argv[0], "readfile")) {
    //     ReadFile_user(buf, 256, &size, fd);
    //     buf[size] = '\0';
    //     memset(buf, 256, 0);
    //     size = 0;
    //     debug(buf);
    // } else if (!strcmp(argv[0], "createdir")) {
    //     CreateDir_user(argv[1]);
    // } else if (!strcmp(argv[0], "cd")) {
    //     OpenDir_user(argv[1]);
    // } else if (!strcmp(argv[0], "deletedir")) {
    //     DeleteDir_user(argv[1]);
    // } else {
    //     debug("input error!");
    // }

    if (!strcmp(argv[0], "mkfile"))
    {
        if (argc != 2)
        {
            printf("paramater count error, need 2!\n");
            return;
        }
        //create(argv[1]);
        char str[100] = "orange1/";
        strcat(str, argv[1]);
        fd = do_vopen(str, O_CREAT);
        disp_int(fd);
        disp_str("\n");
        if (fd != -1)
            printf("create file success!\n");
        else
            printf("create file failure!\n");
    }
    else if (!strcmp(argv[0], "rmfile"))
    {
        delete (argv[1]);
    }
    else if (!strcmp(argv[0], "fopen"))
    {
        int mode = 0;

        char str[100] = "orange1/";
        strcat(str, argv[1]);
        fd = do_vopen(str, O_RDWR);
        if (fd != -1)
            printf("file is opened!\n");
        else
            printf("file is not exist!\n");
    }
    else if (!strcmp(argv[0], "fwrite"))
    {
        int len = do_vwrite(fd, argv[1], 10);
    }
    else if (!strcmp(argv[0], "fclose"))
    {
        do_vclose(fd);
        fd = -1;
    }
    else if (!strcmp(argv[0], "fread"))
    {
        // strcat(str, argv[1]);
        // char buf[20] = "abcd";
        char dist[20] = "";
        // char str[100] = "orange1/";
        // strcat(str, argv[1]);
        // fd = do_vopen(str, O_CREAT | O_RDWR);
        // int len = do_vwrite(fd, buf, 10);
        // // fd = do_vopen(str, O_CREAT | O_RDWR);
        int len = do_vread(fd, dist, 10);
        dist[len] = '\0';
        // printf("%s\n", dist);
        disp_str("\n");
        disp_str(dist);
        disp_str("\n");
    }
    else if (!strcmp(argv[0], "mkdir"))
    {
        createdir(argv[1]);
    }
    else if (!strcmp(argv[0], "cd"))
    {
        opendir(argv[1]);
    }
    else if (!strcmp(argv[0], "rmdir"))
    {
        deletedir(argv[1]);
    }
    else
    {
        disp_str("          input error!\n");
    }

    argc = 0;
}

PUBLIC void split(char *s)
{
    int len = strlen(s);
    int i;
    int pos = 0;

    for (i = 0; i < len; ++i)
    {
        if (s[i] == ' ')
        {
            strncpy(argv[argc++], s + pos, i - pos - 1);
            pos = i + 1;
        }
    }
    strncpy(argv[argc++], s + pos, len - pos - 1);
}

PUBLIC void strncpy(char *s1, char *s2, int len)
{
    int i = 0;

    for (i = 0; i <= len; ++i)
    {
        s1[i] = s2[i];
    }
    s1[len + 1] = '\0';
}

PRIVATE int strcmp(const char *s1, const char *s2)
{
    if ((s1 == 0) || (s2 == 0))
    { /* for robustness */
        return (s1 - s2);
    }

    const char *p1 = s1;
    const char *p2 = s2;

    for (; *p1 && *p2; p1++, p2++)
    {
        if (*p1 != *p2)
        {
            break;
        }
    }

    return (*p1 - *p2);
}
