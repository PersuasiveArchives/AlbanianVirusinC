The infamous Albanian virus that became a meme and was posted widely on social media.
How it works is
The code creates a window with the title "Virus Alert!" and displays a message ("Hi, I am an Albanian virus..."). Three buttons ("Yes", "No", "Cancel") are created, and when any button is clicked, the window closes. It uses Windows API functions like `CreateWindow`, `MessageBox`, and `PostMessage` to handle window creation and button actions.

### Windows Supported versions
It only can be compiled with Windows XP to later.
If you want linux i will do it in the future.

## Compile

To compile the c code
you need the prerequisities
GCC

to compile type this code into the terminal
```
gcc index.c -o output.exe -lgdi32 -luser32


```
then it should compile, no need dependencies it uses windows api
