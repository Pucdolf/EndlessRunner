module; 

#include<iostream>
#include<pqxx/pqxx>

module DatabaseManagerModule;

DatabaseManager::DatabaseManager() {
	std::cout << "Initializing DatabaseManager singleton" <<std::endl;
}

DatabaseManager::~DatabaseManager() {
	std::cout << "Shutting down DatabaseManager and closing connections" << std::endl;
}

DatabaseManager& DatabaseManager::getInstance() {
	static DatabaseManager instance;
	return instance;
}

bool DatabaseManager::connect() {
	std::cout << "Attemtpting to connect to POSTGRESQL" << std::endl;
}

bool DatabaseManager::close() {
}

