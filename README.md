# MK7 PID Grabber
This is a Principal ID grabber CTRPluginFramework designed for Mario Kart 7 on the Nintendo 3DS.

It's purpose is to allow people to report cheaters in their in-game lobbies or opponent list on platforms like [Pretendo](https://pretendo.network/).

> [!TIP]
> The Principal ID is the identifier of any user on the Nintendo 3DS. It's basically the friend code of the system but packed into a different series of numbers. It helps users to be unique and to differentiate them.

# How to use the plugin
Head over to the [releases](https://github.com/H4x0rSpooky/mk7-pid-grabber/releases/latest) and grab the latest `mk7-pid-grabber.3gx` file.

Create a folder on your system's sd card: `sd:luma/plugins/<Title ID>/`.

Use the the following `Title ID` depending on your version:
- **USA**: `0004000000030800`
- **EUR**: `0004000000030700`
- **JPN**: `0004000000030600`
- **KOR**: `0004000000030A00`

> [!NOTE]
> There are more versions however those are untested. If yours isn't included, find it through `FBI` under titles or [3dsdb](https://3dsdb.com/).

Once that's done, place the `mk7-pid-grabber.3gx` file into the same folder.

While you're in the HOME-menu, open the `Rosalina Menu`. The key combination to enter it is `L + DPad Down + Select`. Navigate to the `Plugin Loader`, press `A` on it once to change it to `Enabled` and go to `Save Settings`. After that, close the menu again and launch your game. It should flash blue once, which indicates that the plugin has successfully been loaded. If that doesn't occur, you did something wrong and should go through these steps again.

The button activator for the menu is `Select`.

# How to build the project
| Required Downloads |
|:---------------------------|
| [git](https://git-scm.com/downloads) |
| [devkitPro](https://devkitpro.org/wiki/Getting_Started) |

Download the source code and follow the steps to install [CTRPluginFramework](https://gitlab.com/thepixellizeross/ctrpluginframework). Don't forget to also run `pacman -S 3gxtool` in order to install [3gxtool](https://gitlab.com/thepixellizeross/3gxtool) which is required to compile `.3gx` files.

Once all the steps are completed, run the `build.bat` file inside the source and let it compile the file. After that, you can simply use it like described above this section.

# Reporting issues or suggesting features
Join the [Discord](https://discord.com/invite/QGUNRK9Xw7) server.

# Credits
- H4x0rSpooky for creating this project
- [Anto726](https://github.com/Anto726) for the [CTRPluginFramework-RevolutionBase](https://github.com/Anto726/CTRPluginFramework-RevolutionBase)
- [Nanquitas](https://github.com/Nanquitas) for creating the CTRPluginFramework
