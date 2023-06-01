#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096

void pauseAndMeasureMemory() {
    // Pause the program to allow measurement
    printf("Pausing the program. Press enter to continue...\n");
    getchar();

    // Use ps command to measure memory usage
    printf("Memory Usage:\n");
    system("ps -o pid,rss,vsz,command -p $PPID");

    // Use vmmap command to view memory image
    printf("\nMemory Image:\n");;
    system("ps -v");
}

int main() {
    // Pause the program and measure memory usage
    pauseAndMeasureMemory();

    // Memory map an empty page from the OS
    void* mappedPage = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (mappedPage == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Pause the program and measure memory usage again
    pauseAndMeasureMemory();

    // Write data into the memory-mapped page
    int* data = (int*)mappedPage;
    *data = 42;

    // Pause the program and measure memory usage once more
    pauseAndMeasureMemory();

    // Unmap the memory-mapped page
    if (munmap(mappedPage, PAGE_SIZE) == -1) {
        perror("munmap");
        return 1;
    }

    return 0;
}
