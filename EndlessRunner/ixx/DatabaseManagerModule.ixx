module;

export module DatabaseManagerModule;

export class DatabaseManager {
private:
	DatabaseManager();
	~DatabaseManager();
public:
	DatabaseManager(const DatabaseManager&) = delete;
	DatabaseManager& operator=(const DatabaseManager&) = delete;

	static DatabaseManager& getInstance();

	bool connect();
	bool close();
};
