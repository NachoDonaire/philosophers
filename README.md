# philosophers

## What is philosophers
There is a circle table. In this table we will have n philosophers sit around the table and n forks around them. Each philosopher has a right fork and a left fork. They will be in three states: eating, sleeping and thinking. To eat, a philosopher will need his right fork and his left fork. When they finish eating they will start sleeping and when they finish this last state they will think and start eating again. 

Each philosopher represents a thread of a process. All of these program is developed in C and uses threads for each philosopher.

This program has 4 arguments (5th is not required but admited) in this arguments we will set the number of philosophers and their time to eat, sleep and their death time from their last meal.

## How to play with this program
```bash
make; ./philo [number of philos] [time to die (ms)] [time to eat (ms)] [time to sleep (ms)] ([number of meals of each philo])
```
