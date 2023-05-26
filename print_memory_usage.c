#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define PAGE_SIZE 4096

void print_memory_usage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) != 0) {
        perror("Failed to get resource usage");
        return;
    }

    printf("Memory usage:\n");
    printf("Virtual Memory Size (VSZ): %ld KB\n", usage.ru_maxrss);
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
