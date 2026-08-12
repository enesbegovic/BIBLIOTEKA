#pragma once
#include"sqlite3.h"
#include <memory>

struct StmtDeleter {
	void operator()(sqlite3_stmt* stmt)const {
		sqlite3_finalize(stmt);
	}
};
using StmtPtr = std::unique_ptr<sqlite3_stmt, StmtDeleter>;