# ProjectBuilder

An automated build system wrapper that does all the work for you.

## Usage and Configuration

Syntax:
`projectbuilder <TARGET_DIRECTIRY> <CACHE_DIRECTORY>`

TARGET_DIRECTORY is the folder where you've placed the `BuildInfo.plist` file, (see `ExamplePlist.plist` on how it's configured)

CACHE_DIRECTORY is where ProjectBuilder stores a cache of the source code and build output, two folders are under a `com.zormeister.projectbuilder/UUID/`,  `Sources` and `Binaries`, which should be self-explanatory 