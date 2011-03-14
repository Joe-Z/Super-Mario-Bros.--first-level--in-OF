#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class Tile {
public:
	Tile(bool _solid, string path):
		solid(_solid),
		imagePath(path) {
	};

	bool solid;
	string imagePath;
};

#endif //TILE_H_INCLUDED