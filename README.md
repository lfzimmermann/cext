# cext - Ein einfacher Texteditor in C

`cext` ist ein minimalistischer Texteditor, der in C geschrieben wurde. Er verwendet eine Gap-Buffer-Datenstruktur für effiziente Textmanipulation und Raylib für die grafische Benutzeroberfläche.

## Features (implementiert)

*   Grundlegende Texteingabe und -bearbeitung (Zeichen einfügen, Zeichen löschen mit Backspace)
*   Cursor-Navigation (links, rechts)
*   Anzeige des Buffer-Inhalts (mit einer Visualisierung der Gap-Position)

## Geplante Features

*   Speichern und Laden von Dateien
*   Verbesserte Cursor-Navigation (oben, unten, Wortweise, Zeilenanfang/-ende)
*   Textauswahl
*   Kopieren, Ausschneiden, Einfügen
*   Undo/Redo-Funktionalität
*   Suchfunktion
*   Konfigurierbare Einstellungen

## Abhängigkeiten

*   **Raylib**: Für die grafische Benutzeroberfläche. Stellen Sie sicher, dass Raylib auf Ihrem System installiert ist und die Header-Dateien im `include`-Verzeichnis und die Bibliotheksdateien im `lib`-Verzeichnis dieses Projekts verfügbar sind oder dass Ihr Compiler/Linker sie finden kann. Installationsanweisungen finden Sie auf der [Raylib-Website](https://www.raylib.com/).
*   **CUnit**: Für die Unit-Tests. Wird für das `make test`-Ziel benötigt.

## Bauen des Projekts

Das Projekt verwendet `make` zum Kompilieren. Das `Makefile` ist so konfiguriert, dass es die Quelldateien aus den Verzeichnissen `src/backend`, `src/frontend` und dem Stammverzeichnis (`main.c`) kompiliert und die Objektdateien im `build`-Verzeichnis ablegt.

### Verfügbare Make-Targets

*   `make` oder `make all`:
    Kompiliert das Hauptprojekt und erstellt die grafische Benutzeroberfläche des Editors (standardmäßig `text_editor_gui` im Projektstammverzeichnis). Dies ist das Standardziel.
*   `make gui`:
    Identisch zu `make all`, kompiliert die GUI-Version des Editors (`text_editor_gui`).
*   `make test`:
    Kompiliert und führt die Unit-Tests für den Gap Buffer aus. Die Test-Suite verwendet das CUnit-Framework. Die ausführbare Testdatei ist `main_test` und wird im `build`-Verzeichnis erstellt und von dort ausgeführt.
*   `make clean`:
    Entfernt die kompilierten Binärdateien (`text_editor_gui`), das gesamte `build`-Verzeichnis (einschließlich Objektdateien und der Testausführungsdatei `build/main_test`).
*   `make run`:
    Kompiliert (falls notwendig) und führt die GUI-Version des Editors (`text_editor_gui`) aus.

### Bauanleitung

1.  **Klone das Repository** (falls noch nicht geschehen):
    ```bash
    git clone https://github.com/lfzimmermann/cext
    cd cext
    ```

2.  **Stelle sicher, dass die Abhängigkeiten installiert sind:**
    *   **Raylib**:
        *   Laden Sie die Raylib-Bibliothek herunter oder kompilieren Sie sie.
        *   Platzieren Sie die Raylib-Header-Dateien (z.B. `raylib.h`, `raymath.h`, etc.) in das `include`-Verzeichnis dieses Projekts.
        *   Platzieren Sie die kompilierte Raylib-Bibliotheksdatei (z.B. `libraylib.a` oder `libraylib.so`/`raylib.dll`) in das `lib`-Verzeichnis dieses Projekts.
        *   Alternativ passen Sie die Pfade `COMMON_CFLAGS` (für `-I`) und `COMMON_LDFLAGS` (für `-L`) sowie `RAYLIB_LDFLAGS` im `Makefile` an, falls Raylib systemweit installiert ist.
    *   **CUnit**: (wird für `make test` benötigt)
        Installieren Sie es über den Paketmanager Ihrer Distribution (z.B. `sudo apt-get install libcunit1-dev` auf Debian/Ubuntu, `sudo dnf install cunit-devel` auf Fedora).

3.  **Kompiliere den Editor**:
    ```bash
    make
    ```
    Dies erstellt die ausführbare Datei `text_editor_gui` im Stammverzeichnis des Projekts.

4.  **Kompiliere und führe die Tests aus** (optional):
    ```bash
    make test
    ```
    Die Ausgabe der Tests wird in der Konsole angezeigt.

## Ausführen des Editors

Nach dem erfolgreichen Bauen kannst du den Editor starten, indem du die generierte ausführbare Datei im Stammverzeichnis des Projekts ausführst:

```bash
./text_editor_gui
```
Oder verwende das Make-Target:
```bash
make run
```

## Projektstruktur

```
.
├── Makefile              # Build-Skript für das Projekt
├── README.md             # Diese Datei
├── include/              # Verzeichnis für Header-Dateien von Drittanbietern (z.B. raylib)
├── lib/                  # Verzeichnis für Bibliotheksdateien von Drittanbietern (z.B. raylib)
├── src/
│   ├── backend/
│   │   ├── gap_buffer.c  # Implementierung der Gap-Buffer-Datenstruktur
│   │   └── gap_buffer.h  # Header-Datei für den Gap Buffer
│   ├── frontend/
│   │   ├── gui.c         # Implementierung der grafischen Benutzeroberfläche mit Raylib
│   │   └── gui.h         # Header-Datei für die GUI
│   └── main.c            # Haupteinstiegspunkt der Anwendung (initialisiert Gap Buffer und startet GUI)
├── tests/
│   ├── gap_buffer_test.c # CUnit-Tests für die Gap-Buffer-Implementierung
│   ├── gap_buffer_test.h # Header-Datei für die Gap-Buffer-Tests
│   └── main_test.c       # Hauptdatei zum Ausführen der CUnit-Tests (initialisiert Test-Registry und Suiten)
└── build/                # Verzeichnis für Objektdateien und Test-Binaries (wird von make erstellt)
```

## Beitrag

Beiträge sind willkommen! Wenn Sie Fehler finden oder Verbesserungsvorschläge haben, erstellen Sie bitte einen Issue oder einen Pull Request.
