#pragma once

class Drawable {
public:
	virtual void draw();
	// layer property is used to determine in which order to render this drawable
	// e.g. if drawable A's layer=1 and B's layer=7, A should be rendered first
	int layer = 0;
};