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

#include <InputOutput/Bounds.h>
#include <ScreenManager.h>
#include <CalcServer.h>
#include <AuxiliarMethods.h>

namespace Aqua{ namespace InputOutput{

Bounds::Bounds()
    : _file(NULL)
{
    if(create())
        exit(EXIT_FAILURE);
}

Bounds::~Bounds()
{
    close();
}

bool Bounds::save()
{
    if(!_file){
        return true;
    }

    return false;
}

bool Bounds::create()
{
    char msg[1024];
	ScreenManager *S = ScreenManager::singleton();

    if(file("bounds.%d.dat", 0)){
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
	fprintf(_file,"# x_min = Minimum x coordinate of the fluid.\n");
	fprintf(_file,"# y_min = Minimum y coordinate of the fluid.\n");
	#ifdef HAVE_3D
        fprintf(_file,"# z_min = Minimum z coordinate of the fluid.\n");
	#endif // HAVE_3D
	fprintf(_file,"# x_max = Maximum x coordinate of the fluid.\n");
	fprintf(_file,"# y_max = Maximum y coordinate of the fluid.\n");
	#ifdef HAVE_3D
        fprintf(_file,"# z_max = Maximum z coordinate of the fluid.\n");
	#endif // HAVE_3D
	fprintf(_file,"\n");
	fflush(_file);

	return false;
}

bool Bounds::close()
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
