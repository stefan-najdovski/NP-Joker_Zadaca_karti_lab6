# Napredno Programiranje - Joker_Zadaca_karti_lab6

## Testrirano na Arch Linux/ macOS Ventura 13.3, bi trebalo da raboti i na Windows

### Podredeni:
![DEMO](demo.png)
### Izmeasni:
![DEMO1](demo1.png)

## Compile
```
sudo pacman -S g++ cmake raylib
```
- To compile the code:
```
g++ main.cpp -o main -lraylib
```
```
g++ main.cpp -o main -L/path/to/raylib -lraylib
```
ili koristi CLION (preku cmake kje se simni raylib)

### Originalno baranje:
```
Следете го примерот за мешање на карти, но сега во шпилот карти имате и 2 џокери.
Инструкции правила:
1. Прво картите ги покажувате подредени  1срце,1детелина,1локум,1-Лист, 2srce, 2detelina...
2. Ги покажувате измешани
3. Ги делите на 4 играчи.

*Оваа задача е Џокер задача.
Првите
и уникатни решенија ќе бидат вреднувани. (не споделувајте решенија, не
мора да се држете до примерот од претходни вежби можностите се отворени но треба да ги исполните сите барањата за да се бодува.)

Оваа задача не е задолжителна.
Поените за оваа задача ќе бидат додадени на во текот или крај од семестар и тогаш ќе бидат пишани колку изнесува.
Рок на решавање 10.04.2023

**пс 
https://stackoverflow.com/questions/18117582/picking-rand-number-from-1-6
```
