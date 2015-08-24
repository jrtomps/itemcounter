
#include "CCounterFilter.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

CCounterFilter::CCounterFilter()
  : m_counters()
{
}

void CCounterFilter::initialize() {
  m_counters[BEGIN_RUN]           = 0;
  m_counters[END_RUN]             = 0;
  m_counters[PAUSE_RUN]           = 0;
  m_counters[RESUME_RUN]          = 0;

  m_counters[PACKET_TYPES]        = 0;
  m_counters[MONITORED_VARIABLES] = 0;
  m_counters[RING_FORMAT]         = 0;

  m_counters[PERIODIC_SCALERS]    = 0;

  m_counters[PHYSICS_EVENT]       = 0;
  m_counters[PHYSICS_EVENT_COUNT] = 0;

  m_counters[EVB_FRAGMENT]        = 0;
  m_counters[EVB_UNKNOWN_PAYLOAD] = 0;
  m_counters[EVB_GLOM_INFO]       = 0;

}

CCounterFilter::~CCounterFilter() 
{
}


bool CCounterFilter::counterExists(uint32_t type) 
{
  map<uint32_t,uint32_t>::iterator it;
  it = m_counters.find(type);
  return ( it!=m_counters.end() );

}

void CCounterFilter::printCounters() const
{
  map<uint32_t,uint32_t>::const_iterator it,itend;
  it = m_counters.begin();
  itend = m_counters.end();

  while (it != itend) {
    cout << setw(20) << translate(it->first) 
        << " : " << setw(10) << it->second;
    cout << endl;
    
    ++it;
  }
}


string CCounterFilter::translate(uint32_t type) const
{
  map<uint32_t,string> namemap;
  namemap[BEGIN_RUN]            = "BEGIN_RUN";
  namemap[END_RUN]              = "END_RUN";
  namemap[PAUSE_RUN]            = "PAUSE_RUN";
  namemap[RESUME_RUN]           = "RESUME_RUN";
  namemap[PACKET_TYPES]         = "PACKET_TYPES";
  namemap[MONITORED_VARIABLES]  = "MONITORED_VARIABLES";
  namemap[RING_FORMAT]          = "RING_FORMAT";
  namemap[PERIODIC_SCALERS]     = "PERIODIC_SCALERS";
  namemap[PHYSICS_EVENT]        = "PHYSICS_EVENT";
  namemap[PHYSICS_EVENT_COUNT]  = "PHYSICS_EVENT_COUNT";
  namemap[EVB_FRAGMENT]         = "EVB_FRAGMENT";
  namemap[EVB_UNKNOWN_PAYLOAD]  = "EVB_UNKNOWN_PAYLOAD";
  namemap[EVB_GLOM_INFO]        = "EVB_GLOM_INFO";

  map<uint32_t,string>::const_iterator it;
  it = namemap.find(type);
  if ( it!=namemap.end() ) {
     return it->second;
  } else {
    stringstream name;
    name << "User type #" << type;
    return name.str();
  }


}

void CCounterFilter::finalize() 
{
  cout << "\nCOUNTER FILTER RESULTS" << endl;
  printCounters();
  cout << "----------------------------------------" << endl;
}
