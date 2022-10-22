#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int a, b, c;

void* avg() { 
    int arr[] = {90, 81, 78, 95, 79, 72, 85};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    int sum = 0;
    for(int i = 0; i < arrSize; i++) {
        sum += arr[i];
    }
    printf("Threads are running in parallel\n");
    sleep(3);
    printf("Threads are running in parallel\n");
    sleep(3);
    printf("Average is %d\n", sum/arrSize);
    a = sum/arrSize;
}

void* min() {
    int arr[] = {90, 81, 78, 95, 79, 72, 85};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    int min_ = arr[0];
    for(int i = 0; i < arrSize; i++) {
        if (arr[i] <= min_) {
            min_ = arr[i];
        }
    }
    printf("Threads are running in parallel\n");
    sleep(3);
    printf("Threads are running in parallel\n");
    sleep(3);
    printf("Minimum is %d\n", min_);
    b = min_;
}

void* max() {
    int arr[] = {90, 81, 78, 95, 79, 72, 85};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    int max_ = arr[0];
    for(int i = 0; i < arrSize; i++) {
        if (arr[i] >= max_) {
            max_ = arr[i];
        }
    }
    printf("Threads are running in parallel\n");
    sleep(3);
    printf("Threads are running in parallel\n");
    sleep(3);
    printf("Maximum is %d\n", max_);
    c = max_;
}

int main()
{
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, &avg, NULL);
    pthread_create(&t2, NULL, &min, NULL);
    pthread_create(&t3, NULL, &max, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    sleep(3);
    printf("\nAverage is %d\n", a);
    printf("Minimum is %d\n", b);
    printf("Maximum is %d\n", c);
    return 0;
}