/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2014.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Jeromy Tompkins
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

#include <iostream>
#include <CFatalException.h>
#include <CFilterMain.h>

#include "CCounterFilter.h"
#include "CFragCounterFilter.h"

#include <utility>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>

/// The main function
/**! main function
  Creates a CFilterMain object and 
  executes its operator()() method. 

  \return 0 for normal exit, 
          1 for known fatal error, 
          2 for unknown fatal error
*/

using namespace std;

bool isBuilt = false;
uint32_t defaultSourceId = 0;

pair<int, char**> handleExtraOptions(int argc, char** argv);

int main(int argc, char* argv[])
{
  int status = 0;

  try {

    auto newArgs = handleExtraOptions(argc, argv);
    argc = get<0>(newArgs);
    argv = get<1>(newArgs);

    // Create the main
    CFilterMain theApp(argc,argv);


    // Construct filter(s) here.
    CCounterFilter unbuilt_filter;
    CFragCounterFilter built_filter(defaultSourceId);

    // Register the filter(s) here. Note that if more than
    // one filter will be registered, the order of registration
    // will define the order of execution. If multiple filters are
    // registered, the output of the first filter will become the
    // input of the second filter and so on. 
    if (isBuilt) {
	    theApp.registerFilter(&built_filter);
	} else {
	    theApp.registerFilter(&unbuilt_filter);
	}

    // Run the main loop
    theApp();

  } catch (CFatalException exc) {
    status = 1;
  } catch (...) {
    std::cout << "Caught unknown fatal error...!" << std::endl;
    status = 2;
  }

  return status;
}


 pair<int, char**> handleExtraOptions(int argc, char** argv)
{
	vector<std::string> options;
	for (int i=0; i<argc; ++i) {
		options.push_back(string(argv[i]));
	}

	char** new_args = new char*[argc];
	for (int i=0; i<argc; ++i) {
		new_args[i] = new char[256];
	}
	int loadingIndex = 0;
	int index = 0;
	while ( index < options.size() ) {
		if (options[index] == "--built") {
                	string arg (options[++index]);
			if (arg == "true") {
                          isBuilt = true;
                        } else {
                          isBuilt = false;
                        }  	
			argc -= 2;
		} else if (options[index] == "--id") {
			defaultSourceId = atoi(options[++index].c_str());
			argc -= 2;
                } else if (options[index] == "--help" || options[index]== "-h") {
			cout << "Specific options" <<endl;
			cout << "   --built=(true,false)   data  set to analyze isbuilt of not (default = false)" <<endl;
			cout << "   --id=#		    source id to use for items w/out body headers (default = 0)" <<endl;
			strcpy(new_args[loadingIndex], argv[index]);
			loadingIndex++;
                }else {
			strcpy(new_args[loadingIndex], argv[index]);
			loadingIndex++;
                }
		++index;		
         }
	return make_pair(argc, new_args);
}


