#include "Key.h"

Key::Key(std::string name, std::string description, int exit_id) : Entity(name, description, EntityType::KEY), exit_id(exit_id) {

}