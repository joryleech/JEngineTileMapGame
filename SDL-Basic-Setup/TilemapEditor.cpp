#include "TilemapEditor.h"

TilemapEditor::TilemapEditor()
{
	screen = new JRenderer(0, 0, 640, 480);
	tilemap = new Tilemap(100, 100, 32);
}
