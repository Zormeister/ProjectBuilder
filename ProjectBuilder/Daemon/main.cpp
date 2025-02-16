// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <CoreFoundation/CoreFoundation.h>
#include <SystemConfiguration/SystemConfiguration.h>
#include <xpc/xpc.h>
#include <dispatch/dispatch.h>
#include <os/log.h>

#define ENABLE_LOGS 1
#if ENABLE_LOGS
#define LOG(...) os_log_info(logger, __VA_ARGS__)
#else
#define LOG(...) while (0) {}
#endif

#define LOG_ERROR(...) os_log_error(logger, __VA_ARGS__)

void process_build_request();

xpc_connection_t ourXPC;
xpc_connection_t notMyXPC;

os_log_t logger;

struct BuildRequestData {
    const char *Destination;
    bool BuildOnly;
};

void process_request(xpc_connection_t source, xpc_object_t obj) {
    size_t size;
    
    uint8_t *xmlRawData = (uint8_t *)xpc_dictionary_get_data(obj, "BuildPlist", &size);
    if (!xmlRawData) {
        LOG_ERROR("I don't hate you.");
        xpc_object_t response = xpc_dictionary_create(NULL, NULL, 0);
        xpc_dictionary_set_string(response, "Error", "Bad Data");
        xpc_connection_send_message(source, response);
    }
    
    // Convert to CFData so it works
    CFDataRef data = CFDataCreate(kCFAllocatorDefault, xmlRawData, size);
    CFPropertyListFormat fmt = kCFPropertyListXMLFormat_v1_0;
    CFPropertyListCreateWithData(kCFAllocatorDefault, data, kCFPropertyListImmutable, &fmt, NULL);
}

int main(int argc, const char * argv[]) {
    ourXPC = xpc_connection_create_mach_service("com.Zormeister.ProjectBuilder", NULL, XPC_CONNECTION_MACH_SERVICE_LISTENER | XPC_CONNECTION_MACH_SERVICE_PRIVILEGED);
    
    logger = os_log_create("com.Zormeister.ProjectBuilder", "daemon");
    
    xpc_connection_set_event_handler(ourXPC, ^(xpc_object_t _Nonnull object) {
        LOG("Who's there. (%p)", object);
        xpc_connection_set_event_handler((xpc_connection_t)object, ^(xpc_object_t event) {
            if (event == XPC_ERROR_CONNECTION_INVALID) {
                LOG("Are you still there?");
                return;
            } else if (xpc_get_type(event) != XPC_TYPE_DICTIONARY) {
                LOG("Self test error.");
                return;
            }
            
            process_request((xpc_connection_t)object, event);
        });
    });
    
    SCPreferencesRef pref = SCPreferencesCreate(kCFAllocatorDefault, CFSTR("com.Zormeister.ProjectBuilder"), NULL);
    
    CFPropertyListRef plist = SCPreferencesGetValue(pref, CFSTR("AutoRun"));
    if (CFGetTypeID(plist) == CFBooleanGetTypeID()) {
        CFBooleanRef boolRef = (CFBooleanRef)plist;
        if (boolRef == kCFBooleanTrue) {
            CFRunLoopRef rl = CFRunLoopGetCurrent();
        }
    }
    
    CFPropertyListRef bcd = SCPreferencesGetValue(pref, CFSTR("BuildCacheDirectory"));
    if (bcd && CFGetTypeID(bcd) == CFStringGetTypeID()) {
        
    }
    
    
    
    CFRunLoopRef rl = CFRunLoopGetMain();
    
    xpc_connection_resume(ourXPC);
    
    dispatch_main();

    // Should never get here either.
    return 0;
}
