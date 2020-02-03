#pragma warning(push)
#pragma warning(disable: 4005)
#pragma warning(disable: 4251)
#pragma warning(disable: 4996)

#include <iostream>
#include <fstream>
#include "../protobuf_mud_lib//mud_lib.pb.h"
#include "process_enemy.h"
#include <google/protobuf/util/json_util.h>
#pragma warning(pop)

/*
cmake .. -DCMAKE_TOOLCHAIN_FILE="D:\Programms\vcpkg-master\vcpkg-master\scripts\buildsystems\vcpkg.cmake"
*/


std::ostream& operator << (std::ostream & os, const mud::player & player) {
	os << "name : " << player.name() << std::endl;
	os << "password : " << player.password_hash() << std::endl;
	os << "id : " << player.id() << std::endl;
	os << "characters (" << player.id_characters().size() << ")" << std::endl;

	for (const auto& id : player.id_characters()) {
		os << "\t " << id << std::endl;
	}
	return os;
}

std::ostream& operator << (std::ostream & os, const process_enemy & player) {
	os << "name : " << player.name << std::endl;
	os << "id : " << player.id << std::endl;
	os << "id tile : " << player.titleId << std::endl;
	os << "directions facing :" << player.directionFacing << std::endl;
	os << "states:" << player.enumCharacterState << std::endl;

	return os;
}

int main(int ac, char** av) {
	
	mud::player player{};

	std::string name = player.name();
	player.set_name("jeff");
	name = player.name();

	std::int64_t id = player.id();
	player.set_id(42);
	player.set_password_hash("42");

//test ennemi;
	
	mud::enemy enemy1;
	enemy1.set_name("locuste");
	enemy1.set_id(1);
	enemy1.set_tile_id(0);
	//enemy1.set_allocated_state(mud::enum_character::character_state::enum_character_character_state_NONE);
	process_enemy enemyps1(enemy1.name(), enemy1.id(), enemy1.tile_id());

	std::cout << "Enemy : " << enemyps1;


//Tuto
	std::string nameFile = "pouet.Data";
	mud::player_book book;

	mud::player player1;
	player1.set_name("Julien");
	player1.set_id(9);
	player1.set_password_hash("9");

	mud::character charcarter1;
	mud::tile tile1;

	//deserialize
	std::ifstream ifs{ nameFile, std::ios::in | std::ios::binary };
	
	if (!ifs) {
		std::cerr << "error reading" << std::endl;
	}
	else {
		book.ParseFromIstream(&ifs);
	}
	
	//affiche
	for (const mud::player& playerbooked : book.players()) {
		std::cout << playerbooked;

		/*if (&playerbooked.name != player.name) {
			*book.add_players() = player;
		}
		else {
			std::cout << " name existing " << std::endl;
		}*/
	}


	//add 
	*book.add_players() = player1;
	*book.add_players() = player;

	//serialize
	std::ofstream ofs( nameFile,std::ios::out | std::ios::binary);

	if (!book.SerializeToOstream(&ofs)) {
		std::cerr << "error writing" << std::endl;
		return -1;
	}

	std::string out;
	
	google::protobuf::util::MessageToJsonString(book, & out, google::protobuf::util::JsonOptions());
	std::cout << out;


	return 0;
}
