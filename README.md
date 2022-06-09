# Zadanie Programistyczne: Tetris
Program wykorzystuje bibliotekę [ncurses](https://github.com/mirror/ncurses) (licencja MIT) na linuxie, oraz [pdcurses](https://github.com/wmcbrine/PDCurses)  (Public Domain) na windowsie. 

## Kompilowanie z cmake:
`cmake . && make`
Na systemie Windows należy wskazać ścieżkę do kompilatora oraz rodzaj generatora
(domyślnie powinien to być MSVC)<br>
`cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -G "MinGW Makefiles" .`


## Uruchomienie programu:
Plik wykonywalny `tetris` uruchamiamy w konsoli poleceń

```
OPCJE:
 -k <nazwa_pliku> użyj zestawu klawiszy zapisanych w pliku
 -h 	 wyświetl tą wiadomość pomocy
 -t <0-4>  wybierz motyw od 0 do 4
```
