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

Enjoy exploring!
)help"

#define INTRO R"intro(

Zork is a small text-based adventure game. Explore rooms, inspect and collect items, fight creatures, and move between locations.

To see the full list of available commands and detailed usage, type `help` at the game prompt.

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

// ANSI text attributes and a wide palette of foreground/background colors.
// Use these constants to colorize output. Example:
// std::cout << FG_RED << "text" << FG_RESET;

#include <string>

// Reset / attributes
inline const std::string FG_RESET = "\x1b[0m";
inline const std::string ATTR_BOLD = "\x1b[1m";
inline const std::string ATTR_DIM = "\x1b[2m";
inline const std::string ATTR_UNDERLINE = "\x1b[4m";
inline const std::string ATTR_BLINK = "\x1b[5m";
inline const std::string ATTR_REVERSE = "\x1b[7m";
inline const std::string ATTR_HIDDEN = "\x1b[8m";

// Standard foreground colors
inline const std::string FG_BLACK = "\x1b[30m";
inline const std::string FG_RED = "\x1b[31m";
inline const std::string FG_GREEN = "\x1b[32m";
inline const std::string FG_YELLOW = "\x1b[33m";
inline const std::string FG_BLUE = "\x1b[34m";
inline const std::string FG_MAGENTA = "\x1b[35m";
inline const std::string FG_CYAN = "\x1b[36m";
inline const std::string FG_WHITE = "\x1b[37m";

// Bright foreground colors
inline const std::string FG_BRIGHT_BLACK = "\x1b[90m";
inline const std::string FG_BRIGHT_RED = "\x1b[91m";
inline const std::string FG_BRIGHT_GREEN = "\x1b[92m";
inline const std::string FG_BRIGHT_YELLOW = "\x1b[93m";
inline const std::string FG_BRIGHT_BLUE = "\x1b[94m";
inline const std::string FG_BRIGHT_MAGENTA = "\x1b[95m";
inline const std::string FG_BRIGHT_CYAN = "\x1b[96m";
inline const std::string FG_BRIGHT_WHITE = "\x1b[97m";

// Standard background colors
inline const std::string BG_BLACK = "\x1b[40m";
inline const std::string BG_RED = "\x1b[41m";
inline const std::string BG_GREEN = "\x1b[42m";
inline const std::string BG_YELLOW = "\x1b[43m";
inline const std::string BG_BLUE = "\x1b[44m";
inline const std::string BG_MAGENTA = "\x1b[45m";
inline const std::string BG_CYAN = "\x1b[46m";
inline const std::string BG_WHITE = "\x1b[47m";

// Bright background colors
inline const std::string BG_BRIGHT_BLACK = "\x1b[100m";
inline const std::string BG_BRIGHT_RED = "\x1b[101m";
inline const std::string BG_BRIGHT_GREEN = "\x1b[102m";
inline const std::string BG_BRIGHT_YELLOW = "\x1b[103m";
inline const std::string BG_BRIGHT_BLUE = "\x1b[104m";
inline const std::string BG_BRIGHT_MAGENTA = "\x1b[105m";
inline const std::string BG_BRIGHT_CYAN = "\x1b[106m";
inline const std::string BG_BRIGHT_WHITE = "\x1b[107m";

// Convenience short names used elsewhere in the codebase
inline const std::string TEXT_COLOR_RED = FG_RED;
inline const std::string TEXT_COLOR_GREEN = FG_GREEN;
inline const std::string TEXT_COLOR_RESET = FG_RESET;
inline const std::string TEXT_COLOR_BLUE = FG_BLUE;
inline const std::string TEXT_COLOR_YELLOW = FG_YELLOW;
inline const std::string TEXT_COLOR_BRIGHT_YELLOW = FG_BRIGHT_YELLOW;
inline const std::string TEXT_COLOR_CYAN = FG_CYAN;
inline const std::string TEXT_COLOR_MAGENTA = FG_MAGENTA;


// DEATH DIALOGUE LINES

// How the player died (cause of death)
inline const std::vector<std::string> deathMessages = {
    "A lightning bolt strikes you from a clear blue sky. Typical.",
    "You trip over a pebble and somehow explode.",
    "A rogue seagull carries you into the sun. You do not return.",
    "You sneeze so hard your soul leaves your body.",
    "A piano falls from the sky. No one knows where it came from.",
    "You accidentally swallow your own tongue. The doctors are baffled.",
    "A squirrel looks at you funny and you simply cease to exist.",
    "You die of a papercut. A very, very aggressive papercut.",
    "God alt+F4'd you.",
    "You walk into a wall and the wall wins.",
    "A meteor the size of a grape hits you specifically.",
    "You read the terms and conditions. The shock kills you.",
    "You slip on a banana peel. It's not funny. You're dead.",
    "A level 1 goblin looks at you and you have a heart attack.",
    "You open your inventory and a sword falls out onto your foot. Fatal.",
    "You are eaten by a grue.",
    "You spontaneously combust. Your shoes survive.",
    "A passing wizard points at you and says 'lol'. You die.",
    "You try to pet a dog. The dog is a bear. You are dead.",
    "Death himself shows up, trips on the way to get you, but still gets you.",
    "You are deleted.",
    "You die doing what you loved: absolutely nothing.",
    "A coconut falls on your head. Scientists will study this for years.",
    "You step on a Lego. The pain is fatal.",
    "Your immune system files a resignation letter and leaves.",
    "You are struck by a fish thrown from very far away.",
    "The narrator gets bored and kills you.",
    "You forget how to breathe for just a moment too long.",
    "A skeleton pops out. You die of fright.",
    "You are yeeted into the void by an unseen force.",
    "Your torch goes out. So do you.",
    "Your map was wrong anyway.",
    "You collapse. The dungeon yawns.",
    "You died as you lived: confused and underprepared."
};

// The game saying goodbye to the player
inline const std::vector<std::string> deathScreens = {
    "You have perished. Your legend ends here... for now.",
    "You are very dead. Congratulations.",
    "~ YOU DIED ~\nYour adventure has come to an untimely end.",
    "GAME OVER.",
    "It appears you are no longer alive. How unfortunate.\nThe dungeon will remember your failure.",
    "Your story ends here. The dungeon does not mourn.",
    "Darkness takes you. It feels oddly comfortable.",
    "You have been thoroughly defeated. Well done to the dungeon.",
    "Death was not on your schedule today. Death disagreed.",
    "You fought bravely. You died anyway.",
    "The dungeon has claimed another soul.",
    "Somewhere, a goblin is celebrating.",
    "You have reached the end of your adventure. Permanently.",
    "The dungeon wins this round.",
    "Your bones will make fine dungeon decoration.",
    "You are gone. The dungeon barely noticed.",
    "Even the rats feel a little bad. A little.",
    "The last thing you see is the ceiling. It is unremarkable.",
    "You have been added to the dungeon's body count.",
    "Death looks at you, checks his list, nods slowly.",
    "Your adventure was short. The dungeon's patience was shorter.",
    "Another adventurer lost to the depths. As expected.",
    "The dungeon has seen better heroes. It has also seen worse. Not many though.",
    "The monsters will speak of this battle for minutes.",
    "You didn't make it. Shocking, truly shocking.",
    "The dungeon thanks you for your contribution."
};