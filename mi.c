#include "./mi.h"

char **te;
int to;

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
	int idx = 0;
	if (check_op(argv[++idx]) == 0)
		++cnt;
	while (argv[idx])
	{
		int c_f = check_op(argv[idx]);
		if (c_f > 0 && check_op(argv[idx + 1]) == 0)
			++cnt;
		idx++;
	}
	return (cnt);
}

int op_addr(char **argv, int st)
{
	int cnt = 0;
	int idx = 0;
	if (check_op(argv[++idx]) == 0)
		++cnt;
	while (argv[idx])
	{
		int c_f = check_op(argv[idx]);
		if (c_f > 0 && check_op(argv[idx + 1]) == 0)
		{
			++cnt;
			idx++;
		}
		if (cnt - 1 == st)
			return (idx);
		idx++;
	}
	return (cnt);
}

void start(char **argv, int cnt)
{
	int st = 0;
	while (st < cnt)
	{
		start_fork(argv, cnt, st);
		st++;
	}
	
}

void start_fork(char **argv, int cnt, int st)
{
	int op_flag = 0;
	int idx = op_addr(argv, st);
	int idx2 = op_addr(argv, st);
	while (!check_op(argv[idx]))
		idx++;
	op_flag = check_op(argv[idx]);
	printf("idx2 is %d idx is %d last op %d cnt %d st %d Hello\n", idx2 ,idx ,op_flag, cnt, st);//check
	if (op_flag != 2)
	{
		fork_semi(argv, idx2, idx, st);
		return ;
	}
	int pid = -1;
	int fd[2];
	pid = fork();//error 처리
	pipe(fd);//error처리
	if (pid < 0)
	{
		//error처리
	}
	else if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(to);
		int e_f = 0;
		argv[idx] = NULL;
		e_f = execve(argv[idx2], &argv[idx2], te);
		if (e_f < 0)
		{
			printf("error\n");
			exit(1);
		}
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}	
}

void fork_semi(char **argv, int first_cmd, int null_space, int st)
{
	int pid = -1;
	pid = fork();
	if (pid < 0)
	{
		printf("error\n");
	}
	else if (pid == 0)
	{
		int e_f = 0;
		if (st > 0)
		{
			printf("%s\n", argv[first_cmd - 1]);
			if(check_op(argv[first_cmd - 1]) == 3)
			{
				dup2(0, to);//error처리하기
			}
		}
		close(to);
		argv[null_space] = NULL;
		e_f = execve(argv[first_cmd], &argv[first_cmd], te);
		if (e_f < 0)
		{
			printf("error\n");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void fork_pipe()
{}

int main(int argc, char *argv[], char *envp[])
{
	te = envp;
	to = dup(0);
	int cnt = cnt_op(argv);
	start(argv, cnt);

	close(to);
	return (0);
}