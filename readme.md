# LinUM - Labb 6 Bibliotek
Utvecklingsrepo Lab 6 i kursen Linux som utvecklingsmiljö på Umeå universitet.

## Förslag på filstruktur
| *Mapp*            | *Beskrivning*                   |  
| ------------------| ------------------------------- |  
| src/              | Alla källfiler                  |
| src/libresistance | Källfiler till libresistance.so |
| src/libpower      | Källfiler till libpower.so      |
| src/libcomponent  | Källfiler till libcomponent.so   |
| build/            | Kompilerade filer         |  



## Kom igång med projektet
```bash
1. Clona ner repot till din dator

$ git clone https://github.com/DanielJohnsson87/LinUM.git en/valfri/lokal/mapp
```

```bash
2. Checka ut en egen branch av koden. På så sätt kan vi arbeta utan att vara oroliga för att få konflikter. När ni har kod som är redo kan ni höra av er till mig (Daniel) så mergar jag in era ändringar i master-branchen. 

$ git checkout -b namnet_på_ditt_bibliotek
```

```bash
3. Lägg till nya filer och mappar som du skapar så att git börjar spåra dem

$ git add folder/file.c
$ git status (Du bör nu se att filerna ligger under "Changes to be commited")
```

```bash
4. Committa dina ändringar. Meddelandet du skriver kommer synas i historiken. 

$ git commit -m "Ett meddelande till commiten. Någon förklarande text"
$ git log (Här bör du se din commit och andra commits om det finns några)
```

```bash
5. Pusha dina ändringar till vårt gemensama repo på github.com

Första gången du pushar till repot 
$ git push origin namnet_på_ditt_bibliotek 

Resterande gånger du pushar till repot räcker det med följande
$ git push
```


### Git-kommandon

```bash
1. Kolla status i ditt lokala repo

$ git status
```

```bash
2. Lägg till en ny fil/mapp så att git börjar spåra den
$ git add path/to/file
$ git add . (Lägger till alla filer)
$ git add -A (Lägger till alla filer och raderar filer ifall du plockar bort några)
```

```bash
3. Committa en ändringar

$ git commit -m "Meddelande"
```

```bash
4. Pusha ändringar

$ git push
```

```bash
5. Pusha till en specifik branch

$ git push origin branch_name
```

```bash
6. Se en lista över commit-historiken

$ git log
```

```bash
7. Byta branch

$ git checkout master (Checkar ut master-branchen. Dvs default-branchen.)
$ git checkout branch_name (Checkar ut branch_name) 
$ git checkout -b branch_name (Skapar en ny branch och checkar ut den.)
```
