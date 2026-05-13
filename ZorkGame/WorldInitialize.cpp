#include "World.h"

void World::initialize() {
    /* HOUSE */
    // Creation of the Player
    addEntity(new Player("Player", "the player character", 15, 1, true, EntityType::PLAYER));

    // Creation of the House and its contents
    Room* house = new Room("House", "a simple house for a simple person.");
    currentRoom = house;
    addEntity(house);

    // Creation of a Chest in the house with some items
    Entity* chest = new Entity("Chest", "an old chest that can contain a few items", EntityType::CONTAINER);
    Armor* shirt = new Armor("Shirt", "a dirty shirt for handy labor that will slightly protect you", 1, ArmorPart::BODY);
    Armor* pants = new Armor("Pants", "a pair of rugs some dare too call pants", 1, ArmorPart::LEGS);
    Key* backyardKey = new Key("BackyardKey", "a key to the Backyard", 1);

    house->addItem(chest);
    chest->addItem(shirt);
    chest->addItem(pants);
    chest->addItem(backyardKey);

    addEntity(chest);
    addEntity(shirt);
    addEntity(pants);
    addEntity(backyardKey);


    /* BACKYARD */
    // Creation of the Backyard and its contents
    Room* backyard = new Room("Backyard", "the backyard to your house. You have heard creatures festering from time to time...");
    Creature* beetle = new Creature("Beetle", "a large beetle. It doesn't look aggressive, but who knows what you could find inside it..", 3, 1);
    Key* houseKey = new Key("HouseKey", "a key to the front door of your House", 2);

    backyard->addItem(beetle);
    beetle->addItem(houseKey);

    addEntity(backyard);
    addEntity(beetle);
    addEntity(houseKey);

    // Creation of exits between Backyard and House
    Exit* houseToBackyard = new Exit("HouseToBackyard", Direction::NORTH, house, backyard, false, 1);
    Exit* backyardToHouse = new Exit("BackyardToHouse", Direction::SOUTH, backyard, house);

    house->addItem(houseToBackyard);
    backyard->addItem(backyardToHouse);

    addEntity(houseToBackyard);
    addEntity(backyardToHouse);


    /* FRONTYARD */
    // Creation of the Frontyard room south of the House
    Room* frontyard = new Room("Frontyard", "the front of to house");
    Armor* hat = new Armor("Hat", "a burnt hat to avoid sunburn.", 1, ArmorPart::HEAD);
    Weapon* rock = new Weapon("Rock", "a rock perfect to smash bugs", 2, 0.05f);

    frontyard->addItem(hat);
    frontyard->addItem(rock);

    addEntity(frontyard);
    addEntity(hat);
    addEntity(rock);

    // Creation of exits between House and Frontyard
    Exit* houseToFrontyard = new Exit("HouseToFrontyard", Direction::SOUTH, house, frontyard, false, 2);
    Exit* frontyardToHouse = new Exit("FrontyardToHouse", Direction::NORTH, frontyard, house);

    house->addItem(houseToFrontyard);
    frontyard->addItem(frontyardToHouse);

    addEntity(houseToFrontyard);
    addEntity(frontyardToHouse);


    /* WOODS */
    // Creation of the Woods and its contents
    Room* woods = new Room("Woods", "a forest with short but dense trees.");
    Creature* dragonfly = new Creature("Dragonfly", "the largest you've ever seen. For some reason, every insect seems to be growing in size", 6, 2);
    Weapon* leg = new Weapon("Leg", "a large dragonfly leg that can be used to attack.", 4, 0.1f);

    woods->addItem(dragonfly);
    dragonfly->equip(leg);

    addEntity(woods);
    addEntity(dragonfly);
    addEntity(leg);

    // Creation of exits between Frontyard and Woods
    Exit* frontyardToWoods = new Exit("FrontyardToWoods", Direction::SOUTH, frontyard, woods);
    Exit* woodsToFrontyard = new Exit("WoodsToFrontyard", Direction::NORTH, woods, frontyard);

    frontyard->addItem(frontyardToWoods);
    woods->addItem(woodsToFrontyard);

    addEntity(frontyardToWoods);
    addEntity(woodsToFrontyard);


    /* DUNGEON */
    // Creation of the Dungeon and its contents
    Room* dungeon = new Room("Dungeon", "a lightly illuminated dungeon with many dangers waiting for an easy prey.");
    Creature* undead = new Creature("Undead", "an undead prisoner with a sheathed longsword on his belt. Lucky you, without brains he doesn't know how to use it..", 10, 5, false);
    Weapon* sword = new Weapon("Sword", "a classic longsword used by knights, all now take by the Abyss.", 9, 0.2f);
    Note* secretNote = new Note("SecretNote", "'Dangers lurk in this dungeon, but if you are stupid enough to go deeper, and lucky enough to survive, you will find a secret entrance to the castle at the end.\nHowever if you want to reach it, make sure you are well equipped.'");

    dungeon->addItem(undead);
    dungeon->addItem(secretNote);
    undead->addItem(sword);

    addEntity(dungeon);
    addEntity(undead);
    addEntity(sword);
    addEntity(secretNote);

    // Creation of exits between Woods and Dungeon
    Exit* woodsToDungeon = new Exit("WoodsToDungeon", Direction::WEST, woods, dungeon);
    Exit* dungeonToWoods = new Exit("DungeonToWoods", Direction::EAST, dungeon, woods);

    woods->addItem(woodsToDungeon);
    dungeon->addItem(dungeonToWoods);

    addEntity(woodsToDungeon);
    addEntity(dungeonToWoods);


    /* DUNGEON BASEMENT */
    // Creation of the Dungeon Basement and its contents
    Room* dungeonBasement = new Room("DungeonBasement", "the darker parts of the dungeon. A dim light allows you to spot your foes, otherwise you would already be dead.");
    Creature* demon = new Creature("Demon", "an abominable beast from an older time. Given this name for its abominable hellish traits.", 17, 2);
    Weapon* fangs = new Weapon("Fangs", "demon fangs used as daggers with lower base damage but higher critical strike chance.", 8, 0.5f);
    Creature* vermin = new Creature("Vermin", "a disgusting, gigantic, vermin born of blood and beasts.", 15, 4);

    dungeonBasement->addItem(demon);
    dungeonBasement->addItem(vermin);
    demon->addItem(fangs);

    addEntity(dungeonBasement);
    addEntity(demon);
    addEntity(fangs);
    addEntity(vermin);

    // Creation of exits between Dungeon and Dungeon Basement
    Exit* dungeonToDungeonBasement = new Exit("DungeonToDungeonBasement", Direction::DOWN, dungeon, dungeonBasement);
    Exit* dungeonBasementToDungeon = new Exit("DungeonBasementToDungeon", Direction::UP, dungeonBasement, dungeon);

    dungeon->addItem(dungeonToDungeonBasement);
    dungeonBasement->addItem(dungeonBasementToDungeon);

    addEntity(dungeonToDungeonBasement);
    addEntity(dungeonBasementToDungeon);


    /* CASTLE CATACOMBS */
    // Accessible from Dungeon Basement via secret passage
    Room* castleCatacombs = new Room("CastleCatacombs", "a damp and suffocating catacomb beneath the castle. Burial niches are carved into the rock, the dead resting in uneasy silence. You found the secret passage mentioned in the note.");
    Creature* wraith = new Creature("Wraith", "a translucent, shrieking wraith bound to these catacombs for eternity.", 35, 9, false);

    castleCatacombs->addItem(wraith);

    addEntity(castleCatacombs);
    addEntity(wraith);

    // Creation of exits between Dungeon Basement and Castle Catacombs
    Exit* dungeonBasementToCastleCatacombs = new Exit("DungeonBasementToCastleCatacombs", Direction::EAST, dungeonBasement, castleCatacombs);
    Exit* catacombsToDungeonBasement = new Exit("CatacombsToDungeonBasement", Direction::WEST, castleCatacombs, dungeonBasement);

    dungeonBasement->addItem(dungeonBasementToCastleCatacombs);
    castleCatacombs->addItem(catacombsToDungeonBasement);

    addEntity(dungeonBasementToCastleCatacombs);
    addEntity(catacombsToDungeonBasement);


    /* CASTLE ENTRANCE */
    // Creation of the Castle Entrance
    Room* castleEntrance = new Room("CastleEntrance", "a grand but decrepit entrance to the castle. The stone walls are cold and the air reeks of decay.");

    addEntity(castleEntrance);

    // Creation of exits between Woods and Castle Entrance
    Exit* woodsToCastleEntrance = new Exit("WoodsToCastleEntrance", Direction::EAST, woods, castleEntrance);
    Exit* castleEntranceToWoods = new Exit("CastleEntranceToWoods", Direction::WEST, castleEntrance, woods);

    woods->addItem(woodsToCastleEntrance);
    castleEntrance->addItem(castleEntranceToWoods);

    addEntity(woodsToCastleEntrance);
    addEntity(castleEntranceToWoods);


    /* CASTLE */
    // Creation of the Castle and its contents
    Room* castle = new Room("Castle", "the main hall of the castle. Crumbling pillars line the path forward, and the air is thick with the stench of old blood.");
    Creature* champion = new Creature("Champion", "a towering undead champion, clad in heavy armor and wielding a massive axe. The last line of defense before the throne.", 40, 9, false);
    Weapon* axe = new Weapon("Axe", "a massive battle axe wielded by the castle champion, still sharp enough to cleave stone.", 10, 0.25f);

    castle->addItem(champion);
    champion->addItem(axe);

    addEntity(castle);
    addEntity(champion);
    addEntity(axe);

    // Creation of exits between Castle Entrance and Castle
    Exit* castleEntranceToCastle = new Exit("CastleEntranceToCastle", Direction::NORTH, castleEntrance, castle);
    Exit* castleToCastleEntrance = new Exit("CastleToCastleEntrance", Direction::SOUTH, castle, castleEntrance);

    castleEntrance->addItem(castleEntranceToCastle);
    castle->addItem(castleToCastleEntrance);

    addEntity(castleEntranceToCastle);
    addEntity(castleToCastleEntrance);

    // Creation of exits between Castle Catacombs and Castle
    Exit* castleCatacombsToCastle = new Exit("CastleCatacombsToCastle", Direction::UP, castleCatacombs, castle);
    Exit* castleToCastleCatacombs = new Exit("CastleToCastleCatacombs", Direction::DOWN, castle, castleCatacombs);

    castleCatacombs->addItem(castleCatacombsToCastle);
    castle->addItem(castleToCastleCatacombs);

    addEntity(castleCatacombsToCastle);
    addEntity(castleToCastleCatacombs);


    /* CASTLE ROOFTOP */
    // Creation of the Castle Rooftop and its contents
    Room* castleRooftop = new Room("CastleRooftop", "the first floor of the castle bleeds into the windswept rooftop above. Tattered banners hang from the battlements, and something watches from the shadows.");
    Creature* knight = new Creature("Knight", "a cursed knight still bound to his oath, armor rusted but sword arm strong.", 25, 1);
    Weapon* mace = new Weapon("Mace", "a heavy iron mace stripped from a fallen castle guard.", 12, 0.15f);
    Creature* gargoyle = new Creature("Gargoyle", "a living gargoyle, stone-skinned and ruthless, perched at the edge of the roof.", 40, 3, false);

    castleRooftop->addItem(knight);
    castleRooftop->addItem(gargoyle);
    knight->addItem(mace);

    addEntity(castleRooftop);
    addEntity(knight);
    addEntity(mace);
    addEntity(gargoyle);

    // Creation of exits between Castle and Castle Rooftop
    Exit* castleToCastleRooftop = new Exit("CastleToCastleRooftop", Direction::UP, castle, castleRooftop);
    Exit* castleRooftopToCastle = new Exit("CastleRooftopToCastle", Direction::DOWN, castleRooftop, castle);

    castle->addItem(castleToCastleRooftop);
    castleRooftop->addItem(castleRooftopToCastle);

    addEntity(castleToCastleRooftop);
    addEntity(castleRooftopToCastle);


    /* THRONE ROOM */
    // Creation of the Throne Room and its contents
    Room* throneRoom = new Room("ThroneRoom", "a vast throne room shrouded in shadow. At the far end sits a figure on a decayed throne — the source of everything that has gone wrong.");
    Creature* darkLord = new Creature("DarkLord", "the dark lord himself, a towering figure in black armor radiating malice. This is the final fight.", 60, 12, false);
    Note* warningNote = new Note("WarningNote", "'You have come far, but this is where your journey ends.\nTurn back now, or face oblivion.'");

    throneRoom->addItem(darkLord);
    throneRoom->addItem(warningNote);

    addEntity(throneRoom);
    addEntity(darkLord);
    addEntity(warningNote);

    // Creation of exits between Castle Rooftop and Throne Room
    Exit* castleRooftopToThroneRoom = new Exit("CastleRooftopToThroneRoom", Direction::NORTH, castleRooftop, throneRoom);
    Exit* throneRoomToCastleRooftop = new Exit("ThroneRoomToCastleRooftop", Direction::SOUTH, throneRoom, castleRooftop);

    castleRooftop->addItem(castleRooftopToThroneRoom);
    throneRoom->addItem(throneRoomToCastleRooftop);

    addEntity(castleRooftopToThroneRoom);
    addEntity(throneRoomToCastleRooftop);

    saveGame();
}