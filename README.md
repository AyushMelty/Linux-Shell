# Linux-Shell
* main.c is the main code to run, use the make command to do it 

External commands-
1)ls= list all directories.
  commands=> -a(do not ignore entries starting with .), -m(gives , separated list)
  assumption=> ls -a -m=> invalid commands
2)cat= opens the file.
  commands=> -s(suppress multiple empty lines),-n(gives line number)
  assumption=> if file not found "NO such file" will be printed.
3)mkdir= make directories
  commands=>-v(tells every time directory created or not),-p(do not state anything)
  assumption=> mkdir -p -v=>invalid commands
4)rm= remove files
  commands=>-d(remove empty directories also),-i(asks before removing a file)
5)date= display date
  commands=>-R(output date and time in RFC 5322 format),-u(shows time in UTC)
Internal commands-
1)echo
  commands=>-n(do not output the trailing newline),--help
2)pwd= output current working directory
 commands=>-P,-L 
 assumption=> pwd -P -L ="Invalid Command"
3)cd= changes directory
  commands=>~(changes directory to home),..(changes to previous directory)
  assumption=>if invalid path is entered after cd, "Invalid Path\n"

Test Case:

ls -a
ls -a &t
cd ..
mkdir one two three
rm one
rm -d one
pwd -L
echo hello world
echo --help  
