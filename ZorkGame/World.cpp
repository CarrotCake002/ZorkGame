#include "World.h"

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

void World::cmdLook(void) {
    printDialogue("You look around and see:\n");
	for (auto entity : entities) {
		entity->display();
	}
}

void World::cmdInventory(void) {
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

    if (entity == nullptr) {
        printDialogue("You don't have " + target + " in your inventory.\n");
        return 1;
    } else {
        entities.push_back(entity);
        printDialogue("You drop the " + entity->getName() + ".\n");
    }
    return 0;
}

int World::cmdTake(std::string target, std::string container) {
	Entity* player = getTarget("Player");
    Entity* entity = nullptr;
	Entity* eContainer = nullptr;

    if (container != "") {
        eContainer = getTarget(container);
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
        entity = eContainer->removeItem(target);
		player->addItem(entity);
        printDialogue("You take the " + entity->getName() + " from the " + eContainer->getName() + ".\n");
        return 0;
    }
	entity = getTarget(target);
    if (entity == nullptr) {
        printDialogue("There is no " + target + " here.\n");
        return 1;
    } else if (entity->getType() == EntityType::Player) {
        printDialogue({ { "There is no", 20 }, { "...", 300}, {"", 2000}, {"\n\n", 0}, { "Wait", 70 }, {"", 1500}, {", what?", 70}, {"", 2000}, {"\n\n", 0}, {"You can't take yourself!", 30}, {"", 1000}, {"\n", 0}, {"Why would you even try to take yourself??", 30}, {"", 2500}, {"\n\n", 0}, {"Ooh...", 400}, {" You silly game testers...", 100}, {"", 3000}, {"\n", 0}});
        return 1;
	} else if (entity->getType() == EntityType::Creature) {
        printDialogue("You can't take a creature! You can only take items.\n");
        return 1;
    }
    else if (entity->getType() == EntityType::Item || entity->getType() == EntityType::None) { // temporary until the Item class is created or a different solution is found        
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        player->addItem(entity);
        printDialogue("You take the " + entity->getName() + ".\n");
    } else {
        printDialogue("You can't take that... You can only take items!\n");
		return 1;
    }
    return 0;
}

int World::cmdPut(std::string target, std::string container) {
	Entity* eContainer = getTarget(container);
	Entity* player = getTarget("Player");
    Entity* eTarget = nullptr;
        
    if (eContainer == nullptr) {
        printDialogue("There is no " + container + " here.\n");
        return 0;
    }
    if (eContainer->getType() == EntityType::Creature) {
        printDialogue({ { "Why are you even trying to give an item to a creature??\n" }, {"This is unthinkable...\n", 25 } });
        return 0;
    }
    if (eContainer->getType() != EntityType::Container) {
		printDialogue("You can't put something in there! You can only put items in containers!\n");
        return 0;
    }

    eTarget = player->removeItem(target);
    if (eTarget == nullptr) {
        printDialogue("There is no " + target + " in your inventory!\n");
        return 0;
	}
	eContainer->addItem(eTarget);
    printDialogue("You put the " + eTarget->getName() + " in the " + eContainer->getName() + ".\n");
    return 0;
}

int World::handleAction(std::string action, std::string target, std::string conjunction, std::string container) {
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);

	if (action == "quit") {
        printDialogue("Thanks for playing!\n");
        quit = true;
        return 1;
    }
    else if (action == "look") {
        cmdLook();
    }
    else if (action == "drop") {
        cmdDrop(target);
    }
    else if (action == "take" && (conjunction == "" || conjunction == "from")) {
		cmdTake(target, container);
    }
    else if (action == "inventory" || action == "i") {
        cmdInventory();
    }
    else if (action == "put") {
		cmdPut(target, container);
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
    if (handleAction(action, target, conjunction, container) != 0) {
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