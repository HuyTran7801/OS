#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef __ns_mutex_t {
    sem_t mutex;
    sem_t barrier;
    sem_t locks;
    int num_threads;
} ns_mutex_t;

ns_mutex_t m;

void ns_mutex_init(ns_mutex_t *m, int num_threads) {
    sem_init(&m->barrier, 0, -num_threads + 1);
    sem_init(&m->mutex, 0, 1); 
}

void ns_mutex_acquire(ns_mutex_t *m) {
    sem_wait(&m->locks);
}

void ns_mutex_release(ns_mutex_t *m) {
    sem_post(&m->locks);
    sem_post(&m->barrier);
    sem_wait(&m->barrier);
    sem_wait(&m->mutex);
    for (int i = 0; i < m->num_threads; i++) sem_post(&m->barrier);
    sem_post(&m->mutex);
}


void *worker(void *arg) {
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    printf("parent: end\n");
    return 0;
}
