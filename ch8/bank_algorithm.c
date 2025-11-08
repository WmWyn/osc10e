#include <stddef.h>
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOUCES 4

int available[NUMBER_OF_RESOUCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOUCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOUCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOUCES];

int is_enough(int resource[], int request[]);
int is_safe();
void resource_add(int resource[], int request[]);
void resource_delete(int resource[], int request[]);

void resource_add(int resource[], int request[]) {
    for (size_t i = 0; i < NUMBER_OF_RESOUCES; i++)
    {
        resource[i] += request[i];
    }
}

void resource_delete(int resource[], int request[]) {
    for (size_t i = 0; i < NUMBER_OF_RESOUCES; i++)
    {
        resource[i] -= request[i];
    }
}

// 1=safe 0=unsafe
int is_safe() {
    int finish[NUMBER_OF_CUSTOMERS];
    int current_available[NUMBER_OF_RESOUCES];
    for (size_t i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        finish[i] = 0;
    }
    for (size_t i = 0; i < NUMBER_OF_RESOUCES; i++)
    {
        current_available[i] = available[i];
    }
    for (size_t i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        int find_one = 0;
        for (size_t j = 0; j < NUMBER_OF_CUSTOMERS; j++)
        {
            if (finish[j])
            {
                continue;
            }
            if(!is_enough(current_available, need[j])) {
                continue;
            }
            find_one = 1;
            resource_add(current_available, allocation[j]);
            finish[j] = 1;
        }
        if (!find_one)
        {
            return 0;
        }
    }
    return 1;
        
}

// 1=enough 0=not enough
int is_enough(int resource[], int request[]) {
    
    for (size_t i = 0; i < NUMBER_OF_RESOUCES; i++)
    {
        if (resource[i] < request[i])
        {
            return 0;
        }
    }
    return 1;
    
}

// 0=success -1=failed
int request_resources(int customer_num, int request[]) {
    if (customer_num < 0 || customer_num >= NUMBER_OF_CUSTOMERS)
    {
        /* code */
        exit(-1);
    }
    if(!is_enough(available, request)) {
        return -1;
    }
    if (!is_enough(need[customer_num], request))
    {
        return -1;
    }
    resource_delete(available, request);
    resource_delete(need[customer_num], request);
    resource_add(allocation[customer_num], request);
    if (!is_safe())
    {
        /* code */
        resource_add(available, request);
        resource_add(need[customer_num], request);
        resource_delete(allocation[customer_num], request);
        return -1;
    }
    return 0;
}

void release_resources(int customer_num, int release[]) {
    if (customer_num < 0 || customer_num >= NUMBER_OF_CUSTOMERS)
    {
        /* code */
        exit(-1);
    }
    if (!is_enough(allocation[customer_num], release))
    {
        /* code */
        exit(-1);
    }
    resource_add(available, release);
    resource_add(need[customer_num], release);
    resource_delete(allocation[customer_num], release);
}



