# Far Horizons Game Engine
# Copyright (C) 2022 Michael D Henderson
# Copyright (C) 2021 Raven Zachary
# Copyright (C) 2019 Casey Link, Adam Piggott
# Copyright (C) 1999 Richard A. Morneau
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

#cmake_minimum_required(VERSION 3.21)
cmake_minimum_required(VERSION 3.5)
project(far_horizons C)
include_directories(src)

set(CMAKE_C_STANDARD 99)

include(CheckLibraryExists)

CHECK_LIBRARY_EXISTS(m sqrt "" HAVE_LIB_M)
if (HAVE_LIB_M)
    set(USE_LIB_M m)
endif (HAVE_LIB_M)

add_executable(fh
        src/const.h
        src/fh.c src/fh.h
        src/cfgfile.c src/cfgfile.h
        src/combat.c src/combat.h
        src/command.c src/command.h
        src/commandvars.c src/commandvars.h
        src/create.c src/create.h
        src/data.c src/data.h
        src/dev_log.c src/dev_log.h
        src/do.c src/do.h
        src/engine.c src/engine.h
        src/enginevars.c src/enginevars.h
        src/export.c src/export.h
        src/finish.c src/finish.h
        src/galaxy.c src/galaxy.h
        src/galaxyio.c src/galaxyio.h
        src/import.c src/import.h
        src/intercept.c src/intercept.h
        src/item.c src/item.h
        src/jump.c src/jump.h
        src/jumpvars.c src/jumpvars.h
        src/list.c src/list.h
        src/location.c src/location.h
        src/locationio.c src/locationio.h
        src/locationvars.c src/locationvars.h
        src/log.c src/log.h
        src/logvars.c src/logvars.h
        src/marshal.c src/marshal.h
        src/money.c src/money.h
        src/nampla.c src/nampla.h
        src/namplaio.c src/namplaio.h
        src/namplavars.c src/namplavars.h
        src/orders.c src/orders.h
        src/ordersvars.c src/ordersvars.h
        src/planet.c src/planet.h
        src/planetio.c src/planetio.h
        src/planetvars.c src/planetvars.h
        src/postarrival.c src/postarrival.c
        src/predeparture.c src/predeparture.h
        src/prng.c src/prng.h
        src/production.c src/production.h
        src/productionvars.c src/productionvars.h
        src/report.c src/report.h
        src/ship.c src/ship.h
        src/shipio.c src/shipio.h
        src/shipvars.c src/shipvars.h
        src/scan.c src/scan.h
        src/sexpr.c src/sexpr.h
        src/species.c src/species.h
        src/speciesio.c src/speciesio.h
        src/speciesvars.c src/speciesvars.h
        src/show.c src/show.h
        src/star.c src/star.h
        src/stario.c src/stario.h
        src/starvars.c src/starvars.h
        src/stats.c src/stats.h
        src/transactionio.c src/transactionio.h
        src/turn.c src/turn.h
        src/unmarshal.c src/unmarshal.h
        src/update.c src/update.h
        src/version.c src/version.h
        src/cjson/cJSON.c src/cjson/cJSON.h
        src/cjson/helpers.c src/cjson/helpers.h
        src/memsafe.c src/memsafe.h)

target_link_libraries(fh ${USE_LIB_M})
