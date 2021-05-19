![Passed 100/100](https://img.shields.io/badge/PASSED-100%2F100-green?style=for-the-badge&logo=42)
[![Norminette v3](https://img.shields.io/badge/norminette-v3-blue?style=for-the-badge&logo=42)](https://github.com/42School/norminette) 
# Philosophers
In this project, you will learn the basics of threading a process and how to work on the same memory space. You will learn how to make threads. You will discover the mutex, semaphore and shared memory.

## Content
The project consists of 3 programs written in `.c`. Each of them have their own `.h` file and a `Makefile` to compile it.

## How to test it?
You can start by cloning this repository:
```bash
git clone https://github.com/xpartano/philosophers philosophers && cd philosophers
```
After this we will see 3 folders containing  all the needed code fore each program.
We will test each program first by entering it's folder. In this case we will be testing the `philo_one` program:
```bash
cd philo_one
make
```
After compiling our program, we will execute it as follows:
```bash
./philo_one [num_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [limit_eat_times]
```
* **number_of_philosophers:** is the number of philosophers and also the number of forks. It must not be less than 2.
* **time_to_die:** is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies. It must not be less than 60.
* **time_to_eat:** is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks. It must not be less than 60.
* **time_to_sleep:** is in milliseconds and is the time the philosopher will spend sleeping. It must not be less than 60.
* **number_of_times_each_philosopher_must_eat:** argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher. It must not be less than 1.

Using this format we can test our three programs.
