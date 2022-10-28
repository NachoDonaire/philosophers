# philosophers

## What is philosophers
We have a circle table and a number n of sitting philosophers around the big table. There are kind of rules in this table:

- They can be in one of these thre states: thinking, sleeping or eating.

- Each philosopher has a right fork and a left fork.

- To eat, they will pick both of the forks of their sides.

- Philosophers must eat and dont starve.

- They dont know if other philosopher is going to die and they cant talk to each other.

- All philosophers will fight for their survival.

## In terms of code
In this program, each philo is a thread. Mutex is used to make this program works.

## How to play with this program
```bash
make
```
Then you will have an executable with a few arguments:

1. [number of philosophers]
2. [time to die (ms)]
3. [time to eat (ms)]
4. [time to sleep (ms)]
5. [times every philosopher must eat(optional)]

## Examples
```bash
./philo 4 410 200 200
./philo 5 400 200 200
./philo 1 200 200 200
./philo 4 130 60 60  7
```

Enjoy!
