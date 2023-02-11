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

#define NO_EVENT 0

/** \brief   state machine base class
 *  \details to use it you should make your own class and inherit this and
 *           implement yourself event and state handlers. state handler and
 *           event handler should have saimilar structure. generally it may
 *           be just bug switch-case statement. any action should not block
 *           current thread for a long time */
template <uint32_t VOLUME>
class state_machine
{ public:
    explicit state_machine(uint32_t state, uint32_t event)
      : current_state(state),
        current_event(event)
    {}

    /** \brief handle all active events and after that handle current state */
    void machine_step()
    { if (current_event != NO_EVENT)
      { event_handler(current_event);
        current_event = NO_EVENT; }

      state_handler(current_state); }

    /** \brief this method must contain all of the state handlers
     *
     *  \param state current state that should be handled */
    virtual void state_handler(uint32_t state) = 0;

    /** \brief this method must contain all of the event handlers
     *
     *  \param event current event that should be handled */
    virtual void event_handler(uint32_t event) = 0;

  private:
    /** \brief   current operating state
     *  \details state may be switched in event only. events may be propogated
     *           in states or outside with method add_event() */
    uint32_t current_state;

    /** \brief   current evnet that shall be handled
     *
     *  \details event may be spawned only in one of the state */
    uint32_t current_event; };

#endif // STATE_MACHINE_HPP
