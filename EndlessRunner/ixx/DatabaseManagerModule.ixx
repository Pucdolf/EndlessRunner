module;

#include<memory>

namespace pqxx { class connection; }

export module DatabaseManagerModule;

export class DatabaseManager {
private:
	DatabaseManager();
	~DatabaseManager();

	std::unique_ptr<pqxx::connection> connection;
public:
	DatabaseManager(const DatabaseManager&) = delete;
	DatabaseManager& operator=(const DatabaseManager&) = delete;

	static DatabaseManager& getInstance();
	bool connect();
	void close();
	void initTables();
};
