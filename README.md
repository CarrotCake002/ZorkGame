# Zork

A text-based adventure game written in C++ inspired by the classic Zork series. Explore rooms, fight creatures, collect items and weapons, and make your way through a world that grows increasingly dangerous the further you venture from home.

**Authors:** CarrotCake002

**Repository:** [CarrotCake002/ZorkGame](https://github.com/CarrotCake002/ZorkGame)

**License:** MIT

---

## How to Build and Run

A prebuilt executable can be downloaded from the **Releases** section of the repository. The project is developed and tested with **Visual Studio 2026** — opening the solution and building from there is the recommended approach. Running it any other way is at your own risk.

---

## How to Play

Commands are typed at the prompt (`>`) and are case-insensitive. You can chain multiple commands on one line using `;`.

### Available Commands

| Command | Description |
|---|---|
| `look` | Show the contents of the current room |
| `inventory` / `i` | Show items in your inventory |
| `status` | Show your health and the health of creatures in the room |
| `take <item>` | Pick up an item from the room |
| `take <item> from <container>` | Take an item from a container |
| `drop <item>` | Drop an item from your inventory |
| `put <item> in <container>` | Place an item into a container |
| `walk <direction>` | Move in a direction (`north`, `south`, `east`, `west`, `up`, `down`) |
| `attack <creature>` | Attack a creature unarmed |
| `attack <creature> with <weapon>` | Attack a creature with a weapon from your inventory |
| `help` | Show the help text |
| `quit` | Exit the game |
| `reset` | Restart the game after dying |

### Combat

Attacking a creature will trigger all other creatures in the room to become aggressive and attack you back at the end of your turn. When you clear a room of all enemies, you heal and gain a permanent increase to your max health. Weapons have a base damage value and a critical strike chance — higher critical chance means more variance but higher potential damage.

### Notes and Keys

Notes can be read and taken as items. Keys are used automatically when you attempt to walk through a locked exit — as long as the matching key is in your inventory.

---

## Walkthrough

Below is a full guide to completing the game from start to finish.

### House

You start in your **House**. Use `look` to see what's around you. There is a **Chest** in the room — open it with `take <item> from chest` to retrieve its contents. Grab the **KeyToTheBackyard**, which you will need shortly. You can also take the **Rock**, a basic weapon that will help you in your first fight.

### Backyard

Walk north to enter the **Backyard**. You will find a **Beetle** here. Kill it with `attack beetle` (optionally `with rock`). Once it dies, it drops the **KeyToTheHouse**, which unlocks the front door. Head back south to the House, then walk south again to exit through the front door into the **Frontyard**.

### Frontyard and Woods

From the Frontyard, walk south to enter the **Woods**. Here you will find a **Dragonfly**. Kill it to obtain its **Leg**, a weapon with more damage than the Rock. At this point you have two paths forward.

### Path A: Straight to the Castle

From the Woods, walk east to reach the **Castle Entrance**, then north into the **Castle** itself. This is the faster route but you will miss out on stat increases and better loot from the dungeon.

### Path B: Through the Dungeon (Recommended)

From the Woods, walk west to enter the **Dungeon**. You will find an **Undead** enemy here. Defeat it to obtain the **Longsword**, the best weapon available before the castle. There is also a note in the dungeon hinting at a secret passage.

Walk down to enter the **Dungeon Basement**, where you will face a double enemy fight against a **Demon** and a **Vermin**. Focus the weaker one first, then take down the other. The Demon drops **Fangs**, a weapon with high critical strike chance. Clearing this room will heal you and boost your stats.

Walk east from the Dungeon Basement to find the secret passage leading to the **Castle Catacombs**. Here you will face the **Wraith**, a tough miniboss. It does not drop any items, but defeating it grants a stat increase. Walk up from the Catacombs to arrive in the **Castle**.

### Castle

Inside the **Castle** you will face the **Champion**, a powerful enemy carrying an **Axe**. Defeat it to claim the weapon and earn another stat boost. Walk up to reach the **Castle Rooftop**.

### Castle Rooftop

The Rooftop is your second double enemy fight, against a **Knight** and a **Gargoyle**. Target the Knight first as it is the weaker of the two. The Knight drops a **Mace**. Once both are defeated, walk north to enter the **Throne Room**.

### Throne Room — Final Boss

The **Dark Lord** awaits. This is the hardest fight in the game. Make sure you are well equipped before engaging. Once defeated, a short conclusion message will play and the game will keep running — you are free to explore, backtrack, or simply quit. The adventure is over.

---

## World Map

```
                        [Backyard]
                             |
                          [House]
                             |
                        [Frontyard]
                             |
     [Castle Entrance] -- [Woods] -- [Dungeon]
               |                          |
            [Castle] -- [Catacombs] -- [Dungeon B1]
               |
        [Castle Rooftop]
               |
         [Throne Room]
```

---

## License

This project is licensed under the MIT License. See `LICENSE` for details.
