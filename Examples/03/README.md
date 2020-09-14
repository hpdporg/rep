Example 03.

This example provides a more organized example of how to generate large text files using a table of inputs.

You can define the files and paths in the mainConfig frontend and and output file should be built by double-clicking **rep.exe**.

This example should be used as-is with minor tweaks to **utility.rep** if needed. The terms such as **replaceLettersFlow** are still experimental.

Known issues: 
- **replaceLettersFlow** must take match text (**REPLACE_BLOCK** in this example) as a parameter, but must also be defined earlier (here with **replaceRef**). This is an issue because the reference must be defined though it is not used. (Workaround-> provide match text to **replaceLettersFlow** but also have a reference to the match text anywhere in the **.rep** file)
- Parsing csv files as **flow**s (tables) must not contain a blank line at the end. (Workaround-> delete last line in a .csv file if blank)