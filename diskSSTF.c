#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, total = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], done[n];
    printf("Enter request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        done[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (i = 0; i < n; i++) {
        int min = 1e9, idx = -1;
        for (j = 0; j < n; j++) {
            if (!done[j] && abs(head - req[j]) < min) {
                min = abs(head - req[j]);
                idx = j;
            }
        }
        done[idx] = 1;
        total += abs(head - req[idx]);
        head = req[idx];
        printf("Serviced: %d\n", head);
    }

    printf("Total head movement: %d\n", total);
    return 0;
}
