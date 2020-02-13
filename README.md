[![Build Status](https://dev.azure.com/lewissall/hpdporg/_apis/build/status/hpdporg.datap?branchName=master)](https://dev.azure.com/lewissall/hpdporg/_build/latest?definitionId=2&branchName=master)

# rep #

**Rep** project.

Scans **.rep** representation files and processes their contents. Out of the box, **rep** can be viewed as a sed-like tool that can process and replace textual files, or a processed file generator like Perl that can compile output from textual templates and structured wildcard replacements. It is meant as an intermediary, overly simplistic tokenized format that defines the concept or design of the problem it is trying to solve. It works on stripped-down delimited files, like .tsv (.csv) files and is meant to provide a view of the 'significance' of a solution. **.rep** delimited files should be worked on just in Notepad or a similar text editor, with ideally an efficient, wastefree, view of what you are trying to accomplish. **.rep** has an exposed interface and can be extended with other tools (**hpdp** project extensions are planned). 

## Features ##
* **storeFile**: store the result of your representation in files with the **storeFile** term.
* **retrieveFile**: pull textual data from files using the retrieveFile term.
* **letters**: represent textual data with the **letters** term or its shorthand, just a space ` `. 
* Reference appending: Append textual data by simply chaining their references one after another. *For example: `ref1 ref2` with delimiters (tab) in-between*.
* List: represent a List by simply indenting the list members below the list name.
* **replaceLettersList**: replace wildcards in textual data with the **replaceLettersList** term. Provide the textual reference, List of replacements reference, and wildcard that should be replaced. Every occurence will be replaced, but by each member of the List, not necessarily by the same replacement value.

## Usage ##
* You can use the prebuilt library or build from source on your platform.
* You can use from assembly or link against the function signatures with the C API. A datap.h header is included.
* See the examples and tests to gain familiarity.

## Building ##
* Includes pre-built, libraries and executable, along with VS projects.
* Includes GoogleTest Unit tests.
* Includes the **fasmg** assembler as an external library.
* Includes **datap** as an external library.

## Platforms ##
* x86_64, Windows only
* **.rep** file newlines use \n in tests and \crlf in the built .exe since this is currently Windows-only. The included .gitattributes should allow this to work easily. Just a reminder that saving with \cr\lf will not work with tests unless if you override the delimiter in the source and rebuild, which is possible and has been tested.
* (Other platform support may follow)
