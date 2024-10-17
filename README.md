# ProjectBuilder

An automated build system wrapper that does all the work for you.

## Usage and Configuration

Syntax:
`projectbuilder <TARGET_DIRECTIRY> <CACHE_DIRECTORY>`

TARGET_DIRECTORY is the folder where you've placed the `BuildInfo.plist` file, (see `ExamplePlist.plist` on how it's configured)

CACHE_DIRECTORY is where ProjectBuilder stores a cache of the source code and build output, two folders are under `com.zormeister.projectbuilder/UUID/`,  `Sources` and `Binaries`, which should be self-explanatory 

## TODO

- Extend available configuration to run cleanup and pre-build commands
- Add an available toggle for exiting on build failure
- Create a daemon + ctl for routinely building, IE: every 4 hours
