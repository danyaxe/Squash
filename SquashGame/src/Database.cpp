//Database
#include "json.hpp"
#include <iostream> 
#include <fstream>
using namespace std;
using nlohmann::json;

//Win Dir
string openDir = "";
string saveDir = "";
string usersFileName = "users.json";
string scoreboardFileName = "scoreboard.json";
string settingsFileName = "settings.json";


void addUser(json listaUsuarios, std::string nome) {
	listaUsuarios["users"] += {"name", nome};

	ofstream w(saveDir + usersFileName);
	w << listaUsuarios << endl;
	w.close();
	cout << "\nSuccess Saved the file.\n";
}

json readUser() {
	ifstream i(openDir + usersFileName);
	json j;
	i >> j;
	i.close();
	return j;
}

void visualUserList(json userList) {
	cout << "\nLista de Usuarios:\n";
	cout << userList["users"];
	cout << "\n";
}

void addScoreboard(json listScoreboard, string nome, int score) { 
	listScoreboard["scoreboard"] += { { "nome", nome },{ "score", score } };

	ofstream w(saveDir + scoreboardFileName);
	w << listScoreboard << endl;
	w.close();
	cout << "\nSuccess Saved the file.\n";
}

json readScoreboard() {
	ifstream i(openDir + scoreboardFileName);
	json j;
	i >> j;
	i.close();
	return j;
}

void visualScoreBoard(json scoreboardList) {
	cout << "\nScoreboard:\n";
	cout << scoreboardList["scoreboard"];
	cout << "\n";
}

void clearScoreboard() {
	json obj;
	obj["scoreboard"] = json::array();
	ofstream w(saveDir + scoreboardFileName);
	w << obj << endl;
	w.close();
	//cout << "Success Saved the file.";
}

void clearUserList() {
	json obj;
	obj["users"] = json::array();
	ofstream w(saveDir + usersFileName);
	w << obj << endl;
	w.close();
	//cout << "Success Saved the file.";
}

bool defaultSettings() {
	json obj;
	obj["sound"] = true;

	ofstream w(saveDir + settingsFileName);
	w << obj << endl;
	w.close();
	//cout << "Success Saved the file.";
	return true;
}

bool readSettings() {
	ifstream i(openDir + settingsFileName);
	json j;
	i >> j;
	i.close();
	return j;
}

bool updateSettings(bool sound) {
	json obj;
	obj["sound"] = sound;

	ofstream w(saveDir + settingsFileName);
	w << obj << endl;
	w.close();
	//cout << "Success Saved the file.";
	return true;
}


void initialize() {
	ifstream f(openDir + usersFileName);
	ifstream g(openDir + scoreboardFileName);
	ifstream h(openDir + settingsFileName);

	if (!(bool)f) 
		clearUserList();
	
	if (!(bool) g)
		clearScoreboard();
		
	if (!(bool) h)
		defaultSettings();

	f.close();
	g.close();
	h.close();
}