#include "World.h"

void World::initialize() {
    /* HOUSE */
    // Creation of the Player
    addEntity(new Player("Player", "the player character", 15, 2, true, EntityType::PLAYER));

    // Creation of the House and its contents
    addEntity(new Room("House", "a simple house for a simple person."));
    currentRoom = static_cast<Room*>(getTarget("House"));

    //  Creation of a Chest in the house with some items
    addEntity(new Entity("Chest", "an old chest that can contain a few items", EntityType::CONTAINER));
    addEntity(new Entity("Shirt", "a dirty shirt for handy labor"));
    addEntity(new Entity("Pants", "a pair of rugs some dare too call pants"));
    addEntity(new Weapon("Rock", "a rock perfect to smash bugs", 1, 0.05f));
    getTarget("Chest")->addItem(getTarget("Shirt"));
    getTarget("Chest")->addItem(getTarget("Pants"));
    getTarget("Chest")->addItem(getTarget("Rock"));
    getTarget("House")->addItem(getTarget("Chest"));

    // Creation of a key to the backyard and put it in the house chest
    addEntity(new Key("KeyToTheBackyard", "a key to the Backyard", 1));
    getTarget("Chest")->addItem(getTarget("KeyToTheBackyard"));


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
    addEntity(new Key("KeyToTheHouse", "a key to the front door of your House", 2));
    getTarget("Beetle")->addItem(getTarget("KeyToTheHouse"));


    /* FRONTYARD */
    // Creation of the Frontyard room south of the House
    addEntity(new Room("Frontyard", "the front of to house"));
    addEntity(new Entity("Hat", "a burnt hat to avoid sunburn."));
    getTarget("Frontyard")->addItem(getTarget("Hat"));

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
    addEntity(new Creature("Undead", "an undead prisoner with a sheathed longsword on his belt. Lucky you, without brains he doesn't know how to use it..", 10, 2, false));
    getTarget("Dungeon")->addItem(getTarget("Undead"));
    addEntity(new Weapon("Longsword", "a classic longsword used by knights, all now take by the Abyss.", 7, 0.2f));
    getTarget("Undead")->addItem(getTarget("Longsword"));
    addEntity(new Note("TaintedNote", "'Dangers lurk in this dungeon, but if you are stupid enough to go deeper, and lucky enough to survive, you will find a secret entrance to the castle at the end.\nHowever if you want to reach it, make sure you are well equipped.'"));
    getTarget("Dungeon")->addItem(getTarget("TaintedNote"));

    // Creation of exits between Dungeon and Woods
    addEntity(new Exit("WoodsToDungeon", Direction::NORTH, static_cast<Room*>(getTarget("Woods")), static_cast<Room*>(getTarget("Dungeon"))));
    getTarget("Woods")->addItem(getTarget("WoodsToDungeon"));
    addEntity(new Exit("DungeonToWoods", Direction::SOUTH, static_cast<Room*>(getTarget("Dungeon")), static_cast<Room*>(getTarget("Woods"))));
    getTarget("Dungeon")->addItem(getTarget("DungeonToWoods"));

    /* DUNGEON B1 */
    // Creation of the Dungeon B1
    addEntity(new Room("DungeonBasement", "the darker parts of the dungeon. A dim light allows you to spot your foes, otherwise you would already be dead."));
    addEntity(new Creature("Demon", "an abominable beast from an older time. Given this name for its abominable hellish traits.", 20, 3, false));
    getTarget("DungeonBasement")->addItem(getTarget("Demon"));
    addEntity(new Creature("Vermin", "a disgusting, gigantic, vermin born of blood and beasts.", 15, 2, false));
    getTarget("DungeonBasement")->addItem(getTarget("Vermin"));
    getTarget("Player")->addItem(getTarget("Longsword"));
    currentRoom = static_cast<Room*>(getTarget("DungeonBasement"));
}