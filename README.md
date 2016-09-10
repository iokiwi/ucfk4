For documentation, see http://ecewiki.elec.canterbury.ac.nz/mediawiki/index.php/UCFK4

The directory structure is:
```
apps         --- contains a sub-directory for each application
drivers      --- device driver modules (hardware independent)
drivers/avr  --- device driver modules specifically for AVR architecture
drivers/test --- device driver modules for test scaffold
doc          --- documentation
etc          --- miscellaneous scripts and makefile templates
fonts        --- fonts and font creation program
utils        --- utility modules
```

#### Mac Environment setup
<hr>

1. Install [Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12")
2. Install [MacPorts](https://www.macports.org/")
```bash
xcodebuild -license
```
```bash
xcode-select --install
```
```bash
port install avr-gcc avr-libc dfu-programmer
```
