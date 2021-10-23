# 🍋 Lime
Macro creation tool for MacOs

## Why Does lime require accessibility?
Lime requires the Accessibility API to perform macro actions, such as pressing keys. Disabling accessibility will make lime a useless piece of software that does nothing.

## How do I use lime?
First install it from the release page. Then open up a wonderfull text editor and create a new file and name it ```cool_macro.ini``` and add the following text to that file
```ini
[macro]
name = "Super Epic Macro"
keypress = "hi "
```
This macro will type hi until we stop it. To load it run
```bash
lime new cool_macro.ini
```
BUT WAIT! Before we activate it, how will I disable it??? Its simple to disable a macro while its running click on the button in the upper left hand corner of the screen with the ```X``` button. This will halt all running macros, don't worry it goes away when no macros are running.
Now you can load it with:
```bash
lime load cool_macro
# Loading Super Epic Macro
# Loaded Super Epic Macro.
```

## How it works
```
Let the daemon know we have a new macro ->
Link the macro file to ~/.config/lime/macros/<file>.lime ->
Check if the macro is enabled, if it is perform the action and display gui buttons
```


## Uninstall Lime
If you want to uninstall lime, its not hard. Simply run the following command
```bash
# Make sure all of you're macros are disabled
killall lime
sudo rm $(which lime)
# If the launch agent ius installed remove it with below
rm $HOME/Library/LaunchAgents/dev.interfiber.lime.daemon.plist
```