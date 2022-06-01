# Logistyka Shire

Projekt ma za zadanie wyznaczyć optymalne trasy transportu produktów przemysłu piwowarskiego lokalnymi drogami.

Projekt porusza zagadnienia następujących problemów:

- problem maksymalnego przepływu
- wyznaczenia otoczki wypukłej i przynależności punktu do wielokąta
- problem najtańszego przepływu

_Projekt realizowany bez wykorzystania bibliotek zewnętrznych._

## Kompilacja

Do kompilacji należy użyć pliku `Makefile` dołączonego do projektu.

Aby skompilować projekt, w katalogu z projektem należy wywołać komendę:

```bash
$ make
```

Wynikiem procesu będzie plik wykonywalny `shire`.

> Kompilacja wykonywana jest za pomocą komendy `g++`.

## Uruchamianie

Uruchomienie projektu odbywa się poprzez komendę `shire`:

```
$ shire <dane_grafu_etap_1> <dane_wydajności> <dane_grafu_etap_2> <punkty_graniczne> <współrzędne_pól_uprawnych>
```

Wraz z następującymi parametrami:

- `dane_grafu_etap_1` - ścieżka do pliku zawierającego dane grafu dla etapu 1,
- `dane_wydajności` - ścieżka do pliku zawierającego dane o wydajności pól uprawnych, browarów i karczm
- `dane_grafu_etap_2` - ścieżka do pliku zawierającego dane grafu dla etapu 2,
- `punkty_graniczne` - ścieżka do pliku zawierająca punkty graniczne obszarów wydajnościowych,
- `współrzędne_pól_uprawnych` - ścieżka do pliku zawierającego pozycje pól uprawnych.

## Dane wejściowe

Uruchomienie algorytmu wymaga utworzenia 3 plików z danymi według następującego schematu:

### Dane dla etapu 1

Plik dla etapu 1 powinien zawierać definicję krawędzi oraz przypisaną im przepustowość zdefiniowane następująco:

```
[liczba krawędzi]
[początek krawędzi] [koniec krawędzi] [przepustowość]
```

### Dane dla etapu 2

Plik dla etapu 2 powinien zostać zdefiniowany według tego samego schematu co plik dla etapu 1.

### Dane wydajności

Dane o wydajności poszczególnych elementów infrastruktury należy przedstawić następująco:

```
[p/b/t] [przypisany wierzchołek] [wydajność]
```

Pierwsza kolumna wiersza powinna zawierać informacje o typie, odpowiednio:

- p - dla pól uprawnych,
- b - dla browarów,
- t - dla tawern / karczm.

### Punkty graniczne

Zbiór punktów granicznych wyznaczających poszczególne obszary wydajności pól uprawnych. Każdy obszar powinien być zdefiniowany następująco:

```
[liczba punktów granicznych] [wydajność obszaru]
[współrzędna x] [współrzędna y]
...
```

Do poprawnego działania wymagane jest utworzenie co najmniej jednego obszaru zdefiniowanego przez 3 punkty graniczne.

### Pozycje pól uprawnych

Plik powinien zawierać współrzędne pól uprawnych użytych w algorytmie wraz z indeksem wierzchołka grafu:

```
[indeks wierzchołka] [współrzędna x] [współrzędna y]
```

> Przykładowe pliki konfiguracyjne można znaleźć w katalogu `/conf`, oznaczone słowem kluczowym `*-default.txt`

## Struktura projektu

- `/conf` - katalog zawierający pliki danych wejściowych
- `/lib` - katalog zawierający pliki źródłowe projektu (`*.h` oraz `*.cpp`)
- `/docs` - katalog zawierający dokumentację w postaci `html` oraz `latex`
- `main.cpp` - plik główny z funkcją `main()`
- `Makefile` - plik zawierający instrukcje budowania

