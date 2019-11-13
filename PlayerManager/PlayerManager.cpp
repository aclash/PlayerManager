#include <iostream>
#include <string>
#include "MyHashMap.h"
using namespace std;

struct Player
{
	char* name;
	int id;
	Player(char* name_, int id_) : name(name_), id(id_){}
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
	for (int i = 0; i <= 0; ++i) {
		string str(1, 'a' + i);
		playerMgr->CreatePlayer(str.c_str(), i);
	}
	for (int i = 0; i >= 0; --i) {
		//cout << "player ID: " << playerMgr->GetPlayerById(i)->id << " player name: " << playerMgr->GetPlayerById(i)->name << endl;
		auto pp = playerMgr->GetPlayerById(i);
		string str = playerMgr->GetPlayerById(i)->name;
		cout << str;
	}
	playerMgr->DestroyAllPlayers();
	delete playerMgr;
	system("pause");
    return 0;
}