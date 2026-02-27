#include "World.h"

World::~World() {
	for (auto entity : entities) {
		delete entity;
	}
}

Entity* World::getTarget(std::string target) {
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    std::string entityName;
    for (auto& entity : entities) {
		entityName = entity->getName();
        std::transform(entityName.begin(), entityName.end(), entityName.begin(), ::tolower);
        if (entityName == target) {
            return entity;
        }
    }
    return nullptr;
}

void World::cmdLook(void) {
    slowPrint("You look around and see:\n\n");
	for (auto entity : entities) {
		entity->display();
	}
    std::cout << std::endl;
}

void World::cmdInventory(void) {
    Entity* player = getTarget("Player");

    slowPrint("You check your inventory and find:\n");
    player->printContains();
    std::cout << std::endl;
}

int World::cmdDrop(std::string target) {
    Entity* player = getTarget("Player");
    Entity* entity = player->removeItem(target);

    if (entity == nullptr) {
        slowPrint("You don't have " + target + " in your inventory.");
        std::cout << std::endl;
        return 1;
    } else {
        entities.push_back(entity);
        slowPrint("You drop the " + entity->getName() + ".");
        std::cout << std::endl;
    }
    return 0;
}

int World::cmdTake(std::string target) {
    Entity* entity = getTarget(target);
	Entity* player = getTarget("Player");

    if (entity == nullptr) {
        slowPrint("There is no " + target + " here.");
        std::cout << std::endl;
        return 1;
    } else if (entity->getType() == EntityType::Player) {
        slowPrint("There is no... wait, what? You can't take yourself! Why would you even try that?? You silly game testers...");
        std::cout << std::endl;
        return 1;
	} else if (entity->getType() == EntityType::Creature) {
        slowPrint("You can't take a creature! You can only take items.");
        std::cout << std::endl;
        return 1;
	} else if (entity->getType() == EntityType::Item || entity->getType() == EntityType::None) { // temporary until the Item class is created or a different solution is found
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        player->addItem(entity);
        slowPrint("You take the " + entity->getName() + ".");
        std::cout << std::endl;
    } else {
        slowPrint("You can't take that... You can only take items!");
        std::cout << std::endl;
		return 1;
    }
    return 0;
}

int World::handleAction(std::string action, std::string target, std::string conjunction, std::string item) {
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);

	if (action == "quit") {
        slowPrint("Thanks for playing!");
        std::cout << std::endl;
        quit = true;
        return 1;
    }
    else if (action == "look") {
        cmdLook();
    }
    else if (action == "drop") {
        cmdDrop(target);
    }
    else if (action == "take") {
		cmdTake(target);
    }
    else if (action == "inventory" || action == "i") {
        cmdInventory();
    }
    else {
        slowPrint("Sorry, I did not understand your action.");
        std::cout << std::endl;
    }
    return 0;
}

int World::handleCommand(std::string command) {
    std::istringstream iss(command);
    std::string action, target, conjunction, item;

    iss >> action >> target >> conjunction >> item;
    if (handleAction(action, target, conjunction, item) != 0) {
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

    slowPrint(" > ");
    std::getline(std::cin, input);
    if (splitCommands(input) != 0)
        return 1;
	if (parseCommands() != 0)
        return 1;
    return 0;
}