# Ready Player Me Unreal SDK

This is an open source **Unreal Engine** plugin that contains all the core functionality required for loading and displaying avatars.

Please visit the online documentation and join our public `discord` community.

![](https://i.imgur.com/zGamwPM.png) **[Online Documentation]( https://readyplayer.me/docs )**

![](https://i.imgur.com/FgbNsPN.png) **[Discord Channel]( https://discord.gg/9veRUu2 )**


### Dependencies

**glTFRuntime** An open source third party plugin with functionality for downloading and importing assets from GLTF and GLB files.
The plugin can be found on GitHub [here](https://github.com/rdeioris/glTFRuntime), but can also be purchased from the Unreal Marketplace.

[Discord channel](https://discord.gg/DzS7MHy)

### Requirements

- Unreal Engine Version 4.27 or higher


### Add ReadyPlayerMe and glTFRuntime plugins

There are three ways you can add the ReadyPlayerMe and the glTFRuntime plugins to your project. Add them as submodules, clone the repos, or paste the plugins inside of the Plugins folder.

- To add the plugins to your project as a submodules, run the following command in the terminal from your project folder. Make sure that the ReadyPlayerMe plugin is named as ReadyPlayerMe.

"""
git submodule add --name glTFRuntime -- https://github.com/rdeioris/glTFRuntime.git Plugins/glTFRuntime ; cd Plugins/glTFRuntime ; git checkout $(git describe --tags --abbrev=0) ; cd ../.. ; \
git submodule add --name ReadyPlayerMe -- https://github.com/readyplayerme/rpm-unreal-sdk.git Plugins/ReadyPlayerMe
cd Plugins/ReadyPlayerMe ; git checkout $(git describe --tags --abbrev=0) ; cd ../..
"""

- To clone the plugins into your project, run the following command in the terminal from your project folder.

"""
git clone https://github.com/rdeioris/glTFRuntime.git Plugins/glTFRuntime ; \
cd Plugins/glTFRuntime ; \
git checkout $(git describe --tags --abbrev=0) ; \
cd ../.. ; \
git clone https://github.com/readyplayerme/rpm-unreal-sdk.git Plugins/ReadyPlayerMe ; \
cd Plugins/ReadyPlayerMe ; \
git checkout $(git describe --tags --abbrev=0) ; \
cd ../..
"""

### Update ReadyPlayerMe and glTFRuntime plugins

To update the plugins paste the following command in the terminal from your project folder. This will fetch and switch the plugin repositories to the latest stable release.

"""
cd Plugins/glTFRuntime ; git fetch --tags ; git checkout $(git describe --tags --abbrev=0) ; cd ../.. ; \
cd Plugins/ReadyPlayerMe ; git fetch --tags ; git checkout $(git describe --tags --abbrev=0) ; cd ../..
"""

## Quick Start

A demo map is included in the plugin for demonstrating how the Ready Player Me avatars are loaded aat runtime.
