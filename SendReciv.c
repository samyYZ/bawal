// Sender //

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE1 "/tmp/pipe1"
#define PIPE2 "/tmp/pipe2"

int main() {
    int fd1, fd2;
    char input[1000], output[1000];

  
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

 
    printf("Enter a sentence (type 'exit' to quit): ");
    fgets(input, sizeof(input), stdin);
    if (strncmp(input, "exit", 4) == 0)
        return 0;

    
    fd1 = open(PIPE1, O_WRONLY);
    write(fd1, input, strlen(input) + 1);
    close(fd1);

    
    fd2 = open(PIPE2, O_RDONLY);
    read(fd2, output, sizeof(output));
    close(fd2);

   
    printf("Output from second process:\n%s\n", output);

   // receiver //

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE1 "/tmp/pipe1"
#define PIPE2 "/tmp/pipe2"

int countWords(char *str) {
    int count = 0;
    char *token = strtok(str, " \n");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " \n");
    }
    return count;
}

int countLines(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\n')
            count++;
    return count;
}

int main() {
    int fd1, fd2;
    char input[1000], output[1000];
    int chars, words, lines;
    FILE *file;

    
    fd1 = open(PIPE1, O_RDONLY);
    read(fd1, input, sizeof(input));
    close(fd1);

    
    chars = strlen(input);
    words = countWords(input);
    lines = countLines(input);

    
    file = fopen("output.txt", "w");
    fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    fclose(file);

    
    file = fopen("output.txt", "r");
    fread(output, sizeof(char), sizeof(output), file);
    fclose(file);

   
    fd2 = open(PIPE2, O_WRONLY);
    write(fd2, output, strlen(output) + 1);
    close(fd2);

    return 0;
}

    unlink(PIPE1);
    unlink(PIPE2);
    return 0;
}
