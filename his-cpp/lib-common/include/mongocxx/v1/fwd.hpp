// Copyright 2009-present MongoDB, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// clang-format off
#include <mongocxx/v1/aggregate_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/apm-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/auto_encryption_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/bulk_write-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/change_stream-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/client-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/client_encryption-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/client_session-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/collection-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/count_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/cursor-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/data_key_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/database-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/delete_many_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/delete_many_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/delete_one_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/delete_one_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/distinct_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/encrypt_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/estimated_document_count_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/command_failed-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/command_started-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/command_succeeded-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_closed-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_description-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_description_changed-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_heartbeat_failed-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_heartbeat_started-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_heartbeat_succeeded-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/server_opening-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/topology_closed-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/topology_description-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/topology_description_changed-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/events/topology_opening-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/exception-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/find_one_and_delete_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/find_one_and_replace_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/find_one_and_update_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/find_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/gridfs/bucket-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/gridfs/downloader-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/gridfs/upload_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/gridfs/upload_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/gridfs/uploader-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/hint-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/indexes-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/insert_many_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/insert_many_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/insert_one_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/insert_one_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/instance-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/logger-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/pipeline-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/pool-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/range_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/read_concern-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/read_preference-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/replace_one_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/replace_one_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/return_document-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/rewrap_many_datakey_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/rewrap_many_datakey_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/search_indexes-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/server_api-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/server_error-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/text_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/tls-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/transaction_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/update_many_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/update_many_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/update_one_options-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/update_one_result-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/uri-fwd.hpp> // IWYU pragma: export
#include <mongocxx/v1/write_concern-fwd.hpp> // IWYU pragma: export
// clang-format on

///
/// @file
/// Aggregate of all forward headers declaring entities in @ref mongocxx::v1.
///
/// @par Includes
/// - All header files under `mongocxx/v1` whose filename ends with `-fwd.hpp`.
///
