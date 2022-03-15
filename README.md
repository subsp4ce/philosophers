# philosophers

Codam [42 Network] project: the aim of this project is to create a multi-threaded program to solve the classic computer science "dining philosophers" problem. This is done using mutexes to protect shared resources while ensuring there are no data races or race conditions.
<br/><br/>

## Details

- the program takes 4 arguments with an optional 5th argument
- 1st argument: # of philosophers
- 2nd argument: time until death (if they don't start eating within this timeframe they will die)
- 3rd argument: time spent eating
- 4th argument: time spent sleeping
- 5th argument (optional): # of times they must eat (ie: they each must eat 3 times and then the simulation stops)
<br/><br/>

## Run
- `make` to compile
- examples to run:
  -  `./philo 5 800 200 200` no one should die
  -  `./philo 5 800 200 200 7` they should each eat 7 times and then the simulation stops, no one should die
  -  `./philo 1 800 200 200` philo dies because there is only one fork, needs two to eat
  -  `./philo 4 410 200 200` no one should die
  -  `./philo 4 310 200 100` a philo should die
  -  `./philo 2 60 60 60` a philo should die
<br/><br/>

## Skills
- Unix
- Rigor
- Imperative Programming
<br/><br/>

## Objectives
- Unix logic

<br/><br/>
