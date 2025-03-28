#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[], int frame_count) {
    printf("[");
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\b]\n");
}

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int page_count, int frame_count) {
    int frames[MAX_FRAMES], front = 0, hit = 0, miss = 0;
    for (int i = 0; i < frame_count; i++) frames[i] = -1; 

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < page_count; i++) {
        int found = 0;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                hit++;
                break;
            }
        }
        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % frame_count;
            miss++;
        }
        printf("Page %d → ", pages[i]);
        printFrames(frames, frame_count);
    }
    printf("\nFinal Frame Content: ");
    printFrames(frames, frame_count);
    printf("Total Hits: %d\nTotal Misses: %d\n", hit, miss);
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int page_count, int frame_count) {
    int frames[MAX_FRAMES], last_used[MAX_FRAMES], hit = 0, miss = 0;
    for (int i = 0; i < frame_count; i++) frames[i] = -1;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < page_count; i++) {
        int found = 0, lru_index = -1, oldest = INT_MAX;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                hit++;
                last_used[j] = i;
                break;
            }
            if (frames[j] == -1) lru_index = j; 
        }

        if (!found) {
            if (lru_index == -1) {
                for (int j = 0; j < frame_count; j++) {
                    if (last_used[j] < oldest) {
                        oldest = last_used[j];
                        lru_index = j;
                    }
                }
            }
            frames[lru_index] = pages[i];
            last_used[lru_index] = i;
            miss++;
        }
        printf("Page %d → ", pages[i]);
        printFrames(frames, frame_count);
    }
    printf("\nFinal Frame Content: ");
    printFrames(frames, frame_count);
    printf("Total Hits: %d\nTotal Misses: %d\n", hit, miss);
}

// LFU Page Replacement Algorithm
void LFU(int pages[], int page_count, int frame_count) {
    int frames[MAX_FRAMES], freq[MAX_FRAMES], hit = 0, miss = 0;
    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }

    printf("\nLFU Page Replacement:\n");
    for (int i = 0; i < page_count; i++) {
        int found = 0, lfu_index = -1, min_freq = INT_MAX;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                hit++;
                freq[j]++;
                break;
            }
            if (frames[j] == -1) lfu_index = j;
        }

        if (!found) {
            if (lfu_index == -1) {
                for (int j = 0; j < frame_count; j++) {
                    if (freq[j] < min_freq) {
                        min_freq = freq[j];
                        lfu_index = j;
                    }
                }
            }
            frames[lfu_index] = pages[i];
            freq[lfu_index] = 1;
            miss++;
        }
        printf("Page %d → ", pages[i]);
        printFrames(frames, frame_count);
    }
    printf("\nFinal Frame Content: ");
    printFrames(frames, frame_count);
    printf("Total Hits: %d\nTotal Misses: %d\n", hit, miss);
}

int main() {
    int frame_count, page_count, pages[MAX_PAGES], choice;

    printf("Enter the number of frames: ");
    scanf("%d", &frame_count);

    printf("Enter the number of pages: ");
    scanf("%d", &page_count);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < page_count; i++) {
        scanf("%d", &pages[i]);  
    }
    while (1) {
        printf("\nChoose Page Replacement Algorithm:\n");
        printf("1. FIFO\n2. LRU\n3. LFU\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: FIFO(pages, page_count, frame_count); break;
            case 2: LRU(pages, page_count, frame_count); break;
            case 3: LFU(pages, page_count, frame_count); break;
            case 4: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}