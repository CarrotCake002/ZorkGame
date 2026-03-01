#include "World.h"

World::World() {
    printDialogue(ZORK_ASCII, 0);
	printDialogue(INTRO, 0);
    std::cout << std::endl;

    addEntity(new Player("Player", "the player character", 20, 2, EntityType::PLAYER));
    addEntity(new Weapon("Stick", "a stick to attack enemies with", 2));
    getTarget("Player")->addItem(getTarget("Stick"));

	// Creation of the starting room and its content
	addEntity(new Room("Starting Room", "a small room with a door to the north"));
	currentRoom = static_cast<Room*>(getTarget("Starting Room"));

    addEntity(new Creature("NPC", "a small goofy ennemy", 10, 1));
    addEntity(new Weapon("Rock", "a rock that deals damage with every hit", 1));
	addEntity(new Entity("Coin", "a shiny gold coin that looks valuable"));
	addEntity(new Entity("Key", "a small key that might open a door"));
    getTarget("NPC")->addItem(getTarget("Rock"));
	getTarget("NPC")->addItem(getTarget("Coin"));
	getTarget("NPC")->addItem(getTarget("Key"));
	getTarget("Starting Room")->addItem(getTarget("NPC"));

    addEntity(new Entity("Bag", "a small bag that can contain a few items", EntityType::CONTAINER));
    addEntity(new Entity("Hat", "a cool hat for daring fashion enjoyers"));
    addEntity(new Entity("Shirt", "an elegant shirt for formal events"));
    addEntity(new Entity("Pants", "nice pants that would pair perfectly with a shirt"));
    getTarget("Bag")->addItem(getTarget("Hat"));
    getTarget("Bag")->addItem(getTarget("Shirt"));
    getTarget("Bag")->addItem(getTarget("Pants"));
    getTarget("Starting Room")->addItem(getTarget("Bag"));

	// Creation of the north room and its content
	addEntity(new Room("North Room", "a room to the north of the starting room"));
	addEntity(new Creature("Guard", "a strong guard that looks like it doesn't want you to enter the north room", 20, 5));
	getTarget("North Room")->addItem(getTarget("Guard"));

	// Creation of the exit between the starting room and the north room
	addEntity(new Exit("StartToNorth", Direction::NORTH, static_cast<Room*>(getTarget("Starting Room")), static_cast<Room*>(getTarget("North Room"))));
	getTarget("Starting Room")->addItem(getTarget("StartToNorth"));
	addEntity(new Exit("NorthToStart", Direction::SOUTH, static_cast<Room*>(getTarget("North Room")), static_cast<Room*>(getTarget("Starting Room"))));
	getTarget("North Room")->addItem(getTarget("NorthToStart"));
}

World::~World() {
	for (auto entity : entities) {
        if (entity != nullptr)
            delete entity;
    }
}

Entity* World::getTarget(std::string target) const {
    target = toLower(target);
    std::string entityName;
    for (auto& entity : entities) {
		entityName = entity->getName();
        if (toLower(entityName) == target) {
            return entity;
        }
    }
    return nullptr;
}

int World::moveToRoom(Entity* room) {
    if (room == nullptr || room->getType() != EntityType::ROOM) {
        printDialogue("You can't go there!\n");
        return 1;
    }
	currentRoom = nullptr;
    currentRoom = static_cast<Room*>(room);
    printDialogue("You are now in the " + room->getName() + ".\n");
    return 0;
}

int World::handleCmdDropErrors(std::string target, Entity* eTarget) const {
    if (eTarget == nullptr) {
        printDialogue("You don't have " + target + " in your inventory.\n");
        return 1;
    }
    return 0;
}

int World::handleCmdTakeErrors(std::string target, Entity* eTarget) const {
    if (eTarget == nullptr) {
        printDialogue("There is no " + target + " here.\n");
        return 1;
    }
    else if (eTarget->getType() == EntityType::PLAYER) {
        printDialogue({ { "There is no", 20 }, { "...", 300}, {"", 2000}, {"\n\n", 0}, { "Wait", 70 }, {"", 1500}, {", what?", 70}, {"", 2000}, {"\n\n", 0}, {"You can't take yourself!", 30}, {"", 1000}, {"\n", 0}, {"Why would you even try to take yourself??", 30}, {"", 2500}, {"\n\n", 0}, {"Ooh...", 400}, {" You silly game testers...", 100}, {"", 3000}, {"\n", 0} });
        return 1;
    }
    else if (eTarget->getType() == EntityType::CREATURE) {
        printDialogue("You can't take a creature! You can only take items.\n");
        return 1;
    }
    else if (eTarget->getType() != EntityType::ITEM && eTarget->getType() != EntityType::WEAPON){
        printDialogue("You can't take that... You can only take items!\n");
        return 1;
    }
    return 0;
}

int World::handleCmdTakeFromContainerErrors(std::string target, Entity* eTarget, std::string container, Entity* eContainer) const {
    if (eContainer == nullptr) {
        printDialogue("There is no " + container + " here.\n");
        return 1;
    }
    if (eContainer->getType() == EntityType::CREATURE) {
        printDialogue("Stealing from other creatures will not be tolerated!\n");
        return 1;
    }
    if (eContainer->getType() == EntityType::PLAYER) {
        printDialogue("I mean uuh... sure, why not?\n\n\"You take an item from your inventory and put it back\"\n\nI mean come on you really think I'm going to risk bugs in my game to handle that.\n\nJUST STOP TRYING TO CRASH MY GAME AND PLAY\n");
        return 1;
    }
    if (eContainer->getType() != EntityType::CONTAINER) {
        printDialogue("You can't take something from there! You can only take items from containers!\n");
        return 1;
    }
    if (!eContainer->hasItem(target)) {
        printDialogue("There is no " + target + " in the " + container + ".\n");
        return 1;
    }
    return 0;
}

int World::handleCmdPutErrors(std::string target, Entity* eTarget, std::string container, Entity* eContainer) const {
    if (eContainer == nullptr) {
        printDialogue("There is no " + container + " here.\n");
        return 1;
    }
    if (eContainer->getType() == EntityType::CREATURE) {
        printDialogue("Why are you even trying to give an item to a creature??\nI will not allow this!\n");
        return 1;
    }
    if (eContainer->getType() != EntityType::CONTAINER) {
        printDialogue("You can't put something in there! You can only put items in containers!\n");
        return 1;
    }
    if (eTarget == nullptr) {
        printDialogue("There is no " + target + " in your inventory!\n");
        return 1;
    }
    return 0;
}

int World::handleCmdWalkErrors(Exit* exit) const {
    if (exit == nullptr) {
        printDialogue("You bumped yourself into an object. Pick a valid direction!\n");
        return 1;
    }
    return 0;
}

int World::handleAttack(Entity* target, Entity* eWeapon, std::string weapon) const {
    if (target == nullptr) {
        printDialogue("There is no such creature here to attack!\n");
        return 1;
    }
    if (eWeapon == nullptr && !weapon.empty()) {
        printDialogue("You don't have that weapon in your inventory!\n");
        return 1;
    }
	if (eWeapon != nullptr && eWeapon->getType() != EntityType::WEAPON) {
        printDialogue("You can't attack with that! You can only attack with weapons!\n");
        return 1;
    }
	if (eWeapon != nullptr && target->getType() != EntityType::CREATURE) {
        printDialogue("You can't attack that! You can only attack creatures!\n");
        return 1;
    }
    return 0;
}

bool checkConjunction(std::string action, std::string conjunction) {
    if (action == "take" && conjunction == "from") {
        return true;
    }
    if (action == "put" && (conjunction == "in" || conjunction == "into")) {
        return true;
    }
    if (action == "attack" && (conjunction == "with" || conjunction == "using" || conjunction.empty())) {
        return true;
    }
    printDialogue("Sorry, I don't know what " + conjunction + " means.\n");
    return false;
}

void World::cmdHelp(void) const {
    printDialogue(HELP, 0);
}

void World::cmdLook(void) const {
    printDialogue("You look around and see:\n");
    for (auto &entity : currentRoom->getContains()) {
        if (entity->getType() == EntityType::EXIT)
			static_cast<Exit*>(entity)->display();
        else
            entity->display();
    }
}

void World::cmdInventory(void) const {
    Player* player = static_cast<Player*>(getTarget("Player"));

    if (player->getContains().size() < 1) {
        printDialogue("Your inventory is empty.\n");
        return;
    }
    printDialogue("You check your inventory and find:");
    player->printContains();
    printDialogue("\n");
}

int World::cmdDrop(std::string target) {
    Player* player = static_cast<Player*>(getTarget("Player"));
    Entity* entity = player->removeItem(target);

    if (handleCmdDropErrors(target, entity) != 0)
        return 1;
    currentRoom->addItem(entity);
    printDialogue("You drop the " + entity->getName() + ".\n");
    return 0;
}

int World::cmdTake(std::string target) {
    Player* player = static_cast<Player*>(getTarget("Player"));
    Entity* entity = currentRoom->getItem(target);

    if (handleCmdTakeErrors(target, entity) != 0)
		return 1;
    currentRoom->removeItem(target);
    player->addItem(entity);
    printDialogue("You take the " + entity->getName() + ".\n");
    return 0;
}

int World::cmdTakeFromContainer(std::string target, std::string container) {
    Player* player = static_cast<Player*>(getTarget("Player"));
    Entity* entity = currentRoom->getItem(target);
    Entity* eContainer = currentRoom->getItem(container);

    if (handleCmdTakeFromContainerErrors(target, entity, container, eContainer) != 0)
		return 1;
    entity = eContainer->removeItem(target);
    player->addItem(entity);
    printDialogue("You take the " + entity->getName() + " from the " + eContainer->getName() + ".\n");
    return 0;
}

int World::cmdPut(std::string target, std::string container) {
    Player* player = static_cast<Player*>(getTarget("Player"));
    Entity* eTarget = player->getItem(target);
    Entity* eContainer = currentRoom->getItem(container);

	if (handleCmdPutErrors(target, eTarget, container, eContainer) != 0)
		return 1;
    player->removeItem(target);
	eContainer->addItem(eTarget);
    printDialogue("You put the " + eTarget->getName() + " in the " + eContainer->getName() + ".\n");
    return 0;
}

int World::cmdWalk(std::string target) {
	Direction dir = Exit::strToDirection(target);
    Exit* exit = currentRoom->getExit(dir);

    if (handleCmdWalkErrors(exit) != 0)
        return 1;
	currentRoom = exit->getDestination();
	printDialogue("You walk " + target + " and enter the " + currentRoom->getName() + ".\n");
    return 0;
}

int World::cmdAttack(std::string target, std::string weapon) {
    Player* player = static_cast<Player*>(getTarget("Player"));
    Entity* eTarget = currentRoom->getItem(target);
    Entity* eWeapon = player->getItem(weapon);
    Creature* ennemy = nullptr;

    if (handleAttack(eTarget, eWeapon, weapon) != 0)
        return 1;
	ennemy = static_cast<Creature*>(eTarget);
    player->attack(ennemy, static_cast<Weapon*>(eWeapon));
    if (!ennemy->isAlive()) {
		ennemy->die(currentRoom);
        return 0;
    }
    ennemy->setAggro(true);
    return 0;
}

void World::ennemyAttack(void) {
    auto entities = currentRoom->getContains();
    Creature* ennemy = nullptr;

    for (auto& entity : entities) {
        if (entity->getType() == EntityType::CREATURE) {
            ennemy = static_cast<Creature*>(entity);

            if (ennemy->isAggro()) {
                ennemy->attack(static_cast<Player*>(getTarget("Player")), ennemy->getWeapon());
            }
        }
    }
}

int World::handleAction(std::string action, std::string target, std::string conjunction, std::string container) {
	if (action == "quit" && target.empty()) {
        printDialogue("Thanks for playing!\n");
        quit = true;
        return 1;
    }
    else if (action == "look" && target.empty()) {
        cmdLook();
    }
    else if ((action == "inventory" || action == "i") && target.empty()) {
        cmdInventory();
    }
    else if (action == "help" && target.empty()) {
        cmdHelp();
    }
    else if (action == "drop" && conjunction.empty()) {
        cmdDrop(target);
    }
    else if (action == "take" && conjunction.empty()) {
		cmdTake(target);
    }
    else if (action == "take" && !conjunction.empty()) {
        if (!checkConjunction(action, conjunction))
            return 0;
		cmdTakeFromContainer(target, container);
    }
    else if (action == "put" && !conjunction.empty()) {
        if (!checkConjunction(action, conjunction))
            return 0;
		cmdPut(target, container);
    }
    else if (action == "walk" && conjunction.empty()) {
        cmdWalk(target);
    }
    else if (action == "attack") {
        if (!checkConjunction(action, conjunction))
            return 0;
        cmdAttack(target, container);
	}
    else {
        printDialogue("Sorry, I did not understand your action.\n");
    }
    if (action != "help" && action != "look" && action != "inventory" && action != "i") {
        ennemyAttack();
    }
    return 0;
}

int World::handleCommand(std::string command) {
    std::istringstream iss(command);
    std::string action, target, conjunction, container;

    iss >> action >> target >> conjunction >> container;
    if (handleAction(toLower(action), toLower(target), toLower(conjunction), toLower(container)) != 0) {
		return 1;
    }
    return 0;
}

int World::parseCommands(void) {
    std::string command;

    while (commands.size() > 0) {
        command = commands.front();
        commands.erase(commands.begin());
        if (handleCommand(command) != 0)
			return 1;
    }
    return 0;
}

int World::splitCommands(std::string input) {
    std::istringstream iss(input);
    std::string line;

    while (std::getline(iss, line, ';')) {
		commands.push_back(line);
    }    
    return 0;
}

int World::getInput(void) {
    std::string input;

    std::cout << "\x1b[32m" << " > " << "\x1b[0m";
    std::getline(std::cin, input);
    if (splitCommands(input) != 0)
        return 1;
	if (parseCommands() != 0)
        return 1;
    return 0;
}
