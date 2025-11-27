#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x1=1, x2=2, x3=3, x4=4, x5=5, x6=6;

int w, v, y, z, ans;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

int w_ready=0, v_ready=0, y_ready=0, z_ready=0;

void* thread_a(void* arg) {
    w = x1 * x2;
    pthread_mutex_lock(&mtx);
    w_ready = 1;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);
    printf("Thread A: w=%d\n", w);
    return NULL;
}

void* thread_b(void* arg) {
    v = x3 * x4;
    pthread_mutex_lock(&mtx);
    v_ready = 1;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);
    printf("Thread B: v=%d\n", v);
    return NULL;
}

void* thread_c(void* arg) {
    pthread_mutex_lock(&mtx);
    while(v_ready == 0) pthread_cond_wait(&cv, &mtx);
    y = v * x5;
    y_ready = 1;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);
    printf("Thread C: y=%d\n", y);
    return NULL;
}

void* thread_d(void* arg) {
    pthread_mutex_lock(&mtx);
    while(v_ready == 0) pthread_cond_wait(&cv, &mtx);
    z = v * x6;
    z_ready = 1;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);
    printf("Thread D: z=%d\n", z);
    return NULL;
}

void* thread_e(void* arg) {
    pthread_mutex_lock(&mtx);
    while(w_ready==0 || y_ready==0) pthread_cond_wait(&cv, &mtx);
    y = w * y;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);
    printf("Thread E: y=%d\n", y);
    return NULL;
}

void* thread_f(void* arg) {
    pthread_mutex_lock(&mtx);
    while(w_ready==0 || z_ready==0) pthread_cond_wait(&cv, &mtx);
    z = w * z;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);
    printf("Thread F: z=%d\n", z);
    return NULL;
}

void* thread_g(void* arg) {
    pthread_mutex_lock(&mtx);
    while(y_ready==0 || z_ready==0) pthread_cond_wait(&cv, &mtx);
    ans = y + z;
    pthread_mutex_unlock(&mtx);
    printf("Thread G: ans=%d\n", ans);
    return NULL;
}

int main() {
    pthread_t a,b,c,d,e,f,g;

    pthread_create(&a,NULL,thread_a,NULL);
    pthread_create(&b,NULL,thread_b,NULL);
    pthread_create(&c,NULL,thread_c,NULL);
    pthread_create(&d,NULL,thread_d,NULL);
    pthread_create(&e,NULL,thread_e,NULL);
    pthread_create(&f,NULL,thread_f,NULL);
    pthread_create(&g,NULL,thread_g,NULL);

    pthread_join(a,NULL);
    pthread_join(b,NULL);
    pthread_join(c,NULL);
    pthread_join(d,NULL);
    pthread_join(e,NULL);
    pthread_join(f,NULL);
    pthread_join(g,NULL);

    printf("Final ans=%d\n", ans);
    return 0;
}
