#include <string>
#include <map>
#include "../protobuf_mud_lib//mud_lib.pb.h"

class process_enemy {
public:
	std::string name;
	int64_t id;
	int64_t titleId;
	std::string directionFacing;
	//repeated enum_atribute_name
	std::map<std::int64_t, mud::enum_atribute_name> idAttributeName;
	std::string enumCharacterState;

	process_enemy(const std::string& name,const  int64_t& id,const  int64_t titleId) {
		this->name = name;
		this->id = id;
		this->titleId = id;
		this->idAttributeName = idAttributeName;
	};

};