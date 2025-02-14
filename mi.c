#include "./mi.h"

char **te;

int slen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len);
}

int check_op(char *op)
{
	if (op == NULL)
		return (-1);
	if (!strncmp("|", op, 1) && slen(op) == 1)
		return (2);
	else if (!strncmp(";", op, 1) && slen(op) == 1)
		return (3);
	return (0);
}

int cnt_op(char **argv)
{
	int cnt = 0;
	int idx = 1;
	while (check_op(argv[idx]))
		idx++;
	while (argv[idx])
	{
		while (check_op(argv[idx]))
		{
			if (check_op(argv[idx]) == -1)
				break;
			if (!check_op(argv[idx + 1]))
			{
				if (check_op(argv[idx + 1]) == -1)
					break;
				cnt++;
				break;
			}
			idx++;
		}
		if (check_op(argv[idx]) == -1)
			break;
		idx++;
	}
	return (cnt);
}

int op_addr(char **argv, int st)
{
	int cnt = 0;
	int idx = 1;
	while (check_op(argv[idx]))
		idx++;
	while (argv[idx])
	{
		while (check_op(argv[idx]))
		{
			if (check_op(argv[idx]) == -1)
			break;
			if (!check_op(argv[idx + 1]))
			{
				if (check_op(argv[idx + 1]) == -1)
				break;
				cnt++;
				break;
			}
			idx++;
		}
		if (check_op(argv[idx]) == -1)
		break;
		idx++;
		if (cnt == st)
			return (idx);
	}
	return (0);
}

void start(char **argv, int cnt)
{
	int st = 0;
	while (st <= cnt)
	{
		start_fork(argv, cnt, st);
		st++;
	}
	
}

void start_fork(char **argv, int cnt, int st)
{
	int op_flag = 0;
	int idx = op_addr(argv, st);
	while (!check_op(argv[idx]))
		idx++;
	op_flag = check_op(argv[idx]);
	printf("%d cnt %d st %d Hello\n", op_flag, cnt, st);//check
	
}

int main(int argc, char *argv[], char *envp[])
{
	te = envp;
	int cnt = cnt_op(argv);
	start(argv, cnt);
	return (0);
}