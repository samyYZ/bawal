#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;

   
    printf("Enter number of elements: ");
    scanf("%d", &n);

    
    char *args[n + 2];
    args[0] = "./2Bchild";
    args[n + 1] = NULL;

    printf("Enter elements:\n");
    for (int i = 1; i <= n; i++) {
        args[i] = (char *)malloc(10);
        scanf("%s", args[i]);
    }

  
    pid_t pid = fork();

    if (pid == 0) {
     
        execve(args[0], args, NULL);
        perror("execve failed");
        exit(1);
    } 
    else if (pid > 0) {
       
        wait(NULL);
        printf("Parent: Child execution complete.\n");

     
        for (int i = 1; i <= n; i++)
            free(args[i]);
    } 
    else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

//2Bchild.c//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Child Process: Received elements:\n");

    for (int i = argc - 1 ; i > 0 ; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}
