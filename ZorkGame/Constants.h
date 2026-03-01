#pragma once

#define HELP R"help(
Game Help

Input and parsing
- Commands are typed at the prompt and are case-insensitive.
- Input is parsed into up to four space-separated tokens: action, target, conjunction, container/weapon.
- You can chain multiple commands on one line using `;` (semicolon). Example: `take coin; inventory`.
- Multi-word names are not supported by the parser; use single-word item/creature/container names (for example: `key`, `rock`, `bag`).

Commands
- look
  - Show the contents of the current room (items, creatures, exits).
  - Example: `look`

- inventory (or `i`)
  - Show items currently carried by the player.
  - Example: `inventory`

- take <item>
  - Pick up an item from the current room.
  - Example: `take coin`

- take <item> from <container>
  - Take an item out of a container in the current room.
  - Conjunction: `from` (required in this form).
  - Example: `take hat from bag`

- drop <item>
  - Remove an item from your inventory and drop it into the current room.
  - Example: `drop rock`

- put <item> in <container>  or  put <item> into <container>
  - Put an item from your inventory into a container in the current room.
  - Conjunctions: `in`, `into`.
  - Example: `put hat in bag`

- walk <direction>
  - Move through an exit in the given cardinal direction.
  - Example: `walk north` (common directions: `north`, `south`, `east`, `west`).

- attack <target>
  - Attack a creature in the current room without a specified weapon (unarmed attack).
  - Example: `attack guard`

- attack <target> with <weapon>  or  attack <target> using <weapon>
  - Attack a creature using a weapon from your inventory.
  - Conjunctions: `with`, `using` (or omit conjunction for some forms; the game accepts empty conjunction for attack).
  - Example: `attack guard with stick`

- quit
  - Exit the game.

- help
  - Show this help text.

Notes
- Commands that reference objects will print an explanatory message if the object is missing, the type is incorrect (e.g., trying to take a creature), or the required conjunction is invalid.
- For exact behavior and validation logic, see `ZorkGame/World.cpp` (functions such as `handleAction`, `checkConjunction`, and the `handleCmd*Errors` helpers).

Enjoy exploring!
)help"

#define INTRO R"intro(

Zork is a small text-based adventure. Explore rooms, inspect and collect items, put items into containers, fight creatures with weapons, and move between locations.

Try commands such as:
- `help` — show this help text with more details on how to use the instructions
- `look` — inspect your current location
- `inventory` or `i` — list carried items
- `take <item>` — pick up an item
- `take <item> from <container>` — take an item from a container
- `put <item> in <container>` — put an item into a container
- `drop <item>` — drop an item into the room
- `walk <direction>` — move (e.g., `walk north`)
- `attack <target>` — attack a creature without a weapon (unarmed)
- `attack <target> with <weapon>` — attack a creature using a weapon
- `quit` — exit the game

Commands are case-insensitive. Chain commands with `;` (example: `take key; walk north`).
Enjoy exploring!
)intro"

#undef ZORK_ASCII
#define ZORK_ASCII R"zork(

 ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗ 
 ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗
 ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║
 ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║
 ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝
  ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝

                        ███████╗ ██████╗ ██████╗ ██╗  ██╗
                        ╚══███╔╝██╔═══██╗██╔══██╗██║ ██╔╝
                          ███╔╝ ██║   ██║██████╔╝█████╔╝ 
                         ███╔╝  ██║   ██║██╔══██╗██╔═██╗ 
                        ███████╗╚██████╔╝██║  ██║██║  ██╗
                        ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝

 )zork"

