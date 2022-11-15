#include <stdio.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //include windows header
#define slowdown(x) Sleep(x)
#define TIMEOUT 1000
#endif

#ifdef __linux__
#include <unistd.h> //include POSIX standard C header
#define slowdown(x) usleep(x)
#define TIMEOUT 1000000
#endif

void displaytimer(const unsigned int seconds)
{
    int i = seconds;
	if (i < 0)
	{
		i = 10;
	}
	printf("Counting down\n");
    while (i > 0)
    {
		if (i >= 60)
		{
			printf("\r%02d:%02d\r", (i / 60), (i - 60));
		}
		if (i < 60)
		{
			printf("\r00:%02d\r", i);
		}
        slowdown(TIMEOUT);
		i--;
    }
}

int main()
{
	displaytimer(65);
	printf("Timer completed\r\n");
	return 0;
}