#include "World.h"

int World::cmdSlashKill() {
    Player* player = getPlayer();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, deathMessages.size() - 1);

    printDialogue(deathMessages[dist(gen)] + "\n");

    player->setHealth(0);
    return 0;
}

int World::handleSecretCommands(std::string action, std::string target, std::string conjunction, std::string container) {
	if (action == "/kill" && target.empty()) {
		cmdSlashKill();
        return 0;
	}
	return 1;
}
