#include "Game.h"
#include "World.h"

int main() {
    int status = true;
    World world;

    Player* player = new Player("Player", "the player character.", 10, 2, EntityType::Player);
    player->addItem(new Entity("Stick", "a stick to attack enemies with."));

    Creature* creature = new Creature("NPC", "a small goofy ennemy.", 10, 1);
    creature->addItem(new Entity("Rock", "a rock that deal damage with every hit."));

    world.addEntity(player);
	world.addEntity(creature);

    Entity* bag = new Entity("Smal bag", "a small bag that can contain a few items.");

    Entity* hat = new Entity("Cool hat", "a cool hat for daring fashion enjoyers.");
    Entity* shirt = new Entity("Nice shirt", "an elegant shirt for formal events.");
    Entity* pants = new Entity("Pair of pants", "nice pants that would pair perfectly with a shirt.");

    bag->addItem(hat);
    bag->addItem(shirt);
    bag->addItem(pants);

    world.addEntity(bag);

    while (status) {
        if (getInput() == 1) {
            break;
        }
		world.update();
    }
    return 0;
}