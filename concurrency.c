#include <stdio.h>
#include <pthread.h>

int numOfPeopleInRoom = 0;
int lightSwitch = 0;

pthread_mutex_t lock;
pthread_cond_t roomEmpty;
pthread_cond_t firstPerson;
pthread_cond_t lastPerson;

// Function to turn on the light
void switchOn() {
    lightSwitch = 1;
}

// Function to turn off the light
void switchOff() {
    lightSwitch = 0;
}

// Thread function for a person entering the room
void* personEnter(void* arg) {
    pthread_mutex_lock(&lock);

    // Wait until the room is empty to ensure correct behavior of the first person
    while (numOfPeopleInRoom > 0) {
        pthread_cond_wait(&roomEmpty, &lock);
    }

    numOfPeopleInRoom++;

    // If the current person is the first to enter, turn on the light
    if (numOfPeopleInRoom == 1) {
        switchOn();
        pthread_cond_signal(&firstPerson); // Notify waiting thread that the first person has entered
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}

// Thread function for a person exiting the room
void* personExit(void* arg) {
    pthread_mutex_lock(&lock);

    numOfPeopleInRoom--;

    // If the current person is the last to leave, turn off the light
    if (numOfPeopleInRoom == 0) {
        switchOff();
        pthread_cond_signal(&lastPerson); // Notify waiting thread that the last person has exited
    }

    // If there are still people in the room, wait until the last person exits
    if (numOfPeopleInRoom > 0) {
        pthread_cond_wait(&lastPerson, &lock);
    }

    // If the room is empty now, notify waiting threads
    if (numOfPeopleInRoom == 0) {
        pthread_cond_broadcast(&roomEmpty);
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    // Initialize mutex and condition variables
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&roomEmpty, NULL);
    pthread_cond_init(&firstPerson, NULL);
    pthread_cond_init(&lastPerson, NULL);

    // Create threads representing people entering and exiting the room
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, personEnter, NULL);
    pthread_create(&thread2, NULL, personEnter, NULL);
    pthread_create(&thread3, NULL, personExit, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Cleanup mutex and condition variables
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&roomEmpty);
    pthread_cond_destroy(&firstPerson);
    pthread_cond_destroy(&lastPerson);

    return 0;
}
