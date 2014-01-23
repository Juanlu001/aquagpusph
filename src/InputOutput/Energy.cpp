/*
 *  This file is part of AQUAgpusph, a free CFD program based on SPH.
 *  Copyright (C) 2012  Jose Luis Cercos Pita <jl.cercos@upm.es>
 *
 *  AQUAgpusph is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AQUAgpusph is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with AQUAgpusph.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

#include <InputOutput/Energy.h>
#include <ScreenManager.h>
#include <CalcServer.h>
#include <AuxiliarMethods.h>

namespace Aqua{ namespace InputOutput{

Energy::Energy()
    : _file(NULL)
{
    if(create())
        exit(EXIT_FAILURE);
}

Energy::~Energy()
{
    close();
}

bool Energy::save()
{
    if(!_file){
        return true;
    }

    return false;
}

bool Energy::create()
{
    char msg[1024];
	ScreenManager *S = ScreenManager::singleton();

    if(file("energy.%d.dat", 0)){
        S->addMessageF(3, "Failure getting a valid filename.\n");
        S->addMessageF(0, "\tHow do you received this message?.\n");
        return true;
    }
    _file = fopen(file());
    if(!_file){
        sprintf(msg,
                "Failure creating the log file \"%s\"\n",
                file());
        return true;
    }

	fprintf(_file,"#########################################################\n");
	fprintf(_file,"#                                                       #\n");
	fprintf(_file,"#    #    ##   #  #   #                           #     #\n");
	fprintf(_file,"#   # #  #  #  #  #  # #                          #     #\n");
	fprintf(_file,"#  ##### #  #  #  # #####  ##  ###  #  #  ## ###  ###   #\n");
	fprintf(_file,"#  #   # #  #  #  # #   # #  # #  # #  # #   #  # #  #  #\n");
	fprintf(_file,"#  #   # #  #  #  # #   # #  # #  # #  #   # #  # #  #  #\n");
	fprintf(_file,"#  #   #  ## #  ##  #   #  ### ###   ### ##  ###  #  #  #\n");
	fprintf(_file,"#                            # #             #          #\n");
	fprintf(_file,"#                          ##  #             #          #\n");
	fprintf(_file,"#                                                       #\n");
	fprintf(_file,"#########################################################\n");
	fprintf(_file,"#\n");
	fprintf(_file,"# File autogenerated by AQUAgpusph.\n");
	fprintf(_file,"# The following fields are printed:\n");
	fprintf(_file,"# t = Time instant.\n");
	fprintf(_file,"# E.Pot. = Potential energy (almost unuseful).\n");
	fprintf(_file,"# E.Kin. = Kinetic energy.\n");
	fprintf(_file,"# U = Internal energy (H + TS).\n");
	fprintf(_file,"# H = Enthalpy.\n");
	fprintf(_file,"# TS = Entropy (multiplied by the temperature).\n");
	fprintf(_file,"# E = Energy (U + E.kin.).\n");
	fprintf(_file,"\n");
	fflush(_file);

	return false;
}

bool Energy::close()
{
    if(!_file)
        return true;

	fprintf(_file,"# Simulation finished\n");

	fflush(_file);
    fclose(_file);
    _file = NULL;

	return false;
}

}}  // namespace
