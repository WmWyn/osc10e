#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NORTH 0
#define SOUTH 1
#define NONE 2

#define MAX_CONTINUOUS_NUM 5

int south_count, north_count;
int waiting_count_south, waiting_count_north;
int continuous_count_south, continuous_count_north; // 一个方向连续的数量 
pthread_mutex_t lock;
pthread_cond_t north_can_continue, south_can_continue;
int dir;


void init() {
    pthread_mutex_init(&lock, NULL);
    south_count = north_count = 0;
    waiting_count_north = waiting_count_south = 0;
    continuous_count_north = continuous_count_south = 0;
    pthread_cond_init(&north_can_continue, NULL);
    pthread_cond_init(&south_can_continue, NULL);

    dir = NONE;
}

void *thread_north(void *param) {
    pthread_mutex_lock(&lock);
    while (dir == SOUTH || (continuous_count_north >= MAX_CONTINUOUS_NUM && waiting_count_south > 0))
    {
        waiting_count_north++;
        pthread_cond_wait(&north_can_continue, &lock);
        waiting_count_north--;
    }
    if (dir == NONE)
    {
        dir = NORTH;
        continuous_count_south = 0;
    }
    north_count++;
    continuous_count_north++;
    pthread_mutex_unlock(&lock);

    printf("go across bridge from north\n");
    usleep(100 * 1000);

    pthread_mutex_lock(&lock);
    north_count--;
    if (north_count == 0)
    {
        if (waiting_count_south > 0)
        {
            dir = SOUTH;
            continuous_count_north = 0;
            pthread_cond_broadcast(&south_can_continue);
        } else {
            dir = NONE;
        }
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *thread_south(void *param) {
    // 和thread_north一样，就是方向反过来，省略...
}

int main(int argc, char const *argv[])
{
    /* code */


    return 0;
}
