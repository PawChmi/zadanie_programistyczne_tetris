# Zadanie Programistyczne: Tetris
Program wykorzystuje bibliotekę curses.
Kompilowanie z cmake:
`cmake . && make`
Na systemie Windows należy wskazać ścieżkę do kompilatora oraz rodzaj generatora
(domyślnie powinien to być MSVC)
`cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -G "MinGW Makefiles" .`
Uruchomienie programu:
`./tetris`

```
This is a console based tetris game

OPTIONS:
 -k <filename> to use custom key binds specified in a file
 -h 	 display this help message
 -r 	 reverse the color theme (only applies to block and ghost block)
 -u 	 use unicode characters
```
