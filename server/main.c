# include "../libft/libft.h"

int main(void)
{
    __pid_t pid;

    pid = getpid();
    ft_printf("Server pid: %d\n", pid);
}