# Repository zur Vorlesung CombOpt 

Zur Zeit enthält dieses Repository nur eine elementare Graphenklasse, sowie eine`main.cpp` (mit elementaren Beispielen), zwei Files `randomgraph.{c,h}pp`, welche ich zur Generierung von Zufallsgraphen für die Aufgaben nutze, einem `Makefile` sowie einem `input`-Ordner, welcher ebendiese Aufgaben enthält.

Wichtig:

  - Die Nutzung dieser Klassen ist ein Angebot, keine Pflicht! Jeder ist frei sich seine eigene Graphenklasse in einer beliebigen Sprache zu schreiben.
  - Ich habe versucht die Klassen und Beispiele so zu generieren, dass diese für einen C++ -fremden Anwender, welcher ein grundsätzliches Verständnis für Objektorientierung hat, verstanden und benutzt werden können. Ob ich Erfolg hatte, wird sich zeigen.
    - Fragen immer gerne; am liebsten im Issue-Board dieses Repositories! Antworten von Studenten sind natürlich (sowohl aus didaktischer Sicht wie auch aus Bequemlichkeit) sehr gerne gesehen!
 - Der Code ist nur sehr (!) rudimentär getestet. 
 - Mittels des Makefiles lässt sich der Code sehr einfach in einer Konsole, in welcher Clang (man kann im Makefile auch clang++ durch den zumeist vorhandenen g++-Compiler ersetzen) installiert ist, kompilieren und ausführen.
 ```sh
 $ cd <directory>
 $ make
 $ ./prog.exe
 ```
