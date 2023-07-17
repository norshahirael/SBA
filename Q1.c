#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILD 3

void handle_intrppt(int signal)
{
    printf("Received an interrupt signal in children process with PID %d\n", getpid());
    exit(0);
}

int main()
{
    pid_t child_pids[NUM_CHILD];
    int pipes[NUM_CHILD][2];
    int i;

    for (i = 0; i < NUM_CHILD; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    for (i = 0; i < NUM_CHILD; i++) {
        child_pids[i] = fork();
        if (child_pids[i] == -1) {
            perror("fork");
            exit(1);
        }

        if (child_pids[i] == 0) {
  
            close(pipes[i][1]); 
            signal(SIGINT, handle_intrppt); 
            char message[256];

           
            ssize_t bytes_read = read(pipes[i][0], message, sizeof(message));
            if (bytes_read == -1) {
                perror("read");
                exit(1);
            }

            printf("Children process with PID %d received message: %s\n", getpid(), message);

            close(pipes[i][0]);
            exit(0);
        }
    }

    // Parent process
    for (i = 0; i < NUM_CHILD; i++) {
        close(pipes[i][0]);

        char message[256];
        sprintf(message, "Message from parent to children %d", i+1);
        ssize_t bytes_written = write(pipes[i][1], message, sizeof(message));
        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }

        close(pipes[i][1]); 
    }

   
    for (i = 0; i < NUM_CHILD; i++) {
        waitpid(child_pids[i], NULL, 0);
    }

    printf("Parent process exiting.\n");

    return 0;
}
