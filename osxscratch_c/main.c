//
//  main.c
//  osxscratch_c
//
//  Created by Dexter Haslem on 3/28/21.
//

#include <stdio.h>

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>


#define NUM_THREADS (12)
#define THREAD_MEM_MB (2000)

static void * pfn(void * args) {
    (void)args;
    volatile uint64_t v = 1;

    char *mp = malloc(1024 * 1024 * THREAD_MEM_MB);
    for (uint64_t i = 0; i < UINT64_MAX; ++i)
    {
        v = i;
        mp[i] = v;
    }
    
//    for (uint64_t i = 0; i < UINT64_MAX; ++i)
//    {
//        v += i;
//    }
    
    printf("thread done: %"PRIu64" \n", v);
   free(mp);
    return NULL;
}

int main(int argc, const char * argv[static argc+1]) {
    printf("Hello, World!\n");
    
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i){
        pthread_create(&threads[i], NULL, &pfn, NULL);
    }
    
    for (int i = 0; i < NUM_THREADS; ++i){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
