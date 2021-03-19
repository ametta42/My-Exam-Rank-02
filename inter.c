#include <unistd.h>

int main(int argc, char **argv)
{
	int used[255];
	int let = 0;

	if (argc == 3)
	{
		argc--;
		while (let < 255)
		{
			used[let] = 0;
			let++;
		}
		while (argc > 0)
		{
			let = 0;
			while (argv[argc][let])
			{
				if (argc == 2 && used[(unsigned char)argv[argc][let]] == 0)
					used[(unsigned char)argv[argc][let]] = 1;
				else if (argc == 1 && used[(unsigned char)argv[argc][let]] == 1)
				{
					write(1, &argv[argc][let], 1);
					used[(unsigned char)argv[argc][let]] = 2;
				}
				let++;
			}
			argc--;
		}
	}
	write(1, "\n", 1);
	return (0);
}
