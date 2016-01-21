    #include<sys/types.h>
    #include<sys/wait.h>
    #include<unistd.h>
    #include<stdio.h>
    #include<stdlib.h>

    int main()  
    {
        pid_t pc, pr;
        //创建子进程
        pc = fork();
        if(pc < 0)
        {
            printf("error fork!\n");
        }
        else if(pc == 0)
        {
            printf("start child process\n");
            for(int i = 0;i<6;i++){
                sleep(1);
                //exit(0);
            }
            printf("child process: pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(), getpgid(getpid()));
        }
        else
        {
            printf("before waiting\n");
            do{
                //循环测试是否子进程退出
                pr = waitpid(pc, NULL, WNOHANG);//非阻塞
                //pr =waitpid(pc, NULL, 0);     //阻塞
                if(pr == 0)
                {
                    printf("the child process has not exited!\n");
                    sleep(1);
                }
            }while(pr == 0);

            printf("after waiting\n");
            if(pr == pc)
            {
                printf("child process exited.");
            }
            else
            {
                printf("some error occured.\n");
            }

            printf("parent process: pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(), getpgid(getpid()));

        }
    }