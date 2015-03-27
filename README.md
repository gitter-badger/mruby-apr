mruby-apr
=========

The [Apache Portable Runtime Project]((https://apr.apache.org/)) is a collection of "software libraries that provide a predictable and consistent interface to underlying platform-specific implementations." `mruby-apr` leverages the work done by the APR developers to provide cross-platform functions to mruby without having to repeat this work.

Building
--------

To build `mruby` with `mruby-apr`, you need to set some settings in your `build_config.rb` file. These just tell the compiler where to find the apr headers & libraries, as well as any system libraries apr
depends on for your given platform.

NOTE: [APR](https://apr.apache.org/) is not included. You can download it [here](https://apr.apache.org/download.cgi). It uses cmake, so building on any platform should be easy.

Once built, you can configure mruby to use it. Heres the function I'm using my build_config.rb right now (on Windows):

```Ruby
def configure_apr_lib(conf, link_type = :dynamic)
  # ../apr-1.5.1/ is the directory I extracted the APR lib into
  conf.cc.include_paths << "../apr-1.5.1/include"
  conf.cxx.include_paths << "../apr-1.5.1/include"

  # You need a preprocessor macro defined to use the static library version of APR
  #
  if link_type = :static
    conf.linker.libraries << "apr-1"
    conf.cc.defines << "APR_DECLARE_STATIC"
    conf.cxx.defines << "APR_DECLARE_STATIC"
  else
    conf.linker.libraries << "libapr-1"
  end

  if ENV['OS'] =~ /windows/i
    # apr.h is generated specifically for each platform by cmake.
    # I'm having cmake generate the project files in a folder
    # called "win" under the apr root folder on windows.
    conf.cc.include_paths << "../apr-1.5.1/win"
    conf.cxx.include_paths << "../apr-1.5.1/win"
    if ENV['DEBUG']
      conf.linker.library_paths << "../apr-1.5.1/win/Debug"
    else
      conf.linker.library_paths << "../apr-1.5.1/win/Release"
    end

    conf.linker.libraries << "Advapi32"
    conf.linker.libraries << "Shell32"
  else
    # I haven't gotten here yet.. if you're on linux, you'll know what to do ;)
    raise "No APR build settings configured for this platform"
  end
end
```
API
---

`mruby-apr` defines the APR module along with a set of child modules & classes. All of the functionality of `mruby-apr` can be accessed through this module. In the `APR` module, behavior is permitted to differ from the CRuby standard significantly (opting instead for a more direct APR wrapper). When possible, the routines in APR are wrapped up in a standard Ruby API (for example, by defining methods on the `Kernel` or `Process` modules).

Docs are being generated by a quick-and-dirty markdown extractor dubbed `md-doc.rb` (it's in the repo). Just look in the `doc/` folder for the full API. I sort of like the bare markdown approach, but if you know a better way to document C & Ruby code for mruby let me know!

Note: The docs for a particular module may be split among files, as the doc files are 1-to-1 with the source. So, some `Kernel` methods are defined in `docs/src/mrb_apr_.md`, while others are in `docs/mrblib/kernel.md`

The API is pretty small at the moment, so I'll just throw it here for quick access:

# Class APR::Process

## `::new()`
Creates a new Process object.
To execute the process, configure this object (as needed) and run `APR::Process#exec`

Notes:

- Sets default cmdtype == `:APR_SHELLCMD_ENV `

## `::wait(pid)`
Blocks until the process finishes <br/>
Returns the exit code

## `#cmdtype_set(cmdtype)`
- Args
  + cmdtype: One of
    - `:APR_SHELLCMD`
    - `:APR_PROGRAM`
    - `:APR_PROGRAM_ENV`
    - `:APR_PROGRAM_PATH`
    - `:APR_SHELLCMD_ENV`

## `#exec(argv)`
- Args
  + argv: An array of strings. `argv[0]` should be the process name.
- Returns
  + `self`

## `#pid()`
Returns the pid of the process

## `#wait()`
Blocks until the process finishes <br/>
Returns `self`

# Module APR::TCP
## `::get_open_port`
Return an open TCP port number

# Object ENV
## `#[](name)`
Returns the value of the environemnt variable named `name`

## `#[]=(name, value)`
Sets the value of the environemnt variable named `name` to `value`

## `#delete(name)`
Deletes the environemnt variable named `name`

# Module Kernel

## `#system(*command)`
Runs a process, waits for it to finish, and returns the exit code.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

## `#spawn(*command)`
Starts a new process and returns the PID.
Does not wait for the process to end.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

# Module Process

## `::spawn(*command)`
Starts a new process and returns the PID.
Does not wait for the process to end.
- Args
  + `command`. One of:
     - commandline : command line string which is passed to the standard shell
     - cmdname, arg1, ... : command name and one or more arguments (no shell)

## `::wait(pid)`
Waits for the process with the given PID to exit. <br/>
Returns the exit code (no Process::Status implemented yet)
