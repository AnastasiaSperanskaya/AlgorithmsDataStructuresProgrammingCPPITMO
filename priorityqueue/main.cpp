#include <stdio.h>

struct PrQueue
{
	long long val;
	int str;
};

void siftdown(PrQueue * prq, int t);

void siftup(PrQueue * prq, int t);

int main()
{
	FILE *in, *out;

	in = fopen("priorityqueue.in", "r");
	out = fopen("priorityqueue.out", "w");

	PrQueue prq[1000000];

	int tail = -1;
	int str = 0;
	long long par1, par2;
	int pos;

	char command;
	command = fgetc(in);

	while (command != EOF)
	{
		switch (command)
		{
		case 'p': // push
			str++;
			fseek(in, 3, SEEK_CUR);
			fscanf(in, "%lld", &par1);
			prq[++tail].str = str;
			prq[tail].val = par1;
			siftup(&prq[0], tail);

			break;

		case 'e': // extract-min
			str++;
			fseek(in, 10, SEEK_CUR);

			if (tail > -1)
			{
				fprintf(out, "%lld\n", prq[0].val);
				prq[0] = prq[tail--];
				siftdown(&prq[0], tail);
			}

			else fprintf(out, "*\n");
			break;

		case 'd': //decrease-key
			str++;
			fseek(in, 11, SEEK_CUR);
			fscanf(in, "%d %lld", &par1, &par2);
			pos = 0;
			while (prq[pos++].str != par1);
			prq[--pos].val = par2;
			siftup(&prq[0], pos);
			break;

		default:
			break;
		}

		command = fgetc(in);
	}

}

void siftdown(PrQueue * prq, int t)
{
	int root = 0;
	struct PrQueue swap;
	int l, r, j;

	while (2 * root + 1 <= t)
	{
		l = 2 * root + 1;
		r = 2 * root + 2;
		j = (r <= t && prq[r].val < prq[l].val) ? r : l;

		if (prq[j].val < prq[root].val)
		{
			swap = prq[root];
			prq[root] = prq[j];
			prq[j] = swap;
			root = j;
		}
		else break;
	}
}

void siftup(PrQueue * prq, int t)
{
	struct PrQueue swap;

	while (t > 0 && prq[t].val < prq[(t - 1) / 2].val)
	{
		swap = prq[t];
		prq[t] = prq[(t - 1) / 2];
		prq[(t - 1) / 2] = swap;
		t = (t - 1) / 2;
	}
}