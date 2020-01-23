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

#pragma once

#include <libclsp/types/command.hpp>
#include <libclsp/types/diagnostic.hpp>
#include <libclsp/types/partialResult.hpp>
#include <libclsp/types/range.hpp>
#include <libclsp/types/textDocumentPosition.hpp>
#include <libclsp/types/textDocumentRegistration.hpp>
#include <libclsp/types/workDoneProgress.hpp>
#include <libclsp/types/workspaceEdit.hpp>

namespace libclsp
{

using namespace std;

/// A set of predefined code action kinds.
struct CodeActionKind
{
	String kind;

	operator String()
	{
		return kind;
	}

	bool operator<(CodeActionKind& other)
	{
		return this->kind < other.kind;
	}

	CodeActionKind(String kind);

	/// Empty kind.
	const static CodeActionKind Empty;

	/// Base kind for quickfix actions: 'quickfix'.
	const static CodeActionKind QuickFix;

	/// Base kind for refactoring actions: 'refactor'.
	const static CodeActionKind Refactor;

	/// Base kind for refactoring extraction actions: 'refactor.extract'.
	///
	/// Example extract actions:
	///
	/// - Extract method
	/// - Extract function
	/// - Extract variable
	/// - Extract interface from class
	/// - ...
	const static CodeActionKind RefactorExtract;

	/// Base kind for refactoring inline actions: 'refactor.inline'.
	///
	/// Example inline actions:
	///
	/// - Inline function
	/// - Inline variable
	/// - Inline constant
	/// - ...
	const static CodeActionKind RefactorInline;

	/// Base kind for refactoring rewrite actions: 'refactor.rewrite'.
	///
	/// Example rewrite actions:
	///
	/// - Convert JavaScript function to class
	/// - Add or remove parameter
	/// - Encapsulate field
	/// - Make method static
	/// - Move method to base class
	/// - ...
	const static CodeActionKind RefactorRewrite;

	/// Base kind for source actions: `source`.
	///
	/// Source code actions apply to the entire file.
	const static CodeActionKind Source;

	/// Base kind for an organize imports source action:
	/// `source.organizeImports`.
	const static CodeActionKind SourceOrganizeImports;
};


/// CodeAction request client capabilities
///
/// dynamicRegistration?: Boolean
///
/// codeActionLiteralSupport?: {
///
/// 	codeActionKind: {
///
/// 		valueSet: CodeActionKind[]
///
/// 	}
/// }
///
/// isPreferredSupport?: Boolean
///
struct CodeActionClientCapabilities
{

	const static String dynamicRegistrationKey;

	/// Whether code action supports dynamic registration.
	optional<Boolean> dynamicRegistration;


	const static String codeActionLiteralSupportKey;

	/// The client supports code action literals as a valid
	/// response of the `textDocument/codeAction` request.
	///
	/// @since 3.8.0
	struct CodeActionLiteralSupport
	{

		const static String codeActionKindKey;

		/// The code action kind is supported with the following value
		/// set.
		struct CodeActionKind
		{

			const static String valueSetKey;

			/// The code action kind values the client supports. When this
			/// property exists the client also guarantees that it will
			/// handle values outside its set gracefully and falls back
			/// to a default value when unknown.
			vector<libclsp::CodeActionKind> valueSet;


			CodeActionKind(vector<libclsp::CodeActionKind> valueSet);

			CodeActionKind();

			virtual ~CodeActionKind();
		};

		/// The code action kind is supported with the following value
		/// set.
		CodeActionKind codeActionKind;


		CodeActionLiteralSupport(CodeActionKind codeActionKind);

		CodeActionLiteralSupport();

		virtual ~CodeActionLiteralSupport();

	};

	/// The client supports code action literals as a valid
	/// response of the `textDocument/codeAction` request.
	///
	/// @since 3.8.0
	optional<CodeActionLiteralSupport> codeActionLiteralSupport;


	const static String isPreferredSupportKey;

	optional<Boolean> isPreferredSupport;


	CodeActionClientCapabilities(optional<Boolean> dynamicRegistration,
		optional<CodeActionLiteralSupport> codeActionLiteralSupport,
		optional<Boolean> isPreferredSupport);

	CodeActionClientCapabilities();

	virtual ~CodeActionClientCapabilities();
};

/// Code action server capabilitY
///
/// codeActionKinds?: CodeActionKind[];
///
struct CodeActionOptions: public WorkDoneProgressOptions
{

	const static String codeActionKindsKey;

	/// CodeActionKinds that this server may return.
	///
	/// The list of kinds may be generic, such as `CodeActionKind.Refactor`,
	/// or the server may list out every specific kind they provide.
	optional<vector<CodeActionKind>> codeActionKinds;


	CodeActionOptions(optional<ProgressToken> workDoneProgress,
		optional<vector<CodeActionKind>> codeActionKinds);

	CodeActionOptions();

	virtual ~CodeActionOptions();
};

struct CodeActionRegistrationOptions:
	public TextDocumentRegistrationOptions,
	public CodeActionOptions
{

	CodeActionRegistrationOptions(
		variant<DocumentSelector, Null> documentSelector,
		optional<ProgressToken> workDoneProgress,
		optional<vector<CodeActionKind>> codeActionKinds);

	CodeActionRegistrationOptions();

	virtual ~CodeActionRegistrationOptions();
};

/// Contains additional diagnostic information about the context in which
/// a code action is run.
///
/// diagnostics: Diagnostic[];
///
/// only?: CodeActionKind[];
///
struct CodeActionContext
{

	const static String diagnosticsKey;

	/// An array of diagnostics known on the client side overlapping the range
	/// provided to the `textDocument/codeAction` request. They are provided so
	/// that the server knows which errors are currently presented to the user
	/// for the given range. There is no guarantee that these accurately
	/// reflect the error state of the resource. The primary parameter to
	/// compute code actions is the provided range.
	vector<Diagnostic> diagnostics;


	const static String onlyKey;

	/// Requested kind of actions to return.
	///
	/// Actions not of this kind are filtered out by the client before being
	/// shown. So servers can omit computing them.
	optional<vector<CodeActionKind>> only;


	CodeActionContext(vector<Diagnostic> diagnostics,
		optional<vector<CodeActionKind>> only);

	CodeActionContext();

	virtual ~CodeActionContext();
};

/// Params for the CodeActionRequest
///
/// textDocument: TextDocumentIdentifier;
///
/// range: Range;
///
/// context: CodeActionContext;
///
struct CodeActionParams:
	public WorkDoneProgressParams,
	public PartialResultParams
{

	// FIXME:
	// Even if the struct is not parseable this functions must be declared
	// because virtual inheritance
	virtual void fillInitializer(ObjectInitializer&){};

	const static String textDocumentKey;

	/// The document in which the command was invoked.
	TextDocumentIdentifier textDocument;


	const static String rangeKey;

	/// The range for which the command was invoked.
	Range range;


	const static String contextKey;

	/// Context carrying additional information.
	CodeActionContext context;


	CodeActionParams(optional<ProgressToken> workDoneToken,
		optional<ProgressToken> partialResultToken,
		TextDocumentIdentifier textDocument,
		Range range,
		CodeActionContext context);

	CodeActionParams();

	virtual ~CodeActionParams();
};

/// A code action represents a change that can be performed in code, e.g. to
/// fix a problem or to refactor code.
///
/// A CodeAction must set either `edit` and/or a `command`. If both are
/// supplied, the `edit` is applied first, then the `command` is executed.
///
/// title: String
///
/// kind?: CodeActionKind
///
/// diagnostics?: Diagnostic[]
///
/// isPreferred?: Boolean
///
/// edit?: WorkspaceEdit
///
/// command?: Command
///
struct CodeAction
{

	const static String titleKey;

	/// A short, human-readable, title for this code action.
	String title;


	const static String kindKey;

	/// The kind of the code action.
	///
	/// Used to filter code actions.
	optional<CodeActionKind> kind;


	const static String diagnosticsKey;

	/// The diagnostics that this code action resolves.
	optional<vector<Diagnostic>> diagnostics;


	const static String isPreferredKey;

	/// Marks this as a preferred action. Preferred actions are used by the
	/// `auto fix` command and can be targeted by keybindings.
	///
	/// A quick fix should be marked preferred if it properly addresses the
	/// underlying error.  A refactoring should be marked preferred if it is
	/// the most reasonable choice of actions to take.
	///
	/// @since 3.15.0
	optional<Boolean> isPreferred;


	const static String editKey;

	/// The workspace edit this code action performs.
	optional<WorkspaceEdit> edit;


	const static String commandKey;

	/// A command this code action executes. If a code action
	/// provides an edit and a command, first the edit is
	/// executed and then the command.
	optional<Command> command;


	CodeAction(String title,
		optional<CodeActionKind> kind,
		optional<vector<Diagnostic>> diagnostics,
		optional<Boolean> isPreferred,
		optional<WorkspaceEdit> edit,
		optional<Command> command);

	CodeAction();

	virtual ~CodeAction();
};

}
