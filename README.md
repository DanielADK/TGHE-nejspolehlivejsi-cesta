# Zadání
## Nejspolehlivější cesta
Máme rozlehlou počítačovou síť, která je realizována rádiovým spojením mezi stanicemi očíslovanými $0$
až $n-1$. Rádiové spojení může být nejrůznějším způsobem rušeno a tudíž má omezenou spolehlivost. Rádiové spojení je pro vybrané dvojice stanic dáné: číslem $i$
vysílající stanice, číslem $j$
přijímajícé stanice a pravděpodobností $0<p_{i,j}<1$
přijmutí správného paketu. Spojení mezi dvěma stanicemi je symetrické. Najděte v zadané síti nejspolehlivější spojení z vrcholu $s$
do vrcholu $t$
.

## Popis vstupu a výstupu
Na prvním řádku vstupu je počet stanic $n$
a celkový počet spojení mezi nimi, $m$
. Na dalších $m$
řádkcích je pro každé elementární spojení číslo vysílajícího uzlu, číslo přijímajícího uzlu (číslováno od 0) a pravděpodobnost $p$
(např. 0.8931). Na řádku $m+2$
je počet testovacích dotazů $N$
a na dalších $N$
řádcích jsou data pro jednotlivé dotazy. Jeden dotaz je dvojice stanic, mezi kterými chceme najít spojení, první je index počátečního a druhý index koncového uzlu.

Na výstupu bude $N$
řádků, pro každý dotaz jeden. Výsledek jednoho dotazu je posloupnost indexů stanic nalezeného nejspolehlivějšího spojení včetně počáteční a koncové stanice ze zadání dotazu. V případě, že žádné spojení pro dotaz neexistuje, vypíše se pouze index počátečního uzlu ze zadání dotazu.

## Příklad vstupu
```
3 3
0 1 0.8
0 2 0.5
1 2 0.7
1
0 2
```
## Očekávaný výstup
```
0 1 2
```