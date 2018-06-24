#include "screencasts.h"

json readUser();
json readScoreboard();

void addUser(std::string nome) {
	json listaUsuarios = readUser();
	
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

void visualUserList() {
	json userList = readUser();
	
	cout << "\nLista de Usuarios:\n";
	cout << userList["users"];
	cout << "\n";
}

void addScoreboard(std::string nome, int score) { 
	json listScoreboard = readScoreboard();
		
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

void visualScoreBoard() {
	json scoreboardList = readScoreboard();
	
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


