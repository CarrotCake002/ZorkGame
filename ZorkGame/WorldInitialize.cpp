#include "World.h"

void World::initialize() {
    /* HOUSE */
    // Creation of the Player
    addEntity(new Player("Player", "the player character", 15, 1, true, EntityType::PLAYER));

    // Creation of the House and its contents
    addEntity(new Room("House", "a simple house for a simple person."));
    currentRoom = static_cast<Room*>(getTarget("House"));

    //  Creation of a Chest in the house with some items
    addEntity(new Entity("Chest", "an old chest that can contain a few items", EntityType::CONTAINER));
    addEntity(new Armor("Shirt", "a dirty shirt for handy labor that will slightly protect you", 1, ArmorPart::BODY));
    addEntity(new Armor("Pants", "a pair of rugs some dare too call pants", 1, ArmorPart::LEGS));
    getTarget("Chest")->addItem(getTarget("Shirt"));
    getTarget("Chest")->addItem(getTarget("Pants"));
    getTarget("House")->addItem(getTarget("Chest"));

    // Creation of a key to the backyard and put it in the house chest
    addEntity(new Key("BackyardKey", "a key to the Backyard", 1));
    getTarget("Chest")->addItem(getTarget("BackyardKey"));


    /* BACKYARD */
    // Creation of the Backyard and its content
    addEntity(new Room("Backyard", "the backyard to your house. You have heard creatures festering from time to time..."));
    addEntity(new Creature("Beetle", "a large beetle. It doesn't look aggressive, but who knows what you could find inside it..", 5, 1));
    getTarget("Backyard")->addItem(getTarget("Beetle"));

    // Creation of the exit between the backyard and the House
    addEntity(new Exit("HouseToBackyard", Direction::NORTH, static_cast<Room*>(getTarget("House")), static_cast<Room*>(getTarget("Backyard")), false, 1));
    getTarget("House")->addItem(getTarget("HouseToBackyard"));
    addEntity(new Exit("BackyardToHouse", Direction::SOUTH, static_cast<Room*>(getTarget("Backyard")), static_cast<Room*>(getTarget("House"))));
    getTarget("Backyard")->addItem(getTarget("BackyardToHouse"));

    // Creation of the key from the house to the frontyard
    addEntity(new Key("HouseKey", "a key to the front door of your House", 2));
    getTarget("Beetle")->addItem(getTarget("HouseKey"));


    /* FRONTYARD */
    // Creation of the Frontyard room south of the House
    addEntity(new Room("Frontyard", "the front of to house"));
    addEntity(new Armor("Hat", "a burnt hat to avoid sunburn.", 1, ArmorPart::HEAD));
    addEntity(new Weapon("Rock", "a rock perfect to smash bugs", 2, 0.05f));
    getTarget("Frontyard")->addItem(getTarget("Hat"));
    getTarget("Frontyard")->addItem(getTarget("Rock"));

    // Creation of the exits between house and frontyard
    addEntity(new Exit("HouseToFrontyard", Direction::SOUTH, static_cast<Room*>(getTarget("House")), static_cast<Room*>(getTarget("Frontyard")), false, 2));
    getTarget("House")->addItem(getTarget("HouseToFrontyard"));
    addEntity(new Exit("FrontyardToHouse", Direction::NORTH, static_cast<Room*>(getTarget("Frontyard")), static_cast<Room*>(getTarget("House"))));
    getTarget("Frontyard")->addItem(getTarget("FrontyardToHouse"));

    /* WOODS */
    // Creation of the Woods
    addEntity(new Room("Woods", "a forest with short but dense trees."));
    addEntity(new Creature("Dragonfly", "the largest you've ever seen. For some reason, every insect seems to be growing in size", 10, 2));
    getTarget("Woods")->addItem(getTarget("Dragonfly"));

    addEntity(new Weapon("Leg", "a large dragonfly leg that can be used to attack.", 2, 0.1f));
    getTarget("Dragonfly")->addItem(getTarget("Leg"));

    // Creation of the exits between Frontyard and Woods
    addEntity(new Exit("FrontyardToWoods", Direction::SOUTH, static_cast<Room*>(getTarget("Frontyard")), static_cast<Room*>(getTarget("Woods"))));
    getTarget("Frontyard")->addItem(getTarget("FrontyardToWoods"));
    addEntity(new Exit("WoodsToFrontyard", Direction::NORTH, static_cast<Room*>(getTarget("Woods")), static_cast<Room*>(getTarget("Frontyard"))));
    getTarget("Woods")->addItem(getTarget("WoodsToFrontyard"));

    
    /* DUNGEON */
    // Creation of the Dungeon
    addEntity(new Room("Dungeon", "a lightly illuminated dungeon with many dangers waiting for an easy prey."));
    addEntity(new Creature("Undead", "an undead prisoner with a sheathed longsword on his belt. Lucky you, without brains he doesn't know how to use it..", 10, 5, false));
    getTarget("Dungeon")->addItem(getTarget("Undead"));
    addEntity(new Weapon("Longsword", "a classic longsword used by knights, all now take by the Abyss.", 9, 0.2f));
    getTarget("Undead")->addItem(getTarget("Longsword"));
    addEntity(new Note("SecretNote", "'Dangers lurk in this dungeon, but if you are stupid enough to go deeper, and lucky enough to survive, you will find a secret entrance to the castle at the end.\nHowever if you want to reach it, make sure you are well equipped.'"));
    getTarget("Dungeon")->addItem(getTarget("SecretNote"));

    // Creation of exits between Dungeon and Woods
    addEntity(new Exit("WoodsToDungeon", Direction::WEST, static_cast<Room*>(getTarget("Woods")), static_cast<Room*>(getTarget("Dungeon"))));
    getTarget("Woods")->addItem(getTarget("WoodsToDungeon"));
    addEntity(new Exit("DungeonToWoods", Direction::EAST, static_cast<Room*>(getTarget("Dungeon")), static_cast<Room*>(getTarget("Woods"))));
    getTarget("Dungeon")->addItem(getTarget("DungeonToWoods"));


    /* DUNGEON B1 */
    // Creation of the Dungeon B1
    addEntity(new Room("DungeonBasement", "the darker parts of the dungeon. A dim light allows you to spot your foes, otherwise you would already be dead."));
    addEntity(new Creature("Demon", "an abominable beast from an older time. Given this name for its abominable hellish traits.", 17, 2));
    getTarget("DungeonBasement")->addItem(getTarget("Demon"));
    addEntity(new Weapon("Fangs", "demon fangs used as daggers with lower base damage but higher critical strike chance.", 8, 0.5f));
    getTarget("Demon")->addItem(getTarget("Fangs"));
    addEntity(new Creature("Vermin", "a disgusting, gigantic, vermin born of blood and beasts.", 15, 4));
    getTarget("DungeonBasement")->addItem(getTarget("Vermin"));

    // Creation of exits between DungeonBasement and Dungeon
    addEntity(new Exit("DungeonToDungeonBasement", Direction::DOWN, static_cast<Room*>(getTarget("Dungeon")), static_cast<Room*>(getTarget("DungeonBasement"))));
    getTarget("Dungeon")->addItem(getTarget("DungeonToDungeonBasement"));
    addEntity(new Exit("DungeonBasementToDungeon", Direction::UP, static_cast<Room*>(getTarget("DungeonBasement")), static_cast<Room*>(getTarget("Dungeon"))));
    getTarget("DungeonBasement")->addItem(getTarget("DungeonBasementToDungeon"));

    
    /* CASTLE CATACOMBS */
    // Accessible from Dungeon Basement via secret passage
    addEntity(new Room("CastleCatacombs", "a damp and suffocating catacomb beneath the castle. Burial niches are carved into the rock, the dead resting in uneasy silence. You found the secret passage mentioned in the note."));
    addEntity(new Creature("Wraith", "a translucent, shrieking wraith bound to these catacombs for eternity.", 35, 9, false));
    getTarget("CastleCatacombs")->addItem(getTarget("Wraith"));

    // Exits between DungeonBasement and CastleCatacombs
    addEntity(new Exit("DungeonBasementToCastleCatacombs", Direction::EAST, static_cast<Room*>(getTarget("DungeonBasement")), static_cast<Room*>(getTarget("CastleCatacombs"))));
    getTarget("DungeonBasement")->addItem(getTarget("DungeonBasementToCastleCatacombs"));
    addEntity(new Exit("CatacombsToDungeonBasement", Direction::WEST, static_cast<Room*>(getTarget("CastleCatacombs")), static_cast<Room*>(getTarget("DungeonBasement"))));
    getTarget("CastleCatacombs")->addItem(getTarget("CatacombsToDungeonBasement"));


    /* CASTLE ENTRANCE */
    addEntity(new Room("CastleEntrance", "a grand but decrepit entrance to the castle. The stone walls are cold and the air reeks of decay."));

    // Exits between CastleEntrance and Woods
    addEntity(new Exit("WoodsToCastleEntrance", Direction::EAST, static_cast<Room*>(getTarget("Woods")), static_cast<Room*>(getTarget("CastleEntrance"))));
    getTarget("Woods")->addItem(getTarget("WoodsToCastleEntrance"));
    addEntity(new Exit("CastleEntranceToWoods", Direction::WEST, static_cast<Room*>(getTarget("CastleEntrance")), static_cast<Room*>(getTarget("Woods"))));
    getTarget("CastleEntrance")->addItem(getTarget("CastleEntranceToWoods"));


    /* CASTLE */
    addEntity(new Room("Castle", "the main hall of the castle. Crumbling pillars line the path forward, and the air is thick with the stench of old blood."));
    addEntity(new Creature("Champion", "a towering undead champion, clad in heavy armor and wielding a massive axe. The last line of defense before the throne.", 40, 9, false));
    getTarget("Castle")->addItem(getTarget("Champion"));
    addEntity(new Weapon("Axe", "a massive battle axe wielded by the castle champion, still sharp enough to cleave stone.", 10, 0.25f));
    getTarget("Champion")->addItem(getTarget("Axe"));

    // Exits between CastleEntrance and Castle
    addEntity(new Exit("CastleEntranceToCastle", Direction::NORTH, static_cast<Room*>(getTarget("CastleEntrance")), static_cast<Room*>(getTarget("Castle"))));
    getTarget("CastleEntrance")->addItem(getTarget("CastleEntranceToCastle"));
    addEntity(new Exit("CastleToCastleEntrance", Direction::SOUTH, static_cast<Room*>(getTarget("Castle")), static_cast<Room*>(getTarget("CastleEntrance"))));
    getTarget("Castle")->addItem(getTarget("CastleToCastleEntrance"));

    // Exits between CastleCatacombs and Castle
    addEntity(new Exit("CastleCatacombsToCastle", Direction::UP, static_cast<Room*>(getTarget("CastleCatacombs")), static_cast<Room*>(getTarget("Castle"))));
    getTarget("CastleCatacombs")->addItem(getTarget("CastleCatacombsToCastle"));
    addEntity(new Exit("CastleToCastleCatacombs", Direction::DOWN, static_cast<Room*>(getTarget("Castle")), static_cast<Room*>(getTarget("CastleCatacombs"))));
    getTarget("Castle")->addItem(getTarget("CastleToCastleCatacombs"));


    /* CASTLE ROOFTOP */
    addEntity(new Room("CastleRooftop", "the first floor of the castle bleeds into the windswept rooftop above. Tattered banners hang from the battlements, and something watches from the shadows."));
    addEntity(new Creature("Knight", "a cursed knight still bound to his oath, armor rusted but sword arm strong.", 25, 1));
    getTarget("CastleRooftop")->addItem(getTarget("Knight"));
    addEntity(new Weapon("Mace", "a heavy iron mace stripped from a fallen castle guard.", 12, 0.15f));
    getTarget("Knight")->addItem(getTarget("Mace"));
    addEntity(new Creature("Gargoyle", "a living gargoyle, stone-skinned and ruthless, perched at the edge of the roof.", 40, 3, false));
    getTarget("CastleRooftop")->addItem(getTarget("Gargoyle"));

    // Exits between Castle and CastleRooftop
    addEntity(new Exit("CastleToCastleRooftop", Direction::UP, static_cast<Room*>(getTarget("Castle")), static_cast<Room*>(getTarget("CastleRooftop"))));
    getTarget("Castle")->addItem(getTarget("CastleToCastleRooftop"));
    addEntity(new Exit("CastleRooftopToCastle", Direction::DOWN, static_cast<Room*>(getTarget("CastleRooftop")), static_cast<Room*>(getTarget("Castle"))));
    getTarget("CastleRooftop")->addItem(getTarget("CastleRooftopToCastle"));


    /* THRONE ROOM */
    addEntity(new Room("ThroneRoom", "a vast throne room shrouded in shadow. At the far end sits a figure on a decayed throne — the source of everything that has gone wrong."));
    addEntity(new Creature("DarkLord", "the dark lord himself, a towering figure in black armor radiating malice. This is the final fight.", 60, 12, false));
    addEntity(new Note("WarningNote", "'You have come far, but this is where your journey ends.\nTurn back now, or face oblivion.'"));
    getTarget("ThroneRoom")->addItem(getTarget("DarkLord"));
    getTarget("ThroneRoom")->addItem(getTarget("WarningNote"));

    // Exits between CastleRooftop and ThroneRoom
    addEntity(new Exit("CastleRooftopToThroneRoom", Direction::NORTH, static_cast<Room*>(getTarget("CastleRooftop")), static_cast<Room*>(getTarget("ThroneRoom"))));
    getTarget("CastleRooftop")->addItem(getTarget("CastleRooftopToThroneRoom"));
    addEntity(new Exit("ThroneRoomToCastleRooftop", Direction::SOUTH, static_cast<Room*>(getTarget("ThroneRoom")), static_cast<Room*>(getTarget("CastleRooftop"))));
    getTarget("ThroneRoom")->addItem(getTarget("ThroneRoomToCastleRooftop"));
}