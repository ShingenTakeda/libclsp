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

#include <libclsp/types/documentFilter.hpp>

namespace clsp
{

using namespace std;

const String DocumentFilter::languageKey = "language";
const String DocumentFilter::schemeKey   = "scheme";
const String DocumentFilter::patternKey  = "pattern";

DocumentFilter::DocumentFilter(optional<String> language,
	optional<String> scheme,
	optional<String> pattern):
		language(language),
		scheme(scheme),
		pattern(pattern)
{};

DocumentFilter::DocumentFilter(){};
DocumentFilter::~DocumentFilter(){};

void DocumentFilter::partialWrite(JsonWriter &writer)
{
	// language?
	if(language.has_value())
	{
		writer.Key(languageKey);
		writer.String(*language);
	}

	// scheme?
	if(scheme.has_value())
	{
		writer.Key(schemeKey);
		writer.String(*scheme);
	}

	// pattern?
	if(pattern.has_value())
	{
		writer.Key(patternKey);
		writer.String(*pattern);
	}
}

}
