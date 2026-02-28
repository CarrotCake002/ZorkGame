#include "World.h"

World::World() {
    slowPrint("Welcome to Zork! The game is still in development, but feel free to explore the world and test out the commands! Type 'quit' to exit the game.\n");
    std::cout << std::endl;

    addEntity(new Player("Player", "the player character", 10, 2, EntityType::Player));
    addEntity(new Entity("Stick", "a stick to attack enemies with"));
    getTarget("Player")->addItem(getTarget("Stick"));

	// Creation of the starting room and its content
	addEntity(new Room("Starting Room", "a small room with a door to the north"));
	moveToRoom(getTarget("Starting Room"));

    addEntity(new Creature("NPC", "a small goofy ennemy", 10, 1));
    addEntity(new Entity("Rock", "a rock that deals damage with every hit"));
    getTarget("NPC")->addItem(getTarget("Rock"));
	getTarget("Starting Room")->addItem(getTarget("NPC"));

    addEntity(new Entity("Bag", "a small bag that can contain a few items", EntityType::Container));
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
    if (room == nullptr || room->getType() != EntityType::Room) {
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
    else if (eTarget->getType() == EntityType::Player) {
        printDialogue({ { "There is no", 20 }, { "...", 300}, {"", 2000}, {"\n\n", 0}, { "Wait", 70 }, {"", 1500}, {", what?", 70}, {"", 2000}, {"\n\n", 0}, {"You can't take yourself!", 30}, {"", 1000}, {"\n", 0}, {"Why would you even try to take yourself??", 30}, {"", 2500}, {"\n\n", 0}, {"Ooh...", 400}, {" You silly game testers...", 100}, {"", 3000}, {"\n", 0} });
        return 1;
    }
    else if (eTarget->getType() == EntityType::Creature) {
        printDialogue("You can't take a creature! You can only take items.\n");
        return 1;
    }
    else if (eTarget->getType() != EntityType::Item){
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
    if (eContainer->getType() == EntityType::Creature) {
        printDialogue("Stealing from other creatures will not be tolerated!\n");
        return 1;
    }
    if (eContainer->getType() == EntityType::Player) {
        printDialogue("I mean uuh... sure, why not?\n\n\"You take an item from your inventory and put it back\"\n\nI mean come on you really think I'm going to risk bugs in my game to handle that.\n\nJUST STOP TRYING TO CRASH MY GAME AND PLAY\n");
        return 1;
    }
    if (eContainer->getType() != EntityType::Container) {
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
    if (eContainer->getType() == EntityType::Creature) {
        printDialogue("Why are you even trying to give an item to a creature??\nI will not allow this!\n");
        return 1;
    }
    if (eContainer->getType() != EntityType::Container) {
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
        printDialogue("That's not a valid direction!\n");
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
    if (action == "attack" && (conjunction == "with" || conjunction == "using")) {
        return true;
    }
    printDialogue("Sorry, I don't know what " + conjunction + " means.\n");
    return false;
}

void World::cmdLook(void) const {
    printDialogue("You look around and see:\n");
    for (auto &entity : currentRoom->getContains()) {
        if (entity->getType() == EntityType::Exit)
			static_cast<Exit*>(entity)->display();
        else
            entity->display();
    }
}

void World::cmdInventory(void) const {
    Entity* player = getTarget("Player");

    if (player->getContains().size() < 1) {
        printDialogue("Your inventory is empty.\n");
        return;
    }
    printDialogue("You check your inventory and find:");
    player->printContains();
    printDialogue("\n");
}

int World::cmdDrop(std::string target) {
    Entity* player = getTarget("Player");
    Entity* entity = player->removeItem(target);

    if (handleCmdDropErrors(target, entity) != 0)
        return 1;
    currentRoom->addItem(entity);
    printDialogue("You drop the " + entity->getName() + ".\n");
    return 0;
}

int World::cmdTake(std::string target) {
    Entity* player = getTarget("Player");
    Entity* entity = currentRoom->getItem(target);

    if (handleCmdTakeErrors(target, entity) != 0)
		return 1;
    currentRoom->removeItem(target);
    player->addItem(entity);
    printDialogue("You take the " + entity->getName() + ".\n");
    return 0;
}

int World::cmdTakeFromContainer(std::string target, std::string container) {
    Entity* player = getTarget("Player");
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
    Entity* player = getTarget("Player");
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

int World::handleAction(std::string action, std::string target, std::string conjunction, std::string container) {
	if (action == "quit" && target.empty()) {
        printDialogue("Thanks for playing!\n");
        quit = true;
        return 1;
    }
    else if (action == "look" && target.empty()) {
        cmdLook();
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
    else if ((action == "inventory" || action == "i") && target.empty()) {
        cmdInventory();
    }
    else if (action == "put" && !conjunction.empty()) {
        if (!checkConjunction(action, conjunction))
            return 0;
		cmdPut(target, container);
    }
    else if (action == "walk" && conjunction.empty()) {
        cmdWalk(target);
    }
    else {
        printDialogue("Sorry, I did not understand your action.\n");
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

    std::cout << " > ";
    std::getline(std::cin, input);
    if (splitCommands(input) != 0)
        return 1;
	if (parseCommands() != 0)
        return 1;
    return 0;
}