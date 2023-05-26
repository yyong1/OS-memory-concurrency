#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096

void print_memory_usage() {
    // Read and print memory usage from /proc/<pid>/status file
    char stat_file_path[256];
    sprintf(stat_file_path, "/proc/%d/status", getpid());

    FILE* stat_file = fopen(stat_file_path, "r");
    if (stat_file == NULL) {
        perror("Failed to open stat file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), stat_file) != NULL) {
        if (strstr(line, "VmSize") || strstr(line, "VmRSS")) {
            printf("%s", line);
        }
    }

    fclose(stat_file);
}

int main() {
    printf("Memory usage before mmap:\n");
    print_memory_usage();

    // Memory map an empty page
    void* mapped_page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mapped_page == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Memory usage after mmap:\n");
    print_memory_usage();

    // Write data into the memory mapped page
    int* data = (int*)mapped_page;
    *data = 123;

    printf("Memory usage after writing to the memory mapped page:\n");
    print_memory_usage();

    // Unmap the memory
    if (munmap(mapped_page, PAGE_SIZE) == -1) {
        perror("munmap failed");
        return 1;
    }

    printf("Memory usage after munmap:\n");
    print_memory_usage();

    return 0;
}
