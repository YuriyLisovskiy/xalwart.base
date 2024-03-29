/**
 * interfaces/orm.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Interfaces related to database access.
 */

#pragma once

// C++ libraries.
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <map>

// Module definitions.
#include "../_def_.h"


__ORM_BEGIN__

// TODO: docs for 'IDatabaseConnection'
class IDatabaseConnection
{
public:
	virtual ~IDatabaseConnection() = default;

	[[nodiscard]]
	virtual std::string dbms_name() const = 0;

	// Executes SQL query which returns rows as a result.
	// 'row_handler' can be used for building an instance
	// of the object from columns.
	//
	// If both 'map_handler' and 'vector_handler' were set,
	// 'map_handler' will be used.
	//
	// 'sql_query' should be a valid SQL statement.
	// 'map_handler' can be nullptr.
	// 'vector_handler' can be nullptr.
	virtual void run_query(
		const std::string& sql_query,
		const std::function<void(const std::map<std::string, char*>& /* columns */)>& map_handler,
		const std::function<void(const std::vector<char*>& /* columns */)>& vector_handler
	) const = 0;

	// Executes SQL query which returns last inserted row id as a result.
	//
	// 'sql_query' should be a valid SQL statement.
	virtual void run_query(const std::string& sql_query, std::string& last_row_id) const = 0;

	virtual void begin_transaction() const = 0;

	// If 'end_transaction' ALWAYS should be used after all SQL
	// statements were run if 'begin_transaction' was called.
	virtual void end_transaction() const = 0;

	virtual void rollback_transaction() const = 0;
};

// TODO: docs for 'IBackend'
// Manages database connection pool.
class IBackend
{
public:
	virtual ~IBackend() = default;

	virtual void create_pool() = 0;

	// Provides a free connection from pool to access the database.
	// If there is not any connection available, waits for it.
	// This is a blocking operation.
	virtual std::shared_ptr<IDatabaseConnection> get_connection() = 0;

	// Returns used connection to pool.
	// The code that requested a connection, ALWAYS should return
	// it back after using it, otherwise this connection will be
	// lost.
	virtual void release_connection(const std::shared_ptr<IDatabaseConnection>& connection) = 0;

	[[nodiscard]]
	virtual std::string dbms_name() const = 0;

	// Connection pointer is used when calls are performed during
	// the transaction. Implementation can support or not this feature.
	// In the second case, you need more than one connection pool size,
	// for example, during migration the database.
	[[nodiscard]]
	virtual std::vector<std::string> get_table_names(const IDatabaseConnection*) = 0;
};

__ORM_END__
