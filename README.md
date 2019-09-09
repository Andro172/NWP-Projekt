# Nine Man's Morris Game

Made using c++ with SFML framework for x86 machines

RULES:

The board consists of a grid with twenty-four intersections or points. Each player has nine pieces, or "men", coloured GREEN and RED. Players try to form 'mills'—three of their own men lined horizontally or vertically—allowing a player to remove an opponent's man from the game. A player wins by reducing the opponent to two pieces (where they could no longer form mills and thus be unable to win), or by leaving them without a legal move.

The game proceeds in three phases:

1. -> Placing men on vacant points
2. -> Moving men to adjacent points
3. -> (optional phase) Moving men to any vacant point when the player has been reduced to three men

HAVE FUN!!!


RELEASE INSTRUCTIONS:

To configure release mode go to Configuration Properties->Linker->Input->Aditional Dependencies
and set 
sfml-graphics-d.lib to sfml-graphics.lib
sfml-window-d.lib to sfml-window.lib
sfml-system-d.lib to sfml-window.lib

