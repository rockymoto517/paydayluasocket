# LuaSocket


LuaSocket is a Lua extension library composed of two parts:

1. a set of C modules that provide support for the TCP and UDP transport layers, and
2. a set of Lua modules that provide functions commonly needed by applications that deal with the Internet.

---
This is an attempt at making the LuaSocket library compatible with Payday 2's modloader `SuperBLT`.

## Building
1. Open an instance of `x86 Native Tools Command Prompt`.
2. `cd` into a local copy of the repository.
3. Generate the build files with `cmake -B build -G Ninja` or your preferred build system.
    * If you want LSP integration, this cmake command also generates a `compile_commands.json` file
4. If you generated the build files with Ninja, `cd build` to move into the build folder and compile using `ninja`.
5. After compiling, you should have a file called `luasocket.dll` which can be loaded as a **BLT Native Module**.
