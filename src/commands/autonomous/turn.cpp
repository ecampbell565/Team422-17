#include "turn.hpp"

#include "../../subsystems/subsystems.hpp"

Turn::Turn(float angle) :
angle (angle),
direction(angle > 0), // true for turning right, false for turning left
left_speed (direction ? -0.4 : 0.4),
right_speed (direction ? 0.4 : -0.4) {
	Requires(Subsystems::drive_base);
}

void Turn::Initialize() {
	angle += Subsystems::drive_base->get_angle();
}

void Turn::Execute() {
	Subsystems::drive_base->set_motors_normalized(left_speed, right_speed);
}

bool Turn::IsFinished() {
	if (direction) {
		return Subsystems::drive_base->get_angle() > angle;
	} else {
		return Subsystems::drive_base->get_angle() < angle;
	}
}

void Turn::Interrupted() {
	Subsystems::drive_base->set_motors_normalized(0, 0);
}

void Turn::End() {
	Subsystems::drive_base->set_motors_normalized(0, 0);
}

bool Turn::in_range(float target, float error, float value) {
	bool b1 = value < (target + error);
	bool b2 = value > (target - error);
	return b1 && b2;
}


