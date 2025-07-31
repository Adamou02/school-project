# CookiePlayTime


This program allows you to execute a game in which you control a character who moves on a 2D map and who tries to reach its end point.	
On his way, the character will be able to meet obstacles that make him lose energy and bonuses that make him win energy. 
If the player runs out of energy, the game is lost.
The character can move from top to bottom, with z/x keys, from right to left, with q/d, but also diagonally with a/e/w/c.
The player also has the ability to make up to 6 backward moves to cancel the last one.
It is possible to resume a game in progress after leaving the game, if it has been saved. It is also possible to review an old game.


### Prerequisites

OS Linux only.
Make sure you have installed ```gcc```, ```make``` and ```git```

### Installing

Clone this repository:

```
git clone https://github.com/clementcst/projet_cookie_ing1
```
Move to the cloned directory :

```
cd projet_cookie_ing1
```
End with an example of getting some data out of the system or using it for a little demo

### Compilation

In the cloned directory, run:

```
make
```

### Execution

In the cloned directory, run:

```
make run
```

### Features

Empty the project directories

```
make clean
```

Delete the project directories

```
make hardClean
```

Display the games saved

```
make save
```

Delete the project directories

```
make cleanSaves
```

Empty the project directories, compile and execute

```
make super
```

Display help message:

```
make help
```

## Authors

* **BOUHRARA Adam** _alias_ [@Adamou02](https://github.com/Adamou02)
* **CASSIET Clement** _alias_ [@Clément](https://github.com/clementcst)
* **CERF Fabien** _alias_ [@Fab780](https://github.com/Fab780)
* **GAUTIER Jordan** _alias_ [@JordanG2](https://github.com/JordanG2)
* **LEGRAND Joan** _alias_ [@LegJo](https://github.com/LegJo)

Developped on Ubuntu Linux, Visual Studio Code, 12/2022.
