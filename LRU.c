#include <stdio.h>

void printFrames(int frames[], int frameSize) {
    for (int i = 0; i < frameSize; i++)
        (frames[i] == -1) ? printf(" - ") : printf(" %d ", frames[i]);
    printf("\n");
}

void lru(int ref[], int n, int frameSize) {
    int frames[frameSize], time[frameSize], pageFaults = 0;

    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0, lruIndex = 0;

        // Check if page already in frames
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == ref[i]) {
                found = 1;
                time[j] = i;
                break;
            }
        }

        // If not found, replace least recently used page
        if (!found) {
            for (int j = 0; j < frameSize; j++)
                if (time[j] < time[lruIndex]) lruIndex = j;

            frames[lruIndex] = ref[i];
            time[lruIndex] = i;
            pageFaults++;
        }

        printFrames(frames, frameSize);
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, frameSize;
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    int ref[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);

    printf("Enter number of frames (min 3): ");
    scanf("%d", &frameSize);

    if (frameSize < 3) {
        printf("Frame size should be at least 3.\n");
        return 1;
    }

    lru(ref, n, frameSize);
    return 0;
}
