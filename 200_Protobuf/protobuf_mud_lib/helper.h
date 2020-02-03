#pragma once
#include "../protobuf_mud_lib//mud_lib.pb.h"
#include<map>

namespace helper {
	enum class input {
		FORWARD, 
		BACKWARD,
		LEFT,
		RIGHT,
		QUIT,
		INFO,
		ATTACK,
		NONE
	};

	void initializeTile() {

		mud::tile_book tileBook;
		std::map<int, mud::tile> tileMap;

		//for (int i = 0; i < 10; i++) {
		//	for (int j = 0; j < 10; j++) {
		//		mud::tile tileTmp;
		//		tileTmp.set_id = i;
		//		tileTmp.set_type = 0;


		//		//check for angles
		//		//check right
		//		if (j < 9) {
		//			mud::location locationRightTmp;
		//		}
		//		//tileTmp.neighbour = 2;

		//		tileTmp.occupant_id = 0;
		//		tileTmp.mood = "This is initial mood";
		//	}
		//}

		
		/*
		| 5	| 6	|   |
		| 4	| 1 | 2 |
		|	| 3	|   |
		*/
		if (tileBook.tiles().size() > 0) {
		
		}
		else {
			//tile 1
			{
				mud::tile t0;
				t0.set_id = 0;
				t0.set_type = 0;
				t0.set_occupant_id = 0;
				t0.set_mood("this is tile 0");
				tileMap.insert({ 0, t0 });


				mud::location t3_location;
				t3_location.set_south;
			}
			/*t2*/
			{
				mud::tile t1;
				t1.set_id = 1;
				t1.set_type = 0;
				t1.set_occupant_id = 0;
				t1.set_mood("this is tile 2");
				tileMap.insert({ 1, t1 });

				mud::location t0_location;
				t0_location.set_west;
			}

			/*t3*/
			{
				mud::tile t3;
				t3.set_id = 3;
				t3.set_type = 0;
				t3.set_occupant_id = 0;
				t3.set_mood("this is tile 3");
				tileMap.insert({ 2, t3 });

				mud::location t0_location;
				t0_location.set_north;
			}

		}

	
	}
};
