//
//  main.cpp
//  projectbuilder
//
//  Created by Zormeister on 21/2/2025.
//

#include <CoreFoundation/CoreFoundation.h>
#include <ProjectBuilder/PBProject.h>

#include <sys/stat.h>
#include <sysdir.h>
#include <pwd.h>

static bool DirectoryExists(const char *dirPath) {
    struct stat s;
    if (stat(dirPath, &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

static bool DirectoryExistsCF(CFStringRef cf) {
    struct stat s;
    if (stat(CFStringGetCStringPtr(cf, kCFStringEncodingASCII), &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

static void CreateDirectory(const char *path) {
    mkpath_np(path, 0755); // hopefully it expects the octal format???
}

#define DEFAULT_BUILDROOTS_DIRECTORY "/Library/BuildRoots"

int main(int argc, const char * argv[]) {
    /* This is me testing my shitcode. */
    struct passwd *pwd = getpwuid(getuid());
    size_t size = strlen("/Users/") + strlen(pwd->pw_name) + strlen(DEFAULT_BUILDROOTS_DIRECTORY);
    char *tmp = (char *)malloc(size);
    snprintf(tmp, size, "/Users/%s%s", pwd->pw_name, DEFAULT_BUILDROOTS_DIRECTORY);
    if (!DirectoryExists(tmp)) {
        CreateDirectory(tmp);
    }
    // thus we have created our buildroots directory. clap clap.
    // i need to test PBDiskImage smh
    free(tmp);
    return 0;
}
