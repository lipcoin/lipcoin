
Debian
====================
This directory contains files used to package lipcoind/lipcoin-qt
for Debian-based Linux systems. If you compile lipcoind/lipcoin-qt yourself, there are some useful files here.

## lipcoin: URI support ##


lipcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install lipcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your lipcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/lipcoin128.png` to `/usr/share/pixmaps`

lipcoin-qt.protocol (KDE)

