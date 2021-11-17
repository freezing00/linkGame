#include"menu.h"
#include "initGraph.h"

int main() {
	Menu menu;
	menu.openMusic();
	Graph graph;
	int mapInitFlag = false;
	while (true) {
		if (!menu.getStart()) {
			menu.menuProcess();
			graph.setMapSize(menu.getLevelChoice());
			if (menu.getQuitMenu()) {
				closegraph();
				break;
			}
			mapInitFlag = true;
		}
		else {	
				if (mapInitFlag){
					graph.gameInit();
					mapInitFlag = false;
				}
				graph.initProcess();
				if (graph.returnMenu()) {
					menu.setInMenu();
				}
		}
	}
}