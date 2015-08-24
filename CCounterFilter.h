
#ifndef COUNTERFILTER_H
#define COUNTERFILTER_H

#include <stdint.h>
#include <map>
#include <string>
#include <CFilter.h>
#include <DataFormat.h>
#include <CRingItem.h>
#include <CRingStateChangeItem.h>
#include <CPhysicsEventItem.h>
#include <CRingTextItem.h>
#include <CRingPhysicsEventCountItem.h>
#include <CRingFragmentItem.h>

class CCounterFilter : public CFilter
{
  private:
  std::map<uint32_t, uint32_t> m_counters;

  public:

  CCounterFilter();
  virtual ~CCounterFilter();

  CCounterFilter* clone() const { return new CCounterFilter(*this);}

  // The default handlers
  virtual CRingItem* handleRingItem(CRingItem* pItem) 
  {

    if ( counterExists(pItem->type()) ) {
      m_counters[pItem->type()] = 0;
    }

    m_counters[pItem->type()] += 1;
    return pItem;
  }

  virtual CRingItem* handleStateChangeItem(CRingStateChangeItem* pItem) 
  {
    m_counters[pItem->type()] += 1;
    return static_cast<CRingItem*>(pItem);
  }

  virtual CRingItem* handleScalerItem(CRingScalerItem* pItem) 
  {
    m_counters[pItem->type()] += 1;
    return static_cast<CRingItem*>(pItem);
  }

  virtual CRingItem* handleTextItem(CRingTextItem* pItem) 
  {
    m_counters[pItem->type()] += 1;
    return static_cast<CRingItem*>(pItem);
  }

  virtual CRingItem* handlePhysicsEventItem(CPhysicsEventItem* pItem) 
  {
    m_counters[pItem->type()] += 1;
    return static_cast<CRingItem*>(pItem);
  }

  virtual CRingItem* 
    handlePhysicsEventCountItem(CRingPhysicsEventCountItem* pItem) 
    {
      m_counters[pItem->type()] += 1;
      return static_cast<CRingItem*>(pItem);
    }

  virtual CRingItem* handleFragmentItem(CRingFragmentItem* pItem)
  {
    m_counters[pItem->type()] += 1;
    return static_cast<CRingItem*>(pItem);
  }

  virtual void initialize();
  virtual void finalize();

  private:
  bool counterExists(uint32_t type);

  void printCounters() const;
  std::string translate(uint32_t type) const;
  

};

#endif


