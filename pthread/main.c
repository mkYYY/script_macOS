#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
  int r = pthread_main_np();
  printf("This is%s a main thread\n", r ? "" : " not");
  return NULL;
}

int main(void) {
  pthread_t tid[3];
  for (int i = 0; i < 3; i++) {
    pthread_create(&tid[i], NULL, thread_func, NULL);
    pthread_join(tid[i], NULL);
  }
  (void)thread_func(NULL);

  return 0;
}

