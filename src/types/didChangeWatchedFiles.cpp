// A C++17 library for language servers.
// Copyright © 2019-2020 otreblan
//
// libclsp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libclsp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libclsp.  If not, see <http://www.gnu.org/licenses/>.

#include <libclsp/types/didChangeWatchedFiles.hpp>

namespace clsp
{

using namespace std;

const String DidChangeWatchedFilesClientCapabilities::
	dynamicRegistrationKey = "dynamicRegistration";

DidChangeWatchedFilesClientCapabilities::
	DidChangeWatchedFilesClientCapabilities(optional<Boolean> dynamicRegistration):
		dynamicRegistration(dynamicRegistration)
{};

DidChangeWatchedFilesClientCapabilities::
	DidChangeWatchedFilesClientCapabilities():
		dynamicRegistration()
{};

DidChangeWatchedFilesClientCapabilities::
	~DidChangeWatchedFilesClientCapabilities()
{};


const String FileSystemWatcher::globPatternKey = "globPattern";
const String FileSystemWatcher::kindKey        = "kind";

FileSystemWatcher::FileSystemWatcher(String globPattern, optional<Number> key):
	globPattern(globPattern),
	key(key)
{};

FileSystemWatcher::FileSystemWatcher():
	globPattern(),
	key()
{};

FileSystemWatcher::~FileSystemWatcher(){};


const String DidChangeWatchedFilesRegistrationOptions::watchersKey = "watchers";

DidChangeWatchedFilesRegistrationOptions::
	DidChangeWatchedFilesRegistrationOptions(vector<FileSystemWatcher> watchers):
		watchers(watchers)
{};

DidChangeWatchedFilesRegistrationOptions::
	DidChangeWatchedFilesRegistrationOptions():
		watchers()
{};

DidChangeWatchedFilesRegistrationOptions::
	~DidChangeWatchedFilesRegistrationOptions()
{};


const String FileEvent::uriKey  = "uri";
const String FileEvent::typeKey = "type";

FileEvent::FileEvent(DocumentUri uri, FileChangeType type):
	uri(uri),
	type(type)
{};

FileEvent::FileEvent():
	uri(),
	type()
{};

FileEvent::~FileEvent(){};


const String DidChangeWatchedFilesParams::changesKey = "changes";

DidChangeWatchedFilesParams::DidChangeWatchedFilesParams(vector<FileEvent> changes):
	changes(changes)
{};

DidChangeWatchedFilesParams::DidChangeWatchedFilesParams():
	changes()
{};

DidChangeWatchedFilesParams::~DidChangeWatchedFilesParams(){};

}
