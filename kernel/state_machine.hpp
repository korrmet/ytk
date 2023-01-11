/** \file  state_machine.hpp
 *  \brief state machine interface */

#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <cstdint>
#include "containers/circular_buffer.hpp"

/** \brief   checks condiniton and populate event
 *  \details event population is final point in your state handling, no code
 *           after this action will be executed
 *  
 *  \param evt  event code
 *  \param cond condition */
#define ASSERT_EVENT(evt, cond) \
  if (cond) { add_event(evt); return; }

/** \brief   state machine base class
 *  \details to use it you should make your own class and inherit this and
 *           implement yourself event and state handlers. state handler and
 *           event handler should have saimilar structure. generally it may
 *           be just bug switch-case statement. any action should not block
 *           current thread for a long time */
template <uint32_t VOLUME>
class state_machine
{ public:
  /** \brief   state type
   *  \details make your own states using define or enum mechanisms, it
   *           will be implicitly casted to this type */
  typedef uint32_t state_t;

  /** \brief   event type
   *  \details make your own events using define or enum mechanisms, it
   *           will be implicitly casted to this type */
  typedef uint32_t event_t;

  /** \brief handle all active events and after that handle current state */
  void machine_step()
  { event_t current_event;
    while (event_queue.fetch_head(current_event))
    { event_handler(current_event);
      event_queue.pop_head(); }

    state_handler(current_state); }

  /** \brief this method is needed to populate event outside of the machine
   *
   *  \param event event that need to be handled
   *
   *  \return result of event registration
   *  \retval true  event registrated successfully
   *  \retval false event is not registrated */
  bool add_event(event_t event) { event_queue.push_tail(event); }

  /** \brief this method must contain all of the state handlers
   *  
   *  \param state current state that should be handled */
  virtual void state_handler(state_t state) = 0;

  /** \brief this method must contain all of the event handlers
   * 
   *  \param event current event that should be handled */
  virtual void event_handler(event_t event) = 0;

  private:
  /** \brief   current operating state
   *  \details state may be switched in event only. events may be propogated
   *           in states or outside with method add_event() */
  state_t current_state;

  /** \brief   queue of events that should be handled
   *  \details if you don't use external event propagation mechanism make 
   *           VOLUME template parameter equel 1 */
  circular_buffer_static<event_t, VOLUME> event_queue; };

#endif // STATE_MACHINE_HPP
