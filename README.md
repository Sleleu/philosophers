# philosophers

![huber](https://user-images.githubusercontent.com/93100775/186047534-422cfcbc-ff69-4d12-a6f3-2c5fa03ffdfd.jpg)
>_Jean Huber, Le Dîner des philosophes, 1772-1773, Voltaire Foundation, Oxford._

## Usefull links

- https://cours.polymtl.ca/inf2610/documentation/notes/chap4.pdf
- https://www.hamajima.digital/Randal%20E.%20Bryant,%20David%20R.%20O%E2%80%99Hallaron%20-%20Computer%20Systems.%20A%20Programmer%E2%80%99s%20Perspective%20[3rd%20ed.]%20(2016,%20Pearson)%20(1).pdf

# Notions

This project is an introduction to **concurrent programming** with threads.

## Threads

A **thread** is a logical flow that runs in the context of a process. Each thread are scheduled has its own thread ID (TID), stack, stack pointer, program counter, and condition codes. With logical flows based on threads, multiple threads run in the context of a single process. Unlike proccesses, threads aren't organized in a parent-child hierarchy, they form an independant pool of peers. This means that each peer can kill any other peer without impacting any process tree. Furthermore, each peer can read and write the same shared data.

A thread has several advantages :

- **Reactivity** : The process continues to run even if some parts are blocked
- **Ressource sharing**
- **Saving memory, space and time** : A thread context is much smaller than a process context. For example, under the Solaris OS, creating a process is 30 times slower than creating a threaded process.

To manipulate threads in C programs, there are a standard interface called **Posix threads** (pthreads), who define several functions. This project only allow these functions from `<pthread.h>` :
- pthread_create
- pthread_detach
- pthread_join
- pthread_mutex_init
- pthread_mutex_destroy
- pthread_mutex_lock
- pthread_mutex_unlock

### Creating threads

We can use `pthread_create` which is prototyped as follows :

```C
int pthread_create(pthread_t *tid, pthread_attr_t *attr, func *f, void *arg);
```
This function create a thread, and run a **thread routine** function. If we want neither attributes nor arguments in the routine, we can put a NULL _attr_ and/or NULL _arg_. Otherwise we can place a single pointer, or a pointer to structure if we want multiple arguments. To pass a structure in the routine function :

```C
void* routine(void *arg)
{
  t_struct *data;
  
  data = (t_struct *)arg;
}
```
### Reaping terminated threads

```C
int pthread_join(pthread_t tid, void **thread_return);
```

This function blocks until threads TID terminates, and reaps any memory ressources held by the terminated thread.

### Detaching threads

```C
int pthread_detach(pthread_t tid);
```

At any point in time, a thread is **joinable** or **detached**. In the joinable state, a thread can be reaped or killed by his peers, and memory resources aren't freed until it's reaped. Inversely, memory resources are freed automatically by the system when it terminates with a detached state.

### Shared variables with threads

A variable is shared only if one of its instances is referenced by more than one thread. To access shared variables, it's important to implement a mechanism to protect a variable shared by several threads. This mecanisme is called **mutex** (MUTual EXclusion). A variable can lock a shared memory zone.

To dynamically initialize a mutex, we can use to function `pthread_mutex_init` :

```C
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attributs);
```

The lock/unlock system work with the functions `pthread_mutex_lock` and `pthread_mutex_unlock` :

```C
pthread_mutex_lock(phtread_mutex_t *mutex);

---
locked resources
---

pthread_mutex_unlock(phtread_mutex_t *mutex);

```
### Deadlock

Generally, a set of processes is deadlocked if each process is waiting for the release of a resource that is allocated to another process in the set.
