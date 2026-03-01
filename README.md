# ZorkGame

ZorkGame is a simple text-based adventure game implemented in C++ (Zork-style). Play by typing commands and exploring the world.

Repository
- GitHub: https://github.com/CarrotCake002/ZorkGame
- License: https://github.com/CarrotCake002/ZorkGame/blob/master/LICENSE

Download
- Clone the repository:

  ```bash
  git clone https://github.com/CarrotCake002/ZorkGame.git
  cd ZorkGame
  ```

- Or download the ZIP from the GitHub repository page and extract it locally.

Build and run
- Recommended (Windows / Visual Studio):
  - Open the solution or project in Visual Studio (the `ZorkGame` project or solution file if present).
  - Build the project (Release or Debug) and run from the IDE.

- Using g++ (simple single-file example; adjust source list as needed):
  ```bash
  g++ -std=c++17 ZorkGame/main.cpp ZorkGame/World.cpp ZorkGame/Creature.cpp -o ZorkGame
  ./ZorkGame
  ```

Authors and contributors
- Primary repository owner: `CarrotCake002` (see GitHub for full contributor list)
- Contributions are welcome — open a pull request on the GitHub repository.

How to play

- Input and parsing notes
  - Commands are typed at the prompt and executed when you press Enter.
  - Input is parsed into up to four space-separated tokens: `action`, `target`, `conjunction`, `container` (or `weapon`).
  - Commands are case-insensitive (the game converts input to lowercase before processing).
  - You can chain multiple commands on one line using `;` (semicolon). Example: `take coin; inventory`.
  - Multi-word names are currently not supported by the parser: names must be a single word (for example `key`, `rock`, `bag`).

- Supported actions and syntax (implemented in `ZorkGame/World.cpp`)
  - `look`
    - Description: Show the contents of the current room (items, creatures, exits).
    - Example: `look`

  - `inventory` or `i`
    - Description: Show items currently carried by the player.
    - Example: `inventory`

  - `take <item>`
    - Description: Pick up an item that is present in the current room.
    - Example: `take coin`
    - Notes: Cannot take creatures or containers as a whole. The game will refuse non-item types.

  - `take <item> from <container>`
    - Description: Take an item out of a container that is present in the current room.
    - Example: `take hat from bag`
    - Supported conjunction: `from` (required in this form). The code checks the conjunction exactly.

  - `drop <item>`
    - Description: Remove an item from your inventory and drop it into the current room.
    - Example: `drop rock`

  - `put <item> in <container>` or `put <item> into <container>`
    - Description: Put an item from your inventory into a container in the current room.
    - Example: `put hat in bag` or `put hat into bag`
    - Supported conjunctions: `in`, `into`.

  - `walk <direction>`
    - Description: Move through an exit in the given cardinal direction.
    - Example: `walk north`
    - Notes: Directions are converted via the game's `Exit::strToDirection` mapping; use common words like `north`, `south`, `east`, `west`.

  - `attack <target>`
    - Description: Attack a creature in the current room without a weapon (unarmed attack).
    - Example: `attack guard`

  - `attack <target> with <weapon>` or `attack <target> using <weapon>`
    - Description: Attack a creature using a specific weapon from your inventory.
    - Example: `attack guard with stick` or `attack guard using rock`
    - Supported conjunctions: `with`, `using`. If the weapon token is present but the conjunction is not recognized, the action will not be accepted.

  - `quit`
    - Description: Exit the game cleanly.
    - Example: `quit`

  - `help`
    - Description: A help command exists in the code (`cmdHelp`) but it is currently an empty stub and does not display information.

- Error and behavior notes derived from the code
  - The parser expects tokens separated by spaces; long or multi-word item names are not supported.
  - Conjunctions must match the supported words exactly for compound commands (e.g., `from`, `in`, `into`, `with`, `using`).
  - If an action requires an object that is not present (e.g., item not in room, container not present, weapon not in inventory), the game will print an explanatory message and ignore the action.
  - You can execute multiple commands in a row using `;` (semicolon). Each chunk is parsed separately.

For implementation details and to see the exact acceptance/validation logic, inspect `ZorkGame/World.cpp` (functions such as `handleAction`, `handleCmdTakeFromContainerErrors`, `handleCmdPutErrors`, `handleAttack`, and `splitCommands`).

License
- See the repository `LICENSE` file for licensing details: https://github.com/CarrotCake002/ZorkGame?tab=MIT-1-ov-file#readme

Support
- For issues, feature requests, or contributions, open an issue or pull request on the GitHub repository.
