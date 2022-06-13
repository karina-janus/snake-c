## Snake napisany w C
Projekt zaliczeniowy na przedmiot Wstęp Do Programowania, rok 2021/2022

Projekt jest umieszczony na [githubie](https://github.com/karina-janus/snake-c).
### Spis treści:
- [O projekcie](#o-projekcie)
- [Instrukcje](#instrukcje)
- [Screenshoty](#screenshoty)
- [Opis funkcji](#opis-funkcji)
- [Pliki](#pliki)
- [Wykonanie](#wykonanie)


### O projekcie:
Projekt to odwzorowanie klasycznej gry - Snake - w C. Gra jest stworzona przy użyciu biblioteki [conio](https://en.wikipedia.org/wiki/Conio.h), 
przy pomocy której wyświetlamy grę na ekranie konsoli. Sama gra jest prosta: zaczynamy z wężem długim na 5 segmentów. Jedząc buźki (w oryginale jabłka) 
zwiększamy rozmiar węża. Jeśli wjedziemy w ramę gry lub w samego węża przegrywamy.
Na koniec gry wyświetla się nasz wynik i jest on porównywany z zapisanym (w pliku maxwynik.txt) największym wynikiem. Jeśli aktualny wynik jest większy od poprzedniego, lub większy 
od 100, program wyświetla gratulacje.

### Instrukcje:
Kod źródłowy programu znajduje się w pliku **projekt.cpp**. Program wykorzystuje bibliotekę [conio](https://en.wikipedia.org/wiki/Conio.h), więc działa wyłącznie na windowsie i nie będzie mógł się skompilować na innych systemach operacyjnych.
Skompilowany, gotowy do uruchomienia program jest w pliku **snake.exe**.

### Screenshoty:

Gra: 

![Image](https://user-images.githubusercontent.com/107310262/173195346-db88beeb-00ca-4d93-a036-f49a5b7d4055.png)


Dłuuugi snake: 

![Image](https://user-images.githubusercontent.com/107310262/173195304-c80664a7-b5ed-42d6-8d0d-ea066c746df2.png)

Najlepszy wynik: 

![Image](https://user-images.githubusercontent.com/107310262/173195321-7e73acf5-42bd-4b21-9d03-5f5b167e756d.png)

Game Over: 

![Image](https://user-images.githubusercontent.com/107310262/173195336-fedd656c-d8c7-49e0-a3e4-7c430db2cfcc.png)


### Opis funkcji:

- setup() - jest to funkcja, która tworzy grę: zbiera dane nt. najwyższego wyniku, tworzy węża długiego na 5 segmentów i kieruje go w prawo i ustawia grę na ON.
- start() - prosta funkcja, która czeka aż gracz zacznie grę (coś a la menu gry)
- gameover() - jest to funkcja, która jest wywoływana podczas zakończenia gry. Włącza alert (\a) i wyświetla ekran końca gry: duży napis "Game Over!" (ascii-art znaleziony na internecie), wynik oraz dalsze opcje - restart gry lub jej wyłączenie.
- widok() - prosta funkcja która wyświetla na ekranie: ramkę, węża, buźkę (jabłko) oraz wyniki: aktualny i najwyższy zapisany.
- random() - jest to funkcja wywoływana w celu wygenerowania buźki (jabłka). Za pomocą srand() generuje losową pozycję (X i Y), następnie sprawdza, czy ta pozycja jest w ramce oraz czy nie nachodzi na węża - jeśli nie, buźka (jabłko) jest generowane w tej pozycji.
- ruch() - funkcja odpowiadająca za ruch węża. Za pomocą funkcji getch_noblock() sprawdza aktualnie wciśnięte klawisze i kieruje węża w odpowiednim kierunku. Odpowiada także za kolizję - jeśli wąż wjedzie w buźkę (jabłko), zwiększy się o 1 segment, a gdy wjedzie w samego siebie lub ramkę, kończy grę.
- ogonek() - funkcja przesuwająca ogon węża.
- reset() i getch_noblock() - funkcje, które zarządzają oknem (sprawiają, że się nie porusza) oraz sprawdza jakie klawisze są wciśnięte.

### Pliki:

- projekt.cpp - plik zawierający kod źródłowy
- gameIcon.ico - ikona gry
- resource.rc - plik zasobów (ustawia ikonę gry)
- snake.exe - skompilowana gra
- dokumentacja.html - ta dokumentacja zapisana w pliku .html

### Wykonanie:
Program został wykonany przez
- [Karina Janus](mailto:karina.janus@student.uj.edu.pl)
- [Julia Siatka](mailto:julia.siatka@student.uj.edu.pl)
