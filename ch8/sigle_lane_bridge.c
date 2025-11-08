#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

#define NORTH 0
#define SOUTH 1
#define NONE 2

// 

int south_count, north_count;
pthread_mutex_t lock;
pthread_cond_t direction_change;
int dir ;

void init() {
    pthread_mutex_init(&lock, NULL);
    south_count = 0;
    north_count = 0;
    pthread_cond_init(&direction_change, NULL);
    dir = NONE;
}

void *thread_north(void *param) {
    pthread_mutex_lock(&lock);
    while (dir == SOUTH)
    {
        pthread_cond_wait(&direction_change, &lock);
    }
    if (dir == NONE)
    {
        dir = NORTH;
    }
    north_count++;
    pthread_mutex_unlock(&lock);

    printf("go across bridge from north\n");
    usleep(100 * 1000);


    pthread_mutex_lock(&lock);
    north_count--;
    if (north_count == 0)
    {
        dir = NONE;
        pthread_cond_broadcast(&direction_change);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *thread_south(void *param) {
    pthread_mutex_lock(&lock);
    while (dir == NORTH)
    {
        pthread_cond_wait(&direction_change, &lock);
    }
    if (dir == NONE)
    {
        dir = SOUTH;
    }
    south_count++;
    pthread_mutex_unlock(&lock);

    printf("go across bridge from south\n");
    usleep(100 * 1000);

    pthread_mutex_lock(&lock);
    south_count--;
    if (south_count == 0)
    {
        dir = NONE;
        pthread_cond_broadcast(&direction_change);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char const *argv[])
{
    /* code */


    return 0;
}
