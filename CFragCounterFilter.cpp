
#include "CFragCounterFilter.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <FragmentIndex.h>

using namespace std;

CFragCounterFilter::CFragCounterFilter(uint32_t defaultId)
  : m_counters(), m_defaultId(defaultId)
{
  setupCounters(m_defaultId);
}

CFragCounterFilter::~CFragCounterFilter() 
{
}


bool CFragCounterFilter::counterExists(uint32_t type) 
{
  map<uint32_t,std::map<uint32_t,uint32_t> >::iterator it;
  it = m_counters.find(type);
  return ( it!=m_counters.end() );

}

void CFragCounterFilter::printCounters() const
{
  map<uint32_t,map<uint32_t,uint32_t> >::const_iterator it,itend;
  map<uint32_t,uint32_t>::const_iterator idit,iditend;
  it = m_counters.begin();
  itend = m_counters.end();

  while (it != itend) {
    idit = it->second.begin();
    iditend = it->second.end();
    cout << "Source id : " << it->first << endl;
    while (idit!=iditend) {
      cout << setw(20) << translate(idit->first) 
           << " : " << setw(10) << idit->second;
      cout << endl;
    
      ++idit;
    }
    ++it;
  }
}


string CFragCounterFilter::translate(uint32_t type) const
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

void CFragCounterFilter::finalize() 
{
  cout << "\nFRAGMENT COUNTER FILTER RESULTS" << endl;
  printCounters();
  cout << "----------------------------------------" << endl;
}


void CFragCounterFilter::incrementCounter(CRingItem* pItem) 
{

  if ( pItem->hasBodyHeader() ) {
    if (!counterExists(pItem->getSourceId())) {
      setupCounters(pItem->getSourceId());
    }
    m_counters[pItem->getSourceId()][pItem->type()] += 1;
  } else {
    // this is setup in the constructor
    m_counters[m_defaultId][pItem->type()] += 1;
  }

}

void CFragCounterFilter::setupCounters(uint32_t id) 
{
  m_counters[id][BEGIN_RUN]           = 0;
  m_counters[id][END_RUN]             = 0;
  m_counters[id][PAUSE_RUN]           = 0;
  m_counters[id][RESUME_RUN]          = 0;

  m_counters[id][PACKET_TYPES]        = 0;
  m_counters[id][MONITORED_VARIABLES] = 0;
  m_counters[id][RING_FORMAT]         = 0;

  m_counters[id][PERIODIC_SCALERS]    = 0;

  m_counters[id][PHYSICS_EVENT]       = 0;
  m_counters[id][PHYSICS_EVENT_COUNT] = 0;

  m_counters[id][EVB_FRAGMENT]        = 0;
  m_counters[id][EVB_UNKNOWN_PAYLOAD] = 0;
  m_counters[id][EVB_GLOM_INFO]       = 0;
}
