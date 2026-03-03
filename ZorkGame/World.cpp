#include "World.h"

World::World() {
    // Creation of the Player
    addEntity(new Player("Player", "the player character", 15, 2, EntityType::PLAYER));

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



	// Creation of the Backyard and its content
	addEntity(new Room("Backyard", "the backyard to your house. You have heard creatures festering from time to time..."));
	addEntity(new Creature("Beetle", "a large beetle. It doesn't look aggressive, but who knows what you could find inside it...", 5, 1));
	getTarget("Backyard")->addItem(getTarget("Beetle"));

    // Creation of the exit between the backyard and the House
    addEntity(new Exit("HouseToBackyard", Direction::NORTH, static_cast<Room*>(getTarget("House")), static_cast<Room*>(getTarget("Backyard")), false, 1));
    getTarget("House")->addItem(getTarget("HouseToBackyard"));
	addEntity(new Exit("BackyardToHouse", Direction::SOUTH, static_cast<Room*>(getTarget("Backyard")), static_cast<Room*>(getTarget("House"))));
	getTarget("Backyard")->addItem(getTarget("BackyardToHouse"));

    // Creation of the key from the house to the frontyard
    addEntity(new Key("KeyToTheHouse", "a key to the front door of your House", 2));
    getTarget("Beetle")->addItem(getTarget("KeyToTheHouse"));
    


    // Creation of the Frontyard room south of the House
    addEntity(new Room("Frontyard", "the front of to house"));
    addEntity(new Entity("Hat", "a burnt hat to avoid sunburn."));
    getTarget("Frontyard")->addItem(getTarget("Hat"));

    // Creation of the exits between house and frontyard
    addEntity(new Exit("HouseToFrontyard", Direction::SOUTH, static_cast<Room*>(getTarget("House")), static_cast<Room*>(getTarget("Frontyard")), false, 2));
    getTarget("House")->addItem(getTarget("HouseToFrontyard"));
    addEntity(new Exit("FrontyardToHouse", Direction::NORTH, static_cast<Room*>(getTarget("Frontyard")), static_cast<Room*>(getTarget("House"))));
    getTarget("Frontyard")->addItem(getTarget("FrontyardToHouse"));
    

    // Creation of the Woods
    addEntity(new Room("Woods", "a forest with short but dense trees."));
    addEntity(new Creature("Dragonfly", " the largest you've ever seen. For some reason, every insect seems to be growing in size.", 10, 2));
    getTarget("Woods")->addItem(getTarget("Dragonfly"));

    addEntity(new Weapon("Leg", "a large dragonfly leg that can be used to attack.", 2, 0.1f));
    getTarget("Dragonfly")->addItem(getTarget("Leg"));

    // Creation of the exits between Frontyard and Woods
    addEntity(new Exit("FrontyardToWoods", Direction::SOUTH, static_cast<Room*>(getTarget("Frontyard")), static_cast<Room*>(getTarget("Woods"))));
    getTarget("Frontyard")->addItem(getTarget("FrontyardToWoods"));
    addEntity(new Exit("WoodsToFrontyard", Direction::NORTH, static_cast<Room*>(getTarget("Woods")), static_cast<Room*>(getTarget("Frontyard"))));
    getTarget("Woods")->addItem(getTarget("WoodsToFrontyard"));
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
    else if (eTarget->getType() != EntityType::ITEM && eTarget->getType() != EntityType::WEAPON && eTarget->getType() != EntityType::KEY){
        printDialogue("You can't take that... You can only take items!\n");
        return 1;
    }
    return 0;
}

// handle this errors with containers and targets
int World::handleCmdTakeFromContainerErrors(std::string target, Entity* eTarget, std::string container, Entity* eContainer) const {
    if (eContainer == nullptr) {
        printDialogue("There is no " + container + " here.\n");
        return 1;
    }
    if (eTarget == nullptr) {
        printDialogue("There is no " + target + "in the " + TEXT_COLOR_YELLOW + container + TEXT_COLOR_RESET + ".\n");
        return 1;
    }
    if (eContainer->getType() == EntityType::CREATURE) {
        printDialogue("Stealing from other creatures will not be tolerated!\n");
        return 1;
    }
    if (eTarget->getType() == EntityType::PLAYER) {
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

bool World::checkConjunction(std::string action, std::string conjunction) const {
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
    Player* player = getPlayer();

    if (player->getContains().size() < 1) {
        printDialogue("Your inventory is empty.\n");
        return;
    }
    printDialogue("You check your inventory and find:");
    player->printContains();
    printDialogue("\n");
}

int World::cmdDrop(std::string target) {
    Player* player = getPlayer();
    Entity* entity = player->removeItem(target);

    if (handleCmdDropErrors(target, entity) != 0)
        return 1;
    currentRoom->addItem(entity);
    printDialogue("You drop the " + entity->getName() + ".\n");
    return 0;
}

int World::cmdTake(std::string target) {
    Player* player = getPlayer();
    Entity* entity = currentRoom->getItem(target);

    if (handleCmdTakeErrors(target, entity) != 0)
		return 1;
    currentRoom->removeItem(target);
    player->addItem(entity);
    printDialogue("You take the " + entity->getName() + ".\n");
    return 0;
}

int World::cmdTakeFromContainer(std::string target, std::string container) {
    Player* player = getPlayer();
    Entity* eContainer = currentRoom->getItem(container);
    Entity* entity = nullptr;

    if (eContainer != nullptr)
        entity = eContainer->getItem(target);
    if (handleCmdTakeFromContainerErrors(target, entity, container, eContainer) != 0 || eContainer == nullptr || entity == nullptr)
		return 1;
    eContainer->removeItem(target);
    player->addItem(entity);
    printDialogue("You take the " + entity->getName() + " from the " + eContainer->getName() + ".\n");
    return 0;
}

int World::cmdPut(std::string target, std::string container) {
    Player* player = getPlayer();
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
    if (exit->isLocked() && !exit->openDoor(getPlayer()->getContains())) {
        return 1;
    }
	currentRoom = exit->getDestination();
	printDialogue("You walk " + target + " and enter the " + TEXT_COLOR_CYAN + currentRoom->getName() + TEXT_COLOR_RESET + ".\n");

    return 0;
}

int World::cmdAttack(std::string target, std::string weapon) {
    Player* player = getPlayer();
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
    if (!ennemy->isAggro())
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
                ennemy->attack(getPlayer(), ennemy->getWeapon());
            }
        }
    }
}

void World::displayDeathScreen() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, deathScreens.size() - 1);

    printDialogue(deathScreens[dist(gen)] + "\n");
    printDialogue("Use 'reset' to restart or 'quit' to close the game.\n");
}

int World::handleAction(std::string action, std::string target, std::string conjunction, std::string container) {
	if (action == "quit" && target.empty()) {
        printDialogue("Thanks for playing!\n");
        quit = true;
        return 1;
    }
    else if (action == "look" && target.empty()) {
        cmdLook();
		return 1;
    }
    else if ((action == "inventory" || action == "i") && target.empty()) {
        cmdInventory();
        return 1;
    }
    else if (action == "help" && target.empty()) {
        cmdHelp();
        return 1;
    }
    else if (action == "drop" && conjunction.empty()) {
        cmdDrop(target);
    }
    else if (action == "take" && conjunction.empty()) {
		cmdTake(target);
    }
    else if (action == "take" && !conjunction.empty()) {
        if (!checkConjunction(action, conjunction))
            return 1;
		cmdTakeFromContainer(target, container);
    }
    else if (action == "put" && !conjunction.empty()) {
        if (!checkConjunction(action, conjunction))
            return 1;
		cmdPut(target, container);
    }
    else if (action == "walk" && conjunction.empty()) {
        cmdWalk(target);
    }
    else if (action == "attack") {
        if (!checkConjunction(action, conjunction))
            return 1;
        cmdAttack(target, container);
	}
	else if (handleSecretCommands(toLower(action), toLower(target), toLower(conjunction), toLower(container)) == 0) {
        return 1;
    }
    else {
        printDialogue("Sorry, I did not understand your action.\n");
        return 1;
    }
    return 0;
}

int World::handleCommand(std::string command) {
    std::istringstream iss(command);
    std::string action, target, conjunction, container;

    iss >> action >> target >> conjunction >> container;
    return handleAction(toLower(action), toLower(target), toLower(conjunction), toLower(container));

}

int World::parseCommands(void) {
    std::string command;
    int status = 0;

    while (commands.size() > 0 && !quit && getPlayer()->isAlive()) {
        command = commands.front();
        commands.erase(commands.begin());
		status = handleCommand(command);
        if (status == 0)
            ennemyAttack();
        if (!getPlayer()->isAlive())
            displayDeathScreen();
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

    std::cout << TEXT_COLOR_CYAN << " > " << TEXT_COLOR_RESET;
    std::getline(std::cin, input);
    if (splitCommands(input) != 0)
        return 1;
	if (parseCommands() != 0)
        return 1;
    return 0;
}
