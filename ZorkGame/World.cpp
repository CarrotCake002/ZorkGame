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
    slowPrint("You look around and see:\n\n");
	for (auto entity : entities) {
		entity->display();
	}
    std::cout << std::endl;
}

void World::cmdInventory(void) {
    Entity* player = getTarget("Player");

	if (player->getContains().size() < 1) {
        slowPrint("Your inventory is empty.\n");
        std::cout << std::endl;
        return;
    }
    slowPrint("You check your inventory and find:\n");
    player->printContains();
    std::cout << std::endl;
}

int World::cmdDrop(std::string target) {
    Entity* player = getTarget("Player");
    Entity* entity = player->removeItem(target);

    if (entity == nullptr) {
        slowPrint("You don't have " + target + " in your inventory.\n");
        std::cout << std::endl;
        return 1;
    } else {
        entities.push_back(entity);
        slowPrint("You drop the " + entity->getName() + ".\n");
        std::cout << std::endl;
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
            slowPrint("There is no " + container + " here.\n");
            std::cout << std::endl;
            return 1;
        }
        if (eContainer->getType() == EntityType::Creature) {
            slowPrint("Stealing from other creatures will not be tolerated!\n");
            std::cout << std::endl;
            return 1;
        }
        if (eContainer->getType() != EntityType::Container) {
            slowPrint("You can't take something from there! You can only take items from containers!\n");
            std::cout << std::endl;
            return 1;
        }
        if (!eContainer->hasItem(target)) {
            slowPrint("There is no " + target + " in the " + container + ".\n");
            std::cout << std::endl;
            return 1;
        }
        entity = eContainer->removeItem(target);
		player->addItem(entity);
        slowPrint("You take the " + entity->getName() + " from the " + eContainer->getName() + ".\n");
        std::cout << std::endl;
        return 0;
    }
	entity = getTarget(target);
    if (entity == nullptr) {
        slowPrint("There is no " + target + " here.\n");
        std::cout << std::endl;
        return 1;
    } else if (entity->getType() == EntityType::Player) {
        slowPrint("There is no... wait, what? You can't take yourself! Why would you even try that?? You silly game testers...\n");
        std::cout << std::endl;
        return 1;
	} else if (entity->getType() == EntityType::Creature) {
        slowPrint("You can't take a creature! You can only take items.\n");
        std::cout << std::endl;
        return 1;
    }
    else if (entity->getType() == EntityType::Item || entity->getType() == EntityType::None) { // temporary until the Item class is created or a different solution is found        
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        player->addItem(entity);
        slowPrint("You take the " + entity->getName() + ".\n");
        std::cout << std::endl;
    } else {
        slowPrint("You can't take that... You can only take items!\n");
        std::cout << std::endl;
		return 1;
    }
    return 0;
}

int World::cmdPut(std::string target, std::string container) {
	Entity* eContainer = getTarget(container);
	Entity* player = getTarget("Player");
    Entity* eTarget = nullptr;
        
    if (eContainer == nullptr) {
        slowPrint("There is no " + container + " here.\n");
        std::cout << std::endl;
        return 0;
    }
    if (eContainer->getType() == EntityType::Creature) {
        slowPrint("Why are you even trying to give an item to a creature?? This is unthinkable...\n");
        std::cout << std::endl;
        return 0;
    }
    if (eContainer->getType() != EntityType::Container) {
		slowPrint("You can't put something in there! You can only put items in containers!\n");
		std::cout << std::endl;
        return 0;
    }

    eTarget = player->removeItem(target);
    if (eTarget == nullptr) {
        slowPrint("There is no " + target + " in your inventory!\n");
        std::cout << std::endl;
        return 0;
	}
	eContainer->addItem(eTarget);
    slowPrint("You put the " + eTarget->getName() + " in the " + eContainer->getName() + ".\n");
	std::cout << std::endl;
    return 0;
}

int World::handleAction(std::string action, std::string target, std::string conjunction, std::string container) {
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);

	if (action == "quit") {
        slowPrint("Thanks for playing!\n");
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
        slowPrint("Sorry, I did not understand your action.\n");
        std::cout << std::endl;
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

    slowPrint(" > ");
    std::getline(std::cin, input);
    if (splitCommands(input) != 0)
        return 1;
	if (parseCommands() != 0)
        return 1;
    return 0;
}