/*
 * hunt.h
 *
 *  Created on: Aug 5, 2014
 *      Author: adrienp
 */

#ifndef HUNT_H_
#define HUNT_H_


#include <controllib/blocks.hpp>
#include <controllib/block/BlockParam.hpp>

#include <uORB/uORB.h>
#include <uORB/topics/mission.h>
#include <uORB/topics/home_position.h>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/topics/tracking_cmd.h>
#include <uORB/topics/tracking_status.h>
#include <uORB/topics/hunt_state.h>
#include <uORB/topics/hunt_result.h>

#include "navigator_mode.h"
#include "mission_block.h"


class Navigator;

class Hunt : public MissionBlock
{
public:
	Hunt(Navigator *navigator, const char *name);

	~Hunt();

	virtual void on_inactive();

	virtual void on_activation();

	virtual void on_active();
private:

	/**
	 * get the next command from tracking via mavlink
	 */
	bool get_next_cmd();

	/**
	 * once the next item has been received,
	 * actually set it as a mission item and setpoint
	 */
	void set_next_item();

	/*
	 * put the vehicle in a loiter mode as we wait for tracking to respond
	 */
	void set_waiting();

	/*
	 * update mission result to say that the most recent command has been confirmed finished
	 */
	void report_cmd_finished();

	/*
	 * update the current cmd id being flown
	 */
	void report_cmd_id();

	/*
	 * publish the mission result (which should get picked up by mavlink module to be sent to ground)
	 */
	void publish_hunt_result();

	/*
	 * report that a status change has occurred
	 */
	void report_status();

	/*
	 * publish the changed status to the corresponding orb message
	 */
	void publish_status();

	/*
	 * reset whether or not we have reached the hunt item
	 */
	void rest_hunt_item_reached();

	/**
	 * states that the hunt script can be in
	 * will be used to help identify whether we
	 * should be polling for the next command or not
	 */
	enum HuntState {
		HUNT_STATE_OFF = 0,		// hunt has been turned off
		HUNT_STATE_START,		// hunt just started, need to go to starting position
		HUNT_STATE_WAIT,		// waiting for next command from tracking
		HUNT_STATE_MOVE,		// executing a move command from tracking
		HUNT_STATE_ROTATE,		// executing a rotate command from tracking
	} _hunt_state;

	/**
	 * boolean to simply hold whether or not a hunt has started
	 * will just change the behavior of vehicle when coming from off state
	 */
	bool _started;
	int _current_cmd_id;

	struct tracking_cmd_s _tracking_cmd;

	orb_advert_t _hunt_result_pub;
	struct hunt_result_s _hunt_result;

	orb_advert_t _hunt_state_pub;
	struct hunt_state_s _hunt_state_s;


};


#endif /* HUNT_H_ */
