# Mini-compilateur Pascal

Projet de compilation, ENSI II2. Vérifie qu'un fichier Pascal respecte la grammaire du sujet et s'arrête à la première erreur.

**État :** lexer fait (tables à faire) · parser fait · sémantique et code à pile à faire.

## Utilisation

```
gcc -Wall -Wextra -o pascal main.c lexer.c parser.c
./pascal ok1.pas
```

Succès : `Analyse syntaxique reussie.`
Erreur : `Erreur syntaxique ligne 5 : attendu instruction, trouve 'end'`

## Fichiers

- `lexer.c/.h` : découpe le texte en unités lexicales
- `parser.c/.h` : descente récursive prédictive, une fonction par non-terminal
- `main.c` : ouvre le fichier et lance `parse()`

## Grammaire LL(1)

```
P             → program id ; Dcl Inst_composée .
Dcl           → var Liste_id : Type ; Dcl | ε
Liste_id      → id Liste_id'
Liste_id'     → , id Liste_id' | ε
Type          → integer | char
Inst_composée → begin Inst end
Inst          → Liste_inst | ε
Liste_inst    → I Liste_inst'
Liste_inst'   → ; I Liste_inst' | ε
I             → id := Exp_simple | if Exp then I else I | while Exp do I
              | read ( id ) | readln ( id ) | write ( id ) | writeln ( id )
Exp           → Exp_simple Exp'
Exp'          → oprel Exp_simple | ε
Exp_simple    → Terme Exp_simple'
Exp_simple'   → opadd Terme Exp_simple' | ε
Terme         → Facteur Terme'
Terme'        → opmul Facteur Terme' | ε
Facteur       → id | nb | ( Exp_simple ) | not Facteur
```

## Limites connues

- Numéro de ligne parfois décalé de 1
- Mots-clés sensibles à la casse
- Pas de chaînes ni de caractères littéraux
