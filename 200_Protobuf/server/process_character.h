#include <string>
#include <map>
#include "../protobuf_mud_lib//mud_lib.pb.h"
#include "../protobuf_mud_lib/helper.h"

class process_character {
public :
	std::string name;
	int64_t id;
	int64_t titleId;
	std::string directionFacing;
	//repeated enum_atribute_name
	std::map<std::int64_t, mud::enum_atribute_name> idAttributeName;
	std::string enumCharacterState;

	process_character(std::string& name, int64_t& id, int64_t titleId, std::map<std::int64_t, mud::enum_atribute_name> idAttributeName) {
		this -> name = name;
		this -> id = id;
		this -> titleId = id;
		this->idAttributeName = idAttributeName;
	};

	static bool RunCharacter(helper::input entry, mud::tile& present_tile,std::map<mud::enum_direction, mud::tile>& surrounding_tiles);
};

