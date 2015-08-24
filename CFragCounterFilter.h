
#ifndef CFRAGCOUNTERFILTER_H
#define CFRAGCOUNTERFILTER_H

#include <stdint.h>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <CFilter.h>
#include <DataFormat.h>
#include <CRingItem.h>
#include <CRingStateChangeItem.h>
#include <CPhysicsEventItem.h>
#include <CRingTextItem.h>
#include <CRingItemFactory.h>
#include "FragmentIndex.h"
#include <CRingPhysicsEventCountItem.h>
#include <CRingFragmentItem.h>

class CFragCounterFilter : public CFilter
{
  private:
    std::map<uint32_t, std::map<uint32_t, uint32_t> > m_counters;
    uint32_t m_defaultId;

  public:

    CFragCounterFilter(uint32_t defaultId);
    virtual ~CFragCounterFilter();

    CFragCounterFilter* clone() const { return new CFragCounterFilter(*this);}

    // The default handlers
    virtual CRingItem* handleRingItem(CRingItem* pItem) 
    {
      incrementCounter(pItem);
      return pItem;
    }

    virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem) 
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* handleScalerItem(CRingScalerItem* pItem) 
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* handleTextItem(CRingTextItem* pItem) 
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem) 
    {
      FragmentIndex index(reinterpret_cast<uint16_t*>(pItem->getBodyPointer()));
      FragmentIndex::iterator it = index.begin();
      FragmentIndex::iterator itend = index.end();
      while (it != itend) {
        CRingItem* item = CRingItemFactory::createRingItem(it->s_itemhdr);
        incrementCounter(item);
        delete item;
        ++it;
      }
      return static_cast<CRingItem*>(pItem);
    }

    virtual CRingItem* 
      handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
      {
        incrementCounter(pItem);
        return static_cast<CRingItem*>(pItem);
      }

    virtual CRingItem* handleFragmentItem(CRingFragmentItem* pItem)
    {
      incrementCounter(pItem);
      return static_cast<CRingItem*>(pItem);
    }

    virtual void finalize();

  private:
    bool counterExists(uint32_t type);
    void setupCounters(uint32_t id);
    void incrementCounter(CRingItem* pItem);

    void printCounters() const;
    std::string translate(uint32_t type) const;
  

};

#endif


