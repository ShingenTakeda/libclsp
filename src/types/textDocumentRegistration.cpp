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

#include <libclsp/types/textDocumentRegistration.hpp>

namespace clsp
{

using namespace std;

const String TextDocumentRegistrationOptions::documentSelectorKey = "documentSelector";


TextDocumentRegistrationOptions::
	TextDocumentRegistrationOptions(variant<DocumentSelector, Null> documentSelector):
		documentSelector(documentSelector)
{};

TextDocumentRegistrationOptions::TextDocumentRegistrationOptions(){};
TextDocumentRegistrationOptions::~TextDocumentRegistrationOptions(){};

void TextDocumentRegistrationOptions::partialWrite(JsonWriter &writer)
{
	// documentSelector
	writer.Key(documentSelectorKey);
	visit(overload(
		[&writer](DocumentSelector& arr)
		{
			writer.StartArray();
			for(auto& i: arr)
			{
				writer.Object(i);
			}
			writer.EndArray();
		},
		[&writer](Null)
		{
			writer.Null();
		}
	), documentSelector);
}

}
