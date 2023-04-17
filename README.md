# Ready Player Me Unreal SDK

This is an open source **Unreal Engine** plugin that contains all the core functionality required for loading and displaying avatars.

Please visit the online documentation and join our public `discord` community.

![](https://i.imgur.com/zGamwPM.png) **[Online Documentation]( https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-sdk )**

![](https://i.imgur.com/FgbNsPN.png) **[Discord Channel]( https://discord.gg/9veRUu2 )**


### Dependencies

**glTFRuntime** An open source third party plugin with functionality for downloading and importing assets from GLTF and GLB files.
The plugin can be found on GitHub [here](https://github.com/rdeioris/glTFRuntime), but can also be purchased from the Unreal Marketplace.

[Discord channel](https://discord.gg/DzS7MHy)

### Requirements

- Unreal Engine Version 4.27 or higher


### Add ReadyPlayerMe and glTFRuntime plugins

There are three ways you can add the **ReadyPlayerMe** and the **glTFRuntime** plugins to your project. Add them as submodules, paste the plugins inside of the **Plugins** folder, or add the blueprint version of the plugins to the Engine.

- To add the plugins to your project as a submodules, run the following command in the terminal from your project folder. This case applies if you already have your project in a git repository. This is preferred way of setting up the plugins.

```
git submodule add --name Plugins/glTFRuntime -- https://github.com/rdeioris/glTFRuntime.git Plugins/glTFRuntime ; cd Plugins/glTFRuntime ; git checkout $(git describe --tags $(git rev-list --tags --max-count=1)) ; cd ../.. ; git submodule add --name Plugins/ReadyPlayerMe -- https://github.com/readyplayerme/rpm-unreal-sdk.git Plugins/ReadyPlayerMe ; cd Plugins/ReadyPlayerMe ; git checkout $(git describe --tags $(git rev-list --tags --max-count=1)) ; cd ../..
```

- To paste the plugins inside of the Plugins folder, create a **Plugins** folder from the root of your project, download the latest tags of the [glTFRuntime](https://github.com/rdeioris/glTFRuntime.git) and [ReadyPlayerMe](https://github.com/readyplayerme/rpm-unreal-sdk.git) plugins into it. Rename the **rpm-unreal-sdk** plugin folder to the **ReadyPlayerMe**.

- To add the blueprint version of the plugins, find the **ReadyPlayerMe** and **glTFRuntime** plugins attached in the [Latest Release](https://github.com/readyplayerme/rpm-unreal-sdk/releases/latest), copy the plugin folders ReadyPlayerMe and glTFRuntime into the `ENGINE_VERSION/Engine/Plugins` folder.

### Update ReadyPlayerMe and glTFRuntime plugin submodules

To update the submodules of the plugins, paste the following command in the terminal from your project folder. This will fetch and switch the plugin repositories to the latest stable release.

```
cd Plugins/glTFRuntime ; git fetch --tags ; git checkout $(git describe --tags $(git rev-list --tags --max-count=1)) ; cd ../.. ; cd Plugins/ReadyPlayerMe ; git fetch --tags ; git checkout $(git describe --tags $(git rev-list --tags --max-count=1)) ; cd ../..
```

## Quick Start

A demo map is included in the plugin for demonstrating how the **Ready Player Me** avatars are loaded at runtime.
