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
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/topics/tracking_cmd.h>
#include <uORB/topics/tracking_status.h>
#include <uORB/topics/hunt_state.h>
#include <uORB/topics/hunt_result.h>

#include <lib/geo/geo.h> 		/*< for conversion from local x,y to lat, lon */

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

	/*
	 * get an update of the local position
	 */
	void update_local_position();

	/*
	 * update the reference position used in converting from local position to global position
	 */
	void update_reference_position();

	/*
	 * set the mission lat, lon coordinates from the tracking cmds N, E position
	 */
	void set_mission_latlon();

	/**
	 * states that the hunt script can be in
	 * will be used to help identify whether we
	 * should be polling for the next command or not
	 */
	/*
	enum HuntState {
		HUNT_STATE_OFF = 0,		// hunt has been turned off
		HUNT_STATE_START,		// hunt just started, need to go to starting position
		HUNT_STATE_WAIT,		// waiting for next command from tracking
		HUNT_STATE_MOVE,		// executing a move command from tracking
		HUNT_STATE_ROTATE,		// executing a rotate command from tracking
	} _hunt_state;
	*/

	/**
	 * boolean to simply hold whether or not a hunt has started
	 * will just change the behavior of vehicle when coming from off state
	 */
	bool _started;
	uint16_t _current_cmd_id;			/**< the current command being run */
	int _hunt_state;					/**< the current state */

	/* params */
	control::BlockParamFloat _param_yaw_increment;

	int _local_pos_sub; /**< subscription to the local position */

	orb_advert_t _hunt_result_pub;	/**< publish the current hunt result */
	orb_advert_t _hunt_state_pub;	/**< publish the current hunt state */

	struct vehicle_local_position_s _local_pos;	/**< local position struct */

	struct hunt_result_s _hunt_result;		/**< struct for the result of a cmd */
	struct hunt_state_s _hunt_state_s;		/**< struct for the state of the hunt mode */
	struct tracking_cmd_s _tracking_cmd;	/**< struct for the current tracking command */

	struct map_projection_reference_s _ref_pos;	// this is reference position

	/* rotation handling */
	int		_current_rotation_direction;	/**< -1 ccw, 1 cw and 0 no direction */
	float	_end_rotation_angle;			/**< the angle by which time rotation time should stop (same as initial...) */
	bool	_in_rotation;					/**< true if in a rotation already, false otherwise */
	bool	_allow_rotation_end;			/**< if true will start checking to see if we have reached the mission item */
	float	_total_rotation;				/**< the angle through which we have rotated */
	float	_prev_angle;					/**< the prev angle for total rotation calculation */

	hrt_abstime _temp_time;
	hrt_abstime _test_time;
	hrt_abstime _ref_timestamp;	// timestamp the reference position was taken at
};


#endif /* HUNT_H_ */
