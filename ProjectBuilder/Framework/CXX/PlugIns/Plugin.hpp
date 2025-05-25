//
//  Plugin.hpp
//  ProjectBuilder
//
//  Created by Zormeister on 18/5/25.
//

#ifndef PROJECTBUILDER_PLUGINS_PLUGIN_HPP
#define PROJECTBUILDER_PLUGINS_PLUGIN_HPP

#include <cstdint>

/* Fucking hell. Calling this ProjectBuilder V3 because I genuinely DONT want my shit to be monolithic */

namespace ProjectBuilder {

/* Opaque Pointer */
typedef void *PluginRef;

struct PluginDispatchTable {
    uint32_t Version;

    PluginRef (*CreateRef)(void);
    bool (*InitRef)(PluginRef plugin);

    /* Plug-In callbacks */
    bool (*OnBuildStart)(PluginRef plugin);

};

}

extern "C" const struct PluginDispatchTable pbplugin_dispatch_table;

#endif /* PROJECTBUILDER_PLUGINS_PLUGIN_HPP */
