#include "Monster.h"

Monster::Monster(int x, int y):
	Character(),
	startX(x),
	startY(y) {
}

void Monster::derivedSetup() {
	x = startX;
	y = startY;
	// make the bounding box smaller than the sprite:
	width *= 0.8; // 80% of the sprite width.
	height *= 0.8; // 80% of the sprite height.

	movingLeft = false;
	movingRight = true;
}

void Monster::move(Map* map) {
	// update position every 10 milliseconds:
	if(ofGetElapsedTimeMillis() - timer >= 10) {
		switch(state) {
		case living:
		{
		int mapWidth, mapHeight;
		mapWidth = map->getWidth();
		mapHeight = map->getHeight();

		lastX = x;
		lastY = y;

		velX = 0;

		// larger values when program runs too slow to compensate:
		float step = moveSpeed * ((ofGetElapsedTimeMillis() - timer) / 10);

		if(movingLeft)
			velX = -step;
		if(movingRight)
			velX = step;

		// dont let the monster move faster than the tilesize,
		// or he could move through them without collision:
		velY = ofClamp(velY, -(map->getTileHeight() + 1),
					   map->getTileHeight() - 1);

		//reset the move-direction
		//when the monster collides with sth.
		collisionHandling(map);

		// dont let the monster move out of the map boundaries:
		x = ofClamp(x, 0, mapWidth - width);
		y = ofClamp(y, 0, mapHeight - height);

		//check if monster collided with the level-borders
		//left level border
		if(x == 0) {
			movingLeft = false;
			movingRight = true;
		}
		//right level border
		if(x == mapWidth - width) {
			movingRight = false;
			movingLeft = true;
		}

		
		// pass the movement to the sprite:
		sprite.move(movingLeft, movingRight, false);

		timer = ofGetElapsedTimeMillis();
		}
		break;
		case dying:
		{
		//show killpic
		sprite.killPic(0, 2);
		//after 2 seconds -> kill the monster
		if(getDeathTimer() >= 2000)
			kill();
		}
		break;
		}
	}
}

void Monster::collisionHandling(Map* map) {
	// used for moving the bounding box to the middle of the sprite:
	int xOffset = width / 8;
	int tilecoord;

	// moving right:
	if(movingRight) {
		if(collision_ver((x + xOffset) + velX + width, y, tilecoord, map)) {
			movingRight = false;
			movingLeft = true;
		}
		else
			x += velX;
	}
	// moving left:
	else if(movingLeft) {
		if(collision_ver((x + xOffset) + velX, y, tilecoord, map)) {
			movingLeft = false;
			movingRight = true;
		}
		else
			x += velX;
	}

	//moving down
	if(velY >= 0) {
		if(collision_hor((x + xOffset), y + velY + height, tilecoord, map)) {
			y = tilecoord * map->getTileHeight() - height - 1;
			velY = gravity;
		}
		else {
			//if monster touches the ground 
			//of the map it dies
			if(tilecoord == map->getGridY()) {
				kill();
			}
			else {
				y += velY;
				velY += gravity;
			}
		}
	}
}
