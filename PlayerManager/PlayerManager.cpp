#include <iostream>
#include <string>
#include "MyHashMap.h"
using namespace std;

struct Player
{
	char* name;
	int id;
	Player(char* name_, int id_) : name(name_), id(id_) {}
};

class PlayerManager
{
	MyHashMap<int, shared_ptr<Player>> playersByID;
	MyHashMap<char*, shared_ptr<Player>> playersByName;
	int numPlayers;

public:
	PlayerManager() : numPlayers(0) {}
	~PlayerManager() {
		//don't need to delete memory manually
		//all the pointers of player are stored in shared_ptr
		//the memory of players will delete in its destrctor automatically
	}
	void DestroyAllPlayers() {
		playersByID.clear();
		playersByName.clear();
	}

	shared_ptr<Player> CreatePlayer(const char* name, int id) {
		std::shared_ptr<Player> player(new Player(const_cast<char*>(name), id));
		playersByID.insert({ player->id, player });
		playersByName.insert({ player->name, player });
		++numPlayers;
		return player;
	}
	void DestroyPlayerById(int id) {
		playersByID.remove(id);
	}
	void DestroyPlayerByName(char* name) {
		playersByName.remove(name);
	}
	void DestroyPlayer(Player* pPlayer) {
		DestroyPlayerById(pPlayer->id);
		DestroyPlayerByName(pPlayer->name);
	}

	int GetNumPlayers() {
		return numPlayers;
	}
	shared_ptr<Player> GetPlayerById(int id) {
		return playersByID.find(id);
	}
};

int main()
{
	PlayerManager* playerMgr = new PlayerManager();
	playerMgr->CreatePlayer("Tom", 0);
	playerMgr->CreatePlayer("Jack", 1);
	playerMgr->CreatePlayer("Mike", 2);
	playerMgr->CreatePlayer("Lucy", 3);
	playerMgr->CreatePlayer("Lily", 4);
	playerMgr->CreatePlayer("Neo", 5);
	for (int i = 5; i >= 0; --i) 
		cout << "player ID: " << playerMgr->GetPlayerById(i)->id << " player name: " << playerMgr->GetPlayerById(i)->name << endl;
	playerMgr->DestroyAllPlayers();
	delete playerMgr;
	system("pause");
	return 0;
}