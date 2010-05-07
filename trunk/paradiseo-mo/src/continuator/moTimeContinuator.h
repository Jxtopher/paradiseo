/*
<moTimeContinuator.h>
Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  ue,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.
The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.

ParadisEO WebSite : http://paradiseo.gforge.inria.fr
Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef _moTimeContinuator_h
#define _moTimeContinuator_h

#include <continuator/moContinuator.h>

/**
 * Termination condition until a running time is reached.
 */
template < class Neighbor >
class moTimeContinuator: public moContinuator<Neighbor>
{
public:

	typedef typename Neighbor::EOT EOT;

    /**
     * Ctor.
     * @param _max maximum running time
     */
    moTimeContinuator(time_t _max, bool _verbose=true): max(_max), verbose(_verbose){
        start = time(NULL);
    }


    /**
     * Returns false when the running time is reached.
     * @param _sol the current solution
     */
    virtual bool operator() (EOT& _sol)
    {
    	bool res;
        time_t elapsed = (time_t) difftime(time(NULL), start);
        res = (elapsed < max);
        if(!res && verbose)
    		std::cout << "STOP in moTimeContinuator: Reached maximum time [" << elapsed << "/" << max << "]" << std::endl;
        return res;
    }

    /**
     * reset the start time
     * @param _solution a solution
     */
    virtual void init(EOT & _solution) {
        start = time(NULL);
    }


    /**
     * Class name
     */
    virtual std::string className(void) const
    {
        return "moTimeContinuator";
    }


private:

    /** maximum running time */
    time_t max;
    /** starting time */
    time_t start;
    /** verbose mode */
    bool verbose;

};

#endif