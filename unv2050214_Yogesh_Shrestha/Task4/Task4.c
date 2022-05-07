#include <stdio.h>
#include "lodepng.h"
#include <stdlib.h>
#include <pthread.h>
unsigned char *ImageIn, *ImageOut; // inputing and outputing image initializing
unsigned int W, H, R, G, B, alpha; // Value initializing variables W is width, H is height, R is red, G is green, B is blue and alpha
// Initializing Structure
struct tArgs
{
	int start;
	int end;
};

void *blurImage(void *p)
{
	struct tArgs *Value = (struct tArgs *)p;
	int start = Value->start;
	int end = Value->end;

	for (int i = start; i < end; i++)
	{
		for (int j = 0; j < W; j++)
		{
			R = ImageIn[4 * W * i + 4 * j + 0];
			G = ImageIn[4 * W * i + 4 * j + 1];
			B = ImageIn[4 * W * i + 4 * j + 2];

			if (i == 0 && j == 0)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * i + 4 * 1 + 0] + ImageIn[4 * W * 1 + 4 * j + 0] + ImageIn[4 * W * 1 + 4 * 1 + 0]) / 4;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * i + 4 * 1 + 1] + ImageIn[4 * W * 1 + 4 * j + 1] + ImageIn[4 * W * 1 + 4 * 1 + 1]) / 4;
				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * i + 4 * 1 + 2] + ImageIn[4 * W * 1 + 4 * j + 2] + ImageIn[4 * W * 1 + 4 * 1 + 2]) / 4;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * i + 4 * 1 + 3] + ImageIn[4 * W * 1 + 4 * j + 3] + ImageIn[4 * W * 1 + 4 * 1 + 3]) / 4;
			}
			if (i == 0 && j != 0 && j != W - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * i + 4 * (j - 1) + 0] + ImageIn[4 * W * i + 4 * (j + 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * j + 0] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 0] + ImageIn[4 * W * i + 4 * (j + 1) + 0]) / 6;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * i + 4 * (j - 1) + 1] + ImageIn[4 * W * i + 4 * (j + 1) + 1] + ImageIn[4 * W * (i + 1) + 4 * j + 1] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 1] + ImageIn[4 * W * i + 4 * (j + 1) + 1]) / 6;
				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * i + 4 * (j - 1) + 2] + ImageIn[4 * W * i + 4 * (j + 1) + 2] + ImageIn[4 * W * (i + 1) + 4 * j + 2] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 2] + ImageIn[4 * W * i + 4 * (j + 1) + 2]) / 6;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * i + 4 * (j - 1) + 3] + ImageIn[4 * W * i + 4 * (j + 1) + 3] + ImageIn[4 * W * (i + 1) + 4 * j + 3] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 3] + ImageIn[4 * W * i + 4 * (j + 1) + 3]) / 6;
			}

			if (i == 0 && j == W - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * i + 4 * (j - 1) + 0] + ImageIn[4 * W * 1 + 4 * (j - 1) + 0] + ImageIn[4 * W * 1 + 4 * j + 0]) / 4;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * i + 4 * (j - 1) + 1] + ImageIn[4 * W * 1 + 4 * (j - 1) + 1] + ImageIn[4 * W * 1 + 4 * j + 1]) / 4;
				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * i + 4 * (j - 1) + 2] + ImageIn[4 * W * 1 + 4 * (j - 1) + 2] + ImageIn[4 * W * 1 + 4 * j + 2]) / 4;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * i + 4 * (j - 1) + 3] + ImageIn[4 * W * 1 + 4 * (j - 1) + 3] + ImageIn[4 * W * 1 + 4 * j + 3]) / 4;
			}

			if (i == H - 1 && j == W - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * (i - 1) + 4 * j + 0] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 0] + ImageIn[4 * W * i + 4 * (j + 1) + 0]) / 4;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * (i - 1) + 4 * j + 1] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 1] + ImageIn[4 * W * i + 4 * (j + 1) + 1]) / 4;
				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * (i - 1) + 4 * j + 2] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 2] + ImageIn[4 * W * i + 4 * (j + 1) + 2]) / 4;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * (i - 1) + 4 * j + 3] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 3] + ImageIn[4 * W * i + 4 * (j + 1) + 3]) / 4;
			}
			if (j == 0 && i != 0 && i != H - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * i + 4 * (j + 1) + 0] + ImageIn[4 * W * (i - 1) + 4 * j + 0] + ImageIn[4 * W * (i + 1) + 4 * j + 0] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 0]) / 6;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * i + 4 * (j + 1) + 1] + ImageIn[4 * W * (i - 1) + 4 * j + 1] + ImageIn[4 * W * (i + 1) + 4 * j + 1] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 1] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 1]) / 6;
				ImageOut[4 * W * i + 4 * j + 2] = (R + ImageIn[4 * W * i + 4 * (j + 1) + 2] + ImageIn[4 * W * (i - 1) + 4 * j + 2] + ImageIn[4 * W * (i + 1) + 4 * j + 2] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 2] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 2]) / 6;
				ImageOut[4 * W * i + 4 * j + 3] = (R + ImageIn[4 * W * i + 4 * (j + 1) + 3] + ImageIn[4 * W * (i - 1) + 4 * j + 3] + ImageIn[4 * W * (i + 1) + 4 * j + 3] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 3] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 3]) / 6;
			}
			if (j == W - 1 && i != 0 && i != H - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * j + 0] + ImageIn[4 * W * i + 4 * (j - 1) + 0] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 0]) / 6;
				ImageOut[4 * W * i + 4 * j + 1] = (G + R + ImageIn[4 * W * (i - 1) + 4 * j + 1] + ImageIn[4 * W * (i + 1) + 4 * j + 1] + ImageIn[4 * W * i + 4 * (j - 1) + 1] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 1] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 1]) / 6;
				ImageOut[4 * W * i + 4 * j + 2] = (B + R + ImageIn[4 * W * (i - 1) + 4 * j + 2] + ImageIn[4 * W * (i + 1) + 4 * j + 2] + ImageIn[4 * W * i + 4 * (j - 1) + 2] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 2] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 2]) / 6;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * j + 3] + ImageIn[4 * W * i + 4 * (j - 1) + 3] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 3] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 3]) / 6;
			}

			if (i == H - 1 && j == 0)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * (i - 1) + 4 * j + 0] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 0] + ImageIn[4 * W * i + 4 * (j - 1) + 0]) / 4;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * (i - 1) + 4 * j + 1] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 1] + ImageIn[4 * W * i + 4 * (j - 1) + 1]) / 4;
				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * (i - 1) + 4 * j + 2] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 2] + ImageIn[4 * W * i + 4 * (j - 1) + 2]) / 4;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * (i - 1) + 4 * j + 3] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 3] + ImageIn[4 * W * i + 4 * (j - 1) + 3]) / 4;
			}

			if (i == H - 1 && j != 0 && j != W - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * i + 4 * j + 0] + ImageIn[4 * W * i + 4 * (j + 1) + 0] + ImageIn[4 * W * (i - 1) + 4 * j + 0] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 0] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 0]) / 6;
				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * i + 4 * j + 1] + ImageIn[4 * W * i + 4 * (j + 1) + 1] + ImageIn[4 * W * (i - 1) + 4 * j + 1] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 1] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 1]) / 6;
				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * i + 4 * j + 2] + ImageIn[4 * W * i + 4 * (j + 1) + 2] + ImageIn[4 * W * (i - 1) + 4 * j + 2] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 2] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 2]) / 6;
				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * i + 4 * j + 3] + ImageIn[4 * W * i + 4 * (j + 1) + 3] + ImageIn[4 * W * (i - 1) + 4 * j + 3] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 3] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 3]) / 6;
			}

			if (i != 0 && i != H - 1 && j != 0 && j != W - 1)
			{
				ImageOut[4 * W * i + 4 * j + 0] = (R + ImageIn[4 * W * i + 4 * (j - 1) + 0] + ImageIn[4 * W * i + 4 * (j + 1) + 0] + ImageIn[4 * W * (i - 1) + 4 * j + 0] + ImageIn[4 * W * (i + 1) + 4 * j + 0] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 0] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 0] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 0]) / 9;

				ImageOut[4 * W * i + 4 * j + 1] = (G + ImageIn[4 * W * i + 4 * (j - 1) + 2] + ImageIn[4 * W * i + 4 * (j + 1) + 1] + ImageIn[4 * W * (i - 1) + 4 * j + 1] + ImageIn[4 * W * (i + 1) + 4 * j + 1] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 1] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 1] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 1] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 1]) / 9;

				ImageOut[4 * W * i + 4 * j + 2] = (B + ImageIn[4 * W * i + 4 * (j - 1) + 2] + ImageIn[4 * W * i + 4 * (j + 1) + 2] + ImageIn[4 * W * (i - 1) + 4 * j + 2] + ImageIn[4 * W * (i + 1) + 4 * j + 2] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 2] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 2] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 2] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 2]) / 9;

				ImageOut[4 * W * i + 4 * j + 3] = (alpha + ImageIn[4 * W * i + 4 * (j - 1) + 3] + ImageIn[4 * W * i + 4 * (j + 1) + 3] + ImageIn[4 * W * (i - 1) + 4 * j + 3] + ImageIn[4 * W * (i + 1) + 4 * j + 3] + ImageIn[4 * W * (i - 1) + 4 * (j - 1) + 3] + ImageIn[4 * W * (i - 1) + 4 * (j + 1) + 3] + ImageIn[4 * W * (i + 1) + 4 * (j - 1) + 3] + ImageIn[4 * W * (i + 1) + 4 * (j + 1) + 3]) / 9;
			}
		}
	}
}

void main()
{
	char in[100], out[100];
	printf("Enter the name of image: ");
	scanf("%s", in);

	printf("Enter the Output name of image: ");
	scanf("%s", out);

	unsigned int errorOne, errorTwo;
	int threadn;
	printf("Enter num of threads: ");
	scanf("%d", &threadn);
	errorOne = lodepng_decode32_file(&ImageIn, &W, &H, in); //   using lodepng to decoding the image
	errorTwo = lodepng_decode32_file(&ImageOut, &W, &H, in);
	if (errorOne)
	{
		printf("%d %s\n", errorOne, lodepng_error_text(errorOne));
	}
	pthread_t *thread_id = (pthread_t *)malloc(threadn * sizeof(pthread_t)); //  dynamically Memory allocated

	struct tArgs s[threadn];

	int sliceL[threadn], i;
	for (i = 0; i < threadn; i++)
	{
		sliceL[i] = H / threadn; // Slicing
	}
	int rem = H % threadn;
	for (i = 0; i < rem; i++)
	{
		sliceL[i]++; // Equally distributing the total nnumber of work to threads
	}
	for (i = 0; i < threadn; i++)
	{
		for (i = 0; i < threadn; i++)
		{
			if (i == 0)
			{
				s[i].start = 0;
			}
			else
			{
				s[i].start = s[i - 1].end;
			}
			s[i].end = s[i].start + sliceL[i];
		} //start and end thread
.
		for (i = 0; i < threadn; i++)
		{
			pthread_create(&thread_id[i], NULL, blurImage, &s[i]); //  thread is created
		}
		for (i = 0; i < threadn; i++)
		{
			pthread_join(thread_id[i], NULL); // created thread are joined
		}
		lodepng_encode32_file(out, ImageOut, W, H); // Encoding of the final image
	}
}
