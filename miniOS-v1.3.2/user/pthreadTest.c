#include "stdio.h"

int global = 0;

char *str2, *str3;

void pthread_test3()
{
	int i;
	str2 = malloc(10);
	*(str2 + 0) = 'M';
	*(str2 + 1) = 'a';
	*(str2 + 2) = '\0';

	while (1)
	{
		if (str3 != 0)
		{
			printf("pth3");
			(*(str2 + 1)) += 1;
			printf("%s", str3);
			printf(" ");
		}
		i = 10000;
		while (--i)
		{
		}
	}
}

void pthread_test2()
{
	int i;
	str3 = malloc(10);
	*(str3 + 0) = 'M';
	*(str3 + 1) = 'z';
	*(str3 + 2) = '\0';

	pthread(pthread_test3);
	while (1)
	{
		if (str2 != 0)
		{
			printf("pth2");
			(*(str3 + 1)) -= 1;
			printf("%s", str2);
			printf(" ");
		}

		i = 10000;
		while (--i)
		{
		}
	}
}

void pthread_test1()
{
	int i;
	//pthread(pthread_test2);
	while (1)
	{
		printf("pth1");
		printf("%d", ++global);
		printf(" ");
		i = 10000;
		while (--i)
		{
		}
	}
}

/*======================================================================*
                          Syscall Pthread Test
added by xw, 18/4/27
 *======================================================================*/

int main(int arg, char *argv[])
{
	int i = 10;
	//printf("test1:\n");
	char buf[20] = "abcd";
	int fd = open("orange1/test.txt", O_CREAT | O_RDWR);
	printf("%d     \n", fd);
	char dist[20] = "";
	int len = write(fd, buf, 10);
	printf("%d    \n", len);
	close(fd);
	fd = open("orange1/test.txt", O_RDWR);
	// fd = do_vopen(str, O_CREAT | O_RDWR);
	read(fd, dist, len);
	dist[len] = '\0';
	close(fd);
	printf("%s\n", dist);

	while (1)
	{
	};

	// pthread(pthread_test1);
	// while (1)
	// {
	// 	printf("init");
	// 	printf("%d", ++global);
	// 	printf(" ");
	// 	i = 10000;
	// 	while (--i)
	// 	{
	// 	}
	// }
	return 0;
}
