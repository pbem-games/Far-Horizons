# FAR HORIZONS

> This README is available on GitHub at [playbymail/Far-Horizons](https://github.com/playbymail/Far-Horizons/blob/main/README.md).

FAR HORIZONS is a strategic role-playing game of galactic exploration, trade, diplomacy, and conquest.
The first and second editions were designed for play by postal mail.
Later editions were designed for play by electronic mail.
The seventh edition rules and source code were released in 1999 by [Rick Morneau](http://rickmor.x10.mx).

    Far Horizons is a play-by-email strategy game that I designed several
    years ago.  In this game, each player plays the role of an intelligent
    species that can build starships, explore the galaxy, start new colonies,
    meet other species, go to war, and so on.  Far Horizons is a rich and
    realistic simulation, and the rules are considerably longer and more
    complex than most similar games.  A typical game can last anywhere from
    6 months to a year.  Far Horizons is not an open-ended game, so you may
    not start a new species at any time.
    
    I am not currently running a Far Horizons game, and I have no plans to do
    so in the foreseeable future.  However, if you would like to run your own
    game, a complete source code distribution (written in ANSI C and including
    the rules) is available here.

The code for editions 1 - 6 are not available, and likely never existed on the web.

# Rules

You can find the original 7th edition ASCII rules at [doc/rules](doc/rules).

* Read the manual right in your browser: [Rules in HTML](http://ramblurr.github.io/Far-Horizons/)
* Or in PDF format: [Rules in PDF](http://ramblurr.github.io/Far-Horizons/manual.pdf)
* Or you can find the original 7th edition rules in all their fixed-width ASCII glory here: [doc/rules](doc/rules).

# Change Notes

This repository contains the original source code with various bug fixes and improvements.

There have been *no changes to the game mechanics*, and there are no immediate plans to make any.
Our changes are focused on:

* bug fixes
* removing compiler warnings
* simplify the build process
* making the data files portable between 32- and 64-bit x86 machines
* creating a single executable to reduce the dependencies on Python and Perl to run game turns

If you find a change to the game mechanics, please file a bug report on the
[FAR HORIZONS Issue Tracker](https://github.com/playbymail/Far-Horizons/issues).

The shell scripts used to compile have been replaced with a single CMakefile.
This should allow the engine to build on 32- and 64-bit Linux, Windows and Mac.
Please file a bug report on the
[FAR HORIZONS Issue Tracker](https://github.com/playbymail/Far-Horizons/issues)
if you have problems with the build on any of these systems.

We refactored the source and added a common entry point for all the commands.
Those changes are covered in later sections of this document.

The major change to the engine has been the data structures.
The original code performed some minor miracles to support 16- and 32-bit systems.
We've changed to that support 32- and 64-bit systems.

The internal structures have been cleaned up to remove unused fields.

New structures were created for the external data formats (the binary and JSON data files).
The `get` and `save` functions were updated to convert between the internal and external structures when fetching and saving data.
(A few of the internal structures had new fields added to help with the conversion.)

We replaced the commands used to edit data (`AsciiToBinary`, `BinaryToAscii`, and `Edit`).
Gamemasters must export the binary data files to JSON, edit the JSON data, and then import the JSON back in.
We apologize for the inconvenience of the extra steps, but it simplifies the code and testing.

Again, we have not intentionally changed any of the game mechanics.
If you find a change, please report it as a bug on the
[FAR HORIZONS Issue Tracker](https://github.com/playbymail/Far-Horizons/issues)
page.

## History

Updates to this codebase have been made sporadically over the years.
The project was imported into git in 2009 by `slawcok`.
`slawcok` was part of a polish contigent of FH players.

Since then the following folks have contributed to the codebase:

* slawcok
* rozenfeld.piotr
* Casey Link
* mjoyner
* Raven Zachary
* Michael D Henderson

If you're interested in what changes have been made, see the [git history](https://github.com/playbymail/Far-Horizons/).

# Building

You can build with CMake.

Building with CMake requires version 3.5 or newer.
We highly recommend installing `ninja-build` along with CMake.

If you're on a Linux machine and have checked out the `main` branch, it should be something like:

    ~$ mkdir -p src

    ~$ cd src
    
    ~/src$ cmake --version
      cmake version 3.5.1
    
    ~/src$ git clone https://github.com/playbymail/Far-Horizons.git

    ~/src$ cd Far-Horizons

    ~/src/Far-Horizons$ git remote -v
      origin  git@github.com:playbymail/Far-Horizons.git (fetch)
      origin  git@github.com:playbymail/Far-Horizons.git (push)
    
    ~/src/Far-Horizons$ cd build
    
    ~/src/Far-Horizons/build$ cmake ..
      -- The C compiler identification is GNU 5.4.0
      -- Check for working C compiler: /usr/bin/cc
      -- Check for working C compiler: /usr/bin/cc -- works
      -- Detecting C compiler ABI info
      -- Detecting C compiler ABI info - done
      -- Detecting C compile features
      -- Detecting C compile features - done
      -- Looking for sqrt in m
      -- Looking for sqrt in m - found
      -- Configuring done
      -- Generating done
      -- Build files have been written to: ~/src/Far-Horizons/build
    
    ~/src/Far-Horizons/build$ cd ..
    
    ~/src/Far-Horizons$ cmake --build build

All the resulting binaries are in `build/`.

Compiling is never easy.
Please feel free to reach out to the GitHub site if you have any questions.

# Game Mastering

The game has scripts to help initialize and run a game.
See [tools/README.md](tools/README.md).

## Running by Hand

This application uses a built-in psuedo-random number generator (PRNG)
that required you to set and export a random seed value.
You do that by running something like:

```bash
export FH_SEED=$RANDOM
```

You must do this before every command.
If you don't, each command will start with the same seed value.

Why?
Why would we do this?
It's a hack that allows game-masters to re-run a turn and get identical results.
There's an item on the "to do" list to make a random seed the default and still allow testers to specify their own seed.

### Creating a New Galaxy

```bash
mkdir gamma
cp examples/noorders.txt gamma/
cp examples/species.cfg gamma/
cd gamma
FH_SEED=$RANDOM ../build/fh create galaxy --less-crowded --species=18
FH_SEED=$RANDOM ../build/fh show galaxy
FH_SEED=$RANDOM ../build/fh create home-system-templates
FH_SEED=$RANDOM ../build/fh create species --config=species.cfg.json
FH_SEED=$RANDOM ../build/fh finish
FH_SEED=$RANDOM ../build/fh report
FH_SEED=$RANDOM ../build/fh stats
```

### Running a Turn

```bash
FH_SEED=$RANDOM ../build/fh turn
FH_SEED=$RANDOM ../build/fh locations
FH_SEED=$RANDOM ../build/fh combat
FH_SEED=$RANDOM ../build/fh pre-departure
FH_SEED=$RANDOM ../build/fh jump
FH_SEED=$RANDOM ../build/fh production
FH_SEED=$RANDOM ../build/fh post-arrival
FH_SEED=$RANDOM ../build/fh locations
FH_SEED=$RANDOM ../build/fh combat --strike
FH_SEED=$RANDOM ../build/fh finish
FH_SEED=$RANDOM ../build/fh report
FH_SEED=$RANDOM ../build/fh stats
```

## Create Galaxy

The `fh create-galaxy` command initializes a new game by creating three files:

* `galaxy.dat`, which contains the parameters for the galaxy
* `stars.dat`, which contains data for all the systems in the galaxy
* `planets.dat`, which contains data for all the planets in the galaxy

The command accepts the following options:

* --species=integer, required, defines the number of species
* --stars=integer, optional
* --radius=integer, optional
* --less-crowded, optional
* --suggest-values, optional

The number of species is used to determine the number of stars in the galaxy.
The number of stars is used to determine the radius.
As a game master, you can specify the values, or let the program determine them.
You can also use the `--suggest-values` flag to display suggested values based on the number of species.

The `--less-crowded` flag increases the number of stars by about 50%.
(It has no effect if you specify the number of stars yourself.)

Increasing the number of stars tends to slow the pace of the game since it will take longer for species to encounter each other.

NB: `fh create galaxy` replaces `NewGalaxy`.

## Show Galaxy

The `fh show galaxy` command displays a very crude ASCII map of the galaxy.

The map shows the locations of ideal home worlds, colonies, and other star systems.

NB: `fh show galaxy` replaces `ShowGalaxy`.

## Create Home System Templates

The `fh create home-systems` command creates a set of templates for home systems.
The templates are named `homesystemN.dat` where `N` is the number of planets in the template.
(The number ranges from 3 to 9).
The command ensures that one planet in the system template is "earth-like" and will be a good starting point for a species.

When a species is added to the game,
they are assigned an unclaimed home system.
The template that matches the number of planets in the system is used to update resources in the system.
The actual values are randomly tweaked to prevent all the systems from looking the same.

NB: `fh create home-systems` replaces `MakeHomes`.

# List Galaxy

The `fh list galaxy` command lists all the systems in the galaxy.

The command accepts the following options:

* --planets=bool, optional, default false, reports on planet details
* --wormholes=bool, optional, default false, reports on wormhole details

NB: `fh list galaxy` replaces `ListGalaxy`.

## Make Home System

The `fh update home-system` sets the "home system" flag on a system.
That flag is used when adding new species to a galaxy.

The command accepts the following options:

* --radius=integer, optional, default 10, minimum distance between home systems
* --system=integer,integer,integer, optional, use the system located at x,y,z
* --force, optional, overrides the check for radius and existing home system

If the `--radius` option is given,
this command searches for find a system that has at least 3 planets,
is not already a home system,
and is at least the minimum distance from any other home system.
If it cannot, it reports an error and terminates.

If the `--system` option is given,
this command verifies that the system has at least 3 planets and is not already a home system.
If not, it reports an error and terminates.

If both `--radius` and `--system` are specified,
the command will verify that the system has at least 3 planets,
is not already a home system,
and is at least the minimum distance from any other home system.
If not, it reports an error and terminates.

The system is converted to one suitable for a home system by loading the appropriate template (based on the number of planets in the system).
The values for the planets are adjusted by small random amounts to provide some variation.

If there are no problems, the `planets.dat` file is updated with the new data.

NB: `fh update home-system` replaces `MakeHomeSystem` and `MakeHomeSystemAuto`.

NB: The `fh create species` command automatically creates new home systems as needed,
so this command is useful only if you wish to specify the location of home systems.
(For example, if you're adding a new player in an existing game.)

## Add Species

The `fh create species` adds new players to a galaxy.

The command accepts the following options:

* --config=text, required, name of config file to process

It searches the galaxy for unclaimed home systems and assigns one randomly to the new player.
(If there are no unclaimed home systems, it will attempt to generate a new one and use it.)

The `--config` option is required.
It is the name of the configuration file containing the new species data.

The command will fail if a species already exists.

The configuration file format changes from simple text to JSON with Release 7.5.5.

```json
[
  {
    "email": "alderaan@example.com",
    "name": "Alderaan",
    "homeworld": "Optimus",
    "govt-name": "His Majesty",
    "govt-type": "Degenerated Monarchy",
    "tech-ml": 10,
    "tech-gv": 1,
    "tech-ls": 1,
    "tech-bi": 3
  }
]
```

The file must contain an array of JSON objects with fields for

1. email - the player's email address
2. name - the name of the species
3. homeworld - the name of the species' homeworld
4. govt-name - the name of the species' government
5. govt-type - the type of the species' government
6. tech-XX - the values for the four base techologies, `ml`, `gv`, `ls`, and `bi`.

NB: `fh create species` replaces `AddSpeciesAuto`.

## Update Turn

The `fh turn` command updates the current turn number.

## Update Location

The `fh location` command updates the location of all ships in the galaxy.

## Process Combat Commands

The `fh combat` command runs orders from the COMBAT section.

NB: `fh combat` replaces `Combat`.

## Process Pre-Departure Commands

The `fh pre-departure` command runs orders from the PRE-DEPARTURE section. 

NB: `fh pre-departure` replaces `PreDep`.

## Process Jump Commands

The `fh jump` command runs orders from the JUMP section.

NB: `fh jump` replaces `Jump`.

## Process Production Commands

The `fh production` command runs orders from the PRODUCTION section.

NB: `fh production` replaces `Production`.

## Process Post-Arrival Commands

The `fh post-arrival` command runs orders from the POST-ARRIVAL section.

NB: `fh post-arrival` replaces `PostArrival`.

## Process Strike Commands

The `fh combat --strike` command runs orders from the STRIKE section.

NB: `fh combat --strike` replaces `Strike`.

## Finish Turn

The `fh finish` command completes turn processing.
It updates statistics, materials, damage, and locations for all planets and ships.

NB: `fh finish` replaces `Finish`.

## Generate Turn Reports

The `fh report` command creates a report from the current data.

If you run it before running `fh finish`, you may see inconsistent values.

NB: `fh report` replaces `Report`.

## Stats

The `fh stats` command displays current statistics.

## Show Engine Version

The `fh version` command displays the version of the game engin.

```bash
fh version
7.5.6
```

## Show Game Settings

The `fh show` command can list the game version and several settings.

    d_num_species          maximum number of species\n");
    num_planets            number of planets in cluster\n");
    num_species            number of planets in cluster\n");
    num_stars              number of stars in cluster\n");
    num_natural_wormholes  number of natural wormholes in cluster\n");
    radius                 radius of cluster\n");
    turn_number            current turn number\n");

You may place several values on the command line.
For example,

```bash
fh show num_stars num_planets
162 606
```

## Editing Game Data

You may run `fh export json` to export the game data into JSON files.

You should see output like:

    info: loading binary data...
    info: exporting galaxy.json...
    info: exporting systems.json...
    info: exporting species.001.json...
    info: exporting species.002.json...
    info: exporting species.003.json...
    info: exporting species.004.json...
    info: exporting species.005.json...
    info: export complete

The files created are:

* galaxy.json - the basic game settings
* systems.json - data for all stars and planets
* species.NNN.json - data for each species including ships and colonies

NB: The species JSON file uses 3 digits for the species number!

You can edit the JSON files using any text editor.
Be careful with preserving types and maximum lengths for strings.

NB: Please back up all of your game files before importing data!
There is very little error checking on the data.
You can easily corrupt your game files.

After editing the files, run the `fh import json` 

You should see output like:

    info: loading binary data...
    info: importing galaxy.json...
    info: importing systems.json...
    unmarshal: systems: found      162 stars
    unmarshal: systems: found      606 planets
    info: importing species.001.json...
    info: species   1: name Alderaan planet Optimus
    info: importing species.002.json...
    info: species   2: name Bantustan planet The Nest
    info: importing species.003.json...
    info: species   3: name Charabon planet Nexus Eleven
    info: importing species.004.json...
    info: species   4: name Doop'ov-aci planet Baar'u'bomba
    info: importing species.005.json...
    info: species   5: name Ba' Doop planet Ba'da'boom
    info: saving binary data...
    info: import and save complete

### JSON Notes

You can add new ships and named planets, but please be careful.
There's an internal buffer that allows 25 new items.
Exceeding that can corrupt the data.
If you need to add more items than that, you could try exporting,
adding a few, importing, exporting again, etc.

There's very little error checking during the import.
It's easier to corrupt the data than it should be.

# License

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)

All source code in this repository is licensed under the GPL v3.

The original ANSI C source code and rules are Copyright (c) 1999 by Richard A. Morneau.

# Notes

* [LtanHonor's Gmail Updates](https://github.com/LtanHonor/Far-Horizons/blob/develop/tools/turn_send.py)

## CMake

There's a helpful page on CMake at
[HSF Training](https://hsf-training.github.io/hsf-training-cmake-webpage/02-building/index.html).

## Links

* [PBM List](http://www.pbm.com/~lindahl/pbm_list/)
* [PBeM Magazine](http://www.pbm.com/~lindahl/pbem_magazine.html)
* [Galaxy Design](http://www.pbm.com/~lindahl/pbem_articles/galaxy.design)
* [WarpWar Game](http://www.contrib.andrew.cmu.edu/usr/gc00/reviews/warpwar.html)

