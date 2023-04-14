#include "../__Final__/header/strutture.h"
#include<pthread.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NUM_OF_USERS 10

utente *u;
stanza *s;

void sig_handler(int signo){}

void thread_unlock(pthread_t tid){
    pthread_kill(tid, SIGUSR1);
}

void thread_lock(){
    pause();
}

void fake_start_game(){
    utente *u1 = new_utente("admin", "admin", "admin", 11, 1, 1, pthread_self()); //fake admin
    s = new_stanza(1, "bbb", 10, u1);
    add_user_in_room(u, s);
}

void *thread_admin(){
    printf("thread_admin %ld\n", pthread_self());
    fake_start_game();
    printf("i'm gonna unlock thread: %ld\n", s->players[1]->tid); //l'unlock deve avvenire per tutti i thread presenti nella partita
    sleep(20);
    thread_unlock(s->players[1]->tid);
}

void *thread_utente(){
    signal(SIGUSR1, sig_handler); //associazione del signal hander
    u = new_utente("aaa", "aaa", "aaa", 11, 0, 1, pthread_self()); //utente loggato
    printf("thread_utente %ld\n", pthread_self());
    printf("thread_utente paused\n");
    thread_lock();
    printf("thread_utente unlocked %ld\n", pthread_self());
}

int main(){
    pthread_t tid1, tid2;
    
    if (pthread_create(&tid2, NULL, thread_utente, NULL) < 0) {
        perror("pthread_create failed");
        exit(1);
    }
    if (pthread_create(&tid1, NULL, thread_admin, NULL) < 0) {
        perror("pthread_create failed");
        exit(1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

}