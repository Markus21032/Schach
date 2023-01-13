# Schach
Schach in C++


unser Schach muss können:
- Spielfeld generieren / aufstellen
- Spielfeld auf der Konsole ausgeben
- Spiel Speichern / Laden
- Entscheiden ob die Züge gültig sind

unser Schach soll können:
- automatisches Schnellspeichern
- Schach erkennen
- Schach matt erkennen

unser Schach kann eventuell:
- Speicherdaten verschlüsseln -> anticheat
- Pc gegenspieler





Wie funktioniert unser Programm?


Chess.cpp:
Unsere main Methode steuert den Großteil des Programmablaufs (eingaben vom User / wann wird was gecheckt usw.)
Sie validiert Eingaben und interagiert mit dem Schachbrett (der klasse ChessBoard).
In ihr ist ein Exithandler, welcher den automatisch erstellten Quicksafe in das geladene SaveFile übernimmt.


ChessBoard.hpp:
Das Schachspiel findet auf einem Vector von Vectoren von Figuren statt, dieses wird hier gespeichert.
Die klasse ChessBoard kann ein neues "Schachbrett" inizialisieren, zurücksetzen und kopieren.
Mit ihr werden auf dem Schachbrett Figuren bewegt, nachdem der Zug validiert wurde.
Die Schach, Schachmatt und unentschieden Algorithmen befinden sich auch in dieser Klasse.


ChessFigures.hpp:
Hier gibt es für jede Figuren Art eine eigene Klasse welche von der Klasse "Figure" erbt.
Die Figuren beinhalten ihr Zeichen (P = Pawn, K = King, ...), ihre Spielernummer und ihre position.
Außerdem haben sie eine Funktion (isValidMove), welche abfragt ob sie sich zu den gegebenen Koordinaten bewegen dürfen.


printChess.hpp:
Gibt das mitgegebene Schachbrett (der klasse ChessBoard) aus


saveAndLoadChess.hpp:
speichert ein mitgegebenes Schachbrett oder läd dieses