/*
 * ProjectBuilder, an automated build system using the property list format.
 *
 * Copyright (c) 2024 Zormeister.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <plist/plist++.h>
#include <uuid/uuid.h>
#include <CoreFoundation/CoreFoundation.h> // Xcode is high on my machine. It thinks that CF isn't there.
#include <ctime>
#include <unistd.h>
#include <fstream>

#define ArgumentPositionDirectory 1
#define ArgumentPositionCacheDir 2
#define MaxStrLength 2048

struct Dependent {
    char *name;
    char *requiredAt;
    char *requiredOutput;
};

struct BuildInfoMapEntry {
    unsigned int idx;
    bool isBuilt = false;
    char *name {nullptr};
    char *buildCmd;
    char *installCmd;
    char *pathFromDir;
    char *output;
    bool hasDeps = true;
    unsigned int numDeps;
    Dependent *dependents;
};

BuildInfoMapEntry getEntryByIndex(BuildInfoMapEntry *tbl, size_t entry) {
    return tbl[entry];
};

BuildInfoMapEntry getEntryByName(BuildInfoMapEntry *tbl, const char *entry) {
    BuildInfoMapEntry out;
    size_t idx = 0;
    while (true) {
        size_t len = strlen(entry);
        if (tbl[idx].name == nullptr) {
            printf("Failed to find entry %s!\n", entry);
            return out;
        }
        if (!strncmp(tbl[idx].name, entry, len)) {
            return tbl[idx];
            break;
        } else {
            idx++;
        }
    }
};

int mapEntries(plist_t array, BuildInfoMapEntry *tbl, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        plist_t proj = plist_array_get_item(array, i);
        plist_t name = plist_dict_get_item(proj, "Name");
        plist_t deps = plist_dict_get_item(proj, "Dependencies");
        plist_t path = plist_dict_get_item(proj, "Path from Directory");
        plist_t buildCmd = plist_dict_get_item(proj, "Build Command");
        plist_t output = plist_dict_get_item(proj, "Output");
        if (proj == nullptr || name == nullptr || path == nullptr || buildCmd == nullptr || output == nullptr) {
            printf("Failed to get properties at index %d!\n", i);
            return -1;
        }
        tbl[i].numDeps = plist_array_get_size(deps);
        tbl[i].dependents = new Dependent[tbl[i].numDeps];
        plist_get_string_val(name, &tbl[i].name);
        plist_get_string_val(buildCmd, &tbl[i].buildCmd);
        plist_get_string_val(path, &tbl[i].pathFromDir);
        plist_get_string_val(output, &tbl[i].output);
        tbl[i].idx = i;
        
        if (deps == nullptr) {
            tbl[i].hasDeps = false;
        } else {
            printf("deps %d\n", i);
            tbl[i].numDeps = plist_array_get_size(deps);
            tbl[i].hasDeps = true;
            printf("nd = %d", tbl[i].numDeps);
            for (unsigned int j = 0; j < tbl[i].numDeps; j++) {
                plist_t dep = plist_array_get_item(deps, j);
                if (dep == nullptr) {
                    printf("what\n");
                    return -1;
                }
                plist_t name = plist_dict_get_item(dep, "Name");
                plist_t requiredAt = plist_dict_get_item(dep, "Required At"); // starts from the source root.
                plist_t requiredOut = plist_dict_get_item(dep, "Required Output"); // starts from the source root.
                if (name == nullptr || requiredAt == nullptr) {
                    printf("Missing properties at dependency %d\n", j);
                    return -1;
                }
                plist_get_string_val(name, &tbl[i].dependents[j].name);
                plist_get_string_val(requiredAt, &tbl[i].dependents[j].requiredAt);
                plist_get_string_val(requiredOut, &tbl[i].dependents[j].requiredOutput);
            }
        }
    }
    return 0;
}

int build(const char *srcdir, const char *location, BuildInfoMapEntry entry, bool sourcesAlreadyPrepped) {
    char cmd[MaxStrLength];
    printf("==== Building %s ====\n", entry.name);
    if (sourcesAlreadyPrepped == false) {
        snprintf(cmd, MaxStrLength, "cp -rv %s/%s %s/Sources/%s", srcdir, entry.pathFromDir, location, entry.pathFromDir);
        printf("%s", cmd);
        system(cmd);
        bzero(cmd, MaxStrLength);
    }
    snprintf(cmd, MaxStrLength, "%s/Sources/%s", location, entry.pathFromDir);
    chdir(cmd);
    printf("%s\n", cmd);
    printf("%s\n", entry.buildCmd);
    if (system(entry.buildCmd)) {
        printf("Build command for %s failed!\n", entry.name);
        return -1;
    }
    entry.isBuilt = true;
    return 0;
}

int moveToBinaryDir(const char *location, BuildInfoMapEntry entry) {
    char cmd[MaxStrLength];
    printf("==== Installing %s to binary directory ====\n", entry.name);
    snprintf(cmd, MaxStrLength, "mkdir -p %s/Binaries/%s/%s", location, entry.pathFromDir, entry.output);
    printf("%s", cmd);
    system(cmd);
    snprintf(cmd, MaxStrLength, "cp -rv %s/Sources/%s/%s/* %s/Binaries/%s/%s", location, entry.pathFromDir, entry.output,  location, entry.pathFromDir, entry.output);
    printf("%s", cmd);
    system(cmd);
    return 0;
}

int main(int argc, const char * argv[]) {
    printf("ProjectBuilder, built on %s, now building\n", __TIMESTAMP__);
    if (argv[ArgumentPositionDirectory]) {
        char filename[MaxStrLength];
        FILE *file;
        uint32_t filesize;
        char *buffer;
        snprintf(filename, MaxStrLength, "%s/BuildInfo.plist", argv[ArgumentPositionDirectory]);
        file = fopen(filename, "r");
        if (file == nullptr) {
            printf("==== Failed to open file! ====\n");
            return -1;
        }
        fseek(file, 0, SEEK_END);
        filesize = ftell(file); // shhhhhh
        fseek(file, 0, SEEK_SET);
        buffer = (char *)malloc(filesize + 1);
        fread(buffer, filesize, 1, file);
        fclose(file);
        plist_t plist;
        plist_format_t fmt = PLIST_FORMAT_XML;
        plist_from_memory(const_cast<char *>(buffer), filesize, &plist, &fmt);
        if (plist == nullptr) {
            printf("==== Failed to read file @ %s ====\n", filename);
            return -1;
        }
        plist_t array = plist_dict_get_item(plist, "Projects");
        if (array == nullptr) {
            printf("==== Failed to obtain Projects object! ====\n");
            return -1;
        }
        uint32_t projectCount = plist_array_get_size(array);
        CFUUIDRef tmpId = CFUUIDCreate(kCFAllocatorDefault); // make cross-platform?
        CFUUIDBytes bytes = CFUUIDGetUUIDBytes(tmpId);
        char uuid[40];
        snprintf(uuid, 40, "%x%x%x%x-%x%x-%x%x-%x%x-%x%x%x%x%x%x", bytes.byte0, bytes.byte1, bytes.byte2, bytes.byte3, bytes.byte4, bytes.byte6, bytes.byte7, bytes.byte8, bytes.byte9, bytes.byte10, bytes.byte11, bytes.byte12, bytes.byte13, bytes.byte14, bytes.byte15);
        CFRelease(tmpId);
        char location[MaxStrLength];
        if (argv[ArgumentPositionCacheDir]) {
            snprintf(location, MaxStrLength, "%s/com.zormeister.projectbuilder/BuildCaches/%s", argv[ArgumentPositionCacheDir], uuid);
        } else {
            printf("==== Missing cache argument! ====\n");
            return -1;
        }
        bzero(filename, MaxStrLength);
        snprintf(filename, MaxStrLength, "%s/BuildDate.txt", location);
        char date[MaxStrLength];
        std::ofstream buildDate;
        buildDate.open(filename);
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%c", &tstruct);
        snprintf(date, MaxStrLength, "%s was built on %s", uuid, buf);
        printf("%s\n", date);
        buildDate << date; // FIXME: doesn't seem to work
        buildDate.close();
        char cmd[MaxStrLength];
        snprintf(cmd, MaxStrLength, "mkdir -p %s", location);
        system(cmd);
        bzero(cmd, MaxStrLength);
        snprintf(cmd, MaxStrLength, "mkdir -p %s/Sources", location);
        system(cmd);
        bzero(cmd, MaxStrLength);
        snprintf(cmd, MaxStrLength, "mkdir -p %s/Binaries", location);
        system(cmd);
        BuildInfoMapEntry *tbl = (BuildInfoMapEntry *)calloc(projectCount + 1, sizeof(BuildInfoMapEntry));
        if (mapEntries(array, tbl, projectCount)) {
            printf("==== Failed to map entries! ====\n");
            return -1;
        }
        for (int i = 0; i < projectCount; i++) {
            if (tbl[i].hasDeps) {
                bzero(cmd, MaxStrLength);
                snprintf(cmd, MaxStrLength, "cp -rv %s/%s %s/Sources/%s", argv[ArgumentPositionDirectory], tbl[i].pathFromDir, location, tbl[i].pathFromDir);
                printf("%s", cmd);
                system(cmd);
                bzero(cmd, MaxStrLength);
                for (int d = 0; d < tbl[i].numDeps; d++) {
                    BuildInfoMapEntry entry = getEntryByName(tbl, tbl[i].dependents[d].name);
                    printf("%s", entry.name);
                    if (entry.name == nullptr) {
                        printf("==== Dependency for %s not found! ====\n", tbl[i].name);
                    }
                    if (entry.isBuilt) {
                        printf("==== Dependency %s for %s is already built, skipping ====\n", entry.name, tbl[i].name);
                        char lcmd[MaxStrLength]; // assume binary is already in the required directory
                        snprintf(lcmd, MaxStrLength, "ln -s %s/Binaries/%s/%s %s/Sources/%s/%s", location, entry.pathFromDir, entry.output, location,  tbl[i].pathFromDir, tbl[i].dependents[d].requiredAt);
                        system(lcmd);
                    } else {
                        if (build(argv[ArgumentPositionDirectory], location, entry, false)) {
                            printf("==== Build failure at %s! ====\n", entry.name);
                            return -1;
                        }
                        moveToBinaryDir(location, entry);
                        char lcmd[MaxStrLength];
                        snprintf(lcmd, MaxStrLength, "ln -s %s/Binaries/%s/%s/%s %s/Sources/%s/%s", location, entry.pathFromDir, entry.output, tbl[i].dependents[d].requiredOutput, location,  tbl[i].pathFromDir, tbl[i].dependents[d].requiredAt);
                        system(lcmd);
                    }
                }
                if (build(argv[ArgumentPositionDirectory], location, tbl[i], true)) {
                    printf("==== Build failure at %s! ====\n", tbl[i].name);
                    return -1;
                }
                moveToBinaryDir(location, tbl[i]);
            } else {
                if (tbl[i].isBuilt == false) {
                    if (build(argv[ArgumentPositionDirectory], location, tbl[i], false)) {
                        printf("==== Build failure at %s! ====\n", tbl[i].name);
                        return -1;
                    }
                    moveToBinaryDir(location, tbl[i]);
                }
            }
        }
        free(buffer);
        free(array);
    } else {
        printf("Missing directory argument!\n");
        return -1;
    }
    printf("==== All done! ====\n");
    return 0;
}

